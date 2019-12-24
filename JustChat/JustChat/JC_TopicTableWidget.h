#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include "JsonFileIO.h"

class JC_HomeDialog;
class JC_TopicWidget;
class JC_ProgressDialog;

class JC_TopicTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_TopicTableWidget( QWidget *parent);
	~JC_TopicTableWidget();
	void init();
	public slots:
	void dealShow();
	void dealShowTopic();
private:
	QWidget *fCurWidget;
	QTableWidget *fTopicTableWidget;
	QPushButton *fBtnView;
	//QPushButton *fBtnClose;
	QPushButton *fBtnBack;
	JC_HomeDialog *fHome;
	JC_TopicWidget *fTopicWidget;
	JsonFileIO* jsonFileIo_;
	JC_ProgressDialog* PD;
};
