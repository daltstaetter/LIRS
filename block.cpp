#ifndef RRIP_REPL_H_
#define RRIP_REPL_H_

#include "repl_policies.h"

using namespace std;

class block{
  //private
  
  //public
  public:
    int IRR;
    int Recency;
    
    uint64_t id;
    //default constructor for each block
    block():IRR(0), Recency(0), id(0){}
    //constructor for each block passing the id value
    block(uint64_t id_):IRR(0), Recency(0), id(id_){}
};


// Static RRIP
class LIRUReplPolicy : public ReplPolicy {
    protected:
        // add class member variables here
		uint64_t* array;
		uint32_t* candArray;
		
	    std::vector<block> LIR;
	    std::vector<block> HIR;
    
    	bool onePass;
		uint32_t numLines;
		uint32_t max;
		
    
    public:
		// constructor for the SRRIP replacement policy
		// initialize array, max
		explicit LIRUReplPolicy(uint32_t rpvMax, uint32_t _numLines) :numLines(_numLines), max(rpvMax){
			array = gm_calloc<uint64_t>(numLines);
			onePass = true;
		}
    
    // add member methods here, refer to repl_policies.h
		void update(uint32_t id, const MemReq* req) {
		  int i = 0;
		  while(i < LIR.size() || i < HIR.size()){
		    if(HIR.size()< i){
		      break;
		    }
		    //***************************************
		    //**   update LIR block
		    //**************************************
		    if(LIR.at(i).id == id){
		      //Update the block’s IRR by setting it equal to the stored recency value
		      LIR.at(i).IRR = LIR.at(i).Recency;
		      
		      //Update the recency of the block to 0 indicating its the most recent instruction called.
		      LIR.at(i).Recency = 0;
		      
		      //Increment all other cache entry’s recency by 1.
		      for(int k = 0; k<LIR.size()<k++){
		      	if(i==k){
		      		continue;
		      	}else{
		      		LIR.at(k).Recency = LIR.at(k).Recency + 1;	
		      	}
		        
		      }
		      for(int k = 0; k<HIR.size()<k++){
		        HIR.at(k).Recency = HIR.at(k).Recency + 1;
		      }
		    }
		    
		    
		    //***************************************
		    //**   update HIR block
		    //**************************************
		    if(HIR.at(i).id == id){
		      //Update the block’s IRR by setting it equal to the stored recency value.
		      HIR.at(i).IRR = HIR.at(i).Recency;
		      
		      //Update the recency of the block to 0 indicating its the most recent instruction called.
		      HIR.at(i).Recency = 0;
		      
		      //Compare the IRR of the current block to the blocks in the LIR set
		      int max = 0;
		      int index = 0;
		      block temp;
		      //Get max IRR value in the LIR block
		      for(int k = 0; k<LIR.size()<k++){
		        if(max < LIR.at(k).IRR){
		        	max = LIR.at(k).IRR;
		        	index = k;
		        }
		      }
		      
		      if(HIR.at(i).IRR <max){
		          temp = HIR.at(i);
		          HIR.at(i)= LIR.at(index);
		          LIR.at(index) = temp;
		      }
		      
		      //Increment all other cache entry’s recency by 1.
		      for(int k = 0; k<LIR.size()<k++){
		        LIR.at(k).Recency = LIR.at(k).Recency + 1;
		      }
		      for(int k = 0; k<HIR.size()<k++){
		      	if(i==k){
		      		continue;
		      	}else{
		      		HIR.at(k).Recency = HIR.at(k).Recency + 1;
		      	}
		        
		      }
		    }
		  }
		  
			
		}

		void replaced(uint32_t id) {
			block tempLIR;
			tempLIR = new block(id);
			HIR.at(0) = tempLIR;
		}

		template <typename C> inline uint32_t rank(const MemReq* req, C cands) {
			//go through each candidate
			//auto key = cands.begin();
			uint32_t evictedID;
			if(onePass == true){
				//for the first miss put cand in LIR
				for (ci = cands.begin(); ci != cands.end(); ci.inc()) {
					block tempLIR;
					tempLIR = new block(*ci);
					
					if(ci == cands.end()-1){
						HIR.push_back(tempLIR);
					}else{
						LIR.push_back(tempLIR);
					}
				}
				onePass = false;
			}else{
				//Evict the HIR entry and place the current block in the HIR Set
				evictedID = HIR.at(0).id;
			}
			
			
			// uint32_t topMax = -1;
			// bool repeat = true;
			// auto ci = cands.begin();
			// while(repeat == true) {
				
			// 	for (ci = cands.begin(); ci != cands.end(); ci.inc()) {
			// 		//temp.inc();
			// 		if (array[*ci] == max) {
			// 			repeat = false;
			// 			topMax = *ci;
			// 		}
			// 		//cout << array[*ci] <<"se"<<endl;
			// 	}
			// 	//increment all entries
			// 	if (repeat == true) {
			// 		for (ci = cands.begin(); ci != cands.end(); ci.inc()) {
						
						
			// 				array[*ci] += 1;
						
			// 			//cout << array[*ci] << "incrementing" << endl;
			// 		}
			// 	}
				
			// }
			
			return evictedID;

		}
        DECL_RANK_BINDINGS;

		
};
#endif // RRIP_REPL_H_
