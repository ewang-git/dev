#!/bin/bash
#
# starts two background (using &) subshell processes, enclosed between ()
# parent shell process waits for both to completes
#
# require bash version 4.2 and above(oel 7). version 4.1 in oel6 does not work.
#
echo "Before starting subshell"
echo "parement process id: $$"


( count=1
  echo "process 1 begin $count"
  while [ $count -le 99 ]
  do
#      echo "$count"
#      sleep 1
      (( count++ ))
  done
  echo "process 1 end $count"
) &
echo "process 1 id: $!"

( count=1000
  echo "process 2 begin $count"
  while [ $count -le 1099 ]
  do
#      echo "$count"
#      sleep 1
      (( count++ ))
  done
  echo "process 2 end $count"
) &
echo "process 2 id: $!"s

wait
echo "Finished"
