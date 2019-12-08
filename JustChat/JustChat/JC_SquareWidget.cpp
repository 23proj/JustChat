#include "JC_SquareWidget.h"

JC_SquareWidget::JC_SquareWidget(QWidget *parent)
	: QWidget(nullptr)
{
	fHome = ( JC_HomeDialog * ) parent;
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

	connect( fBtnSendOut, SIGNAL( clicked() ), this, SLOT( dealSendOut() ) );
}

JC_SquareWidget::~JC_SquareWidget()
{
}

void JC_SquareWidget::setMessages( QVector<MessageNode> messages )
{
	fMessages = messages;

	// 窗口消息区填充数据
}

void JC_SquareWidget::addMessage( MessageNode message )
{
	fMessages.append( message );

	// 窗口消息区添加一条数据
}

void JC_SquareWidget::dealShow()
{
	/* 原始数据清空 */

	/* 从数据库中重新读取信息填充到对话框 */

	/* 显示窗口 */
	show();
}

void JC_SquareWidget::dealSendOut()
{
	QString txt = fTxtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;

	
}
