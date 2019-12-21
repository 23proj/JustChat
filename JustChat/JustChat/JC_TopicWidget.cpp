#include "JC_TopicWidget.h"
#include "JC_HomeDialog.h"
#include "windows.h"

JC_TopicWidget::JC_TopicWidget( QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = (JC_HomeDialog *)parent;
	fEventHandler = fHome->fEventHandler;
	jsonFileIo_ = JsonFileIO::GetFileIOPtr();
	connect(ui.btnSendOut, SIGNAL(clicked()), this, SLOT(dealSendOut()));
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
	jsonFileIo_->OpenSAFile();
	int total_num = 0;
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = MsgInfos->at(i).toObject();
		if (jsonObj.value("type").toInt() != COMMENT_MSG) continue;
		if (jsonObj.value("type_id").toString() != topicId_) continue;

		++total_num;
		QString data = jsonObj.value("data").toString();
		//QString *content = new QString(jsonObj.value("data").toString());
		ui.listWidget->addItem(data);
		jsonFileIo_->AddSAFile(data);
		
		

	}
	jsonFileIo_->WriteFlag();
	jsonFileIo_->CloseSAFile();
	Sleep(30000);
	double agree_num = jsonFileIo_->ReadSAFile();
	ui.progressBar->setMaximum(total_num);
	ui.progressBar->setValue(agree_num);
	ui.resultLabel->setText(QString("���棺%1%").arg((int)(agree_num*100 / total_num)));

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
