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
#include "JsonFileIO.h"

#include <iostream>
using std::cout;
using std::endl;


class JC_HomeDialog;

class EventHandler : public QObject
{
	Q_OBJECT
private:
	JsonFileIO* fJsonFileIO;
	DataTransmitter* fTransmitter;
	bool isAlone_;   // 此用户是否与其它节点断层，即不认识当前在线的所有用户
	const int waitForReply_ = 3000;   // ms，上线广播后等待回复的时间
	QList<QString*> ipList_;   // 记录当前在线用户
	JC_HomeDialog *fHome;
public:
	EventHandler( QObject *parent );
	~EventHandler();
	void init();
	void WriteOwnInfo();
	// load id?
//	bool loadData(); 

// 	// 加载表数据，为Tcp发送做准备(若空返回false)
// 	bool LoadData(QByteArray &data, int type);

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
	void dealSendNewTopicMsg(QString theme, QString detail );
	void dealSendNewGroupMsg( QString name, QString intro);
signals:
	// 接收消息的信号
	void sigRecvOnlineMsg( QJsonObject onlineMsg );
	void sigRecvOfflineMsg( QJsonObject offlineMsg );
	void sigRecvSquareMsg( QJsonObject squareMsg );
	void sigRecvGroupMsg( QJsonObject groupMsg );
	void sigRecvCommentMsg( QJsonObject commentMsg );
	void sigRecvNewTopicMsg( QJsonObject newTopicMsg );
	void sigRecvNewGroupMsg( QJsonObject newGroupMsg );
private slots:
	// 接收消息的槽
	void dealUdpReceive( QByteArray* data, QString* senderIp );	
};
