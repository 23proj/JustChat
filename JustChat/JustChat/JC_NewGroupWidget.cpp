#include "JC_NewGroupWidget.h"
#include "JC_HomeDialog.h"

JC_NewGroupWidget::JC_NewGroupWidget(QWidget *parent)
	: QWidget(nullptr)
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;
	ui.lstOnlinePeople->addItems( QStringList() << "����1" << "����2" << "����3" << "����4" << "����5" );

	
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
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}

void JC_NewGroupWidget::dealNewGroup()
{
	// �Ϸ��Լ��
	bool ret = true;

	// ��Ϣ��ʾ�ɹ���ʧ��
	if ( ret == true )
	{
		// ��ʾ
		QMessageBox::information( nullptr, tr( "��ʾ" ), tr( "�������ĳɹ�!" ) );

		// ���뻰����Ϣ�����ݿ�


		// �򿪻����



		// �رյ�ǰ�����б�
		//this->close();
	}
}
