#!/bin/sh

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

tc=../../build/src/tc

for i in *".tig"
do
  $tc -XoA $i > "actual/$i.out"
  diff "actual/$i.out" "outs/$i.out" > /dev/null
  res=$?
  if [ $res -ne 0 ]
  then
    echo "$i : $RED KO input differs from output $NC"
    echo "$BLUE"
    diff -y "actual/$i.out" "outs/$i.out"
    echo "$NC"

  else
    echo "$i : $GREEN OK input matches output$NC"
  fi
done
