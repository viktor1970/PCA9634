/* See the file "LICENSE" for the full license governing this code. */

#include "PCA9634.h"



PCA9634::PCA9634(uint8_t addr){
    _addr = addr;
}

void PCA9634::begin(uint8_t mode1, uint8_t mode2){
    // all leds default OFF; PWM set to 0
    write_reg( PCA9634_REG_MODE1, 0 );
    write_reg( PCA9634_REG_MODE2, mode2 ); 
	_reg0C=0;
}

uint8_t PCA9634::set_mode1(uint8_t mode1){
    return write_reg( PCA9634_REG_MODE1, mode1 );
}

uint8_t PCA9634::set_mode2(uint8_t mode2){
    return write_reg (PCA9634_REG_MODE2, mode2);
}

uint8_t PCA9634::set_pwm(uint8_t led, uint8_t duty_cycle){
    // limit led to a 3-bit unsigned value.
    return write_reg( PCA9634_REG_PWM0 + ( (uint8_t) (led & 0x7) ), duty_cycle );
}

uint8_t PCA9634::set_global_pwm(uint8_t duty_cycle){
    return write_reg( PCA9634_REG_GRPPWM, duty_cycle );
}
uint8_t PCA9634::set_blink_freq(uint8_t frequency){
    return write_reg( PCA9634_REG_GRPFREQ, frequency );
}


uint8_t PCA9634::led_mode(uint8_t led, uint8_t mode){
    if(led>7) return -1;
    if(led<4)
    { _reg0C&=~(0xFF<<(led*2));  _reg0C|=mode<<(led*2); return write_reg(0x0C, _reg0C); }
    else
    { _reg0C&=~(0xFF<<((led-4)*2));  _reg0C|=mode<<((led-4)*2); return write_reg(0x0D, _reg0C);}

}

uint8_t PCA9634::write_reg(uint8_t reg, uint8_t value){
    Wire.beginTransmission( _addr );
    Wire.write( reg );
    Wire.write( value );
    return Wire.endTransmission( );

}
