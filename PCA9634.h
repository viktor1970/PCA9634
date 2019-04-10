/* See the file "LICENSE" for the full license governing this code. 
 * Vittorio Colzani 2019
 * 
 * */

#ifndef __pca9634__
#define __pca9634__

#define PCA9634_MODE1		0x00		// Mode register 1
#define PCA9634_MODE2		0x01		// Mode register 2
#define PCA9634_PWM			0x02		// brightness control LED0 (LED1=0X03, LED2=0x04 and so on)
#define PCA9634_GRPPWM		0x0A		// group duty cycle
#define PCA9634_GRPFREQ		0x0B		// group frequency
#define PCA9634_LEDOUT0		0x0C		// LED output state 0
#define PCA9634_LEDOUT1		0x0D		// LED output state 1

// LEDOUT0 and LEDOUT1 output state register
#define PCA9634_LEDOFF			0x00		// LED OFF 
#define PCA9634_LEDON			0x01		// LED ON
#define PCA9634_LEDPWM			0x02		// LED PWM (PWMx register)
#define PCA9634_LEDBLNK			0x03		// LED PWM GROUP

// MODE register 2 (MODE register 1 not yet implemented)
#define PCA9634_DMBLNK 			0x20		// Group control: blinking (default: dimming)
#define PCA9634_INVRT  			0x10		// Output logic state inverted (default: not inverted)
#define PCA9634_OUTDRV 			0x00		// Open-drain output (default: totem-pole output)

#define ADDRESS_HI							0x12
#define ADDRESS_LO							0x34

#include <Wire.h>

class PCA9634
{
    public:
        
        // addr: I2C address
        PCA9634(uint8_t addr);

        // Set mode1 (0x00, will be implemented in future)and mode2
        void begin(uint8_t mode1, uint8_t mode2);

		//Set mode 1
        uint8_t set_mode1(uint8_t mode1);
		//Set mode 1
        uint8_t set_mode2(uint8_t mode2);
		//Set individual pwm duty-cycle
        uint8_t set_pwm(uint8_t led, uint8_t duty_cycle);
		
		//Set global pwm duty-cycle (used when DMBLNK mode is set)
        uint8_t set_global_pwm(uint8_t duty_cycle);
		//Set global blink frequency (used when DMBLNK mode is set)
        uint8_t set_blink_freq(uint8_t frequency);

		//Reset all pwm/freq to 0; set mode 1 and mode 2 as begin
		void swReset(void);
		
		//set individual led mode
		uint8_t led_mode(uint8_t led, uint8_t mode);

        //set led mode WITHOUT apply it
		uint8_t set_led_global(uint8_t led, uint8_t mode);

		//Set led mode register with values defined in set_led_global
		uint8_t apply_led_global(void);
		
    private:
        uint8_t _addr;
		uint8_t _reg0C;
		uint8_t _reg0D;
		uint8_t _reg0Cg;
		uint8_t _reg0Dg;
		uint8_t _mode1;
		uint8_t _mode2;
        uint8_t write_reg(uint8_t reg, uint8_t value);     
		
};
#endif
