#include "JC_TopicTableWidget.h"
#include "JC_HomeDialog.h"

JC_TopicTableWidget::JC_TopicTableWidget( QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "����������" ) );
	fTopicTableWidget = new QTableWidget( 10, 3, this );
	fCurWidget = fTopicTableWidget;
	fBtnView = new QPushButton("�鿴");
	fBtnBack = new QPushButton( "����" );
	fTopicWidget = new JC_TopicWidget(parent);
	fTopicWidget->hide();

	fTopicTableWidget->setHorizontalHeaderLabels( QStringList() << "id" << "����" << "����" );
	fTopicTableWidget->verticalHeader()->setVisible( true );
	fTopicTableWidget->horizontalHeader()->setVisible( true );
	fTopicTableWidget->horizontalHeader()->setSectionsClickable( false ); //���ñ�ͷ���ɵ����Ĭ�ϵ�����������
	fTopicTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch ); // �����������
	fTopicTableWidget->setEditTriggers( QAbstractItemView::NoEditTriggers );//���ñ༭��ʽ����ֹ�༭���
	fTopicTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );//���ñ��ѡ��ʽ�����ñ��Ϊ����ѡ��
	fTopicTableWidget->setSelectionMode( QAbstractItemView::SingleSelection );//ѡ��Ŀ�귽ʽ
	fTopicTableWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//����ˮƽ������
	fTopicTableWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );//���ô�ֱ������
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget( fTopicTableWidget );
	mainLayout->addWidget( fTopicWidget );
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnBack );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );

	jsonFileIo_ = JsonFileIO::GetFileIOPtr();
}

JC_TopicTableWidget::~JC_TopicTableWidget()
{
}

void JC_TopicTableWidget::init()
{
	connect(fBtnView, SIGNAL(clicked()), this, SLOT(dealShowTopic()));
	connect(fBtnBack, SIGNAL(clicked()), this, SLOT(dealShow()));
}

void JC_TopicTableWidget::dealShow()
{
	/* ԭʼ������� */
	fTopicTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */
	QJsonArray* topicInfos = jsonFileIo_->GetTopicInfos();
	int count = topicInfos->size();
	for (int i = 0; i < count; ++i) {
		QJsonObject jsonObj = topicInfos->at(i).toObject();
		QTableWidgetItem *id = new QTableWidgetItem(jsonObj.value("topic_id").toString());
		QTableWidgetItem *title = new QTableWidgetItem(jsonObj.value("theme").toString());
		QTableWidgetItem *content = new QTableWidgetItem(jsonObj.value("detail").toString());
		id->setTextAlignment(Qt::AlignCenter);
		title->setTextAlignment(Qt::AlignCenter);
		content->setTextAlignment(Qt::AlignCenter);
		fTopicTableWidget->setItem(i, 0, id);
		fTopicTableWidget->setItem(i, 1, title);
		fTopicTableWidget->setItem(i, 2, content);
	}

	/* ��ʾ���� */
	fCurWidget->hide();
	fCurWidget = fTopicTableWidget;
	fCurWidget->show();
}

void JC_TopicTableWidget::dealShowTopic()
{
	// ��ȡ��ǰѡ��Ļ���
	QList<QTableWidgetItem*> items = fTopicTableWidget->selectedItems();
	if ( items.empty() ) QMessageBox::warning( nullptr, tr( "��ʾ" ), tr( "����ѡ��һ������" ) );
	else {


		// ��ȡ������Ϣ
		fTopicWidget->setID(items[0]->text());
		fTopicWidget->setTheme(items[1]->text());
		fTopicWidget->setDetail(items[2]->text());
		//fTopicWidget->setCommentMsgs( QList<QJsonObject>() ); // TODO: �����������
		fCurWidget->hide();
		fCurWidget = fTopicWidget;
		fTopicWidget->dealShow();
	}

}

