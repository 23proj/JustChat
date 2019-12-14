#include "EventHandler.h"
#include "JC_HomeDialog.h"


EventHandler::EventHandler(QObject *parent)
	: QObject(parent)
{
	fHome = ( JC_HomeDialog * ) parent;
	fTransmitter = new DataTransmitter;
}

EventHandler::~EventHandler()
{
}

void EventHandler::init()
{
	// 接收消息
	connect( fTransmitter, &DataTransmitter::UdpReceive, this, &EventHandler::dealUdpReceive );

	connect( this, &EventHandler::sigRecvOnlineMsg, fHome, &JC_HomeDialog::dealRecvOnlineMsg );
	connect( this, &EventHandler::sigRecvOfflineMsg, fHome, &JC_HomeDialog::dealRecvOfflineMsg );
	connect( this, &EventHandler::sigRecvSquareMsg, fHome, &JC_HomeDialog::dealRecvSquareMsg );
	connect( this, &EventHandler::sigRecvGroupMsg, fHome, &JC_HomeDialog::dealRecvGroupMsg );
	connect( this, &EventHandler::sigRecvTopicMsg, fHome, &JC_HomeDialog::dealRecvTopicMsg );
	connect( this, &EventHandler::sigRecvNewTopicMsg, fHome, &JC_HomeDialog::dealRecvNewTopicMsg );
	connect( this, &EventHandler::sigRecvNewGroupMsg, fHome, &JC_HomeDialog::dealRecvNewGroupMsg );
}

bool EventHandler::loadData()
{
	fUserID = generate_id( 18 );
	return true;
}

bool EventHandler::saveData()
{

	return true;
}


void EventHandler::addOnlineMsg( OnlineMsg onlineMsg )
{
	for (int i=0;i<fOnlineMsgs.size();++i)
	{
		if ( fOnlineMsgs[i].user_id == onlineMsg.user_id )
		{
			fOnlineMsgs.removeAt( i );
			break;
		}
	}
	fOnlineMsgs.append( onlineMsg );
}

void EventHandler::addOfflineMsg( OfflineMsg offlineMsg )
{
	for ( int i = 0; i < fOfflineMsgs.size(); ++i )
	{
		if ( fOfflineMsgs[i].user_id == offlineMsg.user_id )
		{
			fOfflineMsgs.removeAt( i );
			break;
		}
	}
	fOfflineMsgs.append( offlineMsg );
}

void EventHandler::addSquareMsg( SquareMsg squareMsg )
{
	fSquareMsgs.append( squareMsg );
}

void EventHandler::setSquareMsgs( QList<SquareMsg> squareMsgs )
{
	fSquareMsgs = squareMsgs;
}

QByteArray EventHandler::createOnlineMsg(  )
{
	return QJsonDocument( QJsonObject( { { "type",ONLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray EventHandler::createOfflineMsg(  )
{
	return QJsonDocument( QJsonObject( { { "type",OFFLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray EventHandler::createSquareMsg( QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",SQUARE_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "data",data } } ) ).toJson();
}

QByteArray EventHandler::createGroupMsg( QString group_id, QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",GROUP_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "group_id",group_id },{ "data",data } } ) ).toJson();
}

QByteArray EventHandler::createTopicMsg( QString topic_id, QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",TOPIC_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "topic_id",topic_id },{ "data",data } } ) ).toJson();
}

QByteArray EventHandler::createNewTopicMsg( QString theme, QString detail )
{
	QString topic_id = generate_id( TOPIC_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",NEW_TOPIC_MSG },{ "topic_id",topic_id },{ "user_id",fUserID },{ "theme",theme },{ "detail",detail }} ) ).toJson();
}

QByteArray EventHandler::createNewGroupMsg( QString name, QString intro, QString member_id_list )
{
	QString group_id = generate_id( GROUP_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",NEW_GROUP_MSG },{ "group_id",group_id },{ "user_id",fUserID },{ "name",name },{ "intro",intro },{ "member_id_list",member_id_list } } ) ).toJson();
}

QStringList EventHandler::getMemberIPList( QString group_id )
{
	// TODO:

	return QStringList();
}

void EventHandler::dealUdpReceive( QByteArray* data, QString* senderIp )
{
	QJsonObject jsonObj( QJsonDocument::fromJson( *data ).object() );
	int type = jsonObj.value( "type" ).toInt();
	switch ( type )
	{
	case ONLINE_MSG:
	{
		// 后台处理

		// 前端处理
		OnlineMsg onlineMsg;
		onlineMsg.type = ONLINE_MSG;
		onlineMsg.user_id = jsonObj.value( "user_id" ).toString();
		onlineMsg.user_ip = *senderIp;
		if ( onlineMsg.user_id == fUserID )
			fUserIP = *senderIp;
		else
		{
			addOnlineMsg( onlineMsg );
			emit sigRecvOnlineMsg( onlineMsg );
		}
		break;
	}
	case OFFLINE_MSG:
	{
		// 后台处理

		// 前端处理
		OfflineMsg offlineMsg;
		offlineMsg.type = OFFLINE_MSG;
		offlineMsg.user_id = jsonObj.value( "user_id" ).toString();
		offlineMsg.user_ip = *senderIp;
		if ( offlineMsg.user_id == fUserID )
			fUserIP = *senderIp;
		else
		{
			addOfflineMsg( offlineMsg );
			emit sigRecvOfflineMsg( offlineMsg );
		}
		break;
	}
	case SQUARE_MSG:
	{
		// 后台处理

		// 前端处理
		SquareMsg squareMsg;
		squareMsg.type = SQUARE_MSG;
		squareMsg.msg_id = jsonObj.value( "msg_id" ).toString();
		squareMsg.user_id = jsonObj.value( "user_id" ).toString();
		squareMsg.data = jsonObj.value( "data" ).toString();
		addSquareMsg( squareMsg );
		emit sigRecvSquareMsg( squareMsg );
		break;
	}
	case GROUP_MSG:
	{
		// 后台处理

		// 前端处理
		GroupMsg groupMsg;
		groupMsg.type = GROUP_MSG;
		groupMsg.msg_id = jsonObj.value( "msg_id" ).toString();
		groupMsg.user_id = jsonObj.value( "user_id" ).toString();
		groupMsg.group_id= jsonObj.value( "group_id" ).toString();
		groupMsg.data = jsonObj.value( "data" ).toString();
		emit sigRecvGroupMsg( groupMsg );
		break;
	}
	case TOPIC_MSG:
	{
		// 后台处理

		// 前端处理
		TopicMsg topicMsg;
		topicMsg.type = TOPIC_MSG;
		topicMsg.msg_id = jsonObj.value( "msg_id" ).toString();
		topicMsg.user_id = jsonObj.value( "user_id" ).toString();
		topicMsg.topic_id = jsonObj.value( "topic_id" ).toString();
		topicMsg.data = jsonObj.value( "data" ).toString();
		emit sigRecvTopicMsg( topicMsg );
		break;
	}
	case NEW_TOPIC_MSG:
	{
		// 后台处理

		// 前端处理
		NewTopicMsg newTopicMsg;
		newTopicMsg.type = NEW_TOPIC_MSG;
		newTopicMsg.topic_id = jsonObj.value( "topic_id" ).toString();
		newTopicMsg.user_id = jsonObj.value( "user_id" ).toString();
		newTopicMsg.theme = jsonObj.value( "theme" ).toString();
		newTopicMsg.detail = jsonObj.value( "detail" ).toString();
		emit sigRecvNewTopicMsg( newTopicMsg );
		break;
	}
	case NEW_GROUP_MSG:
	{
		// 后台处理

		// 前端处理
		NewGroupMsg newGroupMsg;
		newGroupMsg.type = NEW_GROUP_MSG;
		newGroupMsg.group_id = jsonObj.value( "group_id" ).toString();
		newGroupMsg.user_id = jsonObj.value( "user_id" ).toString();
		newGroupMsg.name = jsonObj.value( "name" ).toString();
		newGroupMsg.intro = jsonObj.value( "intro" ).toString();
		newGroupMsg.member_id_list = jsonObj.value( "member_id_list" ).toString();
		emit sigRecvNewGroupMsg( newGroupMsg );
		break;
	}
	default:
		break;
	}
	delete data;
	delete senderIp;
}

void EventHandler::dealSendOnlineMsg()
{
	if ( !loadData() )
	{
		// TODO: 日志
	}
	QByteArray onlineJson = createOnlineMsg();
	fTransmitter->UdpSendBroadcast( onlineJson );
}

void EventHandler::dealSendOfflineMsg()
{
	if ( !saveData() )
	{
		// TODO: 日志记录
	}
	QByteArray offlineJson = createOfflineMsg();
	fTransmitter->UdpSendBroadcast( offlineJson );
}

void EventHandler::dealSendSquareMsg( QString data )
{
	QByteArray squareMsgJson = createSquareMsg( data );
	fTransmitter->UdpSendBroadcast( squareMsgJson );
}

void EventHandler::dealSendGroupMsg( QString group_id, QString data )
{
	QByteArray groupMsgJson = createGroupMsg( group_id, data );
	QStringList member_ip_list = getMemberIPList( group_id );
	foreach( QString member_ip, member_ip_list )
	{
		fTransmitter->UdpSendP2P( groupMsgJson, member_ip );
	}
}

void EventHandler::dealSendTopicMsg( QString topic_id, QString data )
{
	QByteArray topicMsgJson = createTopicMsg( topic_id, data );
	// TODO:
}

void EventHandler::dealSendNewTopicMsg( QString theme, QString detail )
{
	QByteArray newTopicMsgJson = createNewTopicMsg( theme, detail );
	// TODO:
}

void EventHandler::dealSendNewGroupMsg( QString name, QString intro, QString member_id_list )
{
	QByteArray newGroupMsgJson = createNewGroupMsg( name, intro, member_id_list );
	// TODO:
}
