#pragma once
// �ײ㴫������ݰ�����(ͨ��Э��)
/********************************************
MsgType(1 byte) + MsgTypeId(4 byte) + MsgContent(<=256 byte)
��Ϣ����            ����GroupId        ��Ϣ����
*********************************************/
#include <QObject>
#include <QJsonObject>
#include "data_transmitter.h"
#include "JC_Public.h"

const int USER_ID_LEN = 18;
const int MESSAGE_ID_LEN = 15;
const int TOPIC_ID_LEN = 10;
const int GROUP_ID_LEN = 10;

class JC_HomeDialog;

class EventHandler : public QObject
{
	Q_OBJECT

public:
	EventHandler( QObject *parent );
	~EventHandler();
	void init();
	bool loadData();
	bool saveData();
public slots:
	// ������Ϣ�Ĳ�
	void dealSendOnlineMsg( );
	void dealSendOfflineMsg( );
	void dealSendSquareMsg( QString data );
	void dealSendGroupMsg( QString group_id, QString data );
	void dealSendTopicMsg( QString topic_id, QString data );
	void dealSendNewTopicMsg( QString theme, QString detail );
	void dealSendNewGroupMsg( QString name, QString intro, QString member_id_list );
signals:
	// ������Ϣ���ź�
	void sigRecvOnlineMsg( OnlineMsg onlineMsg );
	void sigRecvOfflineMsg(OfflineMsg offlineMsg );
	void sigRecvSquareMsg( SquareMsg squareMsg );
	void sigRecvGroupMsg( GroupMsg groupMsg );
	void sigRecvTopicMsg( TopicMsg topicMsg );
	void sigRecvNewTopicMsg( NewTopicMsg newTopicMsg );
	void sigRecvNewGroupMsg( NewGroupMsg newGroupMsg );
private slots:
	// ������Ϣ�Ĳ�
	void dealUdpReceive( QByteArray* data, QString* senderIp );
private:
	QByteArray createOnlineMsg();
	QByteArray createOfflineMsg();
	QByteArray createSquareMsg( QString data );
	QByteArray createGroupMsg( QString group_id, QString data );
	QByteArray createTopicMsg( QString topic_id, QString data );
	QByteArray createNewTopicMsg( QString theme, QString detail );
	QByteArray createNewGroupMsg( QString name, QString intro, QString member_id_list );
	QStringList getMemberIPList( QString group_id );
	void addOnlineMsg( OnlineMsg onlineMsg );
	void addOfflineMsg( OfflineMsg offlineMsg );
	void addSquareMsg( SquareMsg squareMsg );
	void setSquareMsgs( QList<SquareMsg> squareMsgs );
private:
	DataTransmitter *fTransmitter;
	QString fUserID,fUserIP;
	JC_HomeDialog *fHome;
	QList<OnlineMsg> fOnlineMsgs;
	QList<OfflineMsg> fOfflineMsgs;
	QList<SquareMsg> fSquareMsgs;
};
