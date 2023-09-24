# Forbot: STM32L4 Course

## Interrupts

```c
int message_number = 0;
void send_next_message(void)
{
    static char message[] = "Hello World!\r\n";
    static char message2[] = "Forbot jest super!\r\n";
    switch (message_number) {
    case 0:
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)message, strlen(message));
        message_number = 1;
        break;
    case 1:
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)message2, strlen(message2));
        message_number = 2;
        break;
    default:
        break;
    }
}
// is called after data is transmitted via UART_IT
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
        send_next_message();
}

uint8_t uart_rx_buffer;
//is called after data is recieved via UART_IT
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
        HAL_UART_Recievie_IT(&huart2, &uart_rx_buffer, 1);

}
```

## Timers

## Basic timers

```c
// start the timer
HAL_TIM_Base_Start_IT(&htim6);

// called after timer period elapses
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim3)
        ;
}
```

## General purpose timers

