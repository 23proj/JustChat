#include "JC_TopicWidget.h"
#include "JC_HomeDialog.h"

JC_TopicWidget::JC_TopicWidget( QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;

	connect( ui.btnSendOut, SIGNAL( clicked() ), this, SLOT( dealSendOut() ) );
}

JC_TopicWidget::~JC_TopicWidget()
{
}

void JC_TopicWidget::setTheme( QString theme )
{
	ui.lineEtTheme->setText( theme );
}

void JC_TopicWidget::setDetail( QString detail )
{
	ui.txtDetail->setText( detail );
}

void JC_TopicWidget::setTopicMsgs( QList<TopicMsg> topicMsgs )
{
	fTopicMsgs = topicMsgs;
	
	// 窗口评论区填充数据

}

void JC_TopicWidget::addTopicMsg( TopicMsg topicMsg )
{
	fTopicMsgs.append( topicMsg );

	// 窗口评论区添加一条评论
}

void JC_TopicWidget::dealShow()
{
	/* 原始数据清空 */

	/* 从数据库中重新读取信息填充到对话框 */

	/* 显示窗口 */
	show();
}

void JC_TopicWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;

}
