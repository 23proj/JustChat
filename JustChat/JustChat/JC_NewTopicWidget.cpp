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
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	ui.lineEtTopicTitle->setText("");
	ui.txtTopicContent->setText("");
	show();
}

void JC_NewTopicWidget::dealNewTopic()
{
	// ��ȡ�����������
	QString title(ui.lineEtTopicTitle->text());
	QString content(ui.txtTopicContent->toPlainText());
	// ��������Ƿ�Ϊ��
	if (0 == title.size()) {
		QMessageBox::information(nullptr, tr("��ʾ"), tr("�����뻰������!"));
		return;
	}
	if (0 == content.size()) {
		QMessageBox::information(nullptr, tr("��ʾ"), tr("�����뻰������!"));
		return;
	}
	// �����������
	fEventHandler->dealSendNewTopicMsg(title, content);
	QMessageBox::information(nullptr, tr("��ʾ"), tr("��������ɹ�!"));
	// ��תҳ��(��������ҳ)

}

JC_NewTopicWidget::~JC_NewTopicWidget()
{
}

void JC_NewTopicWidget::init()
{
	// �����źŲ�
	connect( this->ui.btnNewTopic, SIGNAL( clicked() ), this, SLOT( dealNewTopic() ) );
}
