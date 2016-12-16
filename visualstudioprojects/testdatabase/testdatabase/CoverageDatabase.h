#include <stdio.h>
#include <iostream>
#include <occi.h>

#include "common.h"

using namespace std;
using namespace oracle::occi;

/*  Interface to coverage database
 *
 *
 *  Modified :
 *
 *  ewang  04/16/2008  creation
 *
 */

//#include <iostream>
//#include <string>

#include <occi.h>

using namespace oracle::occi ;
using namespace std ;

class CoverageDatabase
{
  string user;
  string pass;
  string conn_string;

  string picktest_rtn_table ;
  string picktest_hit_table ;
  string picktest_tst_table ;
  string picktestTablePrefix ;
  string labelName ;

  Environment *env;
  Connection *conn;

  int get4ByteInt(unsigned char *buffer, int order);
  public:
  CoverageDatabase();
  int SetPicktestTables(string label) ;
  bool getHitMatrixByRtn(std::vector<std::string> changed_routines);
  bool getHitMatrixByTst(std::vector<std::string> test_names);
  bool getHitMatrix(void);
};