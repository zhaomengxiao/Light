#include "rasterWindow\rasterwindow.h"
#include "lightwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LightWindow w;
	w.show();
	return a.exec();
}
