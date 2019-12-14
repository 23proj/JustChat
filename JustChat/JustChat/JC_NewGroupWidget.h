#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include "ui_JC_NewGroupWidget.h"

class JC_HomeDialog;

class JC_NewGroupWidget : public QWidget
{
	Q_OBJECT

public:
	JC_NewGroupWidget(QWidget *parent = Q_NULLPTR);
	~JC_NewGroupWidget();
	void init();
	public slots:
	void dealNewGroup();
private:
	Ui::JC_NewGroupWidget ui;
	JC_HomeDialog *fHome;
};
