#include <iostream>
#include <QString>
#include <QDebug>
#include "fileIO.h"
#include "Cache.h"
#include <QStringList>
#include <QRegExp>

int main(int argc, char *argv[]){
	if(argc != 2){
		qDebug() << "\nIncorrect input, please try again.\nUsage:\t ./simulate tracefile" << endl;
		exit(0);
	}

	fileIO *io = new fileIO(QString::fromStdString(argv[1]));
	QStringList *commands = io->getCommands();
	Cache* c = new Cache();
	foreach(QString command, *commands){
		QStringList operation = command.split(QRegExp("\\s"));
		c->set(c->cacheSize[1], c->blockSize[0], c->mapType::DM, c->writePolicy::WB);
		if(operation.at(0) == "read"){
			qDebug() << "Read";
			c->read(operation.at(1), c->blockSize[0], c->cacheSize[3]);
		}
		else
			qDebug() << "Write";
	}
	return 0;
}
