#include "stm32f4xx.h"

int frekans=40000;
int ho=250;
int lo=7750;
int deger=100;

void SysTick_Handler(){
	
	if(ho>79500){
		deger= deger*-2;
		ho=79350;
	}
	if(ho<500){
		deger= deger*-2;
		ho=650;
	}
	
	//asagidaki sekilde tek bir if icerisinde de yapilabilir.
	//if(duty_cycle > 80000-500 || duty_cycle < 500){
	//	deger = -1*deger;
	//	duty_cycle+=deger;
	// KADEMELI OLARAK LED YANIP S�NER	}
	
	if(GPIOD->ODR & GPIO_ODR_OD14){
		
		ho=ho+deger;
		lo=frekans-ho;
		
		GPIOD->ODR &= ~GPIO_ODR_OD14;
		SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
		SysTick->LOAD |= ho & SysTick_LOAD_RELOAD_Msk;
	}
	else{
		GPIOD->ODR |= GPIO_ODR_OD14;
		SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
		SysTick->LOAD |= lo & SysTick_LOAD_RELOAD_Msk;
	}
}
int main(){
	SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
	SysTick->LOAD |= ho & SysTick_LOAD_RELOAD_Msk;
	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	NVIC_EnableIRQ(SysTick_IRQn);
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER14_0;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	GPIOD->ODR |= GPIO_ODR_OD14;
	
	while(1);	
}