#include "lib.h"

#define PCF8563_ADDRESS 0x51
#define SECONDS_REGISTER 0x02
#define MINUTES_REGISTER 0x03
#define HOURS_REGISTER 0x04
#define DAY_REGISTER 0x05
#define MONTH_REGISTER 0x07
#define YEAR_REGISTER 0x08

#define WRITE 0
#define READ 1

enum time
{
	HOURS,
	MINUTES,
	SECONDS
};

enum date
{
	DAY,
	WEEKDAY,
	MONTH,
	YEAR
};

volatile uint8_t time[3] = {0};
volatile uint8_t date[4] = {0};


void rtc_read_time(void) {
	i2c_start(PCF8563_ADDRESS, WRITE);
	i2c_write(SECONDS_REGISTER);
	i2c_stop();
	
	i2c_start(PCF8563_ADDRESS, READ);
	time[SECONDS] = i2c_read(ACK);
	time[MINUTES] = i2c_read(ACK);
	time[HOURS] = i2c_read(ACK);
	date[DAY] = i2c_read(ACK);
	i2c_read(ACK);
	date[MONTH] = i2c_read(ACK);
	date[YEAR] = i2c_read(NACK);
	i2c_stop();

	time[SECONDS] = ((time[SECONDS] & 0x70) >> 4) * 10 + (time[SECONDS] & 0x0F);
	time[MINUTES] = ((time[MINUTES] & 0x70) >> 4) * 10 + (time[MINUTES] & 0x0F);
	time[HOURS] = (((time[HOURS] & 0b01110000) >> 4 )* 10) + (time[HOURS] & 0b00001111);

	date[DAY] = (((date[DAY] & 0b01110000) >> 4 )* 10) + (date[DAY] & 0b00001111);
	date[MONTH] = (((date[MONTH] & 0b00010000) >> 4 )* 10) + (date[MONTH] & 0b00001111);
	date[YEAR] = (((date[YEAR] & 0b11110000) >> 4 )* 10) + (date[YEAR] & 0b00001111);

}

void update_time(uint8_t updatedTime[3], uint8_t updatedDate[4])
{
	i2c_start(PCF8563_ADDRESS, WRITE);
	i2c_write(SECONDS_REGISTER);
	i2c_write(updatedTime[SECONDS]);
	i2c_write(updatedTime[MINUTES]);
	i2c_write(updatedTime[HOURS]);
	i2c_write(updatedDate[DAY]);
	i2c_write(0);
	i2c_write(updatedDate[MONTH]);
	i2c_write(updatedDate[YEAR]);
	i2c_stop();
}

