#include "Cache.h"
#include <QString>
#include <QDebug>

Cache::Cache(){
	cacheSize = 0;
	blockSize = 0;
	blockCount = 0;
	hitCount = 0;
	accesses = 0;
	memToCache = 0;
	cacheToMem = 0;
	writeBack = true;
	mapType = "DM";
}

void  Cache::resize(int cSize, int bSize, QString m, bool w){
	cacheSize = cSize;
	blockSize = bSize;
	mapType = m;
	writeBack = w;
	blockCount = cSize/bSize;//calculate the block count
	int numWays = ways(m);
	int indexes;
	if(numWays != -1)
		indexes = blockCount/numWays;
	else
		indexes = blockCount;
	cache.resize(indexes); //resize the cache so that the #rows = number of blocks
	for(int i = 0; i < cache.size(); i++){ //resize the cache so that the #columns = block size
		cache[i].resize(numWays);
	}
}

int Cache::ways(QString op){
	if(op == "DM"){
		return 1;
	}

	else if(op == "2Way"){
		return 2;
	}

	else if(op == "4Way"){
		return 4;
	}

	else
		return -1;
}

void Cache::process(QString operation, QString address){
	//qDebug() << address << endl;
	QByteArray data = QByteArray::fromHex(address.toLatin1().toHex());
	bool ok = false;
	int hexAddress = data.toInt(&ok, 16);
	/*qDebug() << "Hex Address\t" << hexAddress;
	qDebug() << "Cache Size\t" << cSize;
	qDebug() << "Block Size\t" << bSize;
	qDebug() << "Block Count\t" << bCount;*/
	int index = (hexAddress/blockSize)%blockCount;
	int offset = hexAddress % blockSize;
	int tag = hexAddress/cacheSize;
	bool hit = false;

	if(operation == "read"){
		accesses++;
		for(int i = 0; i < cache[index].size(); i++){
			if(cache[index][offset] == tag){
				//qDebug() << "HIT";
				hit = true;
				hitCount++;
			}
		}

			if(hit == false){
				cache[index][offset] = tag;
				memToCache += blockSize;
				//qDebug() << "MISS";
			}
	}

	else if(operation == "write"){
		accesses++;
		for(int i = 0; i < cache[index].size(); i++){
			if(cache[index][offset] == tag){
				//qDebug() << "HIT";
				hit = true;
				hitCount++;
			}
		}

			if(hit == false){
				cache[index][offset] = tag;
				memToCache += blockSize;
				//qDebug() << "MISS";
			}
	}


	/*qDebug() << "\nTag:\t" << tag;
	qDebug() << "Index:\t" << index;
	qDebug() << "Offset:\t" << offset;*/

	//return result::HIT;
}

QString Cache::getStats(){
	QString wp = "";
	if(writeBack == true)
		wp = "WB";
	else
		wp = "WT";

	QString temp = "";
	temp += QString::number(cacheSize) + "\t";
	temp += QString::number(blockSize) + "\t";
	temp += mapType + "\t";
	temp += wp + "\t";
	temp += QString::number(double(hitCount)/double(accesses)) + "\t";
	temp += QString::number(memToCache) + "\t";
	temp += QString::number(cacheToMem) + "\t";
	return temp;
}