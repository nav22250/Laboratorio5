/*
 * PWM2.c
 *
 * Created: 4/15/2024 5:06:42 PM
 *  Author: Nico
 */ 
#include "PWM2.h"

void PWM2_init() {
	// Configuración del modo de funcionamiento PWM1 (Fast PWM, non-inverted mode)
	TCCR2A = 0;
	TCCR2B = 0;
	TCCR2A |=(1 << COM2A1); // Configura el modo de PWM y habilita la salida no invertida en OC2A (PB3)
	TCCR2A |= (1<<WGM21)|(1<<WGM20); //configuracion Fast PWM
	TCCR2B |=(1<<CS22)|(1<<CS21)|(1<<CS20);
	// Configuración del pin PB3 (OC2A) como salida
	DDRB |= (1 << DDB3);
}

void PWM2_set_duty_cycle(uint8_t duty_cycle) {
	// Se establece el ciclo de trabajo (OCR1A) del PWM1
	OCR2A = duty_cycle;
}