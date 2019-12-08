#include "JC_GroupWidget.h"
#include "JC_HomeDialog.h"

JC_GroupWidget::JC_GroupWidget( QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	//setFixedSize( 700, 600 );
	fHome = ( JC_HomeDialog * ) parent;
	//fId = id;

	connect( ui.btnSendOut, SIGNAL( clicked() ), this, SLOT( dealSendOut() ) );
}

JC_GroupWidget::~JC_GroupWidget()
{
}

void JC_GroupWidget::setName( QString name )
{
	ui.lbName->setText( name );
}

void JC_GroupWidget::setDetail( QString detail )
{
	//ui.txtDetail->setText( detail );
}

void JC_GroupWidget::setMessages( QVector<MessageNode> messages )
{
	fMessages = messages;

	// ������Ϣ���������

}

void JC_GroupWidget::addMessage( MessageNode message )
{
	fMessages.append( message );

	// ������Ϣ�����һ������
}

void JC_GroupWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}

void JC_GroupWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;
}
