#include "JC_MyGroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyGroupTableWidget::JC_MyGroupTableWidget(QWidget *parent)
	: QWidget(parent)
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "�ҵ�Ⱥ����" ) );
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
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	setWindowTitle( tr( "�鿴�ҵ�Ⱥ��" ) );

	jsonFileIO_ = JsonFileIO::GetFileIOPtr();
	eventHandler_ = fHome->fEventHandler;
}

JC_MyGroupTableWidget::~JC_MyGroupTableWidget()
{
}

void JC_MyGroupTableWidget::init()
{
	// �����źŲ�
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnBack, SIGNAL( clicked() ), this, SLOT( dealShow() ) );
}

void JC_MyGroupTableWidget::DealRecvGroupMsg(QJsonObject msg) {
	// ֻ�е�ǰ���������������Ҹ����ĵ�id�Ƿ�������Ϣ��group_id����ʾ�ڽ�����
	if (fCurWidget == fGroupWidget && fGroupWidget->GetID() == msg.value("type_id").toString())
		fGroupWidget->addGroupMsg(msg);
}

void JC_MyGroupTableWidget::dealShow()
{
	/* ԭʼ������� */
	fGroupTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */
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

	/* ��ʾ���� */
	fCurWidget->hide();
	fCurWidget = fGroupTableWidget;
	fCurWidget->show();
}

void JC_MyGroupTableWidget::dealShowGroup()
{
	// ��ȡ��ǰѡ���Ⱥ��
	QList<QTableWidgetItem*> items = fGroupTableWidget->selectedItems();
	if ( items.empty() ) QMessageBox::warning( nullptr, tr( "��ʾ" ), tr( "����ѡ��һ��Ⱥ��" ) );
	else { 
		QString id = items[0]->text();
		eventHandler_->DealSendEnterGroupMsg(id);
		// ��ȡ������Ϣ
		fGroupWidget->setID(id);
		fGroupWidget->setName(items[1]->text());
		fGroupWidget->setIntro(items[2]->text());
		//fGroupWidget->setGroupMsgs(QList<QJsonObject>()); // TODO: ���Ⱥ����Ϣ����
		fCurWidget->hide();
		fCurWidget = fGroupWidget;
		fGroupWidget->dealShow();
	}
}
