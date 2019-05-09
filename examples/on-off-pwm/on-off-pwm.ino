#include <Wire.h>
#include <PCA9634.h>

// I2C address 0x40: A0-A5->gnd; A6->Vcc

PCA9634 led( 0x40 );

void setup() {

  Wire.begin();

  led.begin(0,PCA9634_OUTDRV+0x02);
  
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

 //Set Led 0 duty-cycle to 100% (255+1/256)
 led.set_pwm(0,255);
 
 //Set Led 1 duty-cycle to 0% 
 led.set_pwm(1,0);

 //Set Leds 0 and 1 to PWM
 led.led_mode(0,PCA9634_LEDPWM);
 led.led_mode(1,PCA9634_LEDPWM);
 
 delay(1000);
 
 //Loop 
 for(int i=0; i<256; i++)
 {
  led.set_pwm(0,255-i);  	//Loop Led 0 from 255 to 0
  led.set_pwm(1,i);			//Loop Led 1 from 0 to 255
  delay(30);
  }

 delay(4000);
 
 }


