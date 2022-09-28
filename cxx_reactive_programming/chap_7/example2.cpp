// First.cpp
// g++ -I<PathToRxCpplibfoldersrc> First.cpp
#include "rx.hpp"
#include <iostream>
int main() {
//------------- Create an Observable.. a Stream of numbers
//------------- Range will produce a sequence from 1 to 12

auto values = rxcpp::observable<>::range(1, 12)
  .filter([](int v){ return v % 2 ==0 ;})
  .map([](int x) {return x*x;});

 values.subscribe(
		  [](int v){
		    printf("OnNext: %d\n", v);
		  },
		  [](){
		    printf("OnCompleted\n");
		  }

		  );
 

}
