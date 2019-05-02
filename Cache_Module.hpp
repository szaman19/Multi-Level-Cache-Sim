#ifndef CACHE_MODULE_HPP
#define CACHE_MODULE_HPP
#include <vector>
#include <queue>
#include <string>
#include "Instruction.hpp"
#include "Block.hpp"

class Cache_Module{
	public:
		Cache_Module(int size, int assoc, int block_size):size(size),assoc(assoc),block_size(block_size){}
		Cache_Module()= default;		
		virtual bool read(unsigned long &address){}
		virtual Block write(unsigned long &address){}
		virtual void replace(unsigned long &address){}
		virtual Block update(unsigned long &address){}


		unsigned int cache_hits = 0;
		unsigned int cache_misses = 0;
		int size;
		int assoc;
		int block_size;
		
};

/*

Implement later 

class Full_Assoc_Module: public Cache_Module{
	public:
		Full_Assoc_Module(int size, int assoc, int block_size):Cache_Module(size,assoc,block_size){
			//No need to to initalize queue. Assume assoc = size / block_size so the number of sets is 1
		}
	private:
		std::queue<Block> cache;


};
*/

class Set_Assoc_Module: public Cache_Module{
	public:	
		Set_Assoc_Module(int size, int assoc, int block_size):Cache_Module(size,assoc,block_size){
			this->sets =  size / (assoc * block_size);
			cache = std::vector<std::queue<Block> >(sets);
		}
		bool read(unsigned long &address);
		virtual Block write(unsigned long &address);
		void replace(unsigned long &address);
		virtual Block update(unsigned long &address);
	private:
		std::vector<std::queue<Block> > cache;
		unsigned int sets;

};

class Direct_Map_Module:public Cache_Module{
	public:
		Direct_Map_Module(int size, int assoc, int block_size):Cache_Module(size,assoc,block_size){
			//Initialize size of cache here using the size and block size. Assoc is assumed to be 1
			num_slots = size / block_size;
			cache = std::vector<Block>(num_slots);			
		}
		
		bool read(unsigned long &address);
		Block write(unsigned long &address);
		void replace(unsigned long &address);
		virtual Block write(unsigned long &address);
	private:
		std::vector<Block> cache;
		int num_slots;

};

#endif

