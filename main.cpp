#include <iostream>
#include <QString>
#include <QDebug>
#include "fileIO.h"
#include "Cache.h"

int main(int argc, char *argv[]){
	//qDebug() << QString::fromStdString(argv[1]) << endl;
	fileIO *io = new fileIO(QString::fromStdString(argv[1]));
	QStringList *commands = io->getCommands();
	Cache* c = new Cache();
	foreach(QString command, *commands){
		qDebug() << command << endl;
	}
	return 0;
}
