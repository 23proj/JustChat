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

	fBtnSend = new QPushButton( tr("����"), this );

	horizontalLayout->addWidget( fBtnSend );
	showArea->addLayout( horizontalLayout );
}

JC_SquareWidget::~JC_SquareWidget()
{
}
