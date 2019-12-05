#include "JC_HomeDialog.h"

JC_HomeDialog::JC_HomeDialog(QWidget *parent)
	: QMainWindow(parent)
{
	// 设置 主界面 ui
	//setupUi(this);

	QWidget *centralWidget = new QWidget( this );
	QGridLayout *gridLayout = new QGridLayout( centralWidget );
	gridLayout->setSpacing( 6 );
	gridLayout->setContentsMargins( 11, 11, 11, 11 );
	fMainLayout = new QHBoxLayout();
	fMainLayout->setSpacing( 6 );
	
	// 创建出7个窗口
	fSquareWidget = new JC_SquareWidget( this );
	fNewTopicWidget = new JC_NewTopicWidget( this );
	fTopicTableWidget = new JC_TopicTableWidget( this );
	fMyTopicTableWidget = new JC_MyTopicTableWidget( this );
	fNewGroupWidget = new JC_NewGroupWidget( this );
	fGroupTableWidget = new JC_GroupTableWidget( this );
	fMyGroupTableWidget = new JC_MyGroupTableWidget( this );
	//this->fBtnBack->setVisible( false );

	fMainLayout->addWidget( fSquareWidget );
	fMainLayout->addWidget( fTopicTableWidget );
	fMainLayout->addWidget( fMyTopicTableWidget );
	fMainLayout->addWidget( fGroupTableWidget );
	fMainLayout->addWidget( fMyGroupTableWidget );

	QWidget *btnArea = new QWidget( centralWidget );
	QVBoxLayout *verticalLayout_3 = new QVBoxLayout( btnArea );
	verticalLayout_3->setSpacing( 6 );
	verticalLayout_3->setContentsMargins( 11, 11, 11, 11 );
	QVBoxLayout *verticalLayout_2 = new QVBoxLayout();
	verticalLayout_2->setSpacing( 6 );
	fBtnSquare = new QPushButton( tr("广场"), btnArea );
	fBtnSquare->setEnabled( false );

	verticalLayout_2->addWidget( fBtnSquare );

	fBtnNewTopic = new QPushButton( tr("创建新话题"), btnArea );

	verticalLayout_2->addWidget( fBtnNewTopic );

	fBtnTopicTable = new QPushButton( tr("所有话题"), btnArea );

	verticalLayout_2->addWidget( fBtnTopicTable );

	fBtnMyTopicTable = new QPushButton( tr("我的话题"), btnArea );

	verticalLayout_2->addWidget( fBtnMyTopicTable );

	fBtnNewGroup = new QPushButton( tr("创建新组聊"), btnArea );

	verticalLayout_2->addWidget( fBtnNewGroup );

	fBtnGroupTable = new QPushButton( tr("已有组聊"), btnArea );

	verticalLayout_2->addWidget( fBtnGroupTable );

	fBtnMyGroupTable = new QPushButton( tr("我的组聊"), btnArea );

	verticalLayout_2->addWidget( fBtnMyGroupTable );

	fBtnBack = new QPushButton( tr("返回上一步"), btnArea );
	fBtnBack->setEnabled( false );

	verticalLayout_2->addWidget( fBtnBack );


	verticalLayout_3->addLayout( verticalLayout_2 );


	fMainLayout->addWidget( btnArea );


	gridLayout->addLayout( fMainLayout, 0, 0, 1, 1 );

	this->setCentralWidget( centralWidget );
	//lstOnlinePeople->setVisible( false );
	fSquareWidget->show();
	fCurWidget = fSquareWidget;
	fTopicTableWidget->hide();
	fMyTopicTableWidget->hide();
	fGroupTableWidget->hide();
	fMyGroupTableWidget->hide();
	//lstOnlinePeople->addItems( QStringList() << "匿名1" << "匿名2" << "匿名3" << "匿名4" << "匿名5" );
	setFixedSize( 700, 600 );


	// 创建3个主题例子窗口,3个我的群组例子窗口
	for ( int i = 0; i < 3; ++i )
	{
		fTopicMap[i] = new JC_TopicWidget( i, this );
		fGroupMap[i] = new JC_GroupWidget( i, this );
		fTopicMap[i]->setVisible( false );
		fGroupMap[i]->setVisible( false );
		fMainLayout->insertWidget( 0, fTopicMap[i] );
		fMainLayout->insertWidget( 0, fGroupMap[i] );
	}

	// 建立信号槽
	connect( fBtnNewTopic, SIGNAL( clicked() ), fNewTopicWidget, SLOT( show() ) );
	connect( fBtnSquare, SIGNAL( clicked() ), this, SLOT( dealShowClientArea() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealBack() ) );
	//connect( this->ui.btnTopicTable, SIGNAL( clicked() ), fTopicTableWidget, SLOT( dealShow() ) );
	connect( fBtnTopicTable, SIGNAL( clicked() ), this, SLOT( dealShowClientArea() ) );
	//connect( this->ui.btnMyTopicTable, SIGNAL( clicked() ), fMyTopicTableWidget, SLOT( dealShow() ) );
	connect( fBtnMyTopicTable, SIGNAL( clicked() ), this, SLOT( dealShowClientArea() ) );
	connect( fBtnNewGroup, SIGNAL( clicked() ), fNewGroupWidget, SLOT( show() ) );
	//connect( this->ui.btnGroupTable, SIGNAL( clicked() ), fGroupTableWidget, SLOT( show() ) );
	connect( fBtnGroupTable, SIGNAL( clicked() ), this, SLOT( dealShowClientArea() ) );
	//connect( this->ui.btnMyGroupTable, SIGNAL( clicked() ), fMyGroupTableWidget, SLOT( show() ) );
	connect( fBtnMyGroupTable, SIGNAL( clicked() ), this, SLOT( dealShowClientArea() ) );
}

void JC_HomeDialog::dealShowTopic( qint32 id )
{
	if ( fTopicMap.count( id ) )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fTopicMap[id];
		fTopicMap[id]->dealShow();
	}
	else
		QMessageBox::warning( nullptr, tr( "警告" ), tr( "未找到id号为%1的主题窗口!" ).arg( id ) );
}

void JC_HomeDialog::dealShowGroup( qint32 id )
{
	if ( fGroupMap.count( id ) )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fGroupMap[id];
		fGroupMap[id]->dealShow();
	}
	else
		QMessageBox::warning( nullptr, tr( "警告" ), tr( "未找到id号为%1的群组窗口!" ).arg( id ) );
}

void JC_HomeDialog::dealShowClientArea()
{
	QWidget *widget = ( QWidget * ) sender();
	if ( widget == fBtnSquare )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fSquareWidget;
		fSquareWidget->show();
		fBtnBack->setEnabled( false );
		fBtnSquare->setEnabled( false );
	}
	if ( widget == fBtnBack )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fSquareWidget;
		fSquareWidget->show();
		//fBtnBack->setVisible( false );
		fBtnBack->setEnabled( false );
		fBtnSquare->setEnabled( false );
	}
	if ( widget == fBtnTopicTable )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fTopicTableWidget;
		fTopicTableWidget->dealShow();
		fBtnBack->setEnabled( true );
		fBtnSquare->setEnabled( true );
	}
	if ( widget == fBtnMyTopicTable )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fMyTopicTableWidget;
		fMyTopicTableWidget->dealShow();
		fBtnBack->setEnabled( true );
		fBtnSquare->setEnabled( true );
	}
	if ( widget == fBtnGroupTable )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fGroupTableWidget;
		fGroupTableWidget->dealShow();
		fBtnBack->setEnabled( true );
		fBtnSquare->setEnabled( true );
	}
	if ( widget == fBtnMyGroupTable )
	{
		fCurWidget->hide();
		fBackList.push( fCurWidget );
		fCurWidget = fMyGroupTableWidget;
		fMyGroupTableWidget->dealShow();
		fBtnBack->setEnabled( true );
		fBtnSquare->setEnabled( true );
	}
}

void JC_HomeDialog::dealBack()
{
	if ( fBackList.empty() )
	{
		QMessageBox::warning( nullptr, "警告", "当前不存在可以返回的记录" );
		return;
	}
	QWidget *widget = fBackList.pop();
	fCurWidget->hide();
	fCurWidget = widget;
	if ( widget == fSquareWidget )
	{
		fBtnBack->setEnabled( false );
		fBtnSquare->setEnabled( false );
	}
	else
	{
		fBtnBack->setEnabled( true );
		fBtnSquare->setEnabled( true );
	}
	widget->show();
}

