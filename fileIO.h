#include <QString>
#include <QStringList>

class fileIO{
	private:
		QStringList *commands;
	public:
		fileIO(QString filename);
		bool checkFile(QString filename);	
		QStringList parseFile(QString filename);
};
