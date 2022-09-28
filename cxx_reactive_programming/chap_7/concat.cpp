// STLContainerStream.cpp
#include "rx.hpp"
#include <iostream>
#include <array>
#include <tuple>

int main() {

  auto values = rxcpp::observable<>::range(1);

  auto s1 = values.take(3).map( [](int prime) { 
    return 2*prime;
  });
  auto s2 = values.take(5).map( []( int prime) {
    return prime*prime;
  });
  auto o1 = rxcpp::observable<>::interval(std::chrono::milliseconds(2));
  auto o2 = rxcpp::observable<>::interval(std::chrono::milliseconds(3));

  auto vals2 = o1.combine_latest(o2);
  vals2.take(5)
    .subscribe(
	       [](std::tuple<int, int> v){
		 printf("OnNext: %d, %d\n", std::get<0>(v), std::get<1>(v));
	       },
	       [](){
		 printf("OnCompleted\n");
	       });


  // auto s3 = s1.combine_latest([=]( int v1, int v2 ) {
  //   return std::make_tuple(v1,v2);
  // });
  // s1.subscribe( 
  // 	       [](int v) {
  // 		 printf("Val :%d\n",v);
  // 	       },
  // 	       []() {
  // 		 printf("Done\n");
  // 	       }
  // 		);
  

  // auto values = rxcpp::observable<>::iterate(ints);

  // ints.subscribe(
  // 		   [](int v){
  // 		     printf("OnNext: %d\n", v);
  // 		   },
  // 		   [](){
  // 		     printf("OnCompleted\n");
  // 		   });
}
