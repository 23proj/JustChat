#include "JC_GroupWidget.h"
#include "JC_HomeDialog.h"
#include <iostream>

JC_GroupWidget::JC_GroupWidget( QWidget *parent)
	: QWidget( parent )
{
	ui.setupUi(this);
	fHome = (JC_HomeDialog *)parent;
	fEventHandler = fHome->fEventHandler;
	jsonFileIo_ = JsonFileIO::GetFileIOPtr();
	connect(ui.btnSendOut, SIGNAL(clicked()), this, SLOT(dealSendOut()));
}

JC_GroupWidget::~JC_GroupWidget()
{
}

void JC_GroupWidget::setName( QString name )
{
	ui.lbName->setText( name );
}

void JC_GroupWidget::setIntro( QString intro )
{
	//ui.txtDetail->setText( detail );
}

void JC_GroupWidget::setGroupMsgs( QList<QJsonObject> groupMsgs )
{
	// 窗口消息区填充数据

}

void JC_GroupWidget::addGroupMsg( QJsonObject groupMsg )
{
	// 窗口消息区添加一条数据
	std::cout << "heh" << std::endl;
	ui.listWidget->addItem(groupMsg.value("data").toString());
}

void JC_GroupWidget::dealShow()
{
	/* 原始数据清空 */
	ui.listWidget->clear();
	/* 从数据库中重新读取信息填充到对话框 */
	QJsonArray* MsgInfos = jsonFileIo_->GetMsgInfos();
	int count = MsgInfos->size();
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = MsgInfos->at(i).toObject();
		if (jsonObj.value("type").toInt() != GROUP_MSG) continue;
		if (jsonObj.value("type_id").toString() != fId) continue;
		ui.listWidget->addItem(jsonObj.value("data").toString());
	}
	/* 显示窗口 */
	show();
}

void JC_GroupWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if (txt.isEmpty())
		return;
	// 后前台处理
	fEventHandler->dealSendGroupMsg(fId, txt);
	ui.txtInputWindow->clear();
	ui.listWidget->addItem(txt);  // 暂时
	
}
