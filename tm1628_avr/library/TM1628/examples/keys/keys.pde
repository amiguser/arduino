// Read buttons and display key code
// When keypressed there is number represents keycode(s)
// Arduino connect:
// digital pin 8 -> DIO, 9 -> CLK, 7 -> STB
// Display-keyboard module by amiguser

#include <TM1628.h>
// define - data pin 8, clock pin 9 and strobe pin 7
TM1628 display(8, 9, 7);
int button;
void setup() {
  display.begin(ON, 2);
}
uint8_t k=0;
void loop() {     
  button = display.getButtons();
  if (button != 0){
    display.printInt(button);
    k=0;
  } else {
    display.setSymbol(k++, 4, 0);
    if (k>3) k=0;
  }
  delay(300);  
}
