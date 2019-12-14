#pragma once
// 底层传输的数据包内容(通信协议)
/********************************************
MsgType(1 byte) + MsgTypeId(4 byte) + MsgContent(<=256 byte)
消息类型            例如GroupId        消息内容
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
	// 发送消息的槽
	void dealSendOnlineMsg( );
	void dealSendOfflineMsg( );
	void dealSendSquareMsg( QString data );
	void dealSendGroupMsg( QString group_id, QString data );
	void dealSendTopicMsg( QString topic_id, QString data );
	void dealSendNewTopicMsg( QString theme, QString detail );
	void dealSendNewGroupMsg( QString name, QString intro, QString member_id_list );
signals:
	// 接收消息的信号
	void sigRecvOnlineMsg( OnlineMsg onlineMsg );
	void sigRecvOfflineMsg(OfflineMsg offlineMsg );
	void sigRecvSquareMsg( SquareMsg squareMsg );
	void sigRecvGroupMsg( GroupMsg groupMsg );
	void sigRecvTopicMsg( TopicMsg topicMsg );
	void sigRecvNewTopicMsg( NewTopicMsg newTopicMsg );
	void sigRecvNewGroupMsg( NewGroupMsg newGroupMsg );
private slots:
	// 接收消息的槽
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
