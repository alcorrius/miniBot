/*
 * miniBot.c
 *
 * Created: 18.10.2015 23:24:47
 *  Author: alcorrius
 */ 


#include <avr/io.h>
#include <util/delay.h>

void uart_init( void )
{
	//��������� �������� ������
	UBRRH = 0;
	UBRRL = 5;
	//UBRRL = ubrr_value;
	//UBRRH = (ubrr_value>>8);
	//8 ��� ������, 1 ���� ���, ��� �������� ��������
	UCSRC = ( 1 << URSEL ) | ( 1 << UCSZ1 ) | ( 1 << UCSZ0 );
	//��������� ����� � �������� ������
	UCSRB = ( 1 << TXEN ) | ( 1 <<RXEN );
}

unsigned char uart_getc( void )
{
	//���� ������ �����
	while( ( UCSRA & ( 1 << RXC ) ) == 0  );
	//��������� �������� ����
	return UDR;
}

void uart_putc( char c )
{
	//���� ��������� �������� ����������� �����
	while( ( UCSRA & ( 1 << UDRE ) ) == 0 );
	UDR = c;
}

void uart_puts( char *str )
{
	unsigned char c;
	while( ( c = *str++ ) != 0 ) {
		uart_putc( c );
	}
}

int main( void )
{
	uart_init();
	OSCCAL = 150;
	_delay_ms( 100 );
	uart_puts( "Hello uart\r\n" );
	while( 1 ) {
		char c = uart_getc();
		if(c=='s') {
			PORTC &= ~_BV(PC1); // ���������� "0" �� ����� 1 ����� C
			PORTC |= _BV(PC2); // ���������� "1" �� ����� 2 ����� C
			PORTC &= ~_BV(PC3); // ���������� "0" �� ����� 3 ����� C
			PORTC |= _BV(PC4); // ���������� "1" �� ����� 4 ����� C
		} 
		if (c=='w')/*forward*/ {
			PORTC |= _BV(PC1); // ���������� "1" �� ����� 1 ����� C
			PORTC &= ~_BV(PC2); // ���������� "0" �� ����� 2 ����� C
			PORTC |= _BV(PC3); // ���������� "1" �� ����� 3 ����� C
			PORTC &= ~_BV(PC4); // ���������� "0" �� ����� 4 ����� C
		} 
		if (c=='x') {
			PORTC &= ~_BV(PC1); // ���������� "0" �� ����� 1 ����� C
			PORTC &= ~_BV(PC2); // ���������� "0" �� ����� 2 ����� C
			PORTC &= ~_BV(PC3); // ���������� "0" �� ����� 3 ����� C
			PORTC &= ~_BV(PC4); // ���������� "0" �� ����� 4 ����� C
		}
		if(c=='d') {
			PORTC &= ~_BV(PC1); // ���������� "0" �� ����� 1 ����� C
			PORTC |= _BV(PC2); // ���������� "1" �� ����� 2 ����� C
			PORTC |= _BV(PC3); // ���������� "1" �� ����� 3 ����� C
			PORTC &= ~_BV(PC4); // ���������� "0" �� ����� 4 ����� C
			
		}
		if (c=='a') {
			PORTC |= _BV(PC1); // ���������� "1" �� ����� 1 ����� C
			PORTC &= ~_BV(PC2); // ���������� "0" �� ����� 2 ����� C
			PORTC &= ~_BV(PC3); // ���������� "0" �� ����� 3 ����� C
			PORTC |= _BV(PC4); // ���������� "1" �� ����� 4 ����� C
			
		}
		
		//uart_putc( c );
		
		//char ci[3];
		
		/*
		unsigned short i;
		for( i=140; i <= 160; i++ ) {
			OSCCAL = i;
			_delay_ms( 10 );
			//printf( "OSCCAL=%u\r\n", i);
			uart_puts("OSCCAL123=");
			uart_puts("���");
			itoa(i, ci, 5);
			//memcpy(ci, (char*)&i, 3);
			uart_puts(ci);
			uart_puts("\r\n");
			_delay_ms( 10 );
		}
		*/
		
	}
	return 0;
}