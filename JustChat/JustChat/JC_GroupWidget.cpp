#include "JC_GroupWidget.h"
#include "JC_HomeDialog.h"

JC_GroupWidget::JC_GroupWidget( qint32 id, QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	//setFixedSize( 700, 600 );
	fHome = ( JC_HomeDialog * ) parent;
	fId = id;
}

JC_GroupWidget::~JC_GroupWidget()
{
}

void JC_GroupWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}
