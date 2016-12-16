// testdatabase.cpp : Defines the entry point for the console application.
//

#include "CoverageDatabase.h"


int main(int argc, char* argv[])
{
	CoverageDatabase *m_db ;
	bool rc ;

	m_db = new CoverageDatabase();

	// init the names of the most recent picktest tables for rdbms_main_linux.x64 for the rest of the sql statements.
    m_db->SetPicktestTables("") ;
/*
    vector<string> vNames;
    vNames.push_back("acl.c/acldrv");
    rc = m_db->getHitMatrixByRtn(vNames);

	vNames.clear() ;
	vNames.push_back("lrga3") ;
    rc = m_db->getHitMatrixByTst(vNames) ;
*/
	rc = m_db->getHitMatrix() ;

	delete m_db ;
	return 0;
}

