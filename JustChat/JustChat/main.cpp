#include "JC_HomeDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	JC_HomeDialog w;
	w.show();
	return a.exec();
}
