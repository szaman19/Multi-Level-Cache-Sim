#ifndef CACHE_HPP
#define CACHE_HPP
#include "Cache_Module.hpp"
#include "Block.hpp"
#include "Instruction.hpp"
#include <vector>

class Cache{

	public :
		std::vector<Instruction> trace;
		Cache(int L1_Size, int L2_Size, int L1_Block, int L2_Block, int L1_Assoc, int L2_Assoc, std::vector<Instruction> &trace):
			L1_Size(L1_Size),L2_Size(L2_Size),L1_Block(L1_Block),L2_Block(L2_Block),L1_Assoc(L1_Assoc),L2_Assoc(L2_Assoc),trace(trace){
			
				if (L1_Assoc == 1){
					L1 = new Direct_Map_Module(L1_Size, L1_Assoc, L1_Block); 
				}else{

						L1 = new Set_Assoc_Module(L1_Size, L1_Assoc, L1_Block);

				}
				if (L2_Assoc == 1){
					L2 = new Direct_Map_Module(L2_Size, L2_Assoc, L2_Block); 
				}else{

						L2 = new Set_Assoc_Module(L2_Size, L2_Assoc, L2_Block);
				}

			}
		~Cache(){
			delete L1;
			delete L2;
		}
		void simulate();
	private:
		int L1_Size;
		int L2_Size;
		int L1_Block;
		int L2_Block;
		int L1_Assoc;
		int L2_Assoc;
		unsigned int L1_Miss;
		unsigned int L2_Miss;
		Cache_Module *L1;
		Cache_Module *L2;

};

#endif
