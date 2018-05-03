#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<math.h>

using namespace std;

//get INDEX value given Cache Size, Set Associativity, Block Size
int getIndexLength(int size, int ways, int block){

	int denom = block * ways;
	int result = size / denom;
	
	int indexLength = log2 (result);
	
	//testing
	//cout << "\n" << index << "\n";
}

int getTagLength(int size, int indexLength, int offsetLength){
	int tagLength = size - indexLength - offsetLength;
}

int64_t getIndex(int indexLength, int offsetLength,  int64_t address){
	
	//initialize mask to 0
	int64_t mask = 0;
	
	//set mask based on length of index
	for (int i = offsetLength; i < indexLength + offsetLength; i++){
		mask += pow(2, i);
	}
	
	//mask & index to isolate index address	
	int64_t index = (address & mask);	

	//test output
	cout << "\n" << "mask is: " << mask << "\n";
	cout << "\n" << "index address is: " << index << "\n";
}

static int64_t hexstrToInt64(std::string hexstr) {
	return std::stol(hexstr, nullptr, 16);
}		


int main(int argc, char *argv[]) {
	
	//testing indexLength
	getIndexLength(65536, 2, 64);

	string hexstr = "7fffe7fefc8";

	int64_t hexString = hexstrToInt64(hexstr);

	cout << "\n" << "hexString is: " << hexString << "\n";

	//testing index
	getIndex(16, 4, hexString); 

	return 0;

}




