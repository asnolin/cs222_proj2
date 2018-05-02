/* CS222 Cache Simulation Project
   written by Andrew Nolin 2018/04/25
   
   compile with: g++ cache.cpp -o cache -std=gnu++11
   
   to run: ./cache CONFIG_FILE_NAME
   
   TODO:
   crawler: needs to read trace and config files in the stuff directory
   
   Mem: needs to provide all address aka, all requests must be hits
   
   cacheLevel: needs mapping type(direct 2 4 8), variable size, variable block size, determine hit or miss, determine index, needs clear function
   
   cache: needs to record hits/misses, handle transfer of blocks,
   
*/


//include libs and use std namespace
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
using namespace std;

//global enums
enum c_type {instr, data, unified};
enum writeBack {fifo, writeThru, writeback};

//dummy main memory class
//this will be used to provide dummy variables to the highest level of cache
class Mem{
private:
  int size;
  vector <int > address;
  
public:
  Mem(){
    size = 10000;
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
  
private:
  static int idSeed;
  int level; //size of the cache
  int size; //size of cache in bytes
  int mapping; //number of blocks per set
  int id = idSeed++;
  struct block{
    int blockNum;
    int blockSize;
    int prefix;
    int addr[];
  };
  
public:
  CacheLevel(int inLevel, int inSize, int inMapping, int inBlockSize){
    level = inLevel;
    size = inSize;
    mapping = inMapping;
  }
  
  //getters
  int getLevel() {
    return level;
  } 
  int getSize () {
    return size;
  }
  
  //setters
  void setLevel(int inLevel){
    level = inLevel;
  }
  void setSize(int inSize){
    size = inSize;
  }
  void setMapping(int inMap){
    mapping = inMap;
  }
  
  //methods
  
  //true if hit, otherwise false
  bool find(long int target){
    bool found = false;
    //determine set 
    //determine block
    //search for target address in block
    
    return found;
  }
  
  //clears all cache
  void clear(){
    //TODO
  }
};//end CacheLevel



//contains cachelevel instances. handles passing between cache levels, associativity, and write stratagy
class Cache{
  vector <CacheLevel> cVec;
  int numLevels;
  int numHits;
  int numMiss;
  //constructors
  
  //methods
  
  //clears all cache levels, in prep for another test
  void clearAll(){
    for(int i = 0; i < cVec.size(); ++i){
      cVec[i].clear();
    }
  }
  //moves blocks between levels
  void passBlock(){
    //TODO
  }
  
  //returns a CacheLevel
  CacheLevel getC(int id){
    
  }
};//end Cache
  
  
  //crawls through directory to read config and trace files
class Crawler{
  
  private:
  string dir = "stuff/";
  string config = "config/";
  string trace = "trace/";
  //config file 
  string configName;
  //prefix and suffix of trace files
  string t_prefix = "gcc-addrs-10K-";
  string t_suffix = ".trace";
  string vers[6] = {"a","b","c","d","e","f"};
  static int testNum;
  
public:
  Crawler(){
    configName = "base.config";
  }
  Crawler(string inName){
    configName = inName;
  }
  //methods
  
  //takes in a CacheLevel to assign from config
  void assign(CacheLevel &inLevel){
    
  }
};//end Crawler


  //set statics
int Crawler::testNum = 0;
int CacheLevel::idSeed = 0;

//main
int main(int argc, char *argv[]) {
  string inName;
  //parse arguments
  if(argc > 1){
    inName = argv[1];
  }else{
    inName = "base.config";
  }
  
  //init 
  Crawler crawl(inName);
  
  return 0;
}

