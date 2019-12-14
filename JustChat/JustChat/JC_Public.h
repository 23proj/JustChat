#pragma once
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QList>

// // 消息节点
// struct MessageNode
// {
// 	QString username;
// 	QString content;
// };
// 
// // 评论节点
// struct ReviewNode
// {
// 	QString username;
// 	QString content;
// };

enum MessageType
{
	SQUARE_MSG, GROUP_MSG, TOPIC_MSG, ONLINE_MSG, OFFLINE_MSG, \
	NEW_TOPIC_MSG, NEW_GROUP_MSG
};

struct OnlineMsg
{
	OnlineMsg() {}
	OnlineMsg( QString user_id, QString user_ip ) :type( ONLINE_MSG ), user_id( user_id ), user_ip( user_ip ) {}
	int type;
	QString user_id;
	QString user_ip;
};

struct OfflineMsg
{
	OfflineMsg() {}
	OfflineMsg( QString user_id, QString user_ip ) :type( OFFLINE_MSG ), user_id( user_id ), user_ip( user_ip ) {}
	int type;
	QString user_id;
	QString user_ip;
};

struct SquareMsg
{
	SquareMsg() {}
	SquareMsg( QString msg_id, QString user_id, QString data ) :
		type( SQUARE_MSG ), msg_id(msg_id), user_id( user_id ), data( data ) {}
	int type;
	QString msg_id;
	QString user_id;
	QString data;
};

struct GroupMsg
{
	GroupMsg() {}
	GroupMsg( QString msg_id, QString user_id, QString group_id, QString data ) :
		type( GROUP_MSG ), msg_id( msg_id ), user_id( user_id ), group_id( group_id ), data( data ){}
	int type;
	QString msg_id;
	QString user_id;
	QString group_id;
	QString data;
};

struct TopicMsg
{
	TopicMsg() {}
	TopicMsg( QString msg_id, QString user_id, QString topic_id, QString data ) :
		type( TOPIC_MSG ), msg_id( msg_id ), user_id( user_id ), topic_id( topic_id ), data( data ){}
	int type;
	QString msg_id;
	QString user_id;
	QString topic_id;
	QString data;
};

struct NewTopicMsg
{
	NewTopicMsg() {}
	NewTopicMsg( QString topic_id, QString user_id, QString theme, QString detail ) :
		type( NEW_TOPIC_MSG ), topic_id( topic_id ), user_id( user_id ), theme( theme ), detail( detail )
	{
	}
	int type;
	QString topic_id;
	QString user_id;
	QString theme;
	QString detail;
};

struct NewGroupMsg
{
	NewGroupMsg() {}
	NewGroupMsg( QString group_id, QString user_id, QString name, QString intro, QString member_id_list ) :
		type( NEW_GROUP_MSG ), group_id( group_id ), user_id( user_id ), name( name ), intro( intro ), member_id_list( member_id_list )
	{
	}
	int type;
	QString group_id;
	QString user_id;
	QString name;
	QString intro;
	QString member_id_list;
};

// 产生位数为digits的随机id
QString generate_id( int digits );

