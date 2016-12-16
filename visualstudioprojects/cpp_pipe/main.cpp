#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h> 

using namespace std ;

int main()
{
  char buff[1024]={0};
  FILE * cvt;
  int status;
 /*launch converter and open a pipe through which the parent will write to it */
 cvt=popen("dir c:\\windows", "r");

 if (!cvt) {
	 printf("couldn't open a pipe; quitting\n");
	 exit(1);
 }

 //char buff[2048] ;
 int i = 0 ;
 for( i =0; i < 50; i++) {				// need to process to EOF
 	memset(buff, 0, sizeof(buff)) ;
 	fgets(buff, sizeof(buff), cvt) ;	// get the whole line including \n
 										// a null is automatically added
 	printf("%s", buff) ;

 }
 fflush(cvt); /*close pipe to converter and wait for it to exit*/
 status=pclose(cvt);
 /*check the exit status of pclose()*/
 //if (!WIFEXITED(status))
 //	printf("error on closing the pipe\n");
 return 0;
}
