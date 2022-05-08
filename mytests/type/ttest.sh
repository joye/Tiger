#!/bin/bash

RED='\033[0;31m'
BLACK='\e[30m'
WHITE='\e[97m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
MAGENTA='\033[0;95m'
F_MAGENTA='\e[45m'
F_NC='\e[49m'
BOLD='\e[1m'
NB='\e[21m'
NC='\033[0m'

tc=../../build/src/tc

pm=(0 5 5 4 5 0 0)
p=("" "-T" "-T" "-T" "-T" "-T" "-H")
files=("int-plus-string.tig" "int-plus-string2.tig" "assign-loop-var.tig" "unknowns.tig" "bad-if.tig" "mutuals.tig" "mutualsH.tig")

k=$((${#p[@]} - 1))

echo -e "$RED @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ $NC"

for j in $(seq 0 $k)
do
  i=${files[j]}
  $tc ${p[j]} "$i" 2> "actual/$i.out" 1> /dev/null
  $tc ${p[j]} "$i" 1>> "actual/$i.out" 2> /dev/null
  res=$?
  diff "actual/$i.out" "outs/$i.out" > /dev/null
  echo -e "${F_MAGENTA}${BLACK}${BOLD}*** FILE : ${WHITE}${i}${BLACK} ***${NB}-------------------------------------------------------------------"
  echo -e "${F_NC}${BLUE}"
  diff -y -W 150 "actual/$i.out" "outs/$i.out"
  echo -e "$NC"
  echo -e "exit code : $GREEN $res $RED ${pm[j]} $NC"
done
