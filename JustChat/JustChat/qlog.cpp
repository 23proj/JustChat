#include "qlog.h"
#include <QMutex>
#include <QFile>
#include <QApplication>
#include <QDate>
#include <QDebug>

static Loger* g_log = nullptr;

Loger::Loger(QObject *parent) : QObject(parent) // ::�������޶����������ⶨ�庯��
{
	g_log = this;
}

void Loger::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString text;
	switch (type)                              //��ͬ������Ϣ
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;
	case QtWarningMsg:
		text = QString("Warning:");
		break;
	case QtCriticalMsg:
		text = QString("Critical:");
		break;
	case QtFatalMsg:
		text = QString("Fatal:");
	}
	// �����ʽ
	QString contextInfo = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString currentDate = QString("(%1)").arg(currentDateTime);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(contextInfo).arg(msg).arg(currentDate);

	emit g_log->sig_sendMessage(message);      // emit���ڷ����ź�
}



LogWrite::LogWrite(QObject *parent) : QObject(parent)
{
	m_pThread = new QThread;                       // �½�һ���߳�
	this->moveToThread(m_pThread);              
	m_pThread->start();                            // �߳̿�ʼִ��
}

LogWrite::~LogWrite()
{
	m_pThread->terminate();                       // ���������������ս��߳�
	m_pThread->deleteLater();
	m_pThread = nullptr;
}

void LogWrite::slot_writeInfo(QString info)       // д��Ϣ
{
	QFile file("log.txt");                        //��־�ļ�
	file.open(QIODevice::WriteOnly | QIODevice::Append); //�򿪷�ʽ
	QTextStream text_stream(&file);
	text_stream << info << "\r\n";
	file.flush();
	file.close();
}




