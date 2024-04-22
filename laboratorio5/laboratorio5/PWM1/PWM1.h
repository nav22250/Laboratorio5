/*
 * PWM1.h
 *
 *  Author: Nico
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <stdint.h>
#include <avr/io.h>

// Inicialización del PWM1
void PWM1init();

// Función para establecer el ciclo de trabajo del PWM1
void PWM1_set_duty_cycle(uint8_t duty_cycle);



#endif /* PWM1_H_ */