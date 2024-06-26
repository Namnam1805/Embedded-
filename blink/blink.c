#include<stm32f10x.h>
#include "myDelay.h"


int main(void){

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(0xFUL<<20);
	GPIOC->CRH |= 0x3<<20;
	
	while(1){
		   GPIOC->BSRR = 1<<13; 
        Delay_ms(100);
        GPIOC->BSRR = 1<<(13 + 16); 
        Delay_ms(100);
	}
}

