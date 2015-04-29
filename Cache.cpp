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
	writePolicy = "WB";
	mapType = "DM";
}

void  Cache::resize(int cSize, int bSize, QString m, QString w){
	cacheSize = cSize;
	blockSize = bSize;
	mapType = m;
	writePolicy = w;
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

	else if(op == "2W"){
		return 2;
	}

	else if(op == "4W"){
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
	int index = (hexAddress/blockSize)%numIndexes; //formula from the class notes
	int tag = (hexAddress/blockSize)/numIndexes; //formula from the class notes
	bool hit = false;

	/*if(operation == "write" && writePolicy == "WT"){
				cacheToMem += 4;
	}*/

	for(int i = 0; i < cache[index].size(); i++){ //this section is responsible for determining if an address is alread in the cache
		qDebug() << operation;
		if(cache[index][i].tag == tag && cache[index][i].valid){ //iterate through the index and find that we have a matching tag, it must also have a valid bit
			cache[index][i].lastAccessed = accesses; //mark that block as accessed on the current access count
			hit = true; //set hit to true for this iteration
			hitCount++; //increment the number of hits for this cache configuration
			//qDebug () << operation;
			if(writePolicy == "WB" && operation == "write"){
				//qDebug() << "Writeback and write operation";
			}
		}
	}

		if(!hit){ //this section determines what to do if the address is not already in the cache, it also implements LRU replacement
			int choice = 0; //this will be the block that we choose
			int max = std::numeric_limits<int>::max(); //set the value to the highest possible integer value
			for(int i = 0; i < cache[index].size(); i++){ //for each block in the index see when the last time that block was accessed
				if(cache[index][i].lastAccessed < max){ //if it was accessed less than the lowest ones before it, it is now the lowest one
					max = cache[index][i].lastAccessed; 
					choice = i; //this means that out of all of the blocks in the current line, this one was accessed the least recently (hence LRU replacement)
				}
			}
			
			cache[index][choice].tag = tag; //replace the LRU, if there are empty spots in the cache then this will simply replace the first empty one it finds
			cache[index][choice].valid = true; //since we just added this address from the main memory, we now have a valid block
			cache[index][choice].lastAccessed = accesses; //since we just updated this one we need to go ahead and mark it as the lastAccessed one
			memToCache += blockSize; //increment the memory to cache byte transfer counter
		}
}

QString Cache::getStats(){
	QString temp = "";
	temp += QString::number(cacheSize) + "\t";
	temp += QString::number(blockSize) + "\t";
	temp += mapType + "\t";
	temp += writePolicy + "\t";
	temp += QString::number(double(hitCount)/double(accesses), 'f', 2) + "\t";
	temp += QString::number(memToCache) + "\t";
	temp += QString::number(cacheToMem) + "\t";
	temp += QString::number(numWays) + "\t";
	return temp;
}

			/*if(cache[index][choice].valid == true && operation == "write" && writePolicy == "WB"){
				if(cache[index][choice].dirty == true){
					cacheToMem += blockSize;
				}
				cache[index][choice].dirty = true;
			}
			cache[index][choice].valid = true;*/