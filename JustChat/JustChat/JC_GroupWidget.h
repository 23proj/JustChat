#pragma once
#pragma execution_character_set("utf-8")

#include "JC_Public.h"
#include <QtWidgets/QWidget>
#include "ui_JC_GroupWidget.h"
#include "EventHandler.h"
#include "JsonFileIO.h"

class JC_HomeDialog;

class JC_GroupWidget : public QWidget
{
	Q_OBJECT

public:
	JC_GroupWidget( QWidget *parent);
	~JC_GroupWidget();
	void setID(QString id) { fId = id; }
	QString GetID() {return fId;}
	void setName( QString name );
	void setIntro( QString intro );
	void setGroupMsgs( QList<QJsonObject> groupMsgs );
	public slots:
	void dealShow();
	void dealSendOut();
	void addGroupMsg(QJsonObject groupMsg);
private:
	Ui::JC_GroupWidget ui;
	JC_HomeDialog *fHome;
	QString	fId;

	EventHandler *fEventHandler;
	JsonFileIO *jsonFileIo_;
};
