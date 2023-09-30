#include "helpers.h"


int is_pressed(GPIO_TypeDef *port, uint16_t pin)
{
    int count = 0;
    int state = (pin == GPIO_PIN_13) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    if (HAL_GPIO_ReadPin(port, pin) == state) {
        count++;
        while (HAL_GPIO_ReadPin(port, pin) == state)
            ;

        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(port, pin) == state) {
            count++;
            while (HAL_GPIO_ReadPin(port, pin) == state)
                ;
        }
    }
    return count;
}

int blink(int count)
{
    if (count < 1)
        return -1;

    for (int i = 0; i < count; i++) {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(100);
    }
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

    return 0;
}
