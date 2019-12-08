#include "JC_MyGroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyGroupTableWidget::JC_MyGroupTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "我的群组表格" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fCurWidget = fGroupTableWidget;
	fBtnView = new QPushButton( "查看" );
	fBtnBack = new QPushButton( "返回" );
	fGroupWidget = new JC_GroupWidget();
	fGroupWidget->hide();

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "我的群组id" << "群组名称" << "群组详情" << "群组人数" );
	fGroupTableWidget->verticalHeader()->setVisible( true );
	fGroupTableWidget->horizontalHeader()->setVisible( true );
	fGroupTableWidget->horizontalHeader()->setSectionsClickable( false ); //设置表头不可点击（默认点击后进行排序）
	fGroupTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch ); // 内容填满表格
	fGroupTableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );//设置编辑方式：禁止编辑表格
	fGroupTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );//设置表格选择方式：设置表格为整行选中
	fGroupTableWidget->setSelectionMode( QAbstractItemView::SingleSelection );//选择目标方式
	fGroupTableWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//设置水平滚动条
	fGroupTableWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//设置垂直滚动条
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget( fGroupTableWidget );
	mainLayout->addWidget( fGroupWidget );
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnBack );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	setWindowTitle( tr( "查看我的群组" ) );

	// 建立信号槽
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealShow() ) );
}

JC_MyGroupTableWidget::~JC_MyGroupTableWidget()
{
}

void JC_MyGroupTableWidget::dealShow()
{
	/* 原始数据清空 */
	fGroupTableWidget->clearContents();

	/* 从数据库中重新读取信息填充到对话框 */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString( "我的群组ID%1" ).arg( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "我的群组名%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "我的群组%1的介绍" ).arg( i ) );
		QTableWidgetItem* itmPeople = new QTableWidgetItem( QString( "我的群组%1的人数" ).arg( i ) );
		itmId->setTextAlignment( Qt::AlignCenter );
		itmTitle->setTextAlignment( Qt::AlignCenter );
		itmContent->setTextAlignment( Qt::AlignCenter );
		itmPeople->setTextAlignment( Qt::AlignCenter );
		fGroupTableWidget->setItem( i, 0, itmId );
		fGroupTableWidget->setItem( i, 1, itmTitle );
		fGroupTableWidget->setItem( i, 2, itmContent );
		fGroupTableWidget->setItem( i, 3, itmPeople );
	}

	/* 显示窗口 */
	fCurWidget->hide();
	fCurWidget = fGroupTableWidget;
	fCurWidget->show();
}

void JC_MyGroupTableWidget::dealShowGroup()
{
	// 获取当前选择的群组
	QList<QTableWidgetItem*> items = fGroupTableWidget->selectedItems();
	if ( items.empty() )
	{
		QMessageBox::warning( nullptr, tr( "提示" ), tr( "请先选择一个群组" ) );
		return;
	}

	// 获取窗口信息
	fGroupWidget->setID( ( qint32 ) items[0]->text().toInt() );
	fGroupWidget->setName( items[1]->text() );
	fGroupWidget->setDetail( items[2]->text() );
	fGroupWidget->setMessages( QVector<MessageNode>() ); // TODO: 填充评论数据
	fCurWidget->hide();
	fCurWidget = fGroupWidget;
	fCurWidget->show();
}
