#pragma once
#include<bitset>
#include "Btree.h"
class filter
{
public:
	static const int max =1000000;
	std::bitset<max> bloomFilter;
	filter() {
		bloomFilter.reset();
	}
	~filter() {
		bloomFilter.~bitset();
	}
	void insertToBloomFilter(std::string str) {    //数据插入
		int hash1 = std::hash<std::string>{}(str) % max;
		int hash2 = std::hash<std::string>{}(str + "salt") % max;
		int hash3 = std::hash<std::string>{}(str + "pepper") % max;

		bloomFilter.set(hash1);
		bloomFilter.set(hash2);
		bloomFilter.set(hash3);
	}
	bool searchInBloomFilter(std::string str) {    //查找数据
		int hash1 = std::hash<std::string>{}(str) % max;
		int hash2 = std::hash<std::string>{}(str + "salt") % max;
		int hash3 = std::hash<std::string>{}(str + "pepper") % max;

		return bloomFilter.test(hash1) && bloomFilter.test(hash2) && bloomFilter.test(hash3);
	}
};


