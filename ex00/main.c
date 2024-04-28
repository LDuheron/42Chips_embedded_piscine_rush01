
#include "lib.h"

volatile int currentMode = 0;

// 3 6 7 8

void	display_led(void)
{
	PORTB = currentMode & 0x01 ? LED0_ON : LED0_OFF;
	PORTB = currentMode & 0x02 ? LED1_ON : LED1_OFF;
	PORTB = currentMode & 0x04 ? LED2_ON : LED2_OFF;
	PORTB = currentMode & 0x08 ? LED3_ON : LED3_OFF;
}

void	switch_mode(void)
{
	switch (currentMode)
	{
		case 0:
			displayRV1();
			break;
		case 1:
			displayLDR();
			break;
		case 2:
			displayNTC();
			break;
		case 3:
			displayTEMP();
			break;
	}
}

// SW1 : go to next mode
// PAS DE MODE 5 ?  
ISR(PCINT0_vect)
{
	if (currentMode == 11)
		currentMode = 0;
	else
		currentMode++;
	display_led();
	uart_printnbr(currentMode);
	switch_mode();
}

// SW2 : go to previous mode
ISR(PCINT2_vect)
{
	if (currentMode == 0)
		currentMode = 11;
	else
		currentMode--;
	display_led();
	switch_mode();
}

int	main(void)
{
	adc_init();
	uart_init();
	i2c_init();
	timer_init();

	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB4);
	sei();
	while (1)
	{

	}

	return (0);
}
