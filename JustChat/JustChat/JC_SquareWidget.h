#pragma once
#pragma execution_character_set("utf-8")

#include "JC_Public.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLayout>

class JC_HomeDialog;

class JC_SquareWidget : public QWidget
{
	Q_OBJECT

public:
	JC_SquareWidget(QWidget *parent = Q_NULLPTR);
	~JC_SquareWidget();
	void setMessages( QVector<MessageNode> messages );
	void addMessage( MessageNode message );
	public slots:
	void dealShow();
	void dealSendOut();
private:
	JC_HomeDialog *fHome;
	QListWidget *fLstMsgWindow;
	QTextEdit *fTxtInputWindow;
	QPushButton *fBtnSendOut;
	QLabel *fOnlineCount;
	QVector<MessageNode> fMessages;
};
