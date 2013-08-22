#!/usr/bin/env bash

if [ "$1" = "fuse" ]; then
  make fuse
elif [ "$1" = "upload" ]; then
  make all
  sudo make upload
  make clean
else
  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install gcc-avr avr-libc
  sudo apt-get install avrdude
fi

