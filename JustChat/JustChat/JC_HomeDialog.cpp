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

	// 创建出7个窗口
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
	fTabWidget->addTab( fSquareWidget, "广场" );
	fTabWidget->addTab( fNewTopicWidget, "创建新话题" );
	fTabWidget->addTab( fTopicTableWidget, "所有话题" );
	fTabWidget->addTab( fMyTopicTableWidget, "我的话题" );
	fTabWidget->addTab( fNewGroupWidget, "创建新组聊" );
	fTabWidget->addTab( fGroupTableWidget, "已有组聊" );
	fTabWidget->addTab( fMyGroupTableWidget, "我的组聊" );
	fMainLayout->addWidget( fTabWidget );

	gridLayout->addLayout( fMainLayout, 0, 0, 1, 1 );

	this->setCentralWidget( centralWidget );
	setMinimumSize( 700, 600 );

}

JC_HomeDialog::~JC_HomeDialog()
{
	// 发送离线广播
	fEventHandler->dealSendOfflineMsg();
}

void JC_HomeDialog::init()
{
	// init
	fEventHandler->init();
	fEventHandler->WriteOwnInfo();  // 这里整个程序只在开始调用了一次，所以在此写入用户自己的信息
	fSquareWidget->init();
	fNewTopicWidget->init();
	fTopicTableWidget->init();
	fMyTopicTableWidget->init();
	fNewGroupWidget->init();
	fGroupTableWidget->init();
	fMyGroupTableWidget->init();

	// 建立信号槽
	connect( fTabWidget, SIGNAL( tabBarClicked( int ) ), this, SLOT( dealShow( int ) ) );
	connect(this, &QObject::destroyed, this, &JC_HomeDialog::exit);

	// 发送在线广播
	fEventHandler->dealSendOnlineMsg();
}
void JC_HomeDialog::exit() {
	JsonFileIO* fileIOPtr_ = JsonFileIO::GetFileIOPtr();
	fileIOPtr_->exit();
}

void JC_HomeDialog::dealShow( int idx )
{
	if ( idx == 0 ) // 广场
	{
		fSquareWidget->dealShow();
	}
	else if ( idx == 1 ) // 创建新话题
	{
		fNewTopicWidget->dealShow();
	}
	else if ( idx == 2 ) // 所有话题
	{
		fTopicTableWidget->dealShow();
	}
	else if ( idx == 3 ) // 我的话题
	{
		fMyTopicTableWidget->dealShow();
	}
	else if ( idx == 4 ) // 创建新组聊
	{
		fNewGroupWidget->dealShow();
	}
	else if ( idx == 5 ) // 已有组聊
	{
		fGroupTableWidget->dealShow();
	}
	else if ( idx == 6 ) // 我的组聊
	{
		fMyGroupTableWidget->dealShow();
	}
}

void JC_HomeDialog::dealRecvOnlineMsg( QJsonObject onlineMsg )
{
	fSquareWidget->addOnlineMsg( onlineMsg );
}

void JC_HomeDialog::dealRecvOfflineMsg( QJsonObject offlineMsg )
{
	fSquareWidget->addOfflineMsg( offlineMsg );
}

void JC_HomeDialog::dealRecvSquareMsg( QJsonObject squareMsg )
{
	fSquareWidget->addSquareMsg( squareMsg );
}

void JC_HomeDialog::dealRecvGroupMsg( QJsonObject groupMsg )
{
	fGroupTableWidget->DealRecvGroupMsg(groupMsg);
	fMyGroupTableWidget->DealRecvGroupMsg(groupMsg);
}

void JC_HomeDialog::dealRecvCommentMsg( QJsonObject commentMsg )
{

}

void JC_HomeDialog::dealRecvNewTopicMsg( QJsonObject newTopicMsg )
{

}

void JC_HomeDialog::dealRecvNewGroupMsg( QJsonObject newGroupMsg )
{

}

