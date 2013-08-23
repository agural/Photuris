#!/usr/bin/env bash

if [ "$1" = "fuse" ]; then
  sudo make fuse
elif [ "$1" = "upload" ]; then
  make all
  sudo make upload
  make clean
elif [ "$1" = "bootload" ]; then
  make all
  sudo make bootload
  make clean
else
  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install gcc-avr avr-libc
  sudo apt-get install avrdude
  sudo apt-get install libusb-dev
fi

