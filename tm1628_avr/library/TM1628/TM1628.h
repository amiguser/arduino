#ifndef TM1628_h
#define TM1628_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TM16XXFonts.h"

//flags for turn on/off
#define ON true
#define OFF false

//Mnemonic for some symbol index in SYMBOL_FONT[]
#define LED7S_blank 0 


class TM1628 
{
  public:
	// init
	TM1628(byte _dio_pin, byte _clk_pin, byte _stb_pin, byte _max_dig=4);
	
	void begin(boolean active, byte intensity);
	void clear();
    void printInt(uint16_t val);
    void setInt(byte digit, byte val, byte point);
    void setSymbol(byte digit, byte val, byte point);
    void setDigits(byte d[10]);
    void setTime(int hour,int min,int sec);
    void sendData(byte addr, byte data);
	byte getButtons();
  protected:
    byte receive();
    
    void sendCommand(byte data);
    void send(byte data);
    
    byte _dio_pin;
    byte _clk_pin;
    byte _stb_pin;
    byte _max_digit;
//	byte buffer[];
//	byte seg_addr[];
};

#endif
