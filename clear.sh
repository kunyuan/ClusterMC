rm -r Beta*
rm -r Data
rm *.log
rm *.dat
rm callgrind*
rm *.pdf

if [ -n "$1" ]
then
  if [ $1 = "-d" ] || [ $1 = "--diag" ]; then
      rm -rf ./diagram/*
  elif [ $1 = "-a" ] || [ $1 = "--all" ]; then
      find . -name "*.so" -exec rm -r {} \;
      rm *.data
  fi
fi