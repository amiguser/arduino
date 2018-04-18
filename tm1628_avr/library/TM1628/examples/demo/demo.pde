// Read buttons and display key code
// When keypressed there is number represents keycode(s)
// Arduino connect:
// digital pin 8 -> DIO, 9 -> CLK, 7 -> STB
// Display-keyboard module by amiguser

#include <TM1628.h>
// define - data pin 8, clock pin 9 and strobe pin 7, 4-digit display
TM1628 display(8, 9, 7, 4);

byte d[10];

void setup() {
  display.begin(ON, 2);
}
uint8_t k=0;
void loop() {     
  for(byte i=0;i<16;i++){
    display.setInt(i&0x03, i , 0);
    delay(200);
  }
  delay(1000);  
  for(k=0; k<4; k++) 
  {
  for(byte j=0; j<4;j++)
    d[j]=SYMBOL_FONT[1];
  display.setDigits(d);
  delay(100);
  for(byte j=0; j<4;j++)
    d[j]=SYMBOL_FONT[4];
  display.setDigits(d);
  delay(100);
  for(byte j=0; j<4;j++)
    d[j]=SYMBOL_FONT[5];
  display.setDigits(d);
  delay(200);
  }
  for (k=0; k<4; k++){
  for(byte l=0; l<6; l++){
    byte data=0;
    data|=(1<<l);
    for(byte j=0; j<4;j++)
      d[j]=data;
      display.setDigits(d);
      delay(100);
  }
  }
  
  display.clear();
  
}
