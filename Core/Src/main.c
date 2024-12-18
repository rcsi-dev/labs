#include "main.h"
#include "stm32f4xx.h"

void delay(uint32_t count) {
    while (count--) {
        // выполняем команду no operations вместо пустого цикла,
        // чтобы избежать проблем при компиляции
        __NOP();
    }
}

int main(void) {
    // включаем тактирование GPIO
	// записывая в регистр AHB1ENR (отвечает за тактирование перифирии шины AHB1)
	// бит, включающий тактирование порта GPIOA (т.к. светодиод подключен к PA5)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // настраиваем PA5 на выход
    GPIOA->MODER &= ~(GPIO_MODER_MODER5_Msk);  // сбрасываем битовое поле MODER5
    GPIOA->MODER |= (1U << GPIO_MODER_MODER5_Pos); // устанавливаем MODER5 в режим Output (01)

    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);  // устанавливаем тип выхода на push-pull
    GPIOA->OSPEEDR |= (0U << GPIO_OSPEEDR_OSPEED5_Pos);  // низкая скорость переключения пина
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5_Msk);  // отключение подтяжки во избежание ненужной нагрузки

    while (1) {
        GPIOA->ODR ^= GPIO_ODR_OD5;  // инверсия состояния пина PA5
        delay(1000000);
    }
}
