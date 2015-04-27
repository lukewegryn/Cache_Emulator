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
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		file.close();
		return false;
	}
	file.close();
	return true;	
}

QStringList* fileIO::getCommands(){
	return commands;
}

void fileIO::parseFile(QString filename){
	commands = new QStringList();
	if(filename != NULL){
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        	return;
		QTextStream in(&file);
		QString line = in.readLine();
		while(!line.isNull()){
			commands->append(line);
			line = in.readLine();
		}
		file.close();
	}
}


