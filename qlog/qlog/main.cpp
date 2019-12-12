#include "qlog.h"
#include <QtWidgets/QApplication>
#include <QDate>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Loger log;
	LogWrite logWrite;
	qInstallMessageHandler(&Loger::outputMessage);
	QObject::connect(&log, &Loger::sig_sendMessage, &logWrite, &LogWrite::slot_writeInfo);
	return a.exec();
}