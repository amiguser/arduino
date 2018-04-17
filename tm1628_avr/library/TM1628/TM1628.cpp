
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TM1628.h"
//byte _curpos = 0x00;
//byte buffer[14] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const byte seg_addr[8]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};//no bit of digital segments
//                       SG0  SG1  SG2  SG3  SG4  SG5  SG6  SG7  DVD  VCD  MP3  PLY  PAU  PBC  RET  DTS  DDD  CL1  CL2   //name   -|

TM1628::TM1628(byte _dio_pin, byte _clk_pin, byte _stb_pin) {
  this->_dio_pin = _dio_pin;
  this->_clk_pin = _clk_pin;
  this->_stb_pin = _stb_pin;

  pinMode(_dio_pin, OUTPUT);
  pinMode(_clk_pin, OUTPUT);
  pinMode(_stb_pin, OUTPUT);

  digitalWrite(_stb_pin, HIGH);
  digitalWrite(_clk_pin, HIGH);

  sendCommand(0x40);
  sendCommand(0x80);

  digitalWrite(_stb_pin, LOW);
  send(0xC0);
  clear();
  digitalWrite(_stb_pin, HIGH);
}
/**
* @param intensity = from 1 to 7
*/
void TM1628::begin(boolean active = true, byte intensity = 1) {
  sendCommand(0x80 | (active ? 8 : 0) | min(7, intensity));
}


void TM1628::setTime(int hour,int min,int sec) {

	if (hour >= 100) setInt(0, (hour/100),0);
	if (hour >= 10) setInt(1, (hour%100)/10,1);
//	setInt(2, (hour%100)%10);
	setInt(2, (min/10),0);
	setInt(3, (min%10),0);
//	setSeg(5, (sec/10));
//	setSeg(6, (sec%10));
//	update();
}

void TM1628::clear() {
	for (int i=0; i<4; i++)
		setSymbol(i,0,0);
}

byte TM1628::getButtons() {
  byte keys = 0;

  digitalWrite(_stb_pin, LOW);
  send(0x42);
  for (int i = 0; i < 5; i++) {
    keys |= receive() << i;
  }
  digitalWrite(_stb_pin, HIGH);

  return keys;
}

/*********** mid level  **********/
void TM1628::sendData(byte addr, byte data) {
  sendCommand(0x44);
  digitalWrite(_stb_pin, LOW);
  send(0xC0 | addr);
  send(data);
  digitalWrite(_stb_pin, HIGH);
}

void TM1628::sendCommand(byte data) {
  digitalWrite(_stb_pin, LOW);
  send(data);
  digitalWrite(_stb_pin, HIGH);
}

/**
* display decimal Integer value 
* @param uint16_t v - integer number tyo display
*/

void TM1628::printInt(uint16_t v){
 uint16_t v10 = 1000;
  if (v > 9999) {
 
  } else {
    for (uint8_t i = 0; i < 3; i++) {
      uint8_t k = v / v10;
      setInt(i, k, false);
      v = v % v10;
      v10 = v10 / 10;
    }
    setInt(3, v, false);
  }    
}

/**
* set digit with integer number from 0 to 0x0F(decimal 15) 
* @param digit - 0-3 position to display in, val - value to display, point - set or not dot segment
*/
void TM1628::setInt(byte digit, byte val, byte point){
    sendData(digit*2, NUMBER_FONT[val&0x0f] | (point * 0x80));
}
/**
* set digit with symbol from SYMBOL_FONT[] 
* @param digit - 0-3 position to display in, val - symbol to display, point - set or not dot segment
*/

void TM1628::setSymbol(byte digit, byte val, byte point){
    sendData(digit*2, SYMBOL_FONT[val] | (point * 0x80));
}


/************ low level **********/
void TM1628::send(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_clk_pin, LOW);
    digitalWrite(_dio_pin, data & 1 ? HIGH : LOW);
    data >>= 1;
    digitalWrite(_clk_pin, HIGH);
  }
}

byte TM1628::receive() {
  byte temp = 0;

  // Pull-up on
  pinMode(_dio_pin, INPUT);
  digitalWrite(_dio_pin, HIGH);

  for (int i = 0; i < 8; i++) {
    temp >>= 1;

    digitalWrite(_clk_pin, LOW);

    if (digitalRead(_dio_pin)) {
      temp |= 0x80;
    }

    digitalWrite(_clk_pin, HIGH);
  }

  // Pull-up off
  pinMode(_dio_pin, OUTPUT);
  digitalWrite(_dio_pin, LOW);

  return temp;
}
