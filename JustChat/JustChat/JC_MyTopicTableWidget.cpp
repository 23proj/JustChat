#include "JC_MyTopicTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyTopicTableWidget::JC_MyTopicTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "我的主题表格" ) );
	fTopicTableWidget = new QTableWidget( 10, 3, this );
	fCurWidget = fTopicTableWidget;
	fBtnView = new QPushButton( "查看" );
	fBtnBack = new QPushButton( "返回" );
	fTopicWidget = new JC_TopicWidget();
	fTopicWidget->hide();

	fTopicTableWidget->setHorizontalHeaderLabels( QStringList() << "id" << "标题" << "内容" );
	fTopicTableWidget->verticalHeader()->setVisible( true );
	fTopicTableWidget->horizontalHeader()->setVisible( true );
	fTopicTableWidget->horizontalHeader()->setSectionsClickable( false ); //设置表头不可点击（默认点击后进行排序）
	fTopicTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch ); // 内容填满表格
	fTopicTableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );//设置编辑方式：禁止编辑表格
	fTopicTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );//设置表格选择方式：设置表格为整行选中
	fTopicTableWidget->setSelectionMode( QAbstractItemView::SingleSelection );//选择目标方式
	fTopicTableWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//设置水平滚动条
	fTopicTableWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//设置垂直滚动条
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget( fTopicTableWidget );
	mainLayout->addWidget( fTopicWidget );
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnBack );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	setWindowTitle( tr( "查看我的话题" ) );
}

JC_MyTopicTableWidget::~JC_MyTopicTableWidget()
{
}

void JC_MyTopicTableWidget::init()
{
	// 建立信号槽
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowTopic() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealShow() ) );
}

void JC_MyTopicTableWidget::dealShow()
{
	/* 原始数据清空 */
	fTopicTableWidget->clearContents();

	/* 从数据库中重新读取信息填充到对话框 */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString::number( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "我的话题%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "我的话题%1的内容" ).arg( i ) );
		itmId->setTextAlignment( Qt::AlignCenter );
		itmTitle->setTextAlignment( Qt::AlignCenter );
		itmContent->setTextAlignment( Qt::AlignCenter );
		fTopicTableWidget->setItem( i, 0, itmId );
		fTopicTableWidget->setItem( i, 1, itmTitle );
		fTopicTableWidget->setItem( i, 2, itmContent );
	}

	/* 显示窗口 */
	fCurWidget->hide();
	fCurWidget = fTopicTableWidget;
	fCurWidget->show();
}

void JC_MyTopicTableWidget::dealShowTopic()
{
	// 获取当前选择的话题
	QList<QTableWidgetItem*> items = fTopicTableWidget->selectedItems();
	if ( items.empty() )
	{
		QMessageBox::warning( nullptr, tr( "提示" ), tr( "请先选择一个主题" ) );
		return;
	}

	// 获取窗口信息
	fTopicWidget->setID( ( qint32 ) items[0]->text().toInt() );
	fTopicWidget->setTheme( items[1]->text() );
	fTopicWidget->setDetail( items[2]->text() );
	fTopicWidget->setTopicMsgs( QList<TopicMsg>() ); // TODO: 填充评论数据
	fCurWidget->hide();
	fCurWidget = fTopicWidget;
	fCurWidget->show();
}
