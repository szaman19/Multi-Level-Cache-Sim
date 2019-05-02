#include "Cache_Module.hpp"
#include "Instruction.hpp"
#include "Block.hpp"

bool Direct_Map_Module::read(unsigned long &address){
	return false;
}

Block  Direct_Map_Module::write(unsigned long &address){
	printf("%s\n", "CALLED");
	return Block();
}


void Direct_Map_Module::replace(unsigned long &address){

}

Block Direct_Map_Module::update(unsigned long &address){

}
