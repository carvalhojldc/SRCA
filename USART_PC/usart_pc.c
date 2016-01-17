/*
 * usart_pc.c
 *
 * Created: 29/05/2015 18:48:41
 *  Author: Carvalho
 */ 

#include "usart_pc.h"

void usart_init() {
	unsigned char myu = MYUBRR;
	UBRR0H = (unsigned char)(myu>>8);	//Ajusta a taxa de transmissão
	UBRR0L = (unsigned char)myu;

	UCSR0A = 0;//desabilitar velocidade dupla (no Arduino é habilitado por padrão)
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //Habilita a transmissão e a recepção
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);/*modo assíncrono, 8 bits de dados, 1 bit de parada, sem paridade*/	
	
}

void usart_transmit(unsigned char dt) {
	itoa(dt,transmit.value,10); // Convertendo dt
	int t=0;
	
	while(t<sizeof(transmit.value)) {
		while (!( UCSR0A & (1<<UDRE0)) ); //espera o dado ser enviado
		UDR0 = transmit.value[t]; //envia o dado
		t++;
	}
}

void usart_receive() {
	bool spin = true; // Para controlar o loop
	char test;
	int r=0;
	while(spin) { // Loop para tratamento dos dados recebidos
		while (!(UCSR0A & (1<<RXC0))); // Espera o dado ser recebido
		test = UDR0; // Armazena o dado recebido
		
		if(test == 's') { // Controle pelos sensores
			spin = false; // Finalizar o loop
			receive.sensor = true;
		}
		else if(test == 'p') { // Controlar posicao
			receive.sensor = false;
			receive.speed = false;
		}
		else if(test == 'v') { // Controlar velocidade
			receive.sensor = false;
			receive.speed = true;
		}
		else if(test == 't') { // Fim da tranferencia
			receive_value = atoi(receive.value);
			
			for(r=0;r<SIZE_BUFFER;r++)
				receive.value[r] = '\0';
			
			spin = false; // Finalizar o loop
		}
		else { // Salva valor da transferencia
			receive.value[r] = test;
			r++;
		}				
	}
}

