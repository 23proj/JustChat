#include "JsonFileIO.h"
#include <QFile>
#include <QDir>
#include <QDataStream>



JsonFileIO* JsonFileIO::ptr = new JsonFileIO;


void JsonFileIO::OpenSAFile() {
	QString file_path = JSON_FILE_DIR + "/comments.csv";
	fopen_s(&SAFileData_, file_path.toStdString().c_str(), "a");
	fputs("label\tx_test\n",SAFileData_);
}
void JsonFileIO::AddSAFile(QString &str) {
	QString data = "0\t" + str + "\n";
	fputs(data.toStdString().c_str(),SAFileData_);
}
void JsonFileIO::WriteFlag() {
	FILE* p = NULL;
	QString file_path = JSON_FILE_DIR + "/flag.csv";
	fopen_s(&p, file_path.toStdString().c_str(), "w");
	fputc('1', p);
	fclose(p);
}
double JsonFileIO::ReadSAFile() {
	std::ifstream in;
	QString file_path = JSON_FILE_DIR + "/result.csv";
	in.open(file_path.toStdString().c_str());
	double agree = 0;
	in >> agree;
	in.close();
	remove(file_path.toStdString().c_str());
	return agree;
}
void JsonFileIO::CloseSAFile() {
	fclose(SAFileData_);
}

JsonFileIO::JsonFileIO(QObject *parent)
	: QObject(parent)
{
	group_member_ip_list_ = new std::map<QString, QStringList*>;
	QDir dir;
	if ( !dir.exists( JSON_FILE_DIR ) )
		dir.mkpath( JSON_FILE_DIR );
	if ( !loadAllData() )
		; // TODO: log
}

void JsonFileIO::exit()
{
	if ( !saveAllData() )
		; // TODO: log
}

bool JsonFileIO::addUserInfo( QJsonObject userInfo )
{
	
	QJsonValue user_id = userInfo.value("user_id");
	// 如果是上线添加自己的信息,更新ip
	if (user_id == fUserID) {
		if(fUserInfos.isEmpty()) fUserInfos.append(userInfo);
		else fUserInfos[0] = userInfo;
		return false;
	}
	for(auto&i : fUserInfos)
		if (user_id == i.toObject().value("user_id")) {
			i = userInfo;
			return false;
		}
	fUserInfos.append( userInfo );
	return true;
}

bool JsonFileIO::addTopicInfo( QJsonObject topicInfo )
{
	topicInfo.remove("type");
	fTopicInfos.append( topicInfo );
	return true;
}

bool JsonFileIO::addGroupInfo( QJsonObject groupInfo ,QString user_ip)
{
	fGroupInfos.append( groupInfo );
	// 顺便更新group_member_ip_list
	QStringList* ip_list = new QStringList;
	ip_list->append(user_ip);
	(*group_member_ip_list_)[groupInfo.value("group_id").toString()] = ip_list;
	return true;
}

bool JsonFileIO::addMsgInfo( QJsonObject msgInfo )
{
	fMsgInfos.append( msgInfo );
	return true;
}


bool JsonFileIO::saveInfo( QString fileRoute, QJsonArray jsonArry )
{
	QFile file( fileRoute );
	if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
		return false;
	QDataStream stream( &file );
	stream << QJsonDocument( jsonArry ).toJson();
	return true;
}

bool JsonFileIO::loadInfo( QString fileRoute, QJsonArray& jsonArry )
{
	
	QFile file( fileRoute );
	if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		return false;
	QDataStream stream( &file );
	QByteArray qbyteArry;
	stream >> qbyteArry;
	jsonArry = QJsonDocument::fromJson( qbyteArry ).array();
	if ( jsonArry.empty() )
		return false;
	return true;
}

bool JsonFileIO::saveAllData()
{
	saveInfo( JSON_FILE_DIR + "/userinfo.json", fUserInfos );
	saveInfo( JSON_FILE_DIR + "/topicinfo.json", fTopicInfos );
	saveInfo( JSON_FILE_DIR + "/groupinfo.json", fGroupInfos );
	saveInfo( JSON_FILE_DIR + "/msginfo.json", fMsgInfos );
	return true;
}

bool JsonFileIO::loadAllData()
{
	if (!loadInfo(JSON_FILE_DIR + "/userinfo.json", fUserInfos)) fUserID = generate_id(18);
	else fUserID = fUserInfos[0].toObject().value("user_id").toString();
	loadInfo( JSON_FILE_DIR + "/topicinfo.json", fTopicInfos );
	loadInfo( JSON_FILE_DIR + "/groupinfo.json", fGroupInfos );
	loadInfo( JSON_FILE_DIR + "/msginfo.json", fMsgInfos );
	return true;
}

void JsonFileIO::EnterGroup(QString group_id, QString user_id, QString user_ip) {
	// 首先更新fGroupInfos
	QJsonArray id_list;
	for (auto&i : fGroupInfos)
		if (group_id == i.toObject().value("group_id").toString()) {
			id_list = i.toObject().value("member_id_list").toArray();
			for (auto&j : id_list)
				if (j.toString() == user_id) return;
			id_list.append(user_id);
			i = QJsonObject({ { "group_id",group_id },{ "user_id",i.toObject().value("user_id").toString() },
				{ "name",i.toObject().value("name").toString() },{ "intro",i.toObject().value("intro").toString() },{ "member_id_list",id_list } });
			break;
		}

	// 然后更新group_member_ip_list_
	QStringList* ip_list = new QStringList;
	for (auto&i : id_list)
		for (auto&j : fUserInfos)
			if (i == j.toObject().value("user_id")) {
				ip_list->append(j.toObject().value("user_ip").toString());
				break;
			}
	if (group_member_ip_list_->find(group_id) != group_member_ip_list_->end()) delete (*group_member_ip_list_)[group_id];
	(*group_member_ip_list_)[group_id] = ip_list;
}

QString JsonFileIO::getUserID()
{
	return fUserID;
}

QByteArray JsonFileIO::createOnlineMsg()
{
	return QJsonDocument( QJsonObject( { { "type",ONLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray JsonFileIO::createReplyOnlineMsg()
{
	return QJsonDocument( QJsonObject( { { "type",REPLY_ONLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray JsonFileIO::createOfflineMsg()
{
	return QJsonDocument( QJsonObject( { { "type",OFFLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray JsonFileIO::createSquareMsg( QString data )
{
	QString msg_id = generate_id(MESSAGE_ID_LEN);
	QJsonObject jsonObj({ { "msg_id",msg_id },{ "user_id",fUserID },{ "type",SQUARE_MSG }, { "type_id","" },{ "data",data } });
	fMsgInfos.append(jsonObj);
	return QJsonDocument(jsonObj).toJson();
}

QByteArray JsonFileIO::createGroupMsg( QString group_id, QString data )
{
	QString msg_id = generate_id(MESSAGE_ID_LEN);
	QJsonObject jsonObj({ { "msg_id",msg_id },{ "user_id",fUserID },{ "type",GROUP_MSG }, { "type_id",group_id },{ "data",data } });
	fMsgInfos.append(jsonObj);
	return QJsonDocument(jsonObj).toJson();
}

QByteArray JsonFileIO::createCommentMsg( QString topic_id, QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	QJsonObject jsonObj({ { "msg_id",msg_id },{ "user_id",fUserID },{ "type",COMMENT_MSG }, { "type_id",topic_id },{ "data",data } });
	fMsgInfos.append(jsonObj);
	return QJsonDocument(jsonObj).toJson();
}

QByteArray JsonFileIO::createNewTopicMsg(QString theme, QString detail )
{
	QString topic_id = generate_id( TOPIC_ID_LEN );
	QJsonObject jsonObj1({ { "type",NEW_TOPIC_MSG },{ "topic_id",topic_id },{ "user_id",fUserID },{ "theme",theme },{ "detail",detail } });
	QJsonObject jsonObj2({ { "topic_id",topic_id },{ "user_id",fUserID },{ "theme",theme },{ "detail",detail } });
	fTopicInfos.append(jsonObj2);
	return QJsonDocument(jsonObj1).toJson();
}

QByteArray JsonFileIO::createNewGroupMsg( QString name, QString intro, QString user_ip)
{
	QString group_id = generate_id( GROUP_ID_LEN );

	QJsonArray id_list;
	id_list.append(fUserID);

	QStringList* ip_list = new QStringList;
	ip_list->append(user_ip);
	(*group_member_ip_list_)[group_id] = ip_list;

	QJsonObject jsonObj1({ { "type",NEW_GROUP_MSG },{ "group_id",group_id },{ "user_id",fUserID },{ "name",name },{ "intro",intro },{ "member_id_list",id_list } });
	QJsonObject jsonObj2({ { "group_id",group_id },{ "user_id",fUserID },{ "name",name },{ "intro",intro },{ "member_id_list",id_list } });
	fGroupInfos.append(jsonObj2);
	return QJsonDocument(jsonObj1).toJson();
}
QByteArray JsonFileIO::createEnterGroupMsg(QString group_id, QString user_ip) {
	for (auto&i : fGroupInfos) 
		if (group_id == i.toObject().value("group_id").toString() && fUserID == i.toObject().value("user_id").toString()) return QByteArray();
	EnterGroup(group_id, fUserID, user_ip);
	QJsonObject jsonObj1({ { "type",ENTER_GROUP_MSG },{ "group_id",group_id },{ "user_id",fUserID }});
	return QJsonDocument(jsonObj1).toJson();
}

QStringList* JsonFileIO::GetMemberIpList(QString group_id) {
	if (group_member_ip_list_->find(group_id) == group_member_ip_list_->end()) {
		// 查询操作,先获取id_list
		QJsonArray id_list;
		for (auto&i : fGroupInfos) 
			if (group_id == i.toObject().value("group_id").toString())
				id_list = i.toObject().value("member_id_list").toArray();
		// 然后获取ip_list
		QStringList* ip_list = new QStringList;
		for (auto& i : id_list)
			for (auto& j : fUserInfos)
				if (j.toObject().value("user_id") == i) {
					ip_list->append(j.toObject().value("user_ip").toString());
					break;
				}
		(*group_member_ip_list_)[group_id] = ip_list;
	}
	return (*group_member_ip_list_)[group_id];
}

void JsonFileIO::addOnlineMsg( QJsonObject onlineMsg )
{
	fOnlineMsgs.append( onlineMsg );
}

void JsonFileIO::addOfflineMsg( QJsonObject offlineMsg )
{
	fOfflineMsgs.append( offlineMsg );
}

void JsonFileIO::addSquareMsg( QJsonObject squareMsg )
{
	fSquareMsgs.append( squareMsg );
}

void JsonFileIO::addGroupMsg( QJsonObject groupMsg )
{
	fGroupMsgs.append( groupMsg );
}

void JsonFileIO::addReplyOnlineMsg( QJsonObject replyOnlineMsg )
{
	fReplyOnlineMsgs.append( replyOnlineMsg );
}

bool JsonFileIO::LoadData( QByteArray &data, int type )
{
	switch ( type )
	{
	case USER_INFO:
	{
		data = QJsonDocument( fUserInfos ).toJson();
		break;
	}
	case GROUP_INFO:
	{
		data = QJsonDocument( fGroupInfos ).toJson();
		break;
	}
	case TOPIC_INFO:
	{
		data = QJsonDocument( fTopicInfos ).toJson();
		break;
	}
	case COMMENT_INFO:
	{
		data = QJsonDocument( fCommentMsgs ).toJson();
		break;
	}
	default:
		break;
	}
	if ( data.isEmpty() )
		return false;
	return true;
}
