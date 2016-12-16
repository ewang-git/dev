//  simple_ls program  -------------------------------------------------------//

//  Copyright Jeff Garland and Beman Dawes, 2002

//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/filesystem for documentation.



#include "stdafx.h"

#include <iostream>

extern int testDynamicBitSet(int) ;
extern int testFileSystem(std::string) ;
extern int testBitMap(void) ;

int main( int argc, char* argv[] )
{
  std::string path = "c:\\me\\download" ;
  
  testFileSystem(path) ;
  testDynamicBitSet(50) ;
  testBitMap() ;


  return 0;
}