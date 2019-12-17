#include "JC_GroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_GroupTableWidget::JC_GroupTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "����Ⱥ����" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fCurWidget = fGroupTableWidget;
	fBtnView = new QPushButton( "�鿴" );
	fBtnBack = new QPushButton( "����" );
	fGroupWidget = new JC_GroupWidget(parent);
	fGroupWidget->hide();

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "id" << "����" << "����" << "����" );
	fGroupTableWidget->verticalHeader()->setVisible( true );
	fGroupTableWidget->horizontalHeader()->setVisible( true );
	fGroupTableWidget->horizontalHeader()->setSectionsClickable( false ); //���ñ�ͷ���ɵ����Ĭ�ϵ�����������
	fGroupTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch ); // �����������
	fGroupTableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );//���ñ༭��ʽ����ֹ�༭���
	fGroupTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );//���ñ��ѡ��ʽ�����ñ��Ϊ����ѡ��
	fGroupTableWidget->setSelectionMode( QAbstractItemView::SingleSelection );//ѡ��Ŀ�귽ʽ
	fGroupTableWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//����ˮƽ������
	fGroupTableWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//���ô�ֱ������
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget( fGroupTableWidget );
	mainLayout->addWidget( fGroupWidget );
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnBack );
	//hLayout->addWidget( fBtnClose );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );

	jsonFileIo_ = JsonFileIO::GetFileIOPtr();
}

JC_GroupTableWidget::~JC_GroupTableWidget()
{
}

void JC_GroupTableWidget::init()
{
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealShow() ) );
}

void JC_GroupTableWidget::DealRecvGroupMsg(QJsonObject msg) {
	// ֻ�е�ǰ���������������Ҹ����ĵ�id�Ƿ�������Ϣ��group_id����ʾ�ڽ�����
	if (fCurWidget == fGroupWidget && fGroupWidget->GetID() == msg.value("group_id").toString())
		fGroupWidget->addGroupMsg(msg);
}

void JC_GroupTableWidget::dealShow()
{
	/* ԭʼ������� */
	fGroupTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */
	QJsonArray* groupInfos = jsonFileIo_->GetGroupInfos();
	int count = groupInfos->size();
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = groupInfos->at(i).toObject();
		QTableWidgetItem *id = new QTableWidgetItem(jsonObj.value("group_id").toString());
		QTableWidgetItem *name = new QTableWidgetItem(jsonObj.value("name").toString());
		QTableWidgetItem *intro = new QTableWidgetItem(jsonObj.value("intro").toString());
		QTableWidgetItem *memberNum = new QTableWidgetItem(QString::number(jsonObj.value("member_id_list").toArray().size()));
		id->setTextAlignment(Qt::AlignCenter);
		name->setTextAlignment(Qt::AlignCenter);
		intro->setTextAlignment(Qt::AlignCenter);
		fGroupTableWidget->setItem(i, 0, id);
		fGroupTableWidget->setItem(i, 1, name);
		fGroupTableWidget->setItem(i, 2, intro);
		fGroupTableWidget->setItem(i, 3, memberNum);
	}

	/* ��ʾ���� */
	fCurWidget->hide();
	fCurWidget = fGroupTableWidget;
	fCurWidget->show();
}

void JC_GroupTableWidget::dealShowGroup()
{
	// ��ȡ��ǰѡ���Ⱥ��
	QList<QTableWidgetItem*> items = fGroupTableWidget->selectedItems();
	if ( items.empty() ) QMessageBox::warning( nullptr, tr( "��ʾ" ), tr( "����ѡ��һ��Ⱥ��" ) );
	else {
		// ��ȡ������Ϣ
		fGroupWidget->setID(items[0]->text());
		fGroupWidget->setName(items[1]->text());
		fGroupWidget->setIntro(items[2]->text());
		//fGroupWidget->setGroupMsgs(QList<QJsonObject>()); // TODO: ���Ⱥ����Ϣ����
		fCurWidget->hide();
		fCurWidget = fGroupWidget;
		fGroupWidget->dealShow();
	}
}
