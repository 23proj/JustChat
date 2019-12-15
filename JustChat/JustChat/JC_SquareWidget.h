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
class EventHandler;
class JC_SquareWidget : public QWidget
{
	Q_OBJECT

public:
	JC_SquareWidget(QWidget *parent = Q_NULLPTR);
	~JC_SquareWidget();
	void init();
	void setSquareMsgs( QList<QJsonObject> squareMsgs );
	void addSquareMsg( QJsonObject squareMsg );
	void addOnlineMsg( QJsonObject onlineMsg );
	void addOfflineMsg( QJsonObject offlineMsg );
	public slots:
	void dealShow();
	void dealSendSquareMsg();
private:
	JC_HomeDialog *fHome;
	QListWidget *fLstMsgWindow;
	QTextEdit *fTxtInputWindow;
	QPushButton *fBtnSendOut;
	QLabel *fOnlineCount;
	EventHandler *fEventHandler;
};
