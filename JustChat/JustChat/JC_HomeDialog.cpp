#include "JC_HomeDialog.h"

JC_HomeDialog::JC_HomeDialog(QWidget *parent)
	: QMainWindow(parent)
{
	QWidget *centralWidget = new QWidget( this );
	QGridLayout *gridLayout = new QGridLayout( centralWidget );
	gridLayout->setSpacing( 6 );
	gridLayout->setContentsMargins( 11, 11, 11, 11 );
	fMainLayout = new QHBoxLayout();
	fMainLayout->setSpacing( 6 );
	fEventHandler = new EventHandler( this );

	// ������7������
	fSquareWidget = new JC_SquareWidget( this );
	fNewTopicWidget = new JC_NewTopicWidget( this );
	fTopicTableWidget = new JC_TopicTableWidget( this );
	fMyTopicTableWidget = new JC_MyTopicTableWidget( this );
	fNewGroupWidget = new JC_NewGroupWidget( this );
	fGroupTableWidget = new JC_GroupTableWidget( this );
	fMyGroupTableWidget = new JC_MyGroupTableWidget( this );
	

	//this->fBtnBack->setVisible( false );
	fTabWidget = new QTabWidget( this );
	//fTabWidget->setTabPosition( QTabWidget::East );
	fTabWidget->addTab( fSquareWidget, "�㳡" );
	fTabWidget->addTab( fNewTopicWidget, "�����»���" );
	fTabWidget->addTab( fTopicTableWidget, "���л���" );
	fTabWidget->addTab( fMyTopicTableWidget, "�ҵĻ���" );
	fTabWidget->addTab( fNewGroupWidget, "����������" );
	fTabWidget->addTab( fGroupTableWidget, "��������" );
	fTabWidget->addTab( fMyGroupTableWidget, "�ҵ�����" );
	fMainLayout->addWidget( fTabWidget );

	gridLayout->addLayout( fMainLayout, 0, 0, 1, 1 );

	this->setCentralWidget( centralWidget );
	setMinimumSize( 700, 600 );

}

JC_HomeDialog::~JC_HomeDialog()
{
	// �������߹㲥
	fEventHandler->dealSendOfflineMsg();
}

void JC_HomeDialog::init()
{
	// init
	fEventHandler->init();
	fSquareWidget->init();
	fNewTopicWidget->init();
	fTopicTableWidget->init();
	fMyTopicTableWidget->init();
	fNewGroupWidget->init();
	fGroupTableWidget->init();
	fMyGroupTableWidget->init();

	// �����źŲ�
	connect( fTabWidget, SIGNAL( tabBarClicked( int ) ), this, SLOT( dealShow( int ) ) );

	// �������߹㲥
	fEventHandler->dealSendOnlineMsg();
}

void JC_HomeDialog::dealShow( int idx )
{
	if ( idx == 0 ) // �㳡
	{
		fSquareWidget->dealShow();
	}
	else if ( idx == 1 ) // �����»���
	{
		fNewTopicWidget->dealShow();
	}
	else if ( idx == 2 ) // ���л���
	{
		fTopicTableWidget->dealShow();
	}
	else if ( idx == 3 ) // �ҵĻ���
	{
		fMyTopicTableWidget->dealShow();
	}
	else if ( idx == 4 ) // ����������
	{

	}
	else if ( idx == 5 ) // ��������
	{
		fGroupTableWidget->dealShow();
	}
	else if ( idx == 6 ) // �ҵ�����
	{
		fMyGroupTableWidget->dealShow();
	}
}

void JC_HomeDialog::dealRecvOnlineMsg( OnlineMsg onlineMsg )
{
	fSquareWidget->addOnlineMsg( onlineMsg );
}

void JC_HomeDialog::dealRecvOfflineMsg( OfflineMsg offlineMsg )
{
	fSquareWidget->addOfflineMsg( offlineMsg );
}

void JC_HomeDialog::dealRecvSquareMsg( SquareMsg squareMsg )
{
	fSquareWidget->addSquareMsg( squareMsg );
}

void JC_HomeDialog::dealRecvGroupMsg( GroupMsg groupMsg )
{

}

void JC_HomeDialog::dealRecvTopicMsg( TopicMsg topicMsg )
{

}

void JC_HomeDialog::dealRecvNewTopicMsg( NewTopicMsg newTopicMsg )
{

}

void JC_HomeDialog::dealRecvNewGroupMsg( NewGroupMsg newGroupMsg )
{

}

