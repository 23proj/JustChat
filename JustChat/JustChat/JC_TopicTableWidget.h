#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QPushButton>

class JC_HomeDialog;
/*
 * ����: ������ʾ�����б�
 * 
 */
class JC_TopicTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_TopicTableWidget( QWidget *parent);
	~JC_TopicTableWidget();
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
