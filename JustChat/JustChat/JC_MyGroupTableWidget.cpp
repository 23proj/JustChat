#include "JC_MyGroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_MyGroupTableWidget::JC_MyGroupTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "�ҵ�Ⱥ����" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fBtnView = new QPushButton( "�鿴" );
	fBtnClose = new QPushButton( "�ر�" );

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "�ҵ�Ⱥ��id" << "Ⱥ������" << "Ⱥ������" << "Ⱥ������" );
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
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->addStretch( 1 );
	hLayout->addWidget( fBtnView );
	hLayout->addWidget( fBtnClose );
	mainLayout->addLayout( hLayout );
	setLayout( mainLayout );
	setWindowTitle( tr( "�鿴�ҵ�Ⱥ��" ) );
	//setFixedSize( QSize( 600, 400 ) );

	// �����źŲ�
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnClose, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( this, SIGNAL( sigViewGroup( qint32 ) ), fHome, SLOT( dealShowGroup( qint32 ) ) );
}

JC_MyGroupTableWidget::~JC_MyGroupTableWidget()
{
}

void JC_MyGroupTableWidget::dealShow()
{
	/* ԭʼ������� */
	fGroupTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString( "�ҵ�Ⱥ��ID%1" ).arg( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "�ҵ�Ⱥ����%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "�ҵ�Ⱥ��%1�Ľ���" ).arg( i ) );
		QTableWidgetItem* itmPeople = new QTableWidgetItem( QString( "�ҵ�Ⱥ��%1������" ).arg( i ) );
		itmId->setTextAlignment( Qt::AlignCenter );
		itmTitle->setTextAlignment( Qt::AlignCenter );
		itmContent->setTextAlignment( Qt::AlignCenter );
		itmPeople->setTextAlignment( Qt::AlignCenter );
		fGroupTableWidget->setItem( i, 0, itmId );
		fGroupTableWidget->setItem( i, 1, itmTitle );
		fGroupTableWidget->setItem( i, 2, itmContent );
		fGroupTableWidget->setItem( i, 3, itmPeople );
	}

	/* ��ʾ���� */
	show();
}

void JC_MyGroupTableWidget::dealShowGroup()
{
	// ��ȡ��ǰѡ���Ⱥ��
	if ( fGroupTableWidget->selectedItems().empty() )
	{
		QMessageBox::warning( nullptr, tr( "��ʾ" ), tr( "����ѡ��һ��Ⱥ��" ) );
		return;
	}
	QTableWidgetItem *curItm = fGroupTableWidget->selectedItems().front();
	qint32 id = ( qint32 ) curItm->text().toInt();
	emit sigViewGroup( id );
}
