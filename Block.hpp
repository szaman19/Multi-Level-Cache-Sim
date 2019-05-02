#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Instruction.hpp"

class Block{
	public:
		bool valid;
		bool null;
		unsigned int tag;
		unsigned int index;
		unsigned long address;
		Block():valid(false),null(true),tag(0), index(0), address(0){}
		Block(unsigned long address, unsigned int offset, unsigned int table_size, unsigned int sets):
		valid(true),null(false), address(address){


			this->tag = ((address) / (table_size / sets));

			this->index = ((address) % (table_size / sets) / offset);
		}
};
#endif
