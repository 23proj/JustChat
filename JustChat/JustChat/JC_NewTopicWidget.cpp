#include "JC_NewTopicWidget.h"
#include "JC_HomeDialog.h"

JC_NewTopicWidget::JC_NewTopicWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = (JC_HomeDialog *)parent;
	fEventHandler = fHome->fEventHandler;
}

JC_NewTopicWidget::~JC_NewTopicWidget()
{
}

void JC_NewTopicWidget::init()
{
	connect(this->ui.btnNewTopic, SIGNAL(clicked()), this, SLOT(dealNewTopic()));
}

void JC_NewTopicWidget::dealShow()
{
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
