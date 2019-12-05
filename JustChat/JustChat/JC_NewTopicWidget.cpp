#include "JC_NewTopicWidget.h"
#include "JC_HomeDialog.h"

JC_NewTopicWidget::JC_NewTopicWidget(QWidget *parent)
	: QWidget( nullptr )
{
	ui.setupUi(this);
	fHome = ( JC_HomeDialog * ) parent;

	// �����źŲ�
	connect( this->ui.btnNewTopic, SIGNAL( clicked() ), this, SLOT( dealNewTopic() ) );
}

void JC_NewTopicWidget::dealNewTopic()
{
	// �Ϸ��Լ��
	bool ret = true;

	// ��Ϣ��ʾ�ɹ���ʧ��
	if ( ret == true )
	{
		// ��ʾ
		QMessageBox::information( nullptr, tr( "��ʾ" ), tr( "��������ɹ�!" ) );
		
		// ���뻰����Ϣ�����ݿ�


		// �򿪻����



		// �رյ�ǰ�����б�
		this->close();
	}
}

JC_NewTopicWidget::~JC_NewTopicWidget()
{
}
