
#ifndef LIB_H
# define LIB_H

#include "avr/io.h"
#include "util/twi.h"
#include "avr/interrupt.h"

// CONFIG 
#define I2C_CPU_CLOCK_FREQ 100000
#define START 1
#define AHT20_ADDR 0x38
#define SLA_W (AHT20_ADDR << 1) // adresse du capteur en mode ecriture 
#define UART_BAUDRATE 115200
#define SPEED 16

// LEDS

#define LED0_ON (PORTB | (1<<PB0))
#define LED0_OFF (PORTB &= ~(1<<PB0))
#define LED1_ON (PORTB | (1<<PB1))
#define LED1_OFF (PORTB &= ~(1<<PB1))
#define LED2_ON (PORTB | (1<<PB2))
#define LED2_OFF (PORTB &= ~(1<<PB2))
#define LED3_ON (PORTB | (1<<PB4))
#define LED3_OFF (PORTB &= ~(1<<PB4))

// EXPANDER 

#define PCA955PW 0b0100000
#define CONFIGURE_PORT_OUT 0x06
#define PORT_OUT 0x02
#define WRITE_MODE 0
#define READ_MODE 1

// BOOL

#define false  0 
#define true 1 

typedef int bool ;

// uart_managmement.c
void	uart_init(void);
void	uart_tx(char c);
void	uart_printstr(const char *str);
char	uart_rx(void);

// ic2Management.c
void	i2c_init(void);
void	i2c_start(void);
void	i2c_stop(void);
void	i2c_write(unsigned char data);
void	i2c_read(void);
void	display_status_code(void);
void	print_hex_value(unsigned char c);


// timer_init.c
void	timer_init(void);

#endif