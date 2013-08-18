Photuris
========

# Photuris E19 Flashlight Code

## Folder Overview
------------------
* `arduino`: Contains arduino libraries.
* `bin`: Contains compiled binary (`*.o`, `*.hex`, etc.).
* `include`: Contains header interface files for lib files.
* `lib`: Contains libraries for the Photuris flashlight.
* `src`: Contains main `photuris.ino` code.
* `tools`: Contains avrdude and avr files.

## \*nix Installation
---------------------

#### Download using USBasp
--------------------------
1. Download Photuris project.
1. Modify `src/photuris.ino` to whatever you want the flashlight to do.
1. Run while having the board's `reset` pin conected to the USBasp's `reset` pin:

    $ make photuris
    $ make upload

#### Download using bootloader
------------------------------
1. Download Photuris project.
1. Modify `src/photuris.ino` to whatever you want the flashlight to do.
1. Run with micro USB ID pin floating:

    $ make photuris
    $ make bootload

