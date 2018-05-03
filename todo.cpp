#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

//true if hit, otherwise false
bool find(int64_t target) {
	bool found = false;
	vector<block> set;
	//determine set
	int64_t index = getIndex(target);
	for (int i = 0; i < sets.size(); ++i)
	{
		if (sets[i].index == index)
		{
			set = sets[i];
		}
	}
	//search for block
	int64_t tag = getTag(target);
	for (int i = 0; i < set.contents.size(); ++i)
	{
		if (found_in_block(tag, set.contents[i]))
		{
			found = true;
		}
		else
		{
			found = false;
		}
	}
	//search for target address in block
	//TODO
	return found;
}

bool found_in_block(int64_t tag, block blok)
{
	for (int i = 0; i < blok.addr.size(); ++i)
	{
		if (blok.addr[i] == tag)
		{
			return true;
		}
	}
	return false;
}