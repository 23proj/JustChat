#pragma once
// �ײ㴫������ݰ�����(ͨ��Э��)
/********************************************
MsgType(1 byte) + MsgTypeId(4 byte) + MsgContent(<=256 byte)
��Ϣ����            ����GroupId        ��Ϣ����
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
	bool isAlone_;   // ���û��Ƿ��������ڵ�ϲ㣬������ʶ��ǰ���ߵ������û�
	const int waitForReply_ = 3000;   // ms�����߹㲥��ȴ��ظ���ʱ��
	QList<QString*> ipList_;   // ��¼��ǰ�����û�
	JC_HomeDialog *fHome;
public:
	EventHandler( QObject *parent );
	~EventHandler();
	void init();
	void WriteOwnInfo();
	// load id?
//	bool loadData(); 

// 	// ���ر����ݣ�ΪTcp������׼��(���շ���false)
// 	bool LoadData(QByteArray &data, int type);

	// �����û�IP��ΪTcp������׼��(���շ���false)
	bool LoadIpList(QList<QString* > &ipList);

	// ����������߷�������Ϣ���������û�����true��
	//bool saveData();

	// ��ĳ������������+����
	void CreateRequestInfoMsg(QByteArray& msg) { REQUEST_INFO; };

public slots:
	// ���߹㲥�ȴ�ʱ�䵽��
	void OnlineReplyTimeout();
// ������Ϣ�Ĳ�
	void dealSendOnlineMsg( );
	void dealSendOfflineMsg( );
	void dealSendSquareMsg( QString data );
	void dealSendGroupMsg( QString group_id, QString data );
	void dealSendCommentMsg( QString topic_id, QString data );
	void dealSendNewTopicMsg(QString theme, QString detail );
	void dealSendNewGroupMsg( QString name, QString intro);
signals:
	// ������Ϣ���ź�
	void sigRecvOnlineMsg( QJsonObject onlineMsg );
	void sigRecvOfflineMsg( QJsonObject offlineMsg );
	void sigRecvSquareMsg( QJsonObject squareMsg );
	void sigRecvGroupMsg( QJsonObject groupMsg );
	void sigRecvCommentMsg( QJsonObject commentMsg );
	void sigRecvNewTopicMsg( QJsonObject newTopicMsg );
	void sigRecvNewGroupMsg( QJsonObject newGroupMsg );
private slots:
	// ������Ϣ�Ĳ�
	void dealUdpReceive( QByteArray* data, QString* senderIp );	
};
