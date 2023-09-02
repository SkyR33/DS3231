
#include "I2C.h" 
#include "DS3231.h"


void RTCinit()
{
	I2Cinit();
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(CONTROL);
	I2Cwrite(0b00000000);	//Oscillator ON, 1 Hz output pin
	I2Cstop();
}

void RTCwriteTime(unsigned char hours, unsigned char minutes, unsigned char seconds)
{
	// Se asegura de que los valores sean válidos antes de configurar la hora
	if (((hours>=0) && (hours<24)) && ((minutes>=0) && (minutes<60)) && ((seconds>=0) && (seconds<60))){
		I2Cstart();
		I2Cwrite(DS3231_WRITE_ADDRESS);
		I2Cwrite(TIME);
		I2Cwrite(((seconds/10)<<4) | (seconds%10));
		I2Cwrite(((minutes/10)<<4) | (minutes%10));
		I2Cwrite(((hours/10)<<4) | (hours%10));
		I2Cstop();
	}
}

void RTCwriteDate(unsigned char day, unsigned char month, unsigned char year)
{
	// Se asegura de que los valores sean válidos antes de configurar la fecha
	if (((day >= 1) && (day <= 31)) && ((month >= 1) && (month <= 12)) && ((year >= 0) && (year <= 99)))
	{
		
		I2Cstart();
		I2Cwrite(DS3231_WRITE_ADDRESS);
		I2Cwrite(REG_DAY);
		I2Cwrite(((day / 10) << 4) | (day % 10));
		I2Cwrite(((month / 10) << 4) | (month % 10));
		I2Cwrite(((year / 10) << 4) | (year % 10));
		I2Cstop();
	}
}

float RTCreadTemperature()
{
	unsigned char tempH, tempL;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_TEMP);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	tempH = I2CreadACK();
	tempL = I2CreadNACK();
	I2Cstop();
	
	return (float)(tempH+(tempL>>6)*0.25);
}

unsigned char RTCreadSeconds()
{
	unsigned char seconds;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_SEC);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	seconds = I2CreadACK();
	I2Cstop();
	
	seconds = ((seconds & 0x70) >> 4) * 10 + (seconds & 0x0F);
	
	return seconds;
}

unsigned char RTCreadMinutes()
{
	unsigned char minutes;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_MIN);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	minutes = I2CreadACK();
	I2Cstop();
	
	minutes = ((minutes & 0x70) >> 4) * 10 + (minutes & 0x0F);
	
	return minutes;
}

unsigned char RTCreadHours()
{
	unsigned char hours;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_HOUR);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	hours = I2CreadACK();
	I2Cstop();
	
	hours = ((hours & 0x30) >> 4) * 10 + (hours & 0x0F);
	
	return hours;
}

unsigned char RTCreadDay()
{
	unsigned char day;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_DAY);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	day = I2CreadACK();
	I2Cstop();
	
	day = ((day & 0x30) >> 4) * 10 + (day & 0x0F);
	
	return day;
}

unsigned char RTCreadMonth()
{
	unsigned char month;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_MONTH);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	month = I2CreadACK();
	I2Cstop();
	
	month = ((month & 0x10) >> 4) * 10 + (month & 0x0F);
	
	return month;
}

unsigned char RTCreadYear()
{
	unsigned char year;
	
	I2Cstart();
	I2Cwrite(DS3231_WRITE_ADDRESS);
	I2Cwrite(REG_YEAR);
	
	I2Cstart();
	I2Cwrite(DS3231_READ_ADDRESS);
	year = I2CreadACK();
	I2Cstop();
	
	year = ((year & 0xF0) >> 4) * 10 + (year & 0x0F);
	
	return year;
}