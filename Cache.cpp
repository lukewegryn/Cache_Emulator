#include "Cache.h"
#include <QString>
#include <QDebug>

Cache::Cache(){
	cacheSize << 1024 << 4096 << 65536 << 131072;
	blockSize << 8 << 16 << 32 << 128;
}

void  Cache::set(int cSize, int bSize, mapType m, writePolicy w){
	int bCount = cSize/bSize; //calculate the block count
	cache.resize(bCount); //resize the cache so that the #rows = number of blocks
	for(int i = 0; i < cache.size(); i++){ //resize the cache so that the #columns = block size
		cache[i].resize(bSize);
	}
}

Cache::result Cache::read(QString address, int bSize, int cSize){
	int bCount = cSize/bSize; //calculate the block count
	qDebug() << address << endl;
	QByteArray data = QByteArray::fromHex(address.toLatin1().toHex());
	bool ok = false;
	int hexAddress = data.toInt(&ok, 16);
	qDebug() << "Hex Address\t" << hexAddress;
	qDebug() << "Cache Size\t" << cSize;
	qDebug() << "Block Size\t" << bSize;
	qDebug() << "Block Count\t" << bCount;
	int index = (hexAddress/bSize)%bCount;
	int offset = hexAddress % bSize;
	int tag = hexAddress/cSize;

	qDebug() << "\nTag:\t" << tag;
	qDebug() << "Index:\t" << index;
	qDebug() << "Offset:\t" << offset;

	return result::HIT;
}