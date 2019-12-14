#include "EventHandler.h"
#include "JC_HomeDialog.h"

EventHandler::EventHandler(QObject *parent): QObject(parent){
	fTransmitter = new DataTransmitter;
	fTransmitter->init();
	
	isAlone_ = true;
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
	connect( this, &EventHandler::sigRecvCommentMsg, fHome, &JC_HomeDialog::dealRecvCommentMsg );
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

QByteArray EventHandler::createOnlineMsg( )
{
	return QJsonDocument( QJsonObject( { { "type",ONLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
}

QByteArray EventHandler::createReplyOnlineMsg()
{
	return QJsonDocument( QJsonObject( { { "type",REPLY_ONLINE_MSG },{ "user_id",fUserID } } ) ).toJson();
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

QByteArray EventHandler::createCommentMsg( QString topic_id, QString data )
{
	QString msg_id = generate_id( MESSAGE_ID_LEN );
	return QJsonDocument( QJsonObject( { { "type",COMMENT_MSG },{ "msg_id",msg_id },{ "user_id",fUserID },{ "topic_id",topic_id },{ "data",data } } ) ).toJson();
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
		OnlineMsg onlineMsg;
		onlineMsg.type = ONLINE_MSG;
		onlineMsg.user_id = jsonObj.value( "user_id" ).toString();
		onlineMsg.user_ip = *senderIp;
		//saveData(user_id, user_ip);
		ipList_.append(senderIp);
		// 回复自己的信息
		QByteArray replyOnlineJson = createReplyOnlineMsg();
		fTransmitter->UdpSendP2P( replyOnlineJson, *senderIp);

		// 前端处理
		if ( onlineMsg.user_id == fUserID )
			fUserIP = *senderIp;
		else
		{
			// 保存别人的信息
			addOnlineMsg( onlineMsg );
			// 发送给前端
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
	case COMMENT_MSG:
	{
		// 后台处理

		// 前端处理
		CommentMsg commentMsg;
		commentMsg.type = COMMENT_MSG;
		commentMsg.msg_id = jsonObj.value( "msg_id" ).toString();
		commentMsg.user_id = jsonObj.value( "user_id" ).toString();
		commentMsg.topic_id = jsonObj.value( "topic_id" ).toString();
		commentMsg.data = jsonObj.value( "data" ).toString();
		emit sigRecvCommentMsg( commentMsg );
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
	case REPLY_ONLINE_MSG: {
		// 保存别人的信息
		ReplyOnlineMsg replyOnlineMsg;
		replyOnlineMsg.type = REPLY_ONLINE_MSG;
		replyOnlineMsg.user_id = jsonObj.value( "user_id" ).toString();
		replyOnlineMsg.user_ip = *senderIp;
		ipList_.append( senderIp );
		if(!saveData(user_id, user_ip)) 
			isAlone_ = false;
		break;
	}
	case USER_INFO: {
		// 收到某人的三张表和评论,更新本地数据,显示在界面
		break;
	}
	case TOPIC_INFO: {
		// 收到请求用户的三张表和评论, 更新本地数据, 显示在界面
		break;
	}
	case GROUP_INFO: {
		// 收到请求用户的三张表和评论, 更新本地数据, 显示在界面
		break;
	}
	case COMMENT_INFO: {
		// 收到请求用户的三张表和评论, 更新本地数据, 显示在界面
		break;
	}
	case REQUEST_INFO: {
		QByteArray User;
		QByteArray Topic;
		QByteArray Group;
		QByteArray Comment;
		if (LoadData(User, USER_INFO)) fTransmitter->TcpSendP2P(User, *senderIp);
		if (LoadData(Topic, TOPIC_INFO)) fTransmitter->TcpSendP2P(Topic, *senderIp);
		if (LoadData(Group, GROUP_INFO)) fTransmitter->TcpSendP2P(Group, *senderIp);
		if (LoadData(Comment, COMMENT_INFO)) fTransmitter->TcpSendP2P(Comment, *senderIp);
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
	// 启动定时器
	QTimer::singleShot(waitForReply_, this, &EventHandler::OnlineReplyTimeout);
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

void EventHandler::dealSendCommentMsg( QString topic_id, QString data )
{
	QByteArray commentMsgJson = createCommentMsg( topic_id, data );
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

void EventHandler::OnlineReplyTimeout() {
	if (0 == ipList_.size()) return;

	if (isAlone_) {  // 孤独节点，先发送自己的再请求别人的
		QByteArray User;
		QByteArray Topic;
		QByteArray Group;
		QByteArray Comment;
		bool hasUser = LoadData(User, USER_INFO);
		bool hasTopic = LoadData(Topic, TOPIC_INFO);
		bool hasGroup = LoadData(Group, GROUP_INFO);
		bool hasComment = false;
		if (hasTopic)  hasComment = LoadData(Comment, COMMENT_INFO);

		// 向在线用户发送自己知道的用户信息、话题、组聊、评论
		for (auto& i : ipList_) {
			if (hasUser) fTransmitter->TcpSendP2P(User, *i);
			if (hasTopic) fTransmitter->TcpSendP2P(Topic, *i);
			if (hasGroup) fTransmitter->TcpSendP2P(Group, *i);
			if (hasComment) fTransmitter->TcpSendP2P(Comment, *i);
		}
	}
	// 向一人请求他知道的用户信息、话题、组聊、评论
	QByteArray requestInfo;
	CreateRequestInfoMsg(requestInfo);
	fTransmitter->UdpSendP2P(requestInfo, *ipList_[0]);
}

bool EventHandler::saveData(QString &id, QString &ip)
{
	return false;
}

bool EventHandler::LoadData(QByteArray &data, int type) {
}
bool EventHandler::LoadIpList(QList<QString* > &ipList) {
}
