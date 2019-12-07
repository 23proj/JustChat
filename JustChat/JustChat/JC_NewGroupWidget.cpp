#include "JC_NewGroupWidget.h"
#include "JC_HomeDialog.h"

JC_NewGroupWidget::JC_NewGroupWidget(QWidget *parent)
	: QWidget(nullptr)
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;
	ui.lstOnlinePeople->addItems( QStringList() << "匿名1" << "匿名2" << "匿名3" << "匿名4" << "匿名5" );

	// 建立信号槽
	connect( this->ui.btnNewGroup, SIGNAL( clicked() ), this, SLOT( dealNewGroup() ) );
}

JC_NewGroupWidget::~JC_NewGroupWidget()
{
}

void JC_NewGroupWidget::dealNewGroup()
{
	// 合法性检查
	bool ret = true;

	// 消息提示成功或失败
	if ( ret == true )
	{
		// 提示
		QMessageBox::information( nullptr, tr( "提示" ), tr( "创建组聊成功!" ) );

		// 插入话题信息到数据库


		// 打开话题框



		// 关闭当前话题列表
		//this->close();
	}
}
