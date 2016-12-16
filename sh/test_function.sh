#!/bin/bash
#
# description : test function() and printf() of bash
#
# note: requires bash version 4 and above
#

add_user()
{
  USER=$1
#  PASSWORD=$2
#  shift; shift;
#  COMMENTS=$@

  # Having shifted twice, the rest is now comments ... 
	printf "Adding user $USER ...\n"
#  echo "Adding user $USER ..."
#  echo useradd -c "$COMMENTS" $USER
#  echo passwd $USER $PASSWORD
#  echo "Added user $USER ($COMMENTS) with password $PASSWORD"

}
 
###
# Main body of script starts here
###

printf "intput argument count: $#\n"

if (( $# < 1 )); then
	printf "missing input parameter: username"
	exit 1 ;
elif (( $# > 1 )); then
	printf "too many input parameters. Need input parameter: username\n"
	exit 1 ;
else
	add_user $1
# add_user bob password comment

fi

