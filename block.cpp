#include <iostream>
#include <climits>

using namespace std;

class block{
  // private
  
  // public
  public:
    int IRR;     // Inter-Reference Recency, i.e. the number of unique instructions between two successive calls to same instruction
    int Recency; // The number of unique instructions have executed since the last call to this instruction
    // int value;
    
    block();  // constructor
    ~block(); // deconstructor
    // status
    // bool HIR;
    // bool LIR;
    
};


block::block(void)
{
    // Simulates setting initial value to infinity
    IRR = INT_MAX;
    Recency = INT_MAX;
}

block::~block(void)
{
    // Deconstructor
}
	
