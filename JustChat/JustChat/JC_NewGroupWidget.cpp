#include "JC_NewGroupWidget.h"
#include "JC_HomeDialog.h"

JC_NewGroupWidget::JC_NewGroupWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;
	ui.lstOnlinePeople->addItems( QStringList() << "匿名1" << "匿名2" << "匿名3" << "匿名4" << "匿名5" );
	fEventHandler = fHome->fEventHandler;
}

JC_NewGroupWidget::~JC_NewGroupWidget()
{
}

void JC_NewGroupWidget::init()
{
	// 建立信号槽
	connect( this->ui.btnNewGroup, SIGNAL( clicked() ), this, SLOT( dealNewGroup() ) );
}

void JC_NewGroupWidget::dealShow()
{
	ui.lineEdit->setText("");
	ui.textEdit->setText("");
	show();
}

void JC_NewGroupWidget::dealNewGroup()
{
	// 获取组聊相关属性
	QString name(ui.lineEdit->text());
	QString intro(ui.textEdit->toPlainText());
	// 检测输入是否为空
	if (0 == name.size()) {
		QMessageBox::information(nullptr, tr("提示"), tr("请输入组聊名字!"));
		return;
	}
	if (0 == intro.size()) {
		QMessageBox::information(nullptr, tr("提示"), tr("请输入组聊介绍!"));
		return;
	}
	// 无问题则继续
	fEventHandler->dealSendNewGroupMsg(name, intro);
	QMessageBox::information(nullptr, tr("提示"), tr("创建组聊成功!"));
	// 跳转页面(组聊详情页)
}
