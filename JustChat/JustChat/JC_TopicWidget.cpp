#include "JC_TopicWidget.h"
#include "JC_HomeDialog.h"

JC_TopicWidget::JC_TopicWidget( QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	//setFixedSize( 700, 600 );
	fHome = ( JC_HomeDialog * ) parent;
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

void JC_TopicWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}
