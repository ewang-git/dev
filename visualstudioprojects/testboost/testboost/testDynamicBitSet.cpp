
#include "stdafx.h"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

int testDynamicBitSet(int i) {

  // example 1	
  boost::dynamic_bitset<> y(i); // all 0's by default

  for (boost::dynamic_bitset<>::size_type i = 0; i < y.size(); ++i){
  	if (i % 2) {   // set bit 1, 3, etc ...
  		y[i] = 1 ;
  	} 
    std::cout << y[i];
  }
  std::cout << "\n";
  std::cout << y << "\n"; 
  	
  //example 2	
  const boost::dynamic_bitset<> mask(12, 2730ul);
  std::cout << "mask = " << mask << std::endl;

  boost::dynamic_bitset<> x(12);

  std::cout << "Enter a 12-bit bitset in binary: " << std::flush;
  if (std::cin >> x) {
    std::cout << "input number:     " << x << std::endl;
    std::cout << "As unsigned long: " << x.to_ulong() << std::endl;
    std::cout << "And with mask:    " << (x & mask) << std::endl;
    std::cout << "Or with mask:     " << (x | mask) << std::endl;
    std::cout << "Shifted left:     " << (x << 1) << std::endl;
    std::cout << "Shifted right:    " << (x >> 1) << std::endl;
  }

  // example 3
  const boost::dynamic_bitset<> b0(2, 0ul);
  std::cout << "bits(0) = " << b0 << std::endl;

  const boost::dynamic_bitset<> b1(2, 1ul);
  std::cout << "bits(1) = " << b1 << std::endl;

  const boost::dynamic_bitset<> b2(2, 2ul);
  std::cout << "bits(2) = " << b2 << std::endl;

  const boost::dynamic_bitset<> b3(2, 3ul);
  std::cout << "bits(3) = " << b3 << std::endl;
  
  
  return EXIT_SUCCESS;
}
