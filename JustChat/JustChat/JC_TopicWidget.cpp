#include "JC_TopicWidget.h"
#include "JC_HomeDialog.h"

JC_TopicWidget::JC_TopicWidget( QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;
	fEventHandler = fHome->fEventHandler;
	jsonFileIo_ = JsonFileIO::GetFileIOPtr();
	connect( ui.btnSendOut, SIGNAL( clicked() ), this, SLOT( dealSendOut() ) );
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

void JC_TopicWidget::setCommentMsgs( QList<QJsonObject> commentMsgs )
{
	// 窗口评论区填充数据

}

void JC_TopicWidget::addCommentMsg( QJsonObject commentMsg )
{
	
	// 窗口评论区添加一条评论
}

void JC_TopicWidget::dealShow()
{
	/* 原始数据清空 */
	ui.listWidget->clear();
	/* 从数据库中重新读取信息填充到对话框 */
	QJsonArray* MsgInfos = jsonFileIo_->GetMsgInfos();
	int count = MsgInfos->size();
	cout << count << endl;
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = MsgInfos->at(i).toObject();
		if (jsonObj.value("type").toInt() != COMMENT_MSG) continue;
		if (jsonObj.value("type_id").toString() != topicId_) continue;
		QString *content = new QString(jsonObj.value("data").toString());
		ui.listWidget->addItem(jsonObj.value("data").toString());
	}
	/* 显示窗口 */
	show();
}

void JC_TopicWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;
	fEventHandler->dealSendCommentMsg(topicId_, txt);
	ui.listWidget->addItem(txt);  // 暂时
	ui.txtInputWindow->clear();
}
