#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QtCore/QMap>
#include <QtCore/QStack>
#include "JC_NewTopicWidget.h"
#include "JC_TopicTableWidget.h"
#include "JC_MyTopicTableWidget.h"
#include "JC_NewGroupWidget.h"
#include "JC_GroupTableWidget.h"
#include "JC_MyGroupTableWidget.h"
#include "JC_TopicWidget.h"
#include "JC_GroupWidget.h"
#include "JC_SquareWidget.h"
#include "EventHandler.h"

class JC_HomeDialog : public QMainWindow
{
	Q_OBJECT

public:
	EventHandler *fEventHandler;
	JC_HomeDialog( QWidget *parent = Q_NULLPTR );
	~JC_HomeDialog();
	void init();
	public slots:
	void dealShow( int idx);
	void dealRecvOnlineMsg( QJsonObject onlineMsg );
	void dealRecvOfflineMsg( QJsonObject offlineMsg );
	void dealRecvSquareMsg( QJsonObject squareMsg );
	void dealRecvGroupMsg( QJsonObject groupMsg );
	void dealRecvCommentMsg( QJsonObject commentMsg );
	void dealRecvNewTopicMsg( QJsonObject newTopicMsg );
	void dealRecvNewGroupMsg( QJsonObject newGroupMsg );
private:
	JC_NewTopicWidget    *fNewTopicWidget;
	JC_TopicTableWidget   *fTopicTableWidget;
	JC_MyTopicTableWidget *fMyTopicTableWidget;
	JC_NewGroupWidget    *fNewGroupWidget;
	JC_GroupTableWidget	 *fGroupTableWidget;
	JC_MyGroupTableWidget *fMyGroupTableWidget;
	JC_SquareWidget *fSquareWidget;
	QTabWidget *fTabWidget;
	QHBoxLayout *fMainLayout;
};
