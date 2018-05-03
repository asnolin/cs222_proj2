/* CS222 Cache Simulation Project
   written by Andrew Nolin 2018/04/25
   
   compile with: g++ cache.cpp -o cache -std=gnu++11
   
   to run: ./cache CONFIG_FILE_NAME
   
   TODO:
   crawler: needs to read trace files in the stuff/trace/ directory
     
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
#include<sstream>
#include<math.h>
using namespace std;


//global enums and structs
enum c_type {instr, data, uni};

struct cache_params
  {
    bool alloc = true;
    int block = 1;
    int level = 1;
    int size = 1;
    int ways = 1;
    string replace = "a";
    c_type type = uni;
    string write = "a";
  };


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
  int blockHit, blockMiss;
  int blSize;
  struct block{
    int blockSize;
    int64_t tag;
    vector < int64_t> addr;
  };
  struct set{
    vector<block> contents;
    int64_t index;
  };

  vector <set> sets;

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
  int getID() {
    return id;
  }
  c_type getType(){
    return type;
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
  void setBlockSize(int inBlSize){
    blSize = inBlSize;
  }

  //methods
  
  //get INDEX length given Cache Size, Set Associativity, Block Size
  int getIndexLength(){

    int denom = blSize * ways;
    int result = size / denom;
    
    int indexLength = log2 (result);
    
    //testing
    //cout << "\n" << index << "\n";
  }

  //get INDEX address based on bitmask
  int64_t getIndex(int indexLength, int offsetLength,  int64_t address){
    
    //initialize mask to 0
    int64_t indexMask = 0;
    
    //set mask based on length of index
    for (int i = offsetLength; i < indexLength + offsetLength; i++){
      indexMask += pow(2, i);
    }
    
    //(mask & index) to isolate index address 
    int64_t index = (address & indexMask);  

    //test output
    //cout << "\n" << "indexMask is: " << indexMask << "\n";
    //cout << "\n" << "index address is: " << index << "\n";
  }

  int getTagLength(int size, int indexLength, int offsetLength){
    int tagLength = size - indexLength - offsetLength;
  }

  //get Tag address based on bitmask
  int64_t getTag(int tagLength, int indexLength, int offsetLength, int64_t address){
    //initialize mask to 0
    int64_t tagMask = 0;

    //set mask based on length of tag
    for (int i = offsetLength + indexLength; i < offsetLength + indexLength + tagLength; i++){
      tagMask += pow(2, i);
    }

    //(mask & tag) to isolate tag address
    int64_t tag = (address & tagMask);

    //cout << "\n" << "tagMask is: " << tagMask << "\n";
    //cout << "\n" << "tag address is: " << tag << "\n";  
  }



  //true if hit, otherwise false
  bool find(int64_t target){
    bool found = false;
    //determine set 
    //determine block
    //search for target address in block
    //TODO
    return found;
  }
  
  //clears all cache fields
  void clear(){
    sets.clear();
    blockHit = 0;
    blockMiss = 0;
  }
  block accessBlock(int64_t address){
    index = getIndex(getIndexLength(), OFFSET, address);
  }


};//end CacheLevel







//contains cachelevel instances. handles passing between cache levels, associativity, fifo write strat
class Cache{
private:
  vector <CacheLevel> cVec;
  int numLevels;
  int cacheHit;
  int cacheMiss;

public:
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

  //returns the l2 cache
  CacheLevel getL2(){
    for(int i = 0; i<cVec.size(); ++i){
      if(cVec[i].getLevel() == 2){
	return cVec[i];
      }
    }
  }

  //returns a CacheLevel
  CacheLevel getC(int id){
    for(int i = 0; i < cVec.size(); i++){
      if(cVec[i].getID() == id){
	return cVec[i];
      }
    }
  }

  //
  void assignCacheLevel(string req){
    //TODO
  }
};//end Cache


  //set statics
int CacheLevel::idSeed = 0;

  



  //crawls through directory to read config and trace files
class Crawler{
  
private:

  vector <string> reqs; //holds data read from config file
  string dir = "stuff/";//head of dir
  string config = "config/";//config dir
  string trace = "trace/";//trace dir
  string configName;//config filename

  //prefix and suffix of trace files
  string t_prefix = "gcc-addrs-10K-";
  string t_suffix = ".trace";
  string vers[6] = {"a","b","c","d","e","f"};
  int maxTests = sizeof(vers)/sizeof(vers[0]);
  int testNum = 0;//holds number of tests done to determine which vers to use
  
  //cache params vector
  vector<cache_params> paramVec;
  //helper functions
  
  vector<cache_params> get_params(string path)
  {
    
    vector<cache_params> params_vect;
    cache_params params;
    
    ifstream f_in;
    f_in.open(path);
    
    string line;
    vector<string> parse_result;
    
    while (f_in)
      {
	getline(f_in, line);
	if (line[0] != '#')
	  {
	    parse_result.push_back(line);
	  }
      }
    
    f_in.close();
    
    for (string segment : parse_result)
      {
	//cout << segment << "\n";
	
	istringstream ss(segment);
	string token;
	
	while (getline(ss, token, ','))
	  {
	    //cout << token << '\n';
	    string param_name = "";
	    string param_value = "";
	    bool on_name = true;
	    for (int i = 0; i < token.length(); ++i)
	      {
		if (token[i] == ':')
		  {
		    on_name = false;
		  }
		
		if (on_name)
		  {
		    param_name += token[i];
		  }
		
		else
		  {
		    if (token[i] != ':')
		      {
			param_value += token[i];
		      }
		  }
	      }
	    
	    // cout << param_name << '\n';
	    // cout << param_value << '\n';
	    
	    if (param_name == "alloc")
	      {
		if (param_value == "true")
		  {
		    params.alloc = true;
		  }
	      }
	    
	    if (param_name == "block")
	      {
		params.block = stoi(param_value);
	      }
	    
	    if (param_name == "level")
	      {
		params.level = stoi(param_value);
	      }
	    
	    if (param_name == "replace")
	      {
		params.replace = param_value;
	      }
	    
	    if (param_name == "size")
	      {
		params.size = stoi(param_value);
	      }
	    
	    if (param_name == "type")
	      {
		if(param_value == "data"){
		  params.type = data;
		}else if(param_value == "unified"){
		  params.type = uni;
		} else{
		  params.type = uni;
		}
	      }
	    
	    if (param_name == "ways")
	      {
		params.ways = stoi(param_value);
	      }
	    
	    if (param_name == "write")
	      {
		params.write = param_value;
	      }
	  }

	params_vect.push_back(params);
      }
	
    return params_vect;
  }

public:
  Crawler(){
    configName = "base.config";
    string fPath = dir+config+configName;
    paramVec = get_params(fPath);

  }
  Crawler(string inName){
    configName = inName;
    string fPath = dir+config+configName;
    paramVec = get_params(fPath);
  }


  //getters
  vector<string> getReqs(){
    return reqs;
  }


  //methods
  
  //takes in a CacheLevel to assign from config
  void assign_param(CacheLevel &inLevel){
    //determine which CacheLevel to modify
    for(int i = 0; i < paramVec.size(); ++i){
      //find the correct cache_params struct to assign to the CacheLevel
      if(inLevel.getLevel() == paramVec[i].level && inLevel.getType() == paramVec[i].type){
	inLevel.setSize(paramVec[i].size);
	inLevel.setBlockSize(paramVec[i].block);
	inLevel.setMapping(paramVec[i].ways);
      }
    }//end for loop
  }

  void incTest(){
    if(testNum < maxTests){
      testNum++;
    }
  }
  bool crawlAgain(){
    if(testNum < maxTests){
      return true;
    }else{
      return false;
    }
  }


};//end Crawler


git 
//from cs222-project-02.pdf
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
  
  //init crawler, cache
  Cache c;
  Crawler crawl(inName);

  //while there are tests to do, pass to inReq and do tests
  while( crawl.crawlAgain()){
    inReq = crawl.getReqs();
    //while inReq is not empty, pop off req from inReq, and record its hits/misses
    while(inReq.size() != 0){
      //pass a req to c, and erase from inReq
      c.assignCacheLevel(inReq.front());
      inReq.erase(inReq.begin());

      //TODO
    }
    crawl.incTest();
    c.clearAll();
  }
  return 0;
}
