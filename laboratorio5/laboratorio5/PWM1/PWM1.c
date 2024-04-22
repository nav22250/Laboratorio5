/*
 * PWM1.c
 *
 * Created: 4/15/2024 12:30:40 PM
 *  Author: Nico
 */ 
#include "PWM1.h"

void PWM1_init() {
	// Configuración del modo de funcionamiento PWM1 (Fast PWM, non-inverted mode)
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1A |=(1 << COM1A1); // Configura el modo de PWM y habilita la salida no invertida en OC1A (PB1)
	TCCR1A |= (1<<WGM12)|(1<<WGM11);
	TCCR1B |= (1<<WGM13)|(1<<CS12);

	DDRB |= (1 << DDB1);// Configuración del pin PB1 (OC1A) como salida

	ICR1 = 0x9B;
}

void PWM1_set_duty_cycle(uint8_t duty_cycle) {
	// Se establece el ciclo de trabajo (OCR1A) del PWM1
	OCR1A = duty_cycle;
}
