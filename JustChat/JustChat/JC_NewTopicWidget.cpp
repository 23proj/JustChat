#include "JC_NewTopicWidget.h"
#include "JC_HomeDialog.h"

JC_NewTopicWidget::JC_NewTopicWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = (JC_HomeDialog *)parent;
	fEventHandler = fHome->fEventHandler;
}

void JC_NewTopicWidget::dealShow()
{
	/* 原始数据清空 */

	/* 从数据库中重新读取信息填充到对话框 */

	/* 显示窗口 */
	ui.lineEtTopicTitle->setText("");
	ui.txtTopicContent->setText("");
	show();
}

void JC_NewTopicWidget::dealNewTopic()
{
	// 获取话题相关属性
	QString title(ui.lineEtTopicTitle->text());
	QString content(ui.txtTopicContent->toPlainText());
	// 检测输入是否为空
	if (0 == title.size()) {
		QMessageBox::information(nullptr, tr("提示"), tr("请输入话题主题!"));
		return;
	}
	if (0 == content.size()) {
		QMessageBox::information(nullptr, tr("提示"), tr("请输入话题详情!"));
		return;
	}
	// 无问题则继续
	fEventHandler->dealSendNewTopicMsg(title, content);
	QMessageBox::information(nullptr, tr("提示"), tr("创建话题成功!"));
	// 跳转页面(话题详情页)

}

JC_NewTopicWidget::~JC_NewTopicWidget()
{
}

void JC_NewTopicWidget::init()
{
	// 建立信号槽
	connect( this->ui.btnNewTopic, SIGNAL( clicked() ), this, SLOT( dealNewTopic() ) );
}
