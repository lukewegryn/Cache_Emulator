#include <QVector>
#include <QByteArray>
#include <QString>

class Node{
	public:
		Node();
		int tag;
		bool valid;
		bool dirty;
};

class Cache{
	public:
		Cache();
		QVector<QVector<Node> > cache;
		int cacheSize;
		int blockSize;
		int blockCount;
		int hitCount;
		int accesses;
		int memToCache;
		int cacheToMem;
		int numWays;

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