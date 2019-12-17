#pragma once

#include "JC_Public.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <map>
#include <iostream>
using std::cout;
using std::endl;

class JsonFileIO : public QObject
{
	Q_OBJECT
private:
	// 改成单例模式了，因为这个类放了很多内存的数据，
	// 如果其它每个需要用到这个模块的都new一个自己的FileIO对象,就做不到互通有无了
	JsonFileIO(QObject *parent = nullptr);
	static JsonFileIO* ptr;
public:
	static JsonFileIO* GetFileIOPtr() {
		return ptr;
	}
	// 退出之前调用一次
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
	// 四张表
	QJsonArray fUserInfos;
	QJsonArray fTopicInfos;
	QJsonArray fGroupInfos;
	QJsonArray fMsgInfos;
	// 存储组成员id<group_id, &id_list>
	std::map<QString , QStringList* >* group_member_id_list_;
	// 存储组成员ip<group_id, &ip_list>(避免每发一次group_msg就要查询一次)
	std::map<QString , QStringList* >* group_member_ip_list_;
	// 
	QString fUserID;

public:
	QJsonArray* GetTopicInfos() {return (&fTopicInfos);};
	QJsonArray* GetGroupInfos() {return (&fGroupInfos);};
	QJsonArray* GetMsgInfos() { return (&fMsgInfos);};

public:
	QString getUserID();
	QByteArray createOnlineMsg();
	QByteArray createReplyOnlineMsg();
	QByteArray createOfflineMsg();
	QByteArray createSquareMsg( QString data );
	QByteArray createGroupMsg( QString group_id, QString data );
	QByteArray createCommentMsg( QString topic_id, QString data );
	QByteArray createNewTopicMsg(QString theme, QString detail );
	QByteArray createNewGroupMsg( QString name, QString intro);
	QStringList* GetMemberIpList(QString group_id);

public:
	void addOnlineMsg( QJsonObject onlineMsg );
	void addOfflineMsg( QJsonObject offlineMsg );
	void addSquareMsg( QJsonObject squareMsg );
	void addGroupMsg( QJsonObject groupMsg );
	void addReplyOnlineMsg( QJsonObject replyOnlineMsg );
	// 加载表数据，为Tcp发送做准备(若空返回false)
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
