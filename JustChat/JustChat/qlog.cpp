#include "qlog.h"
#include <QMutex>
#include <QFile>
#include <QApplication>
#include <QDate>
#include <QDebug>

static Loger* g_log = nullptr;

Loger::Loger(QObject *parent) : QObject(parent) // ::作用域限定符，在类外定义函数
{
	g_log = this;
}

void Loger::outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString text;
	switch (type)                              //不同类别的信息
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
	// 输出格式
	QString contextInfo = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString currentDate = QString("(%1)").arg(currentDateTime);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(contextInfo).arg(msg).arg(currentDate);

	emit g_log->sig_sendMessage(message);      // emit用于发射信号
}



LogWrite::LogWrite(QObject *parent) : QObject(parent)
{
	m_pThread = new QThread;                       // 新建一个线程
	this->moveToThread(m_pThread);              
	m_pThread->start();                            // 线程开始执行
}

LogWrite::~LogWrite()
{
	m_pThread->terminate();                       // 析构函数，用于终结线程
	m_pThread->deleteLater();
	m_pThread = nullptr;
}

void LogWrite::slot_writeInfo(QString info)       // 写信息
{
	QFile file("log.txt");                        //日志文件
	file.open(QIODevice::WriteOnly | QIODevice::Append); //打开方式
	QTextStream text_stream(&file);
	text_stream << info << "\r\n";
	file.flush();
	file.close();
}




