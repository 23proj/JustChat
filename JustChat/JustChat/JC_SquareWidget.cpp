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
	fTxtInputWindow->setPlaceholderText( "������Ҫ�������Ϣ" );
	verticalLayout->addWidget( fTxtInputWindow );

	verticalLayout->setStretch( 0, 3 );
	verticalLayout->setStretch( 1, 1 );

	horizontalLayout_2->addLayout( verticalLayout );

	horizontalLayout_2->setStretch( 0, 5 );

	showArea->addLayout( horizontalLayout_2 );

	QHBoxLayout *horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing( 6 );
	fOnlineCount = new QLabel( this );
	fOnlineCount->setText( "��ǰ����: 5��" );

	horizontalLayout->addWidget( fOnlineCount );

	QSpacerItem *horizontalSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

	horizontalLayout->addItem( horizontalSpacer );

	fBtnSendOut = new QPushButton( tr("����"), this );

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

	// ������Ϣ���������
}

void JC_SquareWidget::addMessage( MessageNode message )
{
	fMessages.append( message );

	// ������Ϣ�����һ������
}

void JC_SquareWidget::dealShow()
{
	/* ԭʼ������� */

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	/* ��ʾ���� */
	show();
}

void JC_SquareWidget::dealSendOut()
{
	QString txt = fTxtInputWindow->toPlainText();
	if ( txt.isEmpty() )
		return;

	
}
