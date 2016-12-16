#!/bin/bash
#
# source will bring the external function into current shell environment
#
# then simply invoke function needed
#
# this can be used to build shared component in shell
#

# bring in external functions
source ./functions.sh

# invoke the function
hello

exit 0 ;
