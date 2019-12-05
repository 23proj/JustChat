#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include "ui_JC_TopicWidget.h"

class JC_HomeDialog;

/*
 * 显示主题详情，包括评论内容
 */
class JC_TopicWidget : public QWidget
{
	Q_OBJECT

public:
	JC_TopicWidget( qint32 id, QWidget *parent = Q_NULLPTR);
	~JC_TopicWidget();
	public slots:
	void dealShow();
private:
	Ui::JC_TopicWidget ui;
	JC_HomeDialog *fHome;
	qint32	fId;
};
