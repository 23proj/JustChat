#include "JC_HomeDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	JC_HomeDialog home; 
	home.show();
	return app.exec();
}

//#include <Python.h>
//
//int main()
//{
//	Py_Initialize();
//	PyObject* pModule = NULL;
//	PyObject* pFunc = NULL;
//	pModule = PyImport_ImportModule("hello_world");
//	pFunc = PyObject_GetAttrString(pModule, "hello");
//	PyEval_CallObject(pFunc, NULL);
//	Py_Finalize();
//	system("pause");
//	return 0;
//}

