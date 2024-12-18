#include "main.h"
#include "stm32f4xx.h"

void delay(uint32_t count) {
    while (count--) {
        __NOP();  // выполняем команду no operations
    }
}

int main(void) {
    // включаем тактирование GPIOA и GPIOC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    // настроим PA5 как выход для светодиода
    GPIOA->MODER &= ~(GPIO_MODER_MODER5_Msk);  // сбрасываем битовое поле MODER5
    GPIOA->MODER |= (1U << GPIO_MODER_MODER5_Pos); // устанавливаем PA5 в режим Output

    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);  // push-pull
    GPIOA->OSPEEDR |= (0U << GPIO_OSPEEDR_OSPEED5_Pos);  // низкая скорость
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5_Msk);  // без подтяжки

    // настроим PC13 как вход с подтяжкой
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_Msk);  // режим входа для PC13
    GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13_Msk);  // сбрасываем, чтобы установить подтяжку
    GPIOC->PUPDR |= GPIO_PUPDR_PUPD13_0;  // подтяжка вверх

    while (1) {
        // чтение состояния кнопки на PC13
        if ((GPIOC->IDR & GPIO_IDR_ID13) == 0) {  // кнопка нажата (активен низкий уровень)
            GPIOA->ODR |= GPIO_ODR_OD5;  // включаем светодиод (PA5 high)
        } else {
            GPIOA->ODR &= ~GPIO_ODR_OD5;  // выключаем светодиод (PA5 low)
        }
        delay(100000);  // небольшой таймаут, чтобы избежать дребезга кнопки
    }
}
