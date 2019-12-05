#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_JC_GroupWidget.h"

class JC_HomeDialog;

class JC_GroupWidget : public QWidget
{
	Q_OBJECT

public:
	JC_GroupWidget( qint32 id, QWidget *parent = Q_NULLPTR);
	~JC_GroupWidget();
	public slots:
	void dealShow();
private:
	Ui::JC_GroupWidget ui;
	JC_HomeDialog *fHome;
	qint32	fId;
};
