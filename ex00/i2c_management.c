
#include "lib.h"

void	i2c_init(void)
{
	// define la clock frequency determine par le TWI bit rate	
	// SCL frequency = CPU clock frequency / (16 + 2 * TWBR * PrescalerValue)
	TWBR = 72;
	// set le prescaler  1	// laissez le prescaler a un
	// TWSR &= ~(1<<TWPS0);
	// TWSR &= ~(1<<TWPS1);
	TWSR = 0;

}

void	display_status_code(void)
{
	if (TWSR == 0x08)
		uart_printstr("A START condition has been transmitted\n\r");
	else if (TWSR == 0x10)
		uart_printstr("A repeated START condition has been transmitted\n\r");
	else if (TWSR == 0x18)
		uart_printstr("SLA+W has been transmitted; ACK has been received\n\r");
	else if (TWSR == 0x20)
		uart_printstr("SLA+W has been transmitted; NOT ACK has been received\n\r");
	else if (TWSR == 0x28)
		uart_printstr("Data byte has been transmitted; ACK has been received\n\r");
	else if (TWSR == 0x30)
		uart_printstr("Data byte has been transmitted; NOT ACK has been received\n\r");
	else if (TWSR == 0x38)
		uart_printstr("Abitration lost in SLA+W or data bytes\n\r");
	else
		uart_printstr("Unknown status\n\r");
}

// Demarre la transmission I2C entre le microcontrolleur et le capteur
void	i2c_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	while (!(TWCR & (1<<TWINT))) {} // wait for TWINT flag set
	// -> indicates that the START condition has been transmitted.

	display_status_code();

}

// Interrompt la communication entre le microcontrolleur et le capteur
void	i2c_stop(void)
{
	// TWCR |= (1<< TWSTO); // Twi stop condition bit
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

// ecrit le contenu du registre TWDR
// et l'envoie dans le capteur de temperature ?
void	i2c_write(unsigned char data)
{
	TWDR = data; // capteur en mode ecriture
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

// affiche le contenu du registre TWDR apres la mesure du capteur.
void	i2c_read(void)
{
	// mettre en mode master transmitter 
	
	// allume
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT))) {}
	// display_status_code();
}

// signed/ unsigned
void	print_hex_value(unsigned char c)
{
	static char	hex[] = "0123456789ABCDEF";
	uart_tx(hex[c / 16]);
	uart_tx(hex[c % 16]);
}
