
#include "lib.h"

// mode 0
void	displayRV1(void)
{
	uint16_t	data;

	data = adc_read(RV1);
}

// mode 1
void	displayLDR(void)
{
	uint16_t	data;

	data = adc_read(LDR);
}

// mode 2
void	displayNTC(void)
{
	uint16_t	data;

	data = adc_read(NTC);
}

// mode 3
void	displayTEMP(void)
{
	uint16_t	data;

	data = adc_read(TEMP);
}

