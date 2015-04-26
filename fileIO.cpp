#include <QString>
#include <QDebug>
#include "fileIO.h"
#include <QFile>
#include <QStringList>

fileIO::fileIO(QString fn){
	if(checkFile(fn)){
		parseFile(fn);
	}

	else{
		qDebug() << "You did not enter a valid filename, or the file is not in the current working directory." << endl;
		exit(0);
	}
}
bool fileIO::checkFile(QString filename){
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return true;
	return false;	
}

QStringList fileIO::parseFile(QString filename){
	commands = new QStringList();
	if(filename != NULL){
		QFile file(filename);
		while(!file.atEnd()){
			QString line = QString(file.readLine());
			qDebug() << line << endl;
			commands->append(line);
		}
	}
}


