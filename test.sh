#!/bin/bash
_GETOPTS=":abcd"
OPTIND=1
while getopts "${_GETOPTS}" opt
do
  case $opt in
        a)
         echo do a stuff with ${FIRSTARG}
         ;;
        b)
         echo do b stuff with ${FIRSTARG}
         ;;
        c)
         echo do c stuff with ${FIRSTARG}
         ;;
        d)
         echo do d stuff with ${FIRSTARG}
         ;;
  esac
done