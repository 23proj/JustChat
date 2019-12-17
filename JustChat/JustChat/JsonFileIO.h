#pragma once

#include "JC_Public.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <iostream>
using std::cout;
using std::endl;

class JsonFileIO : public QObject
{
	Q_OBJECT
private:
	// �ĳɵ���ģʽ�ˣ���Ϊ�������˺ܶ��ڴ�����ݣ�
	// �������ÿ����Ҫ�õ����ģ��Ķ�newһ���Լ���FileIO����,����������ͨ������
	JsonFileIO(QObject *parent = nullptr);
	static JsonFileIO* ptr;
public:
	static JsonFileIO* GetFileIOPtr() {
		return ptr;
	}
	// �˳�֮ǰ����һ��
	void exit();

private:
	QJsonArray fOnlineMsgs;
	QJsonArray fOfflineMsgs;
	QJsonArray fReplyOnlineMsgs;
	QJsonArray fSquareMsgs;
	QJsonArray fGroupMsgs;
	QJsonArray fCommentMsgs;
	QJsonArray fNewGroupMsgs;
	QJsonArray fNewTopicMsgs;
	// ���ű�
	QJsonArray fUserInfos;
	QJsonArray fTopicInfos;
	QJsonArray fGroupInfos;
	QJsonArray fMsgInfos;
	// 
	QString fUserID;

public:
	// ��ȡ���л�����Ϣ
	QJsonArray* GetTopicInfos() {return (&fTopicInfos);};
	QJsonArray* GetMsgInfos() { return (&fMsgInfos); };

public:
	QString getUserID();
	QByteArray createOnlineMsg();
	QByteArray createReplyOnlineMsg();
	QByteArray createOfflineMsg();
	QByteArray createSquareMsg( QString data );
	QByteArray createGroupMsg( QString group_id, QString data );
	QByteArray createCommentMsg( QString topic_id, QString data );
	QByteArray createNewTopicMsg(QString theme, QString detail );
	QByteArray createNewGroupMsg( QString name, QString intro, QString member_id_list );
	QStringList getMemberIPList( QString group_id );
public:
	void addOnlineMsg( QJsonObject onlineMsg );
	void addOfflineMsg( QJsonObject offlineMsg );
	void addSquareMsg( QJsonObject squareMsg );
	void addGroupMsg( QJsonObject groupMsg );
	void addReplyOnlineMsg( QJsonObject replyOnlineMsg );
	// ���ر����ݣ�ΪTcp������׼��(���շ���false)
	bool LoadData(QByteArray &data, int type);
public:

	bool addUserInfo( QJsonObject userInfo );
	bool addTopicInfo( QJsonObject topicInfo );
	bool addGroupInfo( QJsonObject groupInfo );
	bool addMsgInfo( QJsonObject msgInfo );
	bool saveAllData();
	bool loadAllData();
private:
	bool saveInfo( QString fileRoute, QJsonArray jsonArry );
	bool loadInfo( QString fileRoute, QJsonArray& jsonArry );
};
