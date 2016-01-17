/*
 * usart_pc.h
 *
 * Created: 29/05/2015 18:48:55
 *  Author: Carvalho
 */ 


#ifndef USART_PC_H_
#define USART_PC_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>

#define SIZE_BUFFER 3

typedef enum { false, true } bool;

struct data {
	char value[SIZE_BUFFER];
	bool sensor, speed;
};

struct data receive, transmit;

int receive_value;

//----------------------

#define BAUD 	9600		//taxa de 9600 bps
#define MYUBRR	F_CPU/16/BAUD-1

//----------------------

void usart_init();
void usart_transmit(unsigned char);
void usart_receive();

#endif /* USART_PC_H_ */