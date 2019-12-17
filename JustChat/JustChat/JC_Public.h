#pragma once
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QList>

enum MessageType
{
	SQUARE_MSG, GROUP_MSG, COMMENT_MSG, ONLINE_MSG, OFFLINE_MSG, \
	NEW_TOPIC_MSG, NEW_GROUP_MSG, REPLY_ONLINE_MSG, USER_INFO, TOPIC_INFO, GROUP_INFO, COMMENT_INFO, REQUEST_INFO,\
	ENTER_GROUP_MSG,
};


const int USER_ID_LEN = 18;
const int MESSAGE_ID_LEN = 15;
const int TOPIC_ID_LEN = 10;
const int GROUP_ID_LEN = 10;

const QString JSON_FILE_DIR = "../x64/Debug/data";

// 产生位数为digits的随机id
QString generate_id( int digits );

