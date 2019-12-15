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

void JC_SquareWidget::setSquareMsgs( QList<QJsonObject> squareMsgs )
{
	// 窗口消息区填充数据
}

void JC_SquareWidget::addSquareMsg( QJsonObject squareMsg )
{
	// 窗口消息区添加一条数据
	QString squareMsgStr =
		"type:" + QString::number(squareMsg.value("type").toInt()) + "," +
		"msg_id:" + squareMsg.value("msg_id").toString() + "," +
		"user_id:" + squareMsg.value( "user_id").toString() + "," +
		"data:" + squareMsg.value( "data").toString();
	fLstMsgWindow->addItem( squareMsgStr );
}

void JC_SquareWidget::addOnlineMsg( QJsonObject onlineMsg )
{
	// 窗口消息区添加一条在线数据
	QString onlineMsgStr = "用户" + onlineMsg.value( "user_id").toString() + "(" + onlineMsg.value( "user_ip").toString() + ") 已上线";
	fLstMsgWindow->addItem( onlineMsgStr );
}

void JC_SquareWidget::addOfflineMsg( QJsonObject offlineMsg )
{
	// 窗口消息区添加一条下线数据
	QString offlineMsgStr = "用户" + offlineMsg.value( "user_id").toString() + "(" + offlineMsg.value( "user_ip").toString() + ") 已下线";
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
