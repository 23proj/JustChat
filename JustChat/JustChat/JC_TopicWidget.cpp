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

void JC_TopicWidget::setCommentMsgs( QList<CommentMsg> commentMsgs )
{
	fCommentMsgs = commentMsgs;
	
	// �����������������

}

void JC_TopicWidget::addCommentMsg( CommentMsg commentMsg )
{
	fCommentMsgs.append( commentMsg );

	// �������������һ������
}

void JC_TopicWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}

void JC_TopicWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;

}
