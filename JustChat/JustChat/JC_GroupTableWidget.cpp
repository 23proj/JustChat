#include "JC_GroupTableWidget.h"
#include "JC_HomeDialog.h"

JC_GroupTableWidget::JC_GroupTableWidget(QWidget *parent)
	: QWidget( nullptr )
{
	fHome = ( JC_HomeDialog * ) parent;
	setWindowTitle( tr( "����Ⱥ����" ) );
	fGroupTableWidget = new QTableWidget( 10, 4, this );
	fBtnView = new QPushButton( "�鿴" );
	fBtnClose = new QPushButton( "�ر�" );

	fGroupTableWidget->setHorizontalHeaderLabels( QStringList() << "����Ⱥ��id" << "Ⱥ������" << "Ⱥ������" << "Ⱥ������" );
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
	//setFixedSize( QSize( 600, 400 ) );

	// �����źŲ�
	connect( fBtnView, SIGNAL( clicked() ), this, SLOT( dealShowGroup() ) );
	connect( fBtnClose, SIGNAL( clicked() ), this, SLOT( close() ) );
	connect( this, SIGNAL( sigViewGroup( qint32 ) ), fHome, SLOT( dealShowGroup( qint32 ) ) );
}

JC_GroupTableWidget::~JC_GroupTableWidget()
{
}

void JC_GroupTableWidget::dealShow()
{
	/* ԭʼ������� */
	fGroupTableWidget->clearContents();

	/* �����ݿ������¶�ȡ��Ϣ��䵽�Ի��� */

	for ( qint32 i = 0; i < 5; ++i )
	{
		QTableWidgetItem* itmId = new QTableWidgetItem( QString( "����Ⱥ��ID%1" ).arg( i ) );
		QTableWidgetItem* itmTitle = new QTableWidgetItem( QString( "����Ⱥ����%1" ).arg( i ) );
		QTableWidgetItem* itmContent = new QTableWidgetItem( QString( "����Ⱥ��%1�Ľ���" ).arg( i ) );
		QTableWidgetItem* itmPeople = new QTableWidgetItem( QString( "����Ⱥ��%1������" ).arg( i ) );
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

void JC_GroupTableWidget::dealShowGroup()
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
