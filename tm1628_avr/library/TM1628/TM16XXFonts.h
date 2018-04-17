/*
TM16XXFonts.h - Font definition for TM16XX.

Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)

Modified by amiguser 2018

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


The bits are displayed by mapping bellow
 -- 0 --
|       |
5       1
 -- 6 --
4       2
|       |
 -- 3 --  .7

*/

#ifndef TM16XXFonts_h
#define TM16XXFonts_h

// definition for standard hexadecimal numbers
const byte NUMBER_FONT[] = {
  0b00111111, // 0 0x3F
  0b00000110, // 1 0x06
  0b01011011, // 2 0x5B
  0b01001111, // 3 0x4F
  0b01100110, // 4 0x66
  0b01101101, // 5 0x4D
  0b01111101, // 6 0x7D
  0b00000111, // 7 0x07
  0b01111111, // 8 0x7F
  0b01101111, // 9 0x6F
  0b01110111, // A 0x77
  0b01111100, // B 0x7C
  0b00111001, // C 0x39
  0b01011110, // D 0x5E
  0b01111001, // E 0x79
  0b01110001  // F 0x71
};

// definition for the some symbols
const byte SYMBOL_FONT[] = {
  0b00000000, // blank
  0b00000001, // upper line
  0b10000000, // . point
  0b00000001, // upper line
  0b01000000, // - minus = middle line
  0b00001000, // _ lower line
};

#endif
