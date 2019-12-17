#include "JC_HomeDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	JC_HomeDialog home; 
	home.init();
	home.show();
	return app.exec();
}

//#include <python.h>
//
//int main()
//{
//	Py_Initialize();
//	PyObject* pModule = NULL;
//	PyObject* pFunc = NULL;
//	pModule = PyImport_ImportModule("hello_world");
//
//	pFunc = PyObject_GetAttrString(pModule, "hello");
//
//	PyEval_CallObject(pFunc, NULL);
//	Py_Finalize();
//	system("pause");
//	return 0;
//}

// #include "qlog.h"
// #include <QtWidgets/QApplication>
// #include <QDate>
// 
// int main( int argc, char *argv[] )
// {
// 	QApplication a( argc, argv );
// 	Loger log;
// 	LogWrite logWrite;
// 	qInstallMessageHandler( &Loger::outputMessage );
// 	QObject::connect( &log, &Loger::sig_sendMessage, &logWrite, &LogWrite::slot_writeInfo );
// 	return a.exec();
// }
