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
	// �����������������

}

void JC_TopicWidget::addCommentMsg( QJsonObject commentMsg )
{
	
	// �������������һ������
}

void JC_TopicWidget::dealShow()
{
	/* ԭʼ������� */
	ui.listWidget->clear();
	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */
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
	/* ��ʾ���� */
	show();
}

void JC_TopicWidget::dealSendOut()
{
	QString txt = ui.txtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;
	fEventHandler->dealSendCommentMsg(topicId_, txt);
	ui.listWidget->addItem(txt);  // ��ʱ
	ui.txtInputWindow->clear();
}
