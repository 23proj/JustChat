#include "JsonFileIO.h"
#include <QFile>
#include <QDir>
#include <QDataStream>

JsonFileIO* JsonFileIO::ptr = new JsonFileIO;

JsonFileIO::JsonFileIO(QObject *parent)
	: QObject(parent)
{
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
	for( int i=0;i<fUserInfos.size();++i)
	{
		QJsonObject& obj = fUserInfos.at( i ).toObject();
		if ( obj.value( "user_id" ) == userInfo.value( "user_id" ) )
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

bool JsonFileIO::addGroupInfo( QJsonObject groupInfo )
{
	fGroupInfos.append( groupInfo );
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
	if ( !loadInfo( JSON_FILE_DIR + "/userinfo.json", fUserInfos ) )
	{
		fUserID = generate_id( 18 );
		QByteArray byteArry = createOnlineMsg();
		fUserInfos.append( QJsonDocument::fromJson( byteArry ).object() );
	}
	fUserID = fUserInfos.first().toObject().value( "user_id" ).toString();
	loadInfo( JSON_FILE_DIR + "/topicinfo.json", fTopicInfos );
	loadInfo( JSON_FILE_DIR + "/groupinfo.json", fGroupInfos );
	loadInfo( JSON_FILE_DIR + "/msginfo.json", fMsgInfos );
	return true;
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
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	QJsonObject jsonObj1({ { "type",SQUARE_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "data",data } });
	QJsonObject jsonObj2({ { "msg_id",msg_id },{ "user_id",fUserID },{ "type",SQUARE_MSG }, { "type_id","" },{ "data",data } });
	fMsgInfos.append(jsonObj2);
	return QJsonDocument(jsonObj1).toJson();
}

QByteArray JsonFileIO::createGroupMsg( QString group_id, QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",GROUP_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "group_id",group_id },{ "data",data } } ) ).toJson();
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

QByteArray JsonFileIO::createNewGroupMsg( QString name, QString intro, QString member_id_list )
{
	QString group_id = generate_id( GROUP_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",NEW_GROUP_MSG },{ "group_id",group_id },{ "user_id",fUserID },{ "name",name },{ "intro",intro },{ "member_id_list",member_id_list } } ) ).toJson();
}

QStringList JsonFileIO::getMemberIPList( QString group_id )
{
	// TODO:

	return QStringList();
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
