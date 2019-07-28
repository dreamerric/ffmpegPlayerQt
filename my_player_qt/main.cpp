#pragma once

#include "myPlayerQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication::addLibraryPath("./plugins");
	QApplication a(argc, argv);
	myPlayerQt w;
	w.show();
	return a.exec();
}
