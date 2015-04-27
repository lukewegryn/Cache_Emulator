#include <QVector>
#include <QByteArray>
#include <QString>

class Cache{
	public:
		Cache();
		QVector<QVector<int> > cache;
		int cacheSize;
		int blockSize;
		int blockCount;
		int hitCount;
		int accesses;
		int memToCache;
		int cacheToMem;

		bool writeBack;
		QString mapType;
		//enum class mapType {DM, Way_2, Way_4, FA};
		//enum class writePolicy {WB, WT};
		//enum class result {HIT, MISS};

		void resize(int, int, QString, bool);
		void process(QString, QString);
		int ways(QString op);
		QString getStats();
};