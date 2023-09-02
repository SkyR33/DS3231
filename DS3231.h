
#ifndef DS3231_H
#define DS3231_H

#define DS3231_ADDRESS			0b11010000
#define DS3231_WRITE_ADDRESS	0b11010000
#define DS3231_READ_ADDRESS		0b11010001

// Registros
#define TIME			0x00

// Registros individuales
#define REG_SEC			0x00
#define REG_MIN			0x01
#define REG_HOUR		0x02
#define REG_DAY			0x04
#define REG_MONTH		0x05
#define REG_YEAR		0x06
#define REG_TEMP		0x11

// Registros auxiliares
#define DATE			0x03
#define CONTROL			0x0E
#define STATUS			0x0F
#define AGING_OFFSET	0x10



// Inicializa RTC
void RTCinit();

// Setear tiempo (horas, minutos, segundos)
void RTCwriteTime(unsigned char hours, unsigned char minutes, unsigned char seconds); 

// Setear fecha (dia del mes, mes, año)
void RTCwriteDate(unsigned char day, unsigned char month, unsigned char year);

// Leer temperatura
float RTCreadTemperature();

// Leer segundos
unsigned char RTCreadSeconds();

// Leer minutos
unsigned char RTCreadMinutes();

// Leer horas
unsigned char RTCreadHours();

// Leer dia del mes
unsigned char RTCreadDay();

// Leer mes
unsigned char RTCreadMonth();

// Leer año
unsigned char RTCreadYear();


#endif