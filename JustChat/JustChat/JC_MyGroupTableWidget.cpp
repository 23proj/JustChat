#include "JC_MyGroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyGroupTableWidget::JC_MyGroupTableWidget(QWidget *parent)
	: QWidget(parent)
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "我的群组表格" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fCurWidget = fGroupTableWidget;
	fBtnView = new QPushButton( "查看" );
	fBtnBack = new QPushButton( "返回" );
	fGroupWidget = new JC_GroupWidget(parent);
	fGroupWidget->hide();

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "id" << "名称" << "介绍" << "人数" );
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

	jsonFileIO_ = JsonFileIO::GetFileIOPtr();
	eventHandler_ = fHome->fEventHandler;
}

JC_MyGroupTableWidget::~JC_MyGroupTableWidget()
{
}

void JC_MyGroupTableWidget::init()
{
	// 建立信号槽
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealShow() ) );
}

void JC_MyGroupTableWidget::DealRecvGroupMsg(QJsonObject msg) {
	// 只有当前界面是组聊详情且该组聊的id是发来的消息的group_id才显示在界面上
	if (fCurWidget == fGroupWidget && fGroupWidget->GetID() == msg.value("type_id").toString())
		fGroupWidget->addGroupMsg(msg);
}

void JC_MyGroupTableWidget::dealShow()
{
	/* 原始数据清空 */
	fGroupTableWidget->clearContents();

	/* 从数据库中重新读取信息填充到对话框 */
	QJsonArray* groupInfos = jsonFileIO_->GetGroupInfos();
	QString myId = jsonFileIO_->getUserID();
	int count = groupInfos->size();
	int row = 0;
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = groupInfos->at(i).toObject();
		if (jsonObj.value("user_id").toString() != myId) continue;
		QTableWidgetItem *id = new QTableWidgetItem(jsonObj.value("group_id").toString());
		QTableWidgetItem *name = new QTableWidgetItem(jsonObj.value("name").toString());
		QTableWidgetItem *intro = new QTableWidgetItem(jsonObj.value("intro").toString());
		QTableWidgetItem *memberNum = new QTableWidgetItem(QString::number(jsonObj.value("member_id_list").toArray().size()));
		id->setTextAlignment(Qt::AlignCenter);
		name->setTextAlignment(Qt::AlignCenter);
		intro->setTextAlignment(Qt::AlignCenter);
		fGroupTableWidget->setItem(row, 0, id);
		fGroupTableWidget->setItem(row, 1, name);
		fGroupTableWidget->setItem(row, 2, intro);
		fGroupTableWidget->setItem(row, 3, memberNum);
		++row;
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
	if ( items.empty() ) QMessageBox::warning( nullptr, tr( "提示" ), tr( "请先选择一个群组" ) );
	else { 
		QString id = items[0]->text();
		eventHandler_->DealSendEnterGroupMsg(id);
		// 获取窗口信息
		fGroupWidget->setID(id);
		fGroupWidget->setName(items[1]->text());
		fGroupWidget->setIntro(items[2]->text());
		//fGroupWidget->setGroupMsgs(QList<QJsonObject>()); // TODO: 填充群组消息数据
		fCurWidget->hide();
		fCurWidget = fGroupWidget;
		fGroupWidget->dealShow();
	}
}
