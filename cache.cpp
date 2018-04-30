/* CS222 Cache Simulation Project
   written by Andrew Nolin 2018/04/25
   
   compile with: g++ cache.cpp -o cache -std=gnu++11

TODO:
crawler:needs to read trace and config files in the stuff directory
Mem: needs to provide all address aka, all requests must be hits
cacheLevel: needs mapping type(direct 2 4 8), variable size, variable block size, determine hit or miss
cache: needs to record hits/misses, handle transfer of blocks
*/


//iunclude libs and use std namespace
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
using namespace std;


//dummy main memory class
//this will be used to provide dummy variables to the highest level of cache
class Mem{
  //fields
private:
  int size;
  vector <int > address;

public:

  Mem(){
    size = 100;
  }
  Mem(int inSize){
    size = inSize;
    populate();
  }

  //getters
  int getSize() {
    return size;
  }

  int getAddress(int i){
    return address[i];
  }


  //setters

  //methods
  void populate(){
    for(int i = 0; i < size; ++i){
      address[i] = rand()%size+1;
    }
  }
};



//represents one level of cache
//has 2 ints, a enum, and a struct that represents a block
class CacheLevel{
 
private: //fields
  int level; //size of the cache
  int size; //size of cache in bytes
  enum mapping {associative, direct, two, four, eight};
  enum type {instr, data, unified};

  struct block{
    int blockNum;
    int blockSize;
    int addr[];
  };
  
public: //constructor
  CacheLevel(int inLevel, int inSize, int inBlockSize){
    level = inLevel;
    size = inSize;
  }

  //getters
  int getLevel() {
    return level;
  } 
  int getSize () {
    return size;
  }
  
  //setters


  //methods 
  bool find(){
    bool found = false;
    //for each block, search its contents:

    return found;
  }
};



//contains cachelevel instances. handles passing between cache levels, associativity, and write stratagy
class Cache{
  //fields
  int ways; // associativity
  enum writeBack {fifo, writeThru, writeback};
  //constructors
  //methods
};


//crawls through directory to read config and trace files
class Crawler{

private:
  string dir = "stuff/";
  string config = "config/";
  string trace = "trace/";
public:

  Crawler(){}

  void assign(&CacheLevel inLevel){

  }
};



//main
int main(int argc, char *argv[]) {
  //srand(1);
  while(3==3){
    cout << "hello world" << endl;
  }
  return 0;
}
