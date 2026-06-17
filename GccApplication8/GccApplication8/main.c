#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// LCD PINS
#define RS PC0
#define EN PC2

// OUTPUTS
#define RED_LED    PB0
#define GREEN_LED  PB1
#define SOUNDER    PB2
#define MOTOR      PB3

//LCD FUNCTIONS

void LCD_Command(unsigned char cmd)
{
	PORTC &= ~(1<<RS);

	PORTD = cmd;

	PORTC |= (1<<EN);
	_delay_ms(2);
	PORTC &= ~(1<<EN);

	_delay_ms(2);
}

void LCD_Char(unsigned char data)
{
	PORTC |= (1<<RS);

	PORTD = data;

	PORTC |= (1<<EN);
	_delay_ms(2);
	PORTC &= ~(1<<EN);

	_delay_ms(2);
}

void LCD_String(char *str)
{
	while(*str)
	{
		LCD_Char(*str);
		str++;
	}
}

void LCD_SetCursor(int row,int col)
{
	if(row==1)
	LCD_Command(0x80+col);

	else
	LCD_Command(0xC0+col);
}

void LCD_Init()
{
	DDRD = 0xFF;

	DDRC |= (1<<RS)|(1<<EN);

	_delay_ms(20);

	LCD_Command(0x38);
	LCD_Command(0x0C);
	LCD_Command(0x06);
	LCD_Command(0x01);
}

//ADC FUNCTIONS

void ADC_Init()
{
	ADMUX = (1<<REFS0);

	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

unsigned int ADC_Read(unsigned char ch)
{
	ADMUX = (ADMUX & 0xE0) | ch;

	ADCSRA |= (1<<ADSC);

	while(ADCSRA & (1<<ADSC));

	return ADC;
}

//MAIN PROGRAM

int main()
{
	int temp;
	int light;
	int gas;

	char buffer[10];

	// LCD Initialize
	LCD_Init();

	// ADC Initialize
	ADC_Init();

	// PORTB OUTPUTS
	DDRB = 0xFF;

	// Initially OFF
	PORTB = 0x00;

	// Welcome Screen
	LCD_SetCursor(1,0);
	LCD_String("SMART HOME");

	LCD_SetCursor(2,0);
	LCD_String("SYSTEM");

	_delay_ms(2000);

	LCD_Command(0x01);

	while(1)
	{
		//SENSOR READINGS

		// LM35 Temperature
		temp = (ADC_Read(0) * 500UL)/1024;

		// LDR Light
		light = 100 - ((ADC_Read(1) * 100UL)/1024);

		// Gas Sensor
		gas = (ADC_Read(2) * 100UL)/1024;

		//RED LED + FAN MOTOR

		if(temp > 30)
		{
			// RED LED ON
			PORTB |= (1<<RED_LED);

			// MOTOR ON
			PORTB |= (1<<MOTOR);
		}
		else
		{
			// RED LED OFF
			PORTB &= ~(1<<RED_LED);

			// MOTOR OFF
			PORTB &= ~(1<<MOTOR);
		}

		// GREEN LED 

		if(light < 30)
		{
			PORTB |= (1<<GREEN_LED);
		}
		else
		{
			PORTB &= ~(1<<GREEN_LED);
		}

		//SOUNDER

		if(gas > 20)
		{
			PORTB |= (1<<SOUNDER);

			_delay_ms(300);

			PORTB &= ~(1<<SOUNDER);

			_delay_ms(300);
		}
		else
		{
			PORTB &= ~(1<<SOUNDER);
		}

		// LCD DISPLAY

		// First Row
		LCD_SetCursor(1,0);

		LCD_String("T:");

		itoa(temp,buffer,10);
		LCD_String(buffer);

		LCD_String("C ");

		LCD_String("G:");

		itoa(gas,buffer,10);
		LCD_String(buffer);

		LCD_String("% ");

		// Second Row
		LCD_SetCursor(2,0);

		LCD_String("L:");

		itoa(light,buffer,10);
		LCD_String(buffer);

		LCD_String("% ");

		_delay_ms(300);
	}
}