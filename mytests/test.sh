#!/bin/sh

# good = 0
# other = 1
# lexical = 2
# syntax = 3

if [ $# -eq 1 ]; then
    cd "../build"
    make -j10
    cd "../mytests"
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

tc=../build/src/tc

for i in "./good/"*
do
  $tc -X --parse $i
  res=$?
  if [ $res -eq 0 ]
  then
    echo "$GREEN OK, expected 0 $NC $i"
  else
    echo "$RED KO returned $res, expected 0 $NC: $i"
  fi
done

for i in "./other/"*
do
  $tc -X --parse $i
  res=$?
  if [ $res -eq 1 ]
  then
    echo "$GREEN OK, expected 1 $NC $i"
  else
    echo "$RED KO returned $res, expected 1 $NC: $i"
  fi
done

for i in "./lexical/"*
do
  $tc -X --parse $i
  res=$?
  if [ $res -eq 2 ]
  then
    echo
    echo "$GREEN OK, expected 2 $NC $i"
  else
    echo "$RED KO returned $res, expected 2 $NC: $i"
  fi
done

for i in "./syntax/"*
do
  $tc -X --parse $i
  res=$?
  if [ $res -eq 3 ]
  then
    echo
    echo "$GREEN OK, expected 3 $NC $i"
  else
    echo
    echo "$RED KO returned $res, expected 3 $NC: $i"
  fi
done