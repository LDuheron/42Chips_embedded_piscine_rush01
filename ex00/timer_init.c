
#include "lib.h"

void	timer_init(void)
{
	DDRD &= ~(1<<PD2); // SW1 en input
	DDRD &= ~(1<<PD4); // SW2 en input

	PORTB &= ~(1<<PB0);
	// External Interrupt Mask Register : si INTO = 1 et SREG ==1, the external interrupt is enabled;
	EIMSK |= (1<<INT0);
	// External Interrupt Control Register A
	// Definie comment on controle l'interruption (sur le rising, falling, etc..)
	// The falling edge of INT0 generates an interrupt request 
	EICRA |= (1<<ISC01); // 1

	PCMSK2 |= (1<<PCINT20);
	PCICR |= (1<<PCIE2);
}
