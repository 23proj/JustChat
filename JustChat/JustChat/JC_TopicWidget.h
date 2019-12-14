#pragma once
#pragma execution_character_set("utf-8")

#include "JC_Public.h"
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include "ui_JC_TopicWidget.h"

class JC_HomeDialog;

class JC_TopicWidget : public QWidget
{
	Q_OBJECT

public:
	JC_TopicWidget( QWidget *parent = Q_NULLPTR);
	~JC_TopicWidget();
	void setID( qint32 id ) { fId = id; }
	void setTheme( QString theme );
	void setDetail( QString detail );
	void setCommentMsgs( QList<CommentMsg> commentMsgs );
	void addCommentMsg( CommentMsg commentMsg );
	public slots:
	void dealShow();
	void dealSendOut();
private:
	Ui::JC_TopicWidget ui;
	JC_HomeDialog *fHome;
	qint32	fId;
	QList<CommentMsg> fCommentMsgs;
};
