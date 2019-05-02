#include "Cache_Module.hpp"
#include "Instruction.hpp"
#include "Block.hpp"
#include <cassert>

bool Set_Assoc_Module::read(unsigned long &address){

	Block temp = Block(address, this->block_size, this->size, this->assoc);
	std::queue<Block> temp_cache;

	unsigned int tag = temp.tag;
	unsigned int index = temp.index;
	bool miss = true;
	Block MRU ;

	while(cache[index].size()){
	    Block t = cache[index].front();
	    if(t.tag == tag && miss){
	      miss = false;
	      MRU = temp;
	      // Cache_Hits++;

	    }else{
	      temp_cache.push(t);
	    }
	    cache[index].pop();
	}
	if(!miss){
		assert(MRU.tag == tag);
	  // assert(MRU.valid);
	  	// MRU.valid = true; 
	  	temp_cache.push(MRU);
	}
	cache[index] = temp_cache;

	return miss;
}

Block Set_Assoc_Module::write(unsigned long &address){
	Block temp = Block(address, this->block_size, this->size, this->assoc);
	unsigned int tag = temp.tag;
	unsigned int index = temp.index;
	printf("index: %d \t tag: %x \n", index, tag);

	std::queue<Block> temp_cache;
	bool miss = true;
	Block LRU;
	Block MRU;

	//Check if block is in queue
	// If in queue make sure to pop it and insert it at the top
	// If not int queue check whether queue is full or not
	// If queue is full then pop queue

	while(cache[index].size()){
	    Block t = cache[index].front();
	    if(t.tag == tag && miss){
	      miss = false;
	      MRU = temp;
	      // Cache_Hits++;
	    }else{
	      temp_cache.push(t);
	    }
	    cache[index].pop();
	}
	if(miss){
		temp.valid = false;
	  	printf("%s\n","Made block dirty" );
	  if(temp_cache.size() < this->assoc){
	  	// temp.valid = false;
	    temp_cache.push(temp);

	    assert(temp_cache.size() <= this->assoc);
	  }else{

	  	LRU = temp_cache.front(); 
	    temp_cache.pop();

	    printf("%s\n", "Removing BLOCK");
	    // temp.valid = false;
	  	// printf("%s\n","Made block dirty" );
	    temp_cache.push(temp);

	    assert(cache[index].size() <= this->assoc);
	  }
	}else{
	  //Update the cache
	  assert(MRU.tag == tag);
	  // assert(MRU.valid);
	  MRU.valid = false; //Make Block dirty since it's a write
	  printf("%s\n","Made block dirty" );
	  temp_cache.push(MRU);
	}
	cache[index] = temp_cache;
	return LRU;
}



void Set_Assoc_Module::replace(unsigned long &address){

}

Block Set_Assoc_Module::update(unsigned long &address){
	Block temp = Block(address, this->block_size, this->size, this->assoc);
	unsigned int tag = temp.tag;
	unsigned int index = temp.index;
	printf("index: %d \t tag: %x \n", index, tag);

	std::queue<Block> temp_cache;
	bool miss = true;
	Block LRU;
	temp.valid = false;
	// printf("%s\n","Made block dirty" );
	if(temp_cache.size() < this->assoc){
	  	// temp.valid = false;
	    temp_cache.push(temp);

	    assert(temp_cache.size() <= this->assoc);
	}else{

	  	LRU = temp_cache.front(); 
	    temp_cache.pop();

	    printf("%s\n", "Removing BLOCK");
	    // temp.valid = false;
	  	// printf("%s\n","Made block dirty" );
	    temp_cache.push(temp);

	    assert(cache[index].size() <= this->assoc);
	}

}