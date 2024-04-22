//*****************************************************************************
//Universidad del Valle de Guatemala
//IE2023 Programacionde Microcontroladores
//Author : Nicole Navas
//Proyecto: laboratorio 5: PWM y librerías
//IDescripcion: codigo para mover dos servos y un LED RGB con ADC y PWM
//Hardware: ATMega328P
//Created: 4/15/2024 09:12:15 PM
//Actualizado:
//*****************************************************************************
// Encabezado
//*****************************************************************************

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PWM1/PWM1.h"
#include "PWM2/PWM2.h"
#include "PWM0/PWM0.h"

uint8_t vADC = 0; //inicar contador del ADC
volatile uint8_t canal = 6; //variable para lectura del canal
volatile uint16_t pwm_counter = 0;
volatile uint16_t pwm_value = 0;

void setup() {

	DDRC &= ~((1 << DDC5)|(1 << DDC4)); // Configurar PC5 como entradas
	DDRD |=(1<<DDD6);

	DDRB |= (1 << DDB1)|(1 << DDB3); //Configurar PB1(0C1A) y PB3(OC2A) como salidas
	
	CLKPR = 0;
	CLKPR |= (1<<CLKPCE);

	sei(); // Habilitar interrupciones
}

ISR(ADC_vect){

	ADCSRA |= (1<<ADIF);

	switch (canal)
	{
		case 4:
		ADMUX &= ~((1<<MUX2));
		ADMUX |= (1<<MUX2);
		
		vADC = ADCH;
		PWM0_SetDutyCycle(vADC);
		canal = 5;
		
		break;

		case 5:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1<<MUX2)|(1<<MUX0);
		
		vADC = ADCH;
		PWM2_set_duty_cycle(vADC);
		canal =6;
		
		break;

		case 6:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1 << MUX2) | (1 << MUX1);
		
		vADC = ADCH;
		PWM1_set_duty_cycle(vADC);
		
		canal = 4;

		break;

		default:
		ADMUX &= ~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
		ADMUX |= (1 << MUX2) | (1 << MUX1);
		vADC = ADCH;
		PWM1_set_duty_cycle(vADC);
		vADC = ADCH;
		PWM2_set_duty_cycle(vADC);
	}

}

void Timer0_Init() {
	TCCR0A |= (1 << WGM01);    // Modo de comparación CTC
	TCCR0B |= (1 << CS01);      // Prescaler de 8
	OCR0A = 195;              // Valor de comparación para obtener interrupción cada 1ms
	TIMSK0 |= (1 << OCIE0A);    // Habilitar interrupción por comparación A
}

ISR(TIMER0_COMPA_vect) {
	static uint8_t duty_cycle = 0;
	static uint8_t increasing = 1;

	// Incrementar o decrementar el ciclo de trabajo
	if (increasing) {
		duty_cycle++;
		if (duty_cycle == 255) increasing = 0;
		} else {
		duty_cycle--;
		if (duty_cycle == 0) increasing = 1;
	}

	// Actualizar el valor del PWM
	
	PWM0_SetDutyCycle(duty_cycle);
}

void initADC(void){
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // referencia AVCC = 5V
	ADMUX |= (1 << MUX2) | (1 << MUX1);// canal ADC6
	ADMUX |= (1 << ADLAR);

	ADCSRA = 0;
	ADCSRA |= (1<<ADIE); // habilitar interrupción del ADC
	ADCSRA |= (1<<ADEN); // habilitar ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // habilitación de prescaler
}

int main(void)
{
	cli();
	setup();
	initADC();
	PWM1_init();
	PWM2_init();
	PWM0_Init();
	sei();

	while(1)
	{
		ADCSRA |= (1<<ADSC);
	}

	return 0; //retorno
}
