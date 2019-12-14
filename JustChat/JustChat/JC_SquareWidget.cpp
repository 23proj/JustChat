#include "JC_SquareWidget.h"
#include "JC_HomeDialog.h"
#include "EventHandler.h"

JC_SquareWidget::JC_SquareWidget(QWidget *parent)
	: QWidget(nullptr)
{
	fHome = ( JC_HomeDialog * ) parent;
	fEventHandler = fHome->fEventHandler;

	QVBoxLayout *showArea = new QVBoxLayout( this );
	showArea->setSpacing( 6 );
	showArea->setContentsMargins( 11, 11, 11, 11 );
	QHBoxLayout *horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setSpacing( 6 );
	QVBoxLayout *verticalLayout = new QVBoxLayout();
	verticalLayout->setSpacing( 6 );
	fLstMsgWindow = new QListWidget( this );

	verticalLayout->addWidget( fLstMsgWindow );

	fTxtInputWindow = new QTextEdit( this );
	fTxtInputWindow->setPlaceholderText( "请输入要发表的消息" );
	verticalLayout->addWidget( fTxtInputWindow );

	verticalLayout->setStretch( 0, 3 );
	verticalLayout->setStretch( 1, 1 );

	horizontalLayout_2->addLayout( verticalLayout );

	horizontalLayout_2->setStretch( 0, 5 );

	showArea->addLayout( horizontalLayout_2 );

	QHBoxLayout *horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing( 6 );
	fOnlineCount = new QLabel( this );
	fOnlineCount->setText( "当前在线: 5人" );

	horizontalLayout->addWidget( fOnlineCount );

	QSpacerItem *horizontalSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

	horizontalLayout->addItem( horizontalSpacer );

	fBtnSendOut = new QPushButton( tr("发送"), this );

	horizontalLayout->addWidget( fBtnSendOut );
	showArea->addLayout( horizontalLayout );
}

JC_SquareWidget::~JC_SquareWidget()
{
}

void JC_SquareWidget::init()
{
	connect( fBtnSendOut, SIGNAL( clicked() ), this, SLOT( dealSendSquareMsg() ) );
}

void JC_SquareWidget::setSquareMsgs( QList<SquareMsg> squareMsgs )
{
	// 窗口消息区填充数据
}

void JC_SquareWidget::addSquareMsg( SquareMsg squareMsg )
{
	// 窗口消息区添加一条数据
	QString squareMsgStr =
		"type:" + QString::number( squareMsg.type ) + "," +
		"msg_id:" + squareMsg.msg_id + "," +
		"user_id:" + squareMsg.user_id + "," +
		"data:" + squareMsg.data;
	fLstMsgWindow->addItem( squareMsgStr );
}

void JC_SquareWidget::addOnlineMsg( OnlineMsg onlineMsg )
{
	// 窗口消息区添加一条在线数据
	QString onlineMsgStr = "用户" + onlineMsg.user_id + "(" + onlineMsg.user_ip + ") 已上线";
	fLstMsgWindow->addItem( onlineMsgStr );
}

void JC_SquareWidget::addOfflineMsg( OfflineMsg offlineMsg )
{
	// 窗口消息区添加一条下线数据
	QString offlineMsgStr = "用户" + offlineMsg.user_id + "(" + offlineMsg.user_ip + ") 已下线";
}

void JC_SquareWidget::dealShow()
{
	/* 原始数据清空 */

	/* 从数据库中重新读取信息填充到对话框 */

	/* 显示窗口 */
	show();
}

void JC_SquareWidget::dealSendSquareMsg()
{
	QString txt = fTxtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;
	
	// 后台处理
	fEventHandler->dealSendSquareMsg( txt );

	// 前台处理
	fTxtInputWindow->clear();
}
