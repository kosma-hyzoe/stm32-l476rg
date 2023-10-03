# Forbot: kurs STM32L4

## Devices

* I2C - inter-integrated circuit, SDA for data, SCL for clock
* SPI - serial peripheral interface, MISO/MOSI for data, SCK/SS for clock
  (faster than I2C)
* USART - universal asynchronous reciever/transmitter, bidirectional,
* asynchronous-ready UART
* SAI - serial audio interface
* SDMMC - secure digital multimedia card
* CH Polarity Low - GPIO  out acts as GND


## Interrupts

* `SysTick_Handler(void)void SysTick_Handler(void)` is handled by an interrupt
* so is `HardFault_Handler()`
* interrupts procedures cannot use `printf`... why?!
* external event vs external interrupt: events trigger peripheral actions, i.e
  dma's
* HAL_UART_TxCpltCallback is called after HAL_UART_Transmit_IT

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

* `HAL_TIM_Base_Start_IT(*htim),` `HAL_TIM_PeriodElapsedCallback(*htim)`

* Fake PWM
  * `HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1)`,
  * `HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)`
* Real PWM: `HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);`

```c
float calc_pwm(float val)
{
    const float k = 0.13f;
    const float x0 = 70.0f;
    return 10000.0f / (1.0f + exp(-k * (val - x0)));
}
```

* TIM3 > ETR2, `HAL_TIM_Base_Start`, `__HAL_TIM_GET_COUNTER(&htim3)`
* TIM3 > Clock  > Clock filter
* TIM3 > Disable all > Combined Channels > Encoder Mode
  * HAL_TIM_Encoder_Start
  * `__HAL_TIM_GET_COUNTER`

### Measuring pulse width (TIM3)

* Slave mode > Reset
* Trigger > TI1F_ED (edge detection)
* Prescaler > 8000 - 1
* Polarity > Rising edge
* Input filter > 16 - 1
