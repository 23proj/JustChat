#include "JC_MyTopicTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyTopicTableWidget::JC_MyTopicTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "�ҵ�������" ) );
	fTopicTableWidget = new QTableWidget( 10, 3, this );
	fBtnView = new QPushButton( "�鿴" );
	fBtnClose = new QPushButton( "�ر�" );

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
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnClose );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	setWindowTitle( tr( "�鿴�ҵĻ���" ) );
	//setFixedSize( QSize( 600, 400 ) );

	// �����źŲ�
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowTopic() ) );
	connect( fBtnClose, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( this, SIGNAL( sigViewTopic( qint32 ) ), fHome, SLOT( dealShowTopic( qint32 ) ) );
}

JC_MyTopicTableWidget::~JC_MyTopicTableWidget()
{
}

void JC_MyTopicTableWidget::dealShow()
{
	/* ԭʼ������� */
	fTopicTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString::number( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "�ҵĻ���%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "�ҵĻ���%1������" ).arg( i ) );
		itmId->setTextAlignment( Qt::AlignCenter );
		itmTitle->setTextAlignment( Qt::AlignCenter );
		itmContent->setTextAlignment( Qt::AlignCenter );
		fTopicTableWidget->setItem( i, 0, itmId );
		fTopicTableWidget->setItem( i, 1, itmTitle );
		fTopicTableWidget->setItem( i, 2, itmContent );
	}

	/* ��ʾ���� */
	show();
}

void JC_MyTopicTableWidget::dealShowTopic()
{
	// ��ȡ��ǰѡ��Ļ���
	if ( fTopicTableWidget->selectedItems().empty() )
	{
		QMessageBox::warning( nullptr, tr( "��ʾ" ), tr( "����ѡ��һ������" ) );
		return;
	}
	QTableWidgetItem *curItm = fTopicTableWidget->selectedItems().front();
	qint32 id = ( qint32 ) curItm->text().toInt();
	emit sigViewTopic( id );
}
