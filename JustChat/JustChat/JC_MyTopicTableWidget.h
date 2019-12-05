#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class JC_HomeDialog;

class JC_MyTopicTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_MyTopicTableWidget(QWidget *parent);
	~JC_MyTopicTableWidget();
	public slots:
	void dealShow();
	void dealShowTopic();
signals:
	void sigViewTopic( qint32 id );
private:
	QTableWidget *fTopicTableWidget;
	QPushButton *fBtnView;
	QPushButton *fBtnClose;
	JC_HomeDialog *fHome;
};
