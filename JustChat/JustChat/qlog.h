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
	virtual void run();   //�̵߳���㣬�ٵ���start֮���߳̾ͻ�����������
	void outputMessage();

private:
	QMutex m_mutex;
	QList<QString> m_msg;
	QSemaphore m_synSem;
};


class Loger : public QObject
{
	Q_OBJECT                                   // ��Q_OBJECT����Qt�ĳ��������ʹ�����ź��뷴Ӧ�۾ͱ�������Ķ��������������
public:
	explicit Loger(QObject *parent = nullptr); //�ؼ��� explicit ���Խ�ֹ�����������캯�����������Զ�����ת��

	static void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
	void sig_sendMessage(QString mesg);

	// �ź�
};


class LogWrite : public QObject
{
	Q_OBJECT
public:
	explicit LogWrite(QObject *parent = nullptr);
	~LogWrite();                                   // ��������

	public slots:                                 // ��Ӧ��
	void slot_writeInfo(QString info);

private:
	QThread *m_pThread;                            // �߳�
};


#endif // LOG_H
