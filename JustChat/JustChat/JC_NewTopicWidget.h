#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtCore/QString>
#include "ui_JC_NewTopicWidget.h"
#include "EventHandler.h"
#include "JC_TopicWidget.h"

class JC_HomeDialog;

class JC_NewTopicWidget : public QWidget
{
	Q_OBJECT

public:
	JC_NewTopicWidget(QWidget *parent);
	~JC_NewTopicWidget();
	void init();
	public slots:
	void dealShow();
	void dealNewTopic();
private:
	Ui::JC_NewTopicWidget ui;
	JC_HomeDialog *fHome;
	EventHandler *fEventHandler;
};
