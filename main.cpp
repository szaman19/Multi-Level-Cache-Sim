#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Instruction.hpp"
#include "Cache.hpp"

using namespace std;


int main(int arc, char *argv[]){


	ifstream trace;
	string line;
	string type;
	unsigned long address;
	

	trace.open(argv[1]);

	vector<Instruction> instructions;

	if (trace.is_open()){
		int counter = 0;
		while(getline(trace, line)){
			type = line[0];
			address = stoul(line.substr(2),nullptr,16);
			//icout << "Type: " << type << " Address:" << address <<'\n';
			Instruction temp (type, address);
			instructions.push_back(temp);
						
		}
	}

	int L1_Size = 1024;
	int L2_Size = 0;
	int L1_Block = 16;
	int L2_Block = 16;
	int L1_Assoc = 2;
	int L2_Assoc = 2; 

	Cache system (L1_Size, L2_Size, L1_Block, L2_Block, L1_Assoc, L2_Assoc, instructions);
	system.simulate();
	return 0;
}
