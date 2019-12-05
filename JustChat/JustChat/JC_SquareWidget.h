#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>

class JC_HomeDialog;

class JC_SquareWidget : public QWidget
{
	Q_OBJECT

public:
	JC_SquareWidget(QWidget *parent = Q_NULLPTR);
	~JC_SquareWidget();
private:
	JC_HomeDialog *fHome;
	QListWidget *fLstMsgWindow;
	QTextEdit *fTxtInputWindow;
	QPushButton *fBtnSend;
	QLabel *fOnlineCount;
};
