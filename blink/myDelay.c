#include "myDelay.h"
static volatile uint32_t timeTick = 0;

void Delay_us(uint32_t d) {
    timeTick = d;
    SysTick->LOAD = 9 - 1; // 1ms delay
    SysTick->VAL = 0; // Xóa thanh ghi giá tr? hi?n t?i
    SysTick->CTRL |= 1ul<<1;
		SysTick->CTRL |= 1ul<<0; 
    while(timeTick != 0);
    SysTick->CTRL = 0;
}

void Delay_ms(uint32_t d) {
    timeTick = d;
    // C?u hình SysTick d? t?o ng?t m?i 1ms
    SysTick->LOAD = 9000 - 1; // 1ms delay
    SysTick->VAL = 0; // Xóa thanh ghi giá tr? hi?n t?i
    SysTick->CTRL |= 1ul<<1;
		SysTick->CTRL |= 1ul<<0; 
    while(timeTick != 0);
    SysTick->CTRL = 0;
}

void SysTick_Handler(void) {
    if (timeTick > 0) {
        timeTick--;
    }
}
