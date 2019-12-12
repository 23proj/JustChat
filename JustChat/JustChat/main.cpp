#include "JC_HomeDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	JC_HomeDialog home; 
	home.show();
	return app.exec();
}
