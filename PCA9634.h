/* See the file "LICENSE" for the full license governing this code. 
 * Vittorio Colzani 2019
 * 
 * */

#ifndef __pca9634__
#define __pca9634__


#define PCA9634_REG_MODE1		0x00		// Mode register 1
#define PCA9634_REG_MODE2		0x01		// Mode register 2
#define PCA9634_REG_PWM0		0x02		// brightness control LED0
#define PCA9634_REG_PWM1		0x03		// brightness control LED1
#define PCA9634_REG_PWM2		0x04		// brightness control LED2
#define PCA9634_REG_PWM3		0x05		// brightness control LED3
#define PCA9634_REG_PWM4		0x06		// brightness control LED4
#define PCA9634_REG_PWM5		0x07		// brightness control LED5
#define PCA9634_REG_PWM6		0x08		// brightness control LED6
#define PCA9634_REG_PWM7		0x09		// brightness control LED7
#define PCA9634_REG_GRPPWM		0x0A		// group duty cycle
#define PCA9634_REG_GRPFREQ		0x0B		// group frequency
#define PCA9634_REG_LEDOUT0		0x0C		// LED output state 0
#define PCA9634_REG_LEDOUT1		0x0D		// LED output state 1

// LEDOUT0 and LEDOUT1 output state register
#define PCA9634_LEDOFF			0x00		// LED OFF 
#define PCA9634_LEDON			0x55		// LED ON
#define PCA9634_LEDPWM			0xAA		// LED PWM (PWMx register)
#define PCA9634_LEDBLNK		0xFF		// LED PWM GROUP

// MODE register 2 (MODE register 1 not yet implemented)
#define PCA9634_DMBLNK 			0x20		// Group contro: blinking (default: dimming)
#define PCA9634_INVRT  			0x10		// Output logic state inverted (default: not inverted)
#define PCA9634_OUTDRV 			0x00		// Open-drein outout (default: totem-pole output)

#define ADDRESS_HI							0x12
#define ADDRESS_LO							0x34

#include <Wire.h>

class PCA9634
{
    public:
        
        // i2c chip address
        PCA9634(uint8_t addr);

        // sets up pca9634 and turns all leds off
        void begin(uint8_t mode1, uint8_t mode2);

        // these 3 functions do writes directly to pca9634 registers
        // read that manual if you want to use them.
        uint8_t set_mode2(uint8_t mode2);
        uint8_t set_mode1(uint8_t mode1);
        uint8_t set_pwm(uint8_t led, uint8_t duty_cycle);
        uint8_t set_global_pwm(uint8_t duty_cycle);
        uint8_t set_blink_freq(uint8_t frequency);
		
		//set individual led mode
		uint8_t led_mode(uint8_t led, uint8_t mode);

    private:
        uint8_t _addr;
		uint8_t _reg0C;
        uint8_t write_reg(uint8_t reg, uint8_t value);     
};
#endif
