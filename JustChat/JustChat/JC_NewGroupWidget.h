#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include "ui_JC_NewGroupWidget.h"
#include "EventHandler.h"
#include "JC_TopicWidget.h"

class JC_HomeDialog;

class JC_NewGroupWidget : public QWidget
{
	Q_OBJECT

public:
	JC_NewGroupWidget(QWidget *parent);
	~JC_NewGroupWidget();
	void init();
	public slots:
	void dealShow();
	void dealNewGroup();
private:
	Ui::JC_NewGroupWidget ui;
	JC_HomeDialog *fHome;
	EventHandler *fEventHandler;
};
