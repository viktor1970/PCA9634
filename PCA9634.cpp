/* See the file "LICENSE" for the full license governing this code. */

#include <Arduino.h>
#include "PCA9634.h"

PCA9634::PCA9634(uint8_t addr){
    _addr = addr;
}

void PCA9634::begin(uint8_t mode1, uint8_t mode2){
    // all leds default OFF; PWM set to 0
    write_reg(PCA9634_REG_MODE1,0);
    write_reg(PCA9634_REG_MODE2,mode2); 
	_reg0C=0;
	_reg0D=0;
	_mode1=mode1;
	_mode2=mode2;
}

uint8_t PCA9634::set_mode1(uint8_t mode1){
    return write_reg(PCA9634_REG_MODE1,mode1);
}

uint8_t PCA9634::set_mode2(uint8_t mode2){
    return write_reg (PCA9634_REG_MODE2,mode2);
}

uint8_t PCA9634::set_pwm(uint8_t led, uint8_t duty_cycle){
    if (led>7) return -1;
	return write_reg(PCA9634_REG_PWM0+led,duty_cycle);
}

uint8_t PCA9634::set_global_pwm(uint8_t duty_cycle){
    return write_reg(PCA9634_REG_GRPPWM, duty_cycle );
}

uint8_t PCA9634::set_blink_freq(uint8_t frequency){
    return write_reg(PCA9634_REG_GRPFREQ, frequency);
}

uint8_t PCA9634::getReg(){
    return _reg0C;
}

void PCA9634::swReset(){
    for(uint8_t n=0; n<8; n++) write_reg(PCA9634_REG_PWM0+n,0);
	write_reg(PCA9634_REG_GRPPWM,0);
    write_reg(PCA9634_REG_GRPFREQ,0);
    write_reg( PCA9634_REG_MODE1, _mode1);
    write_reg( PCA9634_REG_MODE2, _mode2); 

}


uint8_t PCA9634::led_mode(uint8_t led, uint8_t mode)
{
 if(led>7) return 255;
 switch(led)
 {
  case 0: {_reg0C &=0xFC; break;}
  case 1: {_reg0C &=0xF3; break;}
  case 2: {_reg0C &=0xCF; break;}
  case 3: {_reg0C &=0x3F; break;}
  case 4: {_reg0D &=0xFC; break;}
  case 5: {_reg0D &=0xF3; break;}
  case 6: {_reg0D &=0xCF; break;}
  case 7: {_reg0D &=0x3F; break;}
 }
 if(led<4)
  { _reg0C|=mode<<(led*2); write_reg(0x0C, _reg0C);}
  else
  { _reg0D|=mode<<(led*2); write_reg(0x0D, _reg0D);}
}

uint8_t PCA9634::write_reg(uint8_t reg, uint8_t value){
    Wire.beginTransmission( _addr );
    Wire.write( reg );
    Wire.write( value );
    return Wire.endTransmission( );

}
