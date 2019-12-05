#include "JC_NewTopicWidget.h"
#include "JC_HomeDialog.h"

JC_NewTopicWidget::JC_NewTopicWidget(QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;

	// 建立信号槽
	connect( this->ui.btnNewTopic, SIGNAL( clicked() ), this, SLOT( dealNewTopic() ) );
}

void JC_NewTopicWidget::dealNewTopic()
{
	// 合法性检查
	bool ret = true;

	// 消息提示成功或失败
	if ( ret == true )
	{
		// 提示
		QMessageBox::information( nullptr, tr( "提示" ), tr( "创建话题成功!" ) );
		
		// 插入话题信息到数据库


		// 打开话题框



		// 关闭当前话题列表
		this->close();
	}
}

JC_NewTopicWidget::~JC_NewTopicWidget()
{
}
