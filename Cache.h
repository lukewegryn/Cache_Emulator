#include <QVector>
#include <QByteArray>
class Cache{
	public:
		Cache();
		QVector<QVector<QByteArray> > cache;
		QVector<int> cacheSize;
		QVector<int> blockSize;
		enum class mapType {DM, Way_2, Way_4, FA};
		enum class writePolicy {WB, WT};
		enum class result {HIT, MISS};

		void set(int, int, mapType, writePolicy);
		result read(QString, int, int);
};