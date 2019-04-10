#include <Wire.h>
#include <PCA9634.h>

// I2C address 0x20: A0-A5->gnd; A6->Vcc

PCA9634 led( 0x40 );

void setup() {
  Wire.begin();

  led.begin(0,PCA9634_DMBLNK+PCA9634_OUTDRV+0x02);
}

void loop(){
 
 //Set Leds 0 and 1 to ON
 led.led_mode(0,PCA9634_LEDON);
 led.led_mode(1,PCA9634_LEDON);
 delay(1000);
 
 //Set Leds 0 and 1 to OFF
 led.led_mode(0,PCA9634_LEDOFF); 
 led.led_mode(1,PCA9634_LEDOFF); 
 delay(1000);

 //Set duty-cycle to 50% (128/256)
 led.set_global_pwm(128);  
 
 //Set blink frequency to 2 seconds (47+1/24)
 led.set_blink_freq(23);  

 //Set Leds 0 and 1 to Blink
 led.led_mode(1,PCA9634_LEDBLNK); 
 led.led_mode(0,PCA9634_LEDBLNK); 

 delay(8000);
 
}


