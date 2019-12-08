#pragma once
#pragma execution_character_set("utf-8")

#include "JC_Public.h"
#include <QWidget>
#include "ui_JC_GroupWidget.h"

class JC_HomeDialog;

class JC_GroupWidget : public QWidget
{
	Q_OBJECT

public:
	JC_GroupWidget( QWidget *parent = Q_NULLPTR);
	~JC_GroupWidget();
	void setID( qint32 id ) { fId = id; }
	void setName( QString name );
	void setDetail( QString detail );
	void setMessages( QVector<MessageNode> messages );
	void addMessage( MessageNode message );
	public slots:
	void dealShow();
	void dealSendOut();
private:
	Ui::JC_GroupWidget ui;
	JC_HomeDialog *fHome;
	qint32	fId;
	QVector<MessageNode> fMessages;
};
