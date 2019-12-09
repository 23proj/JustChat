#pragma once
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QMap>

// ��Ϣ�ڵ�
struct MessageNode
{
	QString username;
	QString content;
};

// ���۽ڵ�
struct ReviewNode
{
	QString username;
	QString content;
};

// ��Ϣ����
enum
{
	msgOnline,			// ������Ϣ
	msgOffline,			// ������Ϣ
	msgSquareMessage,	// �㳡������Ϣ
	msgGroupMessage,	// Ⱥ��������Ϣ
	msgReviewMessage,	// ����������Ϣ
	msgNewTopic,		// ����������Ϣ
	msgNewGroup			// ����Ⱥ����Ϣ
};

// ����λ��Ϊdigits�����id
QString generate_id( int digits );

