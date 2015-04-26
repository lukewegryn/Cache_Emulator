#include <iostream>
#include <QString>
#include "fileIO.h"
int main(int argc, char *argv[]){
	fileIO *io = new fileIO(QString::fromStdString(argv[1]));
	return 0;
}
