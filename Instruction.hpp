#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <string>

class Instruction {
	public:	
		unsigned long address;
		bool read;
	Instruction (std::string a, unsigned long address):read(a=="r"),address(address){}
};
#endif
