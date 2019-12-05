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
	/* 原始数据清空 */

	/* 从数据库中重新读取信息填充到对话框 */

	/* 显示窗口 */
	show();
}
