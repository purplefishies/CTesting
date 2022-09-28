// STLContainerStream.cpp
#include "rx.hpp"
#include <iostream>
#include <array>
int main() {

  auto ints = rxcpp::observable<>::create<int> ( 
						[](rxcpp::subscriber<int> s ) {
						  s.on_next(1);
						  s.on_next(4);
						  s.on_next(9);
						  s.on_completed();
						}
						 );

  // auto values = rxcpp::observable<>::iterate(ints);

  ints.subscribe(
		   [](int v){
		     printf("OnNext: %d\n", v);
		   },
		   [](){
		     printf("OnCompleted\n");
		   });
}
