#pragma once
// 底层传输的数据包内容(通信协议)
/********************************************
MsgType(1 byte) + MsgTypeId(4 byte) + MsgContent(<=256 byte)
消息类型            例如GroupId        消息内容
*********************************************/
#include <QObject>
#include <QJsonObject>
#include <QTimer>

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
private:
	
	DataTransmitter* fTransmitter;
	QString fUserID, fUserIP;
	bool isAlone_;   // 此用户是否与其它节点断层，即不认识当前在线的所有用户
	const int waitForReply_ = 3000;   // ms，上线广播后等待回复的时间
	QList<QString* > ipList_;   // 记录当前在线用户

public:
	EventHandler( QObject *parent );
	~EventHandler();
	void init();

	// load id?
	bool loadData(); 

	// 加载表数据，为Tcp发送做准备(若空返回false)
	bool LoadData(QByteArray &data, int type);

	// 加载用户IP，为Tcp发送做准备(若空返回false)
	bool LoadIpList(QList<QString* > &ipList);

	// 保存别人上线发来的信息（若是新用户返回true）
	//bool saveData();

	// 向某个人请求三表+评论
	void CreateRequestInfoMsg(QByteArray& msg) { REQUEST_INFO; };

public slots:
	// 上线广播等待时间到了
	void OnlineReplyTimeout();
// 发送消息的槽
	void dealSendOnlineMsg( );
	void dealSendOfflineMsg( );
	void dealSendSquareMsg( QString data );
	void dealSendGroupMsg( QString group_id, QString data );
	void dealSendCommentMsg( QString topic_id, QString data );
	void dealSendNewTopicMsg( QString theme, QString detail );
	void dealSendNewGroupMsg( QString name, QString intro, QString member_id_list );
signals:
	// 接收消息的信号
	void sigRecvOnlineMsg( OnlineMsg onlineMsg );
	void sigRecvOfflineMsg(OfflineMsg offlineMsg );
	void sigRecvSquareMsg( SquareMsg squareMsg );
	void sigRecvGroupMsg( GroupMsg groupMsg );
	void sigRecvCommentMsg( CommentMsg commentMsg );
	void sigRecvNewTopicMsg( NewTopicMsg newTopicMsg );
	void sigRecvNewGroupMsg( NewGroupMsg newGroupMsg );
private slots:
	// 接收消息的槽
	void dealUdpReceive( QByteArray* data, QString* senderIp );
private:
	QByteArray createOnlineMsg();
	QByteArray createReplyOnlineMsg();
	QByteArray createOfflineMsg();
	QByteArray createSquareMsg( QString data );
	QByteArray createGroupMsg( QString group_id, QString data );
	QByteArray createCommentMsg( QString topic_id, QString data );
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
