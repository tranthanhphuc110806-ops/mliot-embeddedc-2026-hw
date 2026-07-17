#include "stm32f1xx_hal_conf.h"
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"
#include "stm32f1xx_hal.h"


int main(void)
{
    /* Khởi tạo HAL */
    HAL_Init();

    /*Khoi tao GPIO lam Digital Output Push-Pull*/
    RCC->APB2ENR |= (1 << 4);       // Bat clock PORTC
    GPIOC->CRH &= ~(0xF << 20);      // Xoa cac bit cau hinh PC13
    GPIOC->CRH |= (0x2 << 20);      // Output mode, max speed 2 MHz

    while (1)
    {
        /* LED trên Blue Pill active LOW */
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        /* Delay 500 ms */
        HAL_Delay(500);
    }
}


