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
#include<cstdint>
using namespace std;

//global enums
enum c_type {instr, data, uni};
enum writeBack {fifo, writeThru, writeback};


//represents one level of cache
//has ints, a enum, and a struct that represents a block, a vecter 
class CacheLevel{
  
private:
  static int idSeed;
  int level; //size of the cache
  int size; //size of cache in bytes
  c_type type;
  int mapping; //number of blocks per set
  int id = idSeed++;


  struct block{
    int blockNum;
    int blockSize;
   vector < int64_t> addr;
  };

  vector < vector<block> > set;

public:
  CacheLevel(int inLevel, c_type inType){
    level = inLevel;
    type = inType;

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
  Cache(){
    cVec.push_back(CacheLevel(1,instr));
    cVec.push_back(CacheLevel(1,data));
    cVec.push_back(CacheLevel(2, uni));
  }
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
    for(int i = 0; i < cVec.size(); i++){

    }
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

  
//from
static int64_t hexstrToInt64(string hexstr) {
  return stol(hexstr, nullptr, 16);
}



//main
int main(int argc, char *argv[]) {
    string inName;
    vector <string> inReq;
  //parse arguments
  if(argc > 1){
    inName = argv[1];
  }else{
    inName = "base.config";
  }
  
  //init 

  Crawler crawl(inName);
  inReq = crawl.getReqed();
  return 0;
}

