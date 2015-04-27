#include <iostream>
#include <QString>
#include <QDebug>
#include "fileIO.h"
#include "Cache.h"
#include <QStringList>
#include <QRegExp>
#include <QVector>

int cacheSizes[4] = {1024, 4096, 65536, 131072};
int blockSizes[4] = {8, 16, 32, 128};

int main(int argc, char *argv[]){
	if(argc != 2){
		qDebug() << "\nIncorrect input, please try again.\nUsage:\t ./simulate tracefile" << endl;
		exit(0);
	}

	fileIO *io = new fileIO(QString::fromStdString(argv[1]));
	QStringList *commands = io->getCommands();
	Cache* c = new Cache();
	c->resize(cacheSizes[0], blockSizes[0], "DM", true);
	foreach(QString command, *commands){
		QStringList operation = command.split(QRegExp("\\s"));
		c->process(operation.at(0), operation.at(1));
	}

	qDebug() << c->getStats();
	return 0;
}
