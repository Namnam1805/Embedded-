#include "stm32f10x.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM2_Configuration(void);
void delay(uint32_t time);

int main(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    TIM2_Configuration();

    while (1)
    {
        // Kh�ng c?n l�m g� trong v�ng l?p ch�nh v� c�ng vi?c du?c th?c hi?n trong ng?t
    }
}

void RCC_Configuration(void)
{
    // B?t clock cho GPIOC
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // B?t clock cho TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
}

void GPIO_Configuration(void)
{
    // C?u h�nh ch�n C13 l� ch�n output push-pull
    GPIOC->CRH |= GPIO_CRH_MODE13;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
}

void TIM2_Configuration(void)
{
    // Thi?t l?p th�ng s? co b?n cho timer
    TIM2->PSC = 7200 - 1; // T?n s? xung clock c?a timer l� 72MHz / 7200 = 10kHz
    TIM2->ARR = 10000 - 1; // �?m d?n 10000 d? t?o chu k? 1s
    TIM2->CR1 |= TIM_CR1_CEN; // Kh?i d?ng Timer2

    // C�i d?t ng?t cho Timer2
    TIM2->DIER |= TIM_DIER_UIE; // B?t ng?t update
    NVIC_EnableIRQ(TIM2_IRQn); // B?t ng?t c?a TIM2 trong NVIC
}

// X? l� ng?t c?a Timer2
void TIM2_IRQHandler(void)
{
    // Ki?m tra xem ngu?n ng?t c� ph?i t? Timer2 kh�ng
    if (TIM2->SR & TIM_SR_UIF)
    {
        // �?o tr?ng th�i c?a LEDC13
        GPIOC->ODR ^= GPIO_ODR_ODR13;

        // X�a c? ng?t
        TIM2->SR &= ~TIM_SR_UIF;
    }
}

// H�m delay don gi?n
void delay(uint32_t time)
{
    while (time--);
}
