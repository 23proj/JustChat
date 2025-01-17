#include "EventHandler.h"
#include "JC_HomeDialog.h"

EventHandler::EventHandler(QObject *parent): QObject(parent){
	fHome = ( JC_HomeDialog * ) parent;
	fTransmitter = new DataTransmitter;
	fTransmitter->init();
	fJsonFileIO = JsonFileIO::GetFileIOPtr();

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
void EventHandler::WriteOwnInfo() {
	fJsonFileIO->addUserInfo(QJsonObject({ { "user_id",fJsonFileIO->getUserID() },{ "user_ip",fTransmitter->GetIp() } }));
}
// bool EventHandler::loadData()
// {
// 	fUserID = generate_id( 18 );
// 	return true;
// }

// bool EventHandler::saveData()
// {
// 
// 	return true;
// }


void EventHandler::dealUdpReceive( QByteArray* data, QString* senderIp )
{
	QJsonObject jsonObj( QJsonDocument::fromJson( *data ).object() );
	int type = jsonObj.value( "type" ).toInt();
	switch ( type )
	{
	case ONLINE_MSG:
	{
		// 保存信息并回复
		ipList_.append(new QString(*senderIp));
		QByteArray replyOnlineJson = fJsonFileIO->createReplyOnlineMsg();
		fTransmitter->UdpSendP2P( replyOnlineJson, *senderIp);
		fJsonFileIO->addUserInfo(QJsonObject({ { "user_id",jsonObj.value("user_id") },{ "user_ip",*senderIp } }));
		//emit sigRecvOnlineMsg( jsonObj );
		break;
	}
	case REPLY_ONLINE_MSG: {
		// 保存信息
		ipList_.append(new QString(*senderIp));
		fJsonFileIO->addReplyOnlineMsg( jsonObj );
		if (fJsonFileIO->addUserInfo(QJsonObject({ { "user_id",jsonObj.value("user_id") },{ "user_ip",*senderIp } })))
			isAlone_ = false;
		break;
	}
	case OFFLINE_MSG:
	{
		fJsonFileIO->addOfflineMsg( jsonObj );
		emit sigRecvOfflineMsg( jsonObj );
		break;
	}
	case SQUARE_MSG:
	{
		fJsonFileIO->addMsgInfo(jsonObj);
		emit sigRecvSquareMsg( jsonObj );
		break;
	}
	case GROUP_MSG:
	{
		fJsonFileIO->addMsgInfo(jsonObj);
		emit sigRecvGroupMsg( jsonObj );
		break;
	}
	case COMMENT_MSG:
	{
		fJsonFileIO->addMsgInfo(jsonObj);
		//emit sigRecvCommentMsg( jsonObj );
		break;
	}
	case NEW_TOPIC_MSG:
	{
		// 后台处理
		fJsonFileIO->addTopicInfo(jsonObj);

		// 前端处理
	
		//emit sigRecvNewTopicMsg( jsonObj );
		break;
	}
	case NEW_GROUP_MSG:
	{
		// 后台处理
		fJsonFileIO->addGroupInfo(jsonObj, *senderIp);

		// 前端处理
		
		//emit sigRecvNewGroupMsg( jsonObj );
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
		if ( fJsonFileIO->LoadData(User, USER_INFO)) fTransmitter->TcpSendP2P(User, *senderIp);
		if ( fJsonFileIO->LoadData(Topic, TOPIC_INFO)) fTransmitter->TcpSendP2P(Topic, *senderIp);
		if ( fJsonFileIO->LoadData(Group, GROUP_INFO)) fTransmitter->TcpSendP2P(Group, *senderIp);
		if ( fJsonFileIO->LoadData(Comment, COMMENT_INFO)) fTransmitter->TcpSendP2P(Comment, *senderIp);
		break;
	}
	case ENTER_GROUP_MSG: {
		fJsonFileIO->EnterGroup(jsonObj.value("group_id").toString(), jsonObj.value("user_id").toString(), *senderIp);
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
	QByteArray onlineJson = fJsonFileIO->createOnlineMsg();
	fTransmitter->UdpSendBroadcast( onlineJson );
	// 启动定时器
	QTimer::singleShot(waitForReply_, this, &EventHandler::OnlineReplyTimeout);
}

void EventHandler::dealSendOfflineMsg()
{
	QByteArray offlineJson = fJsonFileIO->createOfflineMsg();
	fTransmitter->UdpSendBroadcast( offlineJson );
}

void EventHandler::dealSendSquareMsg( QString data )
{
	QByteArray squareMsgJson = fJsonFileIO->createSquareMsg( data );
	fTransmitter->UdpSendBroadcast( squareMsgJson );
}

void EventHandler::dealSendGroupMsg( QString group_id, QString data )
{
	QByteArray msg = fJsonFileIO->createGroupMsg( group_id, data );
	QStringList* member_ip_list = fJsonFileIO->GetMemberIpList( group_id );

	if (1 == member_ip_list->size()) return; // 只有自己
	cout << "blue" << endl;
	for (auto & i : *member_ip_list) fTransmitter->UdpSendP2P(msg, i);
}

void EventHandler::dealSendCommentMsg( QString topic_id, QString data )
{
	QByteArray commentMsgJson = fJsonFileIO->createCommentMsg( topic_id, data );
	fTransmitter->UdpSendBroadcast(commentMsgJson);
}

void EventHandler::dealSendNewTopicMsg(QString theme, QString detail )
{
	QByteArray newTopicMsgJson = fJsonFileIO->createNewTopicMsg(theme, detail);
	fTransmitter->UdpSendBroadcast(newTopicMsgJson);
}

void EventHandler::dealSendNewGroupMsg( QString name, QString intro)
{
	QByteArray newGroupMsgJson = fJsonFileIO->createNewGroupMsg( name, intro, fTransmitter->GetIp());
	fTransmitter->UdpSendBroadcast(newGroupMsgJson);
}
void EventHandler::DealSendEnterGroupMsg(QString group_id) {
	QByteArray enterGroupMsgJson = fJsonFileIO->createEnterGroupMsg(group_id, fTransmitter->GetIp());
	if(!enterGroupMsgJson.isEmpty()) fTransmitter->UdpSendBroadcast(enterGroupMsgJson);
}
void EventHandler::OnlineReplyTimeout() {
	if (0 == ipList_.size()) return;

	if (isAlone_) {  // 孤独节点，先发送自己的再请求别人的
		QByteArray User;
		QByteArray Topic;
		QByteArray Group;
		QByteArray Comment;
		bool hasUser = fJsonFileIO->LoadData(User, USER_INFO);
		bool hasTopic = fJsonFileIO->LoadData(Topic, TOPIC_INFO);
		bool hasGroup = fJsonFileIO->LoadData(Group, GROUP_INFO);
		bool hasComment = false;
		if (hasTopic)  hasComment = fJsonFileIO->LoadData(Comment, COMMENT_INFO);

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

// bool EventHandler::saveData(QString &id, QString &ip)
// {
// 	return false;
// }

// bool EventHandler::LoadData(QByteArray &data, int type) {
// }
bool EventHandler::LoadIpList(QList<QString* > &ipList) {
	return true;
}
