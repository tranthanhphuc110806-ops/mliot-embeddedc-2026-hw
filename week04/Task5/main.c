#include "stm32f1xx_hal_conf.h"
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"
#include "stm32f1xx_hal.h"

uint16_t ROW_PINS[2] = {GPIO_PIN_0, GPIO_PIN_1};
uint16_t COL_PINS[2] = {GPIO_PIN_2, GPIO_PIN_3};

void KEYPAD_2x2_Scan(void)
{
    for (uint8_t r = 0; r < 2; r++)
    {
        for (uint8_t i = 0; i < 2; i++) // Chi dap Hang r xuong 0
            HAL_GPIO_WritePin(GPIOA, ROW_PINS[i], (i == r) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_Delay(1);
        for (uint8_t c = 0; c < 2; c++)
        {
            if (HAL_GPIO_ReadPin(GPIOA, COL_PINS[c]) == GPIO_PIN_RESET)
            {
                HAL_Delay(20); // chong doi
                if (HAL_GPIO_ReadPin(GPIOA, COL_PINS[c]) == GPIO_PIN_RESET)
                {
                    if (r == 0 && c == 0) 
                    {
                        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);      // Dao trang thai hang 1 cot 1
                    }
                    else if (r == 0 && c == 1)
                    {
                        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);      // Dao trang thai hang 1 cot 2
                    }
                    else if (r == 1 && c == 0)
                    {
                        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);      // Dao trang thai hang 2 cot 1
                    }
                    else if (r == 1 && c == 1)
                    {
                        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);      // Dao trang thai hang 2 cot 2
                    }
                    while (HAL_GPIO_ReadPin(GPIOA, COL_PINS[c]) == GPIO_PIN_RESET) 
                    {
                        // doi nha phim
                    }
                }
            }
        }
    }
    return; // khong co phim nao duoc nhan
}

int main(void)
{
    /* Khởi tạo HAL */
    HAL_Init();

    RCC->APB2ENR |= (1 << 2); // Bat clock PORTA
    GPIOA->CRL = 0;           // Xoa cac bit cau hinh PortA

    /*Khoi tao GPIO lam output*/
    GPIOA->CRL |= (0x2 << 0) | (0x2 << 4) // PA0, PA1
                | (0x2 << 16) | (0x2 << 20) // PA4, PA5
                | (0x2 << 24) | (0x2 << 28); // P6, PA7: Output mode, max speed 2 MHz

    /*Khoi tao GPIO lam input pullup*/
    GPIOA->CRL |= (0x8 << 8) | (0x8 << 12); //  PA2, PA3: Input with pull-up / pull-down cho PA2 va PA3
    GPIOA->ODR |= (1 << 2) | (1 << 3); // pull up

    while (1)
    {
        KEYPAD_2x2_Scan();
    }
}
