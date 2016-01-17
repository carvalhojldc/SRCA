/*
 * USART_PC.c
 *
 * Created: 29/05/2015 18:48:01
 *  Author: Carvalho
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "usart_pc.h"

int main(void) {	

	usart_init();
	
	int cont=40;
	
    while(1) {
		usart_receive(); /*variavel global receive_value*/
		
		usart_transmit(cont);
		
		cont++;
    }
}