/*
 * PWM2.h
 *
 * Created: 4/15/2024 5:06:24 PM
 *  Author: Nico
 */ 


#ifndef PWM2_H_
#define PWM2_H_

#include <stdint.h>
#include <avr/io.h>

// Inicialización del PWM1
void PWM2_init();

// Función para establecer el ciclo de trabajo del PWM1
void PWM2_set_duty_cycle(uint8_t duty_cycle);



#endif /* PWM2_H_ */