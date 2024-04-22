/*
 * PWM0.h
 *
 * Created: 4/18/2024 12:51:41 PM
 *  Author: Nico
 */ 


#ifndef PWM0_H_
#define PWM0_H_

#include <avr/io.h>

void PWM0_Init();
void PWM0_SetDutyCycle(uint8_t duty_cycle);




#endif /* PWM0_H_ */