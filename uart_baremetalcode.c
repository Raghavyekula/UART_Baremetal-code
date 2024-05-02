#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

char uart_read();
 void uart_write(char );
 void UART_init();

unsigned int *PAHB1ENR       = (unsigned int*)0x40023830;
unsigned int *APB1ENR        = (unsigned int*)0x40023840;
unsigned int *GPIOMODER      = (unsigned int*)0x40020000;
unsigned int *GPIOOODR       = (unsigned int*)0x40020014;
unsigned int *GPIOAFRL       = (unsigned int*)0x40020020;
unsigned int *USART_STA      = (unsigned int*)0x40004400;
unsigned int *USART_DATA     = (unsigned int*)0x40004404;
unsigned int *USART_BRR      = (unsigned int*)0x40004408;
unsigned int *USART_CONTROL  = (unsigned int*)0x4000440C;




uart_write(int ch)
{
	while(!(*USART_STA&0x0080))
	{
		*USART_DATA=(ch&0xff);
	}
}

char uart_read()
{
	while(!(*USART_STA&0x0020))
	{
		return *USART_DATA;
	}
}
UART_init()
{
	//Enable clock access for GPIOA
	*PAHB1ENR |= (1<<0);
	//Enable clock access for USART2
	*APB1ENR |= (1<<17);
	//Configure the GPIO Mode register to alt function
	//set PA2 to ALT FUNC
	*GPIOMODER &=~(1<<4);
    *GPIOMODER |=(1<<5);

     //set PA3 to ALT FUNC
     *GPIOMODER &=~(1<<6);
     *GPIOMODER |=(1<<7);

	//Configure the GPIO to o/p function
     //set PA5 as output
     *GPIOMODER |=(1<<10);
     *GPIOMODER &=~(1<<11);

	//Configure the ALT Function to AFRL For PA2 and PA3
     //PA2
     *GPIOAFRL|=(1<<8);
     *GPIOAFRL |=(1<<9);
     *GPIOAFRL |=(1<<10);
     *GPIOAFRL &=~(1<<11);
     //PA3
     *GPIOAFRL|=(1<<12);
     *GPIOAFRL |=(1<<13);
     *GPIOAFRL |=(1<<14);
     *GPIOAFRL &=~(1<<15);


	//Configure the BRR TO 9600

	 *USART_BRR =0x0683;


	//Configure the UART for tx and rx
	 //Tx Enable bit
	 *USART_CONTROL =0x0008;
	 //Rx enable bit
	 *USART_CONTROL =0x0004;
	 //USART enable bit
	 *USART_CONTROL =0x2000;
}


int main(void)
{
char ch;
UART_init();

while(1)
{
	ch=uart_read();
}

}
