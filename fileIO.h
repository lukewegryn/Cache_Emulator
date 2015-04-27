#include <QString>
#include <QStringList>
#include <QFile>

class fileIO{
	private:
		QStringList* commands;
	public:
		fileIO(QString filename);
		bool checkFile(QString filename);	
		void parseFile(QString filename);
		QStringList* getCommands();
		QFile* getStream(QString filename);

};
