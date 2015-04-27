#include "Cache.h"
#include <QString>
#include <QDebug>
#include <cmath>
#include <limits>

Node::Node(){
	tag = -1;
	valid = false;
	dirty = false;
	lastAccessed = 0;
}

Cache::Cache(){
	cacheSize = 0;
	numIndexes = 0;
	blockSize = 0;
	blockCount = 0;
	hitCount = 0;
	accesses = 0;
	memToCache = 0;
	cacheToMem = 0;
	numWays = 0;
	writeBack = true;
	mapType = "DM";
}

void  Cache::resize(int cSize, int bSize, QString m, bool w){
	cacheSize = cSize;
	blockSize = bSize;
	mapType = m;
	writeBack = w;
	blockCount = cSize/bSize;//calculate the block count
	numWays = ways(m);
	numIndexes = blockCount/numWays;

	cache.resize(numIndexes); //resize the cache so that the #rows = number of blocks
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
		return blockCount;
}

void Cache::process(QString operation, QString address){
	accesses++; //incrememnt this every time a read or write occurs
	QByteArray data = QByteArray::fromHex(address.toLatin1().toHex());
	bool ok = false;
	int hexAddress = data.toInt(&ok, 16);
	//int numIndex = blockCount/numWays;
	qDebug() << numIndexes;
	int index = (hexAddress/blockSize)%numIndexes;
	//int offset = hexAddress % blockSize;
	int tag = hexAddress/cacheSize;
	//int offset = (hexAddress & log2(blockSize))
	bool hit = false;

	for(int i = 0; i < cache[index].size(); i++){
		if(cache[index][i].tag == tag){//&& (cache[index][i].valid == true)){
			cache[index][i].lastAccessed = accesses;
			hit = true;
			hitCount++;
		}
	}

		if(hit == false){
			int choice = 0;
			int max = std::numeric_limits<int>::max();
			for(int i = 0; i < cache[index].size(); i++){
				if(cache[index][i].lastAccessed < max){ //Implements LRU replacement
					max = cache[index][i].lastAccessed;
					choice = i;
				}
			}
				//qDebug() << choice;

			if((cache[index][choice].dirty == true) && (writeBack == true) && (operation == "write")){
				cacheToMem += blockSize;
			}
			cache[index][choice].tag = tag;
			cache[index][choice].lastAccessed = accesses;
			if(operation == "write")
				cache[index][choice].dirty = true;
			cache[index][choice].valid = true;
			memToCache += blockSize;
		}
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
	temp += QString::number(double(hitCount)/double(accesses), 'f', 2) + "\t";
	temp += QString::number(memToCache) + "\t";
	temp += QString::number(cacheToMem) + "\t";
	temp += QString::number(numWays) + "\t";
	return temp;
}