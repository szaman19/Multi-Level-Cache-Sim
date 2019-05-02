#include "Instruction.hpp"
#include "Block.hpp"
#include "Cache.hpp"
#include "stdio.h"
void Cache::simulate(){

	// printf("%d\n", this->trace.size());

	printf("L1_Size : %d\n", L1_Size);
	printf("Blocksize: %d\n", L1_Block);
	printf("Address: \t %x\n", trace[0].address);

	// unsigned int index = (trace[1].address % (L1_Size / 2) / L1_Block) ;

	// printf("index : \t %d\n", index);
	Block temp(trace[0].address,this->L1_Block, this->L1_Size, this->L1_Assoc);

	unsigned int reads = 0;
	unsigned int writes = 0;
	unsigned int L1_Read_Hits = 0;
	unsigned int L2_Read_Hits = 0;
	unsigned int L1_Write_Hits = 0;
	unsigned int L2_Write_Hits = 0;

	//Wrap this around a for
	for (int i = 0; i < 20; ++i){
		/* code */
		Instruction cur = trace[i]; 
		printf("%s\n", "-------------------------------------------------------");
		if(cur.read){
			printf("# %d : read %x \n", i,cur.address);
			printf("L1 read: %x \n", cur.address);

			// printf("%s\n", "Read Instruction");
			reads ++;
			//Check if in L1 cache
			//If in L1 Cache, then done
			//If not in L1 Cache, then check L2 Cache
				// If in L2 cache
				// Write to L1 Cache
				// Update L2 Cache with victim 
				// If not in L2 Cache
				// Write to L1 Cache
				// Update L2 Cache with victim 
			if(!L1->read(cur.address)){
				L1_Read_Hits++; //For cross-checking purposes
				printf("%s\n","Cache Hit");
			}else{
				Block victim = L1->write(cur.address);
				printf("%s\n","Cache Miss");
				if(L2_Size){

					if(L2->read(cur.address)){
						L2_Read_Hits++; //For cross-checking purposes
					}
					if(!victim.null){
						unsigned long victim_address = victim.index + (victim.tag * L1_Size / L1_Assoc);
						L2->write(victim_address);
					}
				}
			}
		}else{
			printf("# %d : write %x \n",i, cur.address);
			printf("L1 write: %x \n", cur.address);
			writes++;

			//Check if in L1 Cache
			// If in L1 Cache, then update state and done
			// If not in L1 Cache, Then Move on to L2 Cache
					// If in L2 Cache
					// Write to L1 Cache
					// Update L2 cache with victim 
					// If not in L2 Cache
					// Write to L1 Cache
					// Update L2 cache with victim

			if(!L1->read(cur.address)){
				printf("%s\n","L1 Cache Hit");
				Block victim = this->L1->write(cur.address);
	
			}else{
				printf("%s\n","L1 Cache Miss");
				Block victim = this->L1->write(cur.address);
				if(!victim.null){
					//L1 miss
					if(L2_Size){	
						if(L2->read(cur.address)){
							L2_Write_Hits++;
						}
						unsigned long victim_address = victim.index + (victim.tag * L1_Size / L1_Assoc);
						L2->write(victim_address);
					}
				}else{
					L1_Write_Hits++;
				}
			}
			
		}
	}
}