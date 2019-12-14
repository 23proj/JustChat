#pragma once

#include <QtWidgets/QMainWindow>

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QThread>
#include <QtCore/QList>
#include <QtCore/QSemaphore>
#include <QtCore/QMutex>
#include <QtCore/QDateTime>



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


#endif // LOG_H
