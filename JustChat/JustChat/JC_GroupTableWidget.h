#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QPushButton>

class JC_HomeDialog;
class JC_GroupWidget;

class JC_GroupTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_GroupTableWidget(QWidget *parent);
	~JC_GroupTableWidget();
	public slots:
	void dealShow();
	void dealShowGroup();
private:
	QWidget *fCurWidget;
	QTableWidget *fGroupTableWidget;
	QPushButton *fBtnView;
	QPushButton *fBtnBack;
	JC_HomeDialog *fHome;
	JC_GroupWidget *fGroupWidget;
};
