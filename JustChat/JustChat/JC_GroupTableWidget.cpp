#include "JC_GroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_GroupTableWidget::JC_GroupTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "所有群组表格" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fBtnView = new QPushButton( "查看" );
	fBtnClose = new QPushButton( "关闭" );

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "所有群组id" << "群组名称" << "群组详情" << "群组人数" );
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
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnClose );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	//setFixedSize( QSize( 600, 400 ) );

	// 建立信号槽
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnClose, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( this, SIGNAL( sigViewGroup( qint32 ) ), fHome, SLOT( dealShowGroup( qint32 ) ) );
}

JC_GroupTableWidget::~JC_GroupTableWidget()
{
}

void JC_GroupTableWidget::dealShow()
{
	/* 原始数据清空 */
	fGroupTableWidget->clearContents();

	/* 从数据库中重新读取信息填充到对话框 */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString( "所有群组ID%1" ).arg( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "所有群组名%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "所有群组%1的介绍" ).arg( i ) );
		QTableWidgetItem* itmPeople = new QTableWidgetItem( QString( "所有群组%1的人数" ).arg( i ) );
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
	show();
}

void JC_GroupTableWidget::dealShowGroup()
{
	// 获取当前选择的群组
	if ( fGroupTableWidget->selectedItems().empty() )
	{
		QMessageBox::warning( nullptr, tr( "提示" ), tr( "请先选择一个群组" ) );
		return;
	}
	QTableWidgetItem *curItm = fGroupTableWidget->selectedItems().front();
	qint32 id = ( qint32 ) curItm->text().toInt();
	emit sigViewGroup( id );
}
