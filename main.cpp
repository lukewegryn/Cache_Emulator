#include <iostream>
#include <QString>
#include <QDebug>
#include "fileIO.h"
#include "Cache.h"
#include <QStringList>
#include <QRegExp>
#include <QVector>
#include <QString>

int main(int argc, char *argv[]){
	int cacheSizes[4] = {1024, 4096, 65536, 131072};
	int blockSizes[4] = {8, 16, 32, 128};
	QString maps[4] = {"DM", "2W","4W","FA"};
	QString writePolicy[2] = {"WB", "WT"};
	if(argc != 2){
		qDebug() << "\nIncorrect input, please try again.\nUsage:\t ./simulate tracefile" << endl;
		exit(0);
	}

	fileIO *io = new fileIO(QString::fromStdString(argv[1]));
	QFile *file = io->getStream(argv[1]);
	QTextStream out(file);
	QStringList *commands = io->getCommands();
	Cache* c;
	for(int i = 0; i < 4; i++){
		for(int k = 0; k < 4; k++){
			for(int j = 0; j < 4; j++){
				for(int l = 0; l < 2; l++){
				c = new Cache();
				c->resize(cacheSizes[i], blockSizes[k], maps[j], writePolicy[l]);
				foreach(QString command, *commands){
					QStringList operation = command.split(QRegExp("\\s"));
					c->process(operation.at(0), operation.at(1));
					}
					c->cleanUp();
					out << c->getStats() << endl;
				}
			}
		}
	}
	return 0;
}
