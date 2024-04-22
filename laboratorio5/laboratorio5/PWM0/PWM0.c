/*
 * PWM0.c
 *
 * Created: 4/18/2024 12:51:56 PM
 *  Author: Nico
 */ 
#include "PWM0.h"

void PWM0_Init() {
	DDRD |= (1 << PD6);         // Configurar PD6 (OC0A) como salida

	// Configuración del Timer0 para PWM
	TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01); // Modo PWM rápido, no inversor
	TCCR0B |= (1 << CS00);      // Sin prescaler
}

void PWM0_SetDutyCycle(uint8_t duty_cycle) {
	OCR0A = duty_cycle;
}