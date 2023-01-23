#include <iostream>
#include <map>
#include <vector>
#include <gtest/gtest.h>
#include <algorithm>

class Range
{
  public:
  int min, max;
  Range(int mn, int mx) : min(mn), max(mx) {} ;
  bool hasOverlap( Range &o ) {
    if ( this->min <= o.min && this->max >= o.min ) {
      return true;
    } else if ( o.min <= this->min && o.max >= this->min ) {
      return true;
    } else {
      return false;
    }
  }
  bool operator==( Range &oval )
  {
    return (this->min == oval.min &&  this->max == oval.max );
  }

  bool operator<( const Range &oval ) const 
  {
    return ( this->min < oval.min );
  }

  Range intersect( Range & oval )
  {
    if ( this->hasOverlap( oval) ) {
      return Range( std::max(this->min,oval.min), std::min(this->max,oval.max ));
    } else {
      return Range(-10000,-10000);
    }
  }


};
//               |-----------------A-------------|
//                 |---B---|      |-----C------|
//                                    |--D--|              |----E----| 
//
// A -> B -> C -> D -> E 
//--------
// A ^ B 
// A ^ C 
// A ^ D
// A ^ E 
// -------
// B ^ C
// B ^ D
// B ^ E 
// ------
// C ^ D 
// C ^ E
// ------
// D ^ E
// -------
// E doesn't have any ...


std::vector<Range> reduce_set( const std::vector<Range> &&input )
{
  std::vector<Range> retval;
  retval = input;
  bool intersections = true;

  std::vector<Range> keep = input;

  while ( intersections ) {
    std::set<Range> s;
    std::vector<Range> tmpvals;
    bool ints = false;
    for ( int i = 0; i < keep.size(); i ++ ) {
      bool overlaps = false;
      for ( int j = i+1; j < keep.size(); j ++ ) {
        if ( keep[i].hasOverlap(keep[j]) ) {
          s.insert( keep[i].intersect(keep[j]));
          overlaps= true;
        }
      }
      if ( !overlaps ) {
        s.insert(keep[i]);
      } else {
        ints = true;
      }
    }
    keep.clear();
    std::copy(s.begin(),s.end(),std::back_inserter(keep));
    if ( !ints ) {
      intersections = false;
      retval = keep;
      break;
    }    
  }

  return retval;
}

TEST(SampleTest,Initial)
{
  Range a(1,2);
  Range b(2,3);
  
  ASSERT_EQ( a.hasOverlap(b), true );

  Range c(3,4);
  ASSERT_EQ( c.hasOverlap(b), true );
  
  Range d(4,5);
  ASSERT_EQ( d.hasOverlap(b), false );
}

TEST(SampleTest,MinValue)
{
  Range a(1,2);
  Range b(2,3);
  
  auto v = a.intersect(b);
  ASSERT_EQ( v.min, 2 );
  ASSERT_EQ( v.max, 2 );// A point

  Range c(10,20);
  auto v2 = a.intersect(c);
  ASSERT_EQ( v2.min, -10000) ;
          
}

TEST(Reduce, ReduceValues)
{
  Range a(1,2);
  Range b(2,3);
  Range c(3,4);
  
  auto tmp = a.intersect(b).intersect(c);
  ASSERT_EQ( tmp.min , -10000);
  ASSERT_EQ( tmp.max , -10000 );

  Range d(1,4);
  Range e(2,4);
  Range f(3,4);

  tmp = d.intersect(e).intersect(f);

  ASSERT_EQ( tmp.min , 3);
  ASSERT_EQ( tmp.max , 4 );

  auto v = reduce_set( std::vector<Range>{d,e,f} );

  ASSERT_EQ( v.size(), 1 );
  ASSERT_EQ( v[0].min, 3 );
  ASSERT_EQ( v[0].max, 4 );
  
}

TEST(Reduce,ReduceSets)
{

  Range a(1,6);
  Range b(2,3);
  Range c(4,5);

  auto v = reduce_set( std::vector<Range>{a,b,c} );

  ASSERT_EQ( v.size(), 2 );
}


TEST(Reduce,ReduceSets2)
{

  Range a(1,6);
  Range b(2,3);
  Range c(4,5);
  Range d(7,8);
  
  auto v = reduce_set( std::vector<Range>{a,b,c,d} );

  ASSERT_EQ( v.size(), 3 );
}

int main(int argc, char *argv[])
{

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}
