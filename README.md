# Photuris

[Photuris E19 Flashlight Code][3].  See the [Photuris E19 website][1] for more
details, or [Photuris E19 Product][2] to buy!

## Folder Overview

* `arduino`: Contains arduino libraries.
* `bin`: Contains compiled binary (`*.o`, `*.hex`, etc.).
* `include`: Contains header interface files for lib files.
* `lib`: Contains libraries for the Photuris flashlight.
* `src`: Contains main `photuris.ino` code.
* `tools`: Contains avrdude and avr files.

## Linux Installation

#### Download using a programmer
1. Download Photuris project.
1. Modify `src/photuris.ino` to whatever you want the flashlight to do.
1. Modify the `Makefile` to match your programmer and port.
1. Run while having the board's `reset` pin conected to the USBasp's `reset` pin:

<pre>
$ make all
$ make fuse
$ make upload
</pre>

#### Download using bootloader
1. Download Photuris project.
1. Modify `src/photuris.ino` to whatever you want the flashlight to do.
1. Run with micro USB ID pin floating (NOT tied to ground):

<pre>
$ make all
$ make fuse
$ make bootload
</pre>

## Important Resources

* [ATmega168 Datasheet](http://www.atmel.com/Images/doc2545.pdf)
* [ATmega168 Arduino Pinout](http://arduino.cc/en/uploads/Hacking/Atmega168PinMap2.png)
* [AVR Fuse Calculator](http://www.engbedded.com/fusecalc)
* [Arduino](http://arduino.cc)
* [ArduinoPure](https://github.com/omnidan/ArduinoPure)
* [AVRDUDE Manual](http://www.nongnu.org/avrdude/user-manual/avrdude_4.html)
* [fischl USBasp](http://www.fischl.de/usbasp)
* [V-USB](http://obdev.at/products/vusb)
* [V-USB Bootloader](http://obdev.at/products/vusb/bootloadhid.html)
* [V-USB Bootloader Tutorial](http://www.workinprogress.ca/v-usb-tutorial-software-only-usb-for-mega-tiny)
* [CapSense](http://playground.arduino.cc//Main/CapacitiveSensor)

  [1]: http://albertgural.com/projects/2013-projects/photuris-e19   "Photuris E19 Project Page"
  [2]: http://ag-element.com/flashlight/photuris/photuris-e19       "Photuris E19 Product Page"
  [3]: https://github.com/agural/Photuris                           "Photuris E19 GitHub Code"

