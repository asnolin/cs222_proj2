/* CS222 Cache Simulation Project
   written by Andrew Nolin 2018/04/25
   
   compile with: g++ cache.cpp -std=gnu++11

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
private://fields
  int size;
  vector <int> address;

public:

  //constructor

  //getters

  int getSize() {
    return size;
  }

  int getAddress(int i){
    return address[i];
  }
  //setters

  //methods
};



//represents one level of cache
//has 2 ints, a enum, and a struct that can be 
class CacheLevel{
 
private: //fields
  int level; //size of the cache
  int size; //size of cache in bytes
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





//main
int main(int argc, char *argv[]) {

  return 0;
}
