#include "helpers.h"


int is_pressed(uint16_t pin, GPIO_TypeDef *port)
{
    int count = 0;
    if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET) {
        count++;
        while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)
            ;

        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET) {
            count++;
            while (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_RESET)
                ;
        }
    }
    return count;
}