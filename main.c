#include "stm32f4xx.h"

int i,j;
char data[15]="abcdefghi\n";
// mikro denetleyiciden bilgisayara veri g�nderme 
int main(void){	


	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODE2_1; //Tx PA2
	//Alternatif fonksiyon ayari , modera 10 yazilmasi Rx PA3
	//GPIOA->MODER |= GPIO_MODER_MODE3_1;
	//speed register, High speed
	//GPIOA->OSPEEDR |=GPIO_OSPEEDR_OSPEED3_1;
	//GPIOA->OSPEEDR |=GPIO_OSPEEDR_OSPEED2_1;
	//USART1 Altenatif fonksiyon 7 olarak tanimli
	//GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_2 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_2 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_0;

	USART2->BRR =  0x683U; //9600
	USART2->CR1 |= USART_CR1_UE;
	USART2->CR1 |= USART_CR1_TE;

	while(1){		
		for(i=0;i<=10;i++){
			USART2->DR=data[i];
			while(!(USART2->SR & USART_SR_TXE));
			while(!(USART2->SR & USART_SR_TC));
		}
		for(j=0;j<1000000;j++);					
	}
}
