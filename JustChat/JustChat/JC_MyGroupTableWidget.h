#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class JC_HomeDialog;

class JC_MyGroupTableWidget : public QWidget
{
	Q_OBJECT

public:
	JC_MyGroupTableWidget(QWidget *parent);
	~JC_MyGroupTableWidget();
	public slots:
	void dealShow();
	void dealShowGroup();
signals:
	void sigViewGroup( qint32 id );
private:
	QTableWidget *fGroupTableWidget;
	QPushButton *fBtnView;
	QPushButton *fBtnClose;
	JC_HomeDialog *fHome;
};
