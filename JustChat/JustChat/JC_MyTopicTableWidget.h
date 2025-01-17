#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QPushButton>
#include "JsonFileIO.h"

class JC_HomeDialog;
class JC_TopicWidget;

class JC_MyTopicTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_MyTopicTableWidget(QWidget *parent);
	~JC_MyTopicTableWidget();
	void init();
	public slots:
	void dealShow();
	void dealShowTopic();
private:
	QWidget *fCurWidget;
	QTableWidget *fTopicTableWidget;
	QPushButton *fBtnView;
	QPushButton *fBtnBack;
	JC_TopicWidget *fTopicWidget;
	JC_HomeDialog *fHome;
	JsonFileIO* jsonFileIo_;
};
