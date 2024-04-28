
#include "lib.h"

// mode 0
void	displayRV1(void)
{
	uint16_t	data;

	data = adc_read(RV1);
	display_number(data, 0);
}

// mode 1
void	displayLDR(void)
{
	uint16_t	data;

	data = adc_read(LDR);
	display_number(data, 0);
}

// mode 2
void	displayNTC(void)
{
	uint16_t	data;

	data = adc_read(NTC);
	display_number(data, 0);
}

// mode 3
void	displayTEMP(void)
{
	uint16_t	data;

	data = (adc_read(TEMP) * 25) / 314;
	display_number(data, 0);
}

// mode 6 : affiche la temperature ambiante en celsus 