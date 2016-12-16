#include "CoverageDatabase.h"
#include <bitset> 
#include <time.h>

using namespace oracle::occi ;
using namespace std ;
CoverageDatabase::CoverageDatabase()
{
  conn_string = "(DESCRIPTION=(ADDRESS=(PROTOCOL=tcp)(HOST=dbtest.us.oracle.com)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=dbtest.oracle.com)))";

  env =Environment::createEnvironment(Environment::DEFAULT);
  try {
	conn = env->createConnection("user", "password", conn_string);
  } catch (SQLException &e)
  {
	  cout << e.what() << endl ;
  }
}

/*
 * initialize class variables for the most recent code coverage labels of rdbms_main_linux.x64
 *    picktestTablePrefix
 *    labelName
 */
int CoverageDatabase::SetPicktestTables(string label)
{
	Statement *stmt;
	ResultSet *rs;

	try {
			string qstr = "select max(pck_table_prefix) from labels where branch = 'RDBMS_MAIN_LINUX.X64' and pck_status = 'Y'" ;
			stmt = conn->createStatement (qstr);

			rs = stmt->executeQuery();

			while(rs->next()){
			    picktestTablePrefix = rs->getString(1);
				picktest_rtn_table = picktestTablePrefix + "_rtn" ;
			    picktest_hit_table = picktestTablePrefix + "_hit" ;
				picktest_tst_table = picktestTablePrefix + "_tst" ;
			}

			cout << "picktest table prefix: " << picktestTablePrefix << endl ;

		    stmt->closeResultSet(rs) ;

			qstr = "select label from labels where pck_table_prefix = (select max(pck_table_prefix) from labels where branch = 'RDBMS_MAIN_LINUX.X64' and pck_status = 'Y')" ;
			stmt = conn->createStatement (qstr);

			rs = stmt->executeQuery();

			while(rs->next()){
			    labelName = rs->getString(1);
			}

			cout << "label name: " << labelName << endl;


    } catch (SQLException &e)
    {
	  cout << e.what() << endl ;
    }

	return 0 ;
}

bool CoverageDatabase::getHitMatrixByRtn(vector<string> changed_routines)
{
  Statement *stmt;
  ResultSet *rs;
  int test_id, hitcnt, hitblks;

  // use the following to get oracle RAW column
  Bytes rawdata ;
  unsigned char *mapdata ;

  for (int i=0; i<changed_routines.size(); i++)
  {
    try {

		string qstr = "select test_id, hitcnt, hitblks, hit_map  \
			   from " + picktest_hit_table + " h, "       \
			          + picktest_rtn_table + " r          \
			   where r.rname_with_ext =:1                 \
			     and r.routine_id = h.routine_id " ;
		stmt = conn->createStatement (qstr);
		stmt->setString(1, changed_routines[i]);

		rs = stmt->executeQuery();

		// fetch single row
		while (rs->next()) {
			test_id = rs->getInt(1);
			hitcnt = rs->getInt(2);
			hitblks = rs->getInt(3);
			rawdata = rs->getBytes(4);

//			bitset<8> *hit ; 
//			bitset<8> *hitmap[1000] ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{ hit = new bitset<8>(rawdata.byteAt(i % 8)) ;
//			  hitmap[i] = hit ; 
//			}

//			cout << "test id: " << test_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{
//				cout << hitmap[i]->to_string() ;
//			}
//			cout << endl ; 

	//		cout << "test id: " << test_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
		    // map data contains the raw bytes of the binary
			mapdata = new unsigned char [rawdata.length()] ;
			memset((void *)mapdata, 0, rawdata.length()) ;
			rawdata.getBytes(mapdata, rawdata.length()) ;
	//		for(int i = 0; i< rawdata.length(); i++)
	//		{
	//			cout << bitset<8>(mapdata[i]) ;
	//		}
	//		cout << endl ;

		} // of while()




	} catch (SQLException &e) {
      cout << e.what();
    }

  }
  
  return true;
}

bool CoverageDatabase::getHitMatrixByTst(vector<string> test_names)
{
  Statement *stmt;
  ResultSet *rs;
  int routine_id, hitcnt, hitblks;

  // use the following to get oracle RAW column
  Bytes rawdata ;
  unsigned char *mapdata ;

  for (int i=0; i< test_names.size(); i++)
  {
    try {

		string qstr = "select routine_id, hitcnt, hitblks, hit_map  \
			   from " + picktest_hit_table + " h, "       \
			          + picktest_tst_table + " t          \
			   where t.test_name =:1                 \
			     and t.test_id = h.test_id " ;
		stmt = conn->createStatement (qstr);
		stmt->setString(1, test_names[i]);

		rs = stmt->executeQuery();

		while (rs->next()) {
			routine_id = rs->getInt(1);
			hitcnt = rs->getInt(2);
			hitblks = rs->getInt(3);

			rawdata = rs->getBytes(4);

//			bitset<8> *hit ; 
//			bitset<8> *hitmap[1000] ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{ hit = new bitset<8>(rawdata.byteAt(i % 8)) ;
//			  hitmap[i] = hit ; 
//			}

//			cout << "routine id: " << routine_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{
//				cout << hitmap[i]->to_string() ;
//			}
//			cout << endl ;

//			cout << "routine id: " << routine_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
			mapdata = new unsigned char [rawdata.length()] ;
			memset((void *)mapdata, 0, rawdata.length()) ;
			rawdata.getBytes(mapdata, rawdata.length()) ;
//            cout << endl ;

		} // of while()
	} catch (SQLException &e) {
      cout << e.what();
    }

  }
  
  return true;
}


/*
 * get the complete hit matrix for the label
 */
bool CoverageDatabase::getHitMatrix(void)
{
  Statement *stmt;
  ResultSet *rs;
  int test_id, routine_id, hitcnt, hitblks;
  time_t startTime ;

  // use the following to get oracle RAW column
  Bytes rawdata ;
  unsigned char *mapdata ;

  try {

	    startTime = time(NULL) ;

		string qstr = "select test_id, routine_id, hitcnt, hitblks, hit_map  \
			   from " + picktest_hit_table + " h         \
			   order by test_id, routine_id" ;
		stmt = conn->createStatement (qstr);
		rs = stmt->executeQuery();
		int rows = 0 ;
		while (rs->next()) {
			test_id = rs->getInt(1);
			routine_id = rs->getInt(2);
			hitcnt = rs->getInt(3);
			hitblks = rs->getInt(4);

			rawdata = rs->getBytes(5);

//			bitset<8> *hit ; 
//			bitset<8> *hitmap[1000] ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{ hit = new bitset<8>(rawdata.byteAt(i % 8)) ;
//			  hitmap[i] = hit ; 
//			}

//			cout << "routine id: " << routine_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
//			for(int i = 0; i< rawdata.length(); i++)
//			{
//				cout << hitmap[i]->to_string() ;
//			}
//			cout << endl ;

//			cout << "routine id: " << routine_id << " hit blocks: " << hitblks << " hitmap length: " << rawdata.length() << " hitmap " ;
			mapdata = new unsigned char [rawdata.length()] ;
			memset((void *)mapdata, 0, rawdata.length()) ;
			rawdata.getBytes(mapdata, rawdata.length()) ;
			rows++ ;

//            cout << endl ;
			if (rows > 1000) break ;

		} // of while()
	} catch (SQLException &e) {
      cout << e.what();
    }

    cout << "elapsed time: " << time(NULL) - startTime << endl ;



  
  return true;
}

// from java implementation
int CoverageDatabase::get4ByteInt (unsigned char *buffer, int order)
{
  if (order == 0 ) //LITTLE_ENDIAN
  {
    return ((buffer[0] & 0xff)
                + ((buffer[1] & 0xff) << 8)
                + ((buffer[2] & 0xff) << 16)
                + (buffer[3] << 24));
  }

  return (int) ((buffer[0] << 24)
                  + ((buffer[1] & 0xff) << 16)
                  + ((buffer[2] & 0xff) << 8)
                  + (buffer[3] & 0xff));
}
