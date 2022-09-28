//////////
// First.cpp
// g++ -I<PathToRxCpplibfoldersrc> First.cpp
#include "rx.hpp"
#include <iostream>
int main() {
//------------- Create an Observable.. a Stream of numbers
//------------- Range will produce a sequence from 1 to 12
auto observable = rxcpp::observable<>::range(1, 12);
//------------ Subscribe (only OnNext and OnCompleted Lambda given
observable.subscribe(
		     [](int v){printf("OnNext: %d\n", v);},
		     [](){
		       printf("OnCompleted\n");
		     });
}
