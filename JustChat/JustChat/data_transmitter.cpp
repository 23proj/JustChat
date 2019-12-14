#include "data_transmitter.h"
#include <assert.h>

DataTransmitter::DataTransmitter(QObject* parent):QObject(parent){
	// UDP
	sendUdpSocket_ = new QUdpSocket;
	recvUdpSocket_ = new QUdpSocket;
	if ( !sendUdpSocket_->bind( QHostAddress::LocalHost, sendUdpPort_ ) )
	{
		// ��Ҫ������־��ӡ������Ϣ
		std::cout << "send UdpSocket�����������˿�ʧ�ܣ�\n";
		sendUdpSocket_->close();
	}
	if ( !recvUdpSocket_->bind( QHostAddress::LocalHost, recvUdpPort_ ) )
	{
		// ��Ҫ������־��ӡ������Ϣ
		std::cout << "recv UdpSocket�����������˿�ʧ�ܣ�\n";
		recvUdpSocket_->close();
	}
	
	// TCP
	sendTcpSocket_ = new QTcpSocket;
	sendTcpSocket_->bind(QHostAddress::LocalHost, sendTcpPort_);
	tcpServer_ = new QTcpServer;
	NewListen();
};
DataTransmitter::~DataTransmitter() {
	delete sendUdpSocket_;
	delete recvUdpSocket_;
	delete sendTcpSocket_;
	delete tcpServer_;

	for (auto&i : tcpReceiver_) {
		delete i.second->socket;
		delete i.second->dataBuf;
	}
};

void DataTransmitter::init()
{
	QObject::connect( recvUdpSocket_, &QUdpSocket::readyRead,
					  this, &DataTransmitter::UdpReadyReadSlot );
	QObject::connect( this, &DataTransmitter::TcpReadyRead, this,
					  &DataTransmitter::TcpReadyReadSlot );
}

void DataTransmitter::NewListen() {
	if (!tcpServer_->listen(QHostAddress::LocalHost, recvTcpPort_)) {
		// ��Ҫ������־��ӡ������Ϣ
		std::cout << "TcpServer�����������˿�ʧ�ܣ�\n";
		tcpServer_->close();
	}
}

void DataTransmitter::incomingConnection(qintptr socketHandle) {
	QTcpSocket* newSocket = new QTcpSocket();
	newSocket->setSocketDescriptor(socketHandle);
	// ���������������
	if (tcpReceiver_.size() > tcpServer_->maxPendingConnections()) {
		newSocket->disconnectFromHost();
		delete newSocket;
		return;
	}
	// �����¼����
	tcpReceiver_[socketHandle]->socket = newSocket;
	tcpReceiver_[socketHandle]->dataBuf = new QByteArray;
	tcpReceiver_[socketHandle]->dataSize = 0;
	QObject::connect(newSocket, &QTcpSocket::readyRead, [socketHandle, this]()-> \
		void{ emit TcpReadyRead(socketHandle); });
}

bool DataTransmitter::UdpSendP2P(const QByteArray &data, const QString &receiverIp) {
	qint64 ret = sendUdpSocket_->writeDatagram(data, QHostAddress(receiverIp), recvUdpPort_);
	if ( ret == -1 )
	{
		return false;
	}
	return true;
}

bool DataTransmitter::UdpSendBroadcast(const QByteArray &data) {
	qint64 ret = sendUdpSocket_->writeDatagram(data, QHostAddress::Broadcast, recvUdpPort_);
	if ( ret == -1 )
	{
		return false;
	}
	return true;
}

void DataTransmitter::UdpReadyReadSlot() {
	QNetworkDatagram dataGram = recvUdpSocket_->receiveDatagram();
	QByteArray* data = new QByteArray(dataGram.data());
	QString* senderIp = new QString(dataGram.senderAddress().toString());
	emit UdpReceive(data, senderIp);
}

void DataTransmitter::TcpSendP2P(const QByteArray &data, const QString &receiverIp) {
	// ע�⣬���п�С��ΪbufSize_,ÿ�����һ�ֽ��Ǳ�־λ��Ϊ��Ч�ʣ�
	// ������
	int tryTimes = 0;
TRY_CONNECT:
	sendTcpSocket_->connectToHost(QHostAddress(receiverIp), recvTcpPort_);
CONNECT_OK:
	if (sendTcpSocket_->state() == QTcpSocket::UnconnectedState) {
		if (++tryTimes == 3) {
			// ��¼��־
			return;
		}
		Sleep(1000);
		goto TRY_CONNECT;
	}

	// Ȼ��ͷ��:size
	int size = data.size();
	QByteArray head = QByteArray::number(size);
	head.resize(bufSize_);
	head[bufSize_ - 1] = 'h';  // ��������ͷ��
	if (bufSize_ != sendTcpSocket_->write(head)) {
		// ��¼��־
		goto CONNECT_OK;
	}; 

	// Ȼ������
	int leftSize = size;
	const char* p = data;
	while (leftSize >= bufSize_ - 1) {
		QByteArray content(p, bufSize_ - 1);
		content[bufSize_ - 1] = 'c'; // ������������
		leftSize -= (bufSize_ - 1);
		p += (bufSize_ - 1);
		if (bufSize_ != sendTcpSocket_->write(content)) {
			// ��¼��־
			goto CONNECT_OK;
		};
	}

	// ���������leftSize == 0��leftSize > 0
	if (bufSize_ > 0) {
		QByteArray content(p, leftSize);
		content.resize(bufSize_);
		content[bufSize_ - 1] = 'c';
		if (bufSize_ != sendTcpSocket_->write(content)) {
			// ��¼��־
			goto CONNECT_OK;
		};
	}

	// �������ʾ���ݷ�����ɣ��ٷ�һ��������־
	QByteArray content(bufSize_, '\0');
	content[bufSize_ - 1] = 'e';
	if (bufSize_ != sendTcpSocket_->write(content)) {
		// ��¼��־
		goto CONNECT_OK;
	};

	// ��ɴ˴δ��䣬�Ͽ�����
	sendTcpSocket_->disconnectFromHost();
}

void DataTransmitter::TcpReadyReadSlot(qintptr socketHandle) {
	QTcpSocket* socket = tcpReceiver_[socketHandle]->socket;
	QByteArray* dataBuf = tcpReceiver_[socketHandle]->dataBuf;
	int dataSize = tcpReceiver_[socketHandle]->dataSize;
	int leftSize = dataSize - dataBuf->size();

	QByteArray tmpBuf = socket->read(bufSize_);
	char flag = tmpBuf[bufSize_ - 1];

	if ('h' == flag) {  // ˵����ͷ��
		tmpBuf.resize(bufSize_ - 1);   // ȥ����־λ
		tcpReceiver_[socketHandle]->dataSize = tmpBuf.toInt();
		dataBuf->clear();
	}
	else if ('c' == flag) { // ˵��������
		if (leftSize >= bufSize_ - 1) tmpBuf.resize(bufSize_ - 1);    // ȥ����־λ
		else tmpBuf.resize(leftSize);    // ȥ����λ�ͱ�־λ
		dataBuf->append(tmpBuf);
	}
	else if ('e' == flag) { // ˵����β��
		assert(dataSize == dataBuf->size());
		socket->disconnectFromHost();
		delete socket;
		tcpReceiver_.erase(socketHandle);
		emit TcpReceive(dataBuf);
	}
}

void DataTransmitter::PrintIp() {
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			std::cout << ipAddressesList.at(i).toString().toStdString() << std::endl;
		}
	}
	/*
	169.254.24.189
	169.254.252.28
	169.254.92.118     // 169.254.�������������ip��ַ,����Ŀ�����
	192.168.42.1
	192.168.72.1
	211.83.106.229*/
}