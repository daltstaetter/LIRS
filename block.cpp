#include <iostream>
#include <climits>

using namespace std;

class block{
  // private
  
  // public
  public:
    int IRR;
    int Recency;
    int value;
      
    // status
    // bool HIR;
    // bool LIR;
    
    block()
    {	// Simulates setting initial value to infinity
	IRR = INT_MAX;
	Recency = INT_MAX;
	value = 0;

    }	
};
