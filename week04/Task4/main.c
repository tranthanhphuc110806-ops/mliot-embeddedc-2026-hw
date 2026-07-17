#include "stm32f1xx_hal_conf.h"
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"
#include "stm32f1xx_hal.h"

int main(void)
{
    /* Khởi tạo HAL */
    HAL_Init();

    /*Khoi tao GPIO lam Digital Output Push-Pull*/
    RCC->APB2ENR |= (1 << 4);   // Bat clock PORTC
    GPIOC->CRH &= ~(0xF << 20); // Xoa cac bit cau hinh PC13
    GPIOC->CRH |= (0x2 << 20);  // Output mode, max speed 2 MHz

    /*Khoi tao GPIO lam Digital Output Push-Pull*/
    RCC->APB2ENR |= (1 << 2);  // Bat clock PORTA
    GPIOA->CRL &= ~(0xF << 0); // Xoa cac bit cau hinh PA0
    GPIOA->CRL |= (0x8 << 0);  // Input mode, Input with pull-up / pull-down
    GPIOA->ODR |= (1 << 0);    // Pull up

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);   // Tat led PC13

    while (1)
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)               // Kiem tra nut nhan
        {
            HAL_Delay(20);
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)           // Kiem tra lan nua
            {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);             // Dao trang thai
                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)    // Cho nha nut nhan
                {
                }
            }
        }
    }
}
