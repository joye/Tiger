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

pm=(0 0 4 4 0 4 0 5 4 0 5 4 0)
p=("-XbBA" "-bBA" "-bBA" "-bBA" "-XbBA" "-b" "-XbBA" "-T" "-XbBA" "-X --object-bindings-compute -BA" "--object-types-compute" "-X --object-bindings-compute -BA" "-X --object-bindings-compute -BA")
files=("me.tig" "meme.tig" "nome.tig" "tome.tig" "breaks-in-embedded-loops.tig" "break.tig" "box.tig" "box2.tig" "bad-member-bindings.tig" "bad-member-bindings2.tig" "self.tig")

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
