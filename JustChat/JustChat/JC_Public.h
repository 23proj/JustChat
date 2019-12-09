#pragma once
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QMap>

// 消息节点
struct MessageNode
{
	QString username;
	QString content;
};

// 评论节点
struct ReviewNode
{
	QString username;
	QString content;
};

// 消息类型
enum
{
	msgOnline,			// 在线消息
	msgOffline,			// 离线消息
	msgSquareMessage,	// 广场聊天消息
	msgGroupMessage,	// 群组聊天消息
	msgReviewMessage,	// 话题评论消息
	msgNewTopic,		// 建立主题消息
	msgNewGroup			// 建立群组消息
};

// 产生位数为digits的随机id
QString generate_id( int digits );

