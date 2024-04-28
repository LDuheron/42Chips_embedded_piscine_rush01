#include "lib.h"

void	init_segments(void)
{
	uint8_t slave_address = (0b0100 << 3)| 0b000;
	i2c_start(slave_address, 0);
	i2c_write(0x06);
	// Set Digit ouput by setting io04 to io07 as output for dp1, dp2, dp3, dp4
	i2c_write(0b00001111);
	// set all 7 segment display to 0
	i2c_write(0x00);
	i2c_stop();
}

void	display_segments(uint8_t dpindex, uint8_t n)
{
	static const uint8_t dpNumber[10] = {
		0b00111111, // 0
		0b00000110, // 1
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111, // 9
	};
	//clear
	uint8_t slave_address = (0b0100 << 3)| 0b000;
	i2c_start(slave_address, 0);
	i2c_write(0x02);
	i2c_write(0xff);
	i2c_write(0);
	i2c_stop();

	// 0x80 is the address of the first digit
	i2c_start(slave_address, 0);
	i2c_write(0x02);
	i2c_write(~(0x80 >> dpindex));
	i2c_write(dpNumber[n]);
	i2c_stop();
}

void	display_number(uint32_t n, uint8_t dpindex)
{
	uint8_t	digit = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		digit = n % 10;
		display_segments(dpindex + i, digit);
		n /= 10;
	}
}
