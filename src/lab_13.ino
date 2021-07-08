#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
volatile bool interruptOccured = false; //must be declared volatile if used inside an isr.
volatile bool interruptEnabled = true;
u_int16_t interruptNumber = 0;
  // defaults to HIGH

void isr() {
  // your interrupt handler code here
  interruptOccured = true;
}
 // D6 will now generate an interrupt on the falling edge and will run the code in the isr

// setup() runs once, when the device is first turned on.
void setup() {
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);

  display.setup();
	display.clearDisplay();
	display.display();
  attachInterrupt(D6, isr, FALLING);
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  if(digitalRead(D7) == 0){
    if(interruptEnabled){
       // enables interrupt handling
      noInterrupts(); 
      interruptEnabled = false;
    } else{
      interrupts();
      interruptEnabled = true;
    }
    delay(1000);
  }
  if(interruptOccured){
    interruptNumber = 1 + interruptNumber;
    interruptOccured = false;
  }
    display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
    display.println(interruptNumber);
		display.display();
    
  // The core of your code will likely live here.

}