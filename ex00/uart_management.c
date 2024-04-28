
#include "lib.h"

// How to launch screen : screen PORT BAUDRATE : screen /dev/ttyUSB0 115200
// Setting the baudrate
void	uart_init(void)
{	
	// Write to lower byte
	long UBRR_Value = F_CPU / (SPEED * UART_BAUDRATE);
	UBRR0L = (uint8_t) (UBRR_Value & 0xFF);

	// Write to higher byte
	UBRR0H = (uint8_t) (UBRR_Value >> 8);

	// Enable the UART transmitter and receiver
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	// UCSR0B |= (1 << RXCIE0);
}

void	uart_tx(char c)
{
	// wait for data
	while (!(UCSR0A & (1 << UDRE0)))
	{
	}

	// return data
	UDR0 = c;
}

void	uart_printstr(const char *str)
{
	for (int i = 0; str[i]; ++i)
		uart_tx(str[i]);
}

/// Read
char	uart_rx(void)
{
	// wait for data
    while(!(UCSR0A & (1 << RXC0)))
	{
	}

    // return data
    return UDR0;
}


void	uart_printnbr(unsigned int nb)
{
    if (nb >= 10)
        uart_printnbr(nb / 10);
    uart_tx(nb % 10 + '0');
}

void uart_printhex(uint8_t n) {
	uart_printstr("0x");
	char c = n >> 4;
	uart_tx(c < 10 ? c + '0' : c - 10 + 'A');
	c = n & 0x0F;
	uart_tx(c < 10 ? c + '0' : c - 10 + 'A');
}

