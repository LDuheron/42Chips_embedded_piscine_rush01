
#include "lib.h"

#define SCL_CLOCK 100000L

void i2c_init(void) {
	// set the clock period
	TWBR =  ((F_CPU / SCL_CLOCK) - 16) / 2;
	// set prescale 0
	TWSR = 0;
	// enable i2c
	TWCR = (1 << TWEN);
}

void i2c_start(uint8_t addr, uint8_t directionBit) {
	// send start
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	// wait for start condition ack
	while ((TWCR & (1 << TWINT)) == 0) {}
	// check if start is received
	if (TW_STATUS != TW_START)
		return ;
	// set data with address / directionBit 1 = read 0 = write
	TWDR = (addr << 1) | directionBit;
	// sent data
	TWCR = (1 << TWINT) | (1 << TWEN);
	// wait the ack
	while ((TWCR & (1 << TWINT)) == 0) {}
}

void i2c_stop(void) {
	// send stop
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	TWCR &= ~(1 << TWEN);
}

void i2c_write(unsigned char data) {
	// Load data in tw data register
	TWDR = data;
	// clear twcr to start transmission
	TWCR = (1 << TWINT) | (1 << TWEN);
	//wait the end of transmission
	while ((TWCR & (1 << TWINT)) == 0) {}
}

uint8_t i2c_read(uint8_t ack) {
	// Enable data transmission with read direction bit
	TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0); // Enable ACK after reading
	// Wait for read to complete
	while (!(TWCR & (1 << TWINT)));
	// Read received data
	uint8_t received_data = TWDR;

	// uart_printhex(received_data);
	// uart_printStr(" ");
	// Return the read data
	return received_data;
}
