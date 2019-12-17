#pragma once
#pragma execution_character_set("utf-8")

#include "JC_Public.h"
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include "ui_JC_TopicWidget.h"
#include "EventHandler.h"
#include "JsonFileIO.h"

class JC_HomeDialog;

class JC_TopicWidget : public QWidget
{
	Q_OBJECT

public:
	JC_TopicWidget( QWidget *parent);
	~JC_TopicWidget();
	void setID(QString id) { topicId_ = id; }
	void setTheme( QString theme );
	void setDetail( QString detail );
	void setCommentMsgs( QList<QJsonObject> commentMsgs );
	void addCommentMsg( QJsonObject commentMsg );
	public slots:
	void dealShow();
	// ·¢ËÍÆÀÂÛ£¿
	void dealSendOut();
private:
	Ui::JC_TopicWidget ui;
	JC_HomeDialog *fHome;
	QString topicId_;

	EventHandler *fEventHandler;
	JsonFileIO *jsonFileIo_;
};
