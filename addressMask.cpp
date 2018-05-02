#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<math.h>

using namespace std;

//get INDEX value given Cache Size, Set Associativity, Block Size
int getIndex(int size, int ways, int block){

	int denom = block * ways;
	int result = size / denom;
	
	int index = log2 (result);
	
	//testing
	//cout << "\n" << index << "\n";
}

int getTag(int size, int index, int offset){
	int tag = size - index - offset;
}

int64_t indexMask(int index, int64_t address){
	

}

int main(int argc, char *argv[]) {
	
	//testing
	getIndex(65536, 2, 64);

	return 0;

}




