#include "JC_NewGroupWidget.h"
#include "JC_HomeDialog.h"

JC_NewGroupWidget::JC_NewGroupWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;
	ui.lstOnlinePeople->addItems( QStringList() << "����1" << "����2" << "����3" << "����4" << "����5" );
	fEventHandler = fHome->fEventHandler;
}

JC_NewGroupWidget::~JC_NewGroupWidget()
{
}

void JC_NewGroupWidget::init()
{
	// �����źŲ�
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
	// ��ȡ�����������
	QString name(ui.lineEdit->text());
	QString intro(ui.textEdit->toPlainText());
	// ��������Ƿ�Ϊ��
	if (0 == name.size()) {
		QMessageBox::information(nullptr, tr("��ʾ"), tr("��������������!"));
		return;
	}
	if (0 == intro.size()) {
		QMessageBox::information(nullptr, tr("��ʾ"), tr("���������Ľ���!"));
		return;
	}
	// �����������
	fEventHandler->dealSendNewGroupMsg(name, intro);
	QMessageBox::information(nullptr, tr("��ʾ"), tr("�������ĳɹ�!"));
	// ��תҳ��(��������ҳ)
}
