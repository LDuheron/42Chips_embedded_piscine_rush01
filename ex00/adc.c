#include "./lib.h"

void adc_init() {
	// Configure voltage reference to AVCC
	ADMUX |= (1 << REFS0);  // Set REFS0 bit to 1 for AVCC
	ADMUX &= ~(1 << REFS1); // Set REFS1 bit to 0 for AVCC (already 0 by default)

	// Configure resolution to 10 bits
	ADMUX &= ~(1 << ADLAR); 

	// Enable ADC, set frequency prescaler (divide by 64)
	ADCSRA |= (1 << ADEN);   // Enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // Divide frequency by 64
	ADCSRA &= ~(1 << ADPS0); // Divide frequency by 64

	// Allow ADC to stabilize
	_delay_ms(10);
}


uint16_t adc_read(adc_channel channel) {

	if (channel == RV1) {
		ADMUX &= ~(1 << MUX0);
		ADMUX &= ~(1 << MUX1);
		ADMUX &= ~(1 << MUX2);
		ADMUX &= ~(1 << MUX3);
	} else if (channel == LDR) {
		ADMUX |= (1 << MUX0);
		ADMUX &= ~(1 << MUX1);
		ADMUX &= ~(1 << MUX2);
		ADMUX &= ~(1 << MUX3);
	} else if (channel == NTC) {
		ADMUX &= ~(1 << MUX0);
		ADMUX |= (1 << MUX1);
		ADMUX &= ~(1 << MUX2);
		ADMUX &= ~(1 << MUX3);
	} else if (channel == TEMP) {
		ADMUX &= ~(1 << MUX0);
		ADMUX &= ~(1 << MUX1);
		ADMUX &= ~(1 << MUX2);
		ADMUX |= (1 << MUX3);
	}
	// Start ADC conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	
	// Return ADC result (10-bit resolution)
	return ADC;
}
