#include "JC_TopicWidget.h"
#include "JC_HomeDialog.h"

JC_TopicWidget::JC_TopicWidget( qint32 id, QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	//setFixedSize( 700, 600 );
	fHome = ( JC_HomeDialog * ) parent;
	fId = id;
	
}

JC_TopicWidget::~JC_TopicWidget()
{
}

void JC_TopicWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}
