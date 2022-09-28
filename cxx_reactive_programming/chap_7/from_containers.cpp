// STLContainerStream.cpp
#include "rx.hpp"
#include <iostream>
#include <array>
int main() {
  std::array< int, 3 > a={{1, 2, 3}};
  auto values = rxcpp::observable<>::iterate(a);
  values.subscribe(
		   [](int v){
		     printf("OnNext: %d\n", v);
		   },
		   [](){
		     printf("OnCompleted\n");
		   });
}
