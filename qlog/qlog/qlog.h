#pragma once

#include <QtWidgets/QMainWindow>

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QThread>
#include <QList>
#include <QSemaphore>
#include <QMutex>



class Clog : public QThread
{
	Q_OBJECT

public:
	Clog();
	void write(const QString &msg);
	virtual void run();   //线程的起点，再调用start之后，线程就会调用这个函数
	void outputMessage();

private:
	QMutex m_mutex;
	QList<QString> m_msg;
	QSemaphore m_synSem;
};


class Loger : public QObject
{
	Q_OBJECT                                   // 宏Q_OBJECT，在Qt的程序中如果使用了信号与反应槽就必须在类的定义中声明这个宏
public:
	explicit Loger(QObject *parent = nullptr); //关键字 explicit 可以禁止“单参数构造函数”被用于自动类型转换

	static void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
	void sig_sendMessage(QString mesg);

	// 信号
};
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




class LogWrite : public QObject
{
	Q_OBJECT
public:
	explicit LogWrite(QObject *parent = nullptr);
	~LogWrite();                                   // 析构函数

	public slots:                                 // 反应槽
	void slot_writeInfo(QString info);

private:
	QThread *m_pThread;                            // 线程
};


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

#endif // LOG_H
