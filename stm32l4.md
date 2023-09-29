# Forbot: kurs STM32L4

## Devices

* I2C - inter-integrated circuit, SDA for data, SCL for clock
* SPI - serial peripheral interface, MISO/MOSI for data, SCK/SS for clock
  (faster than I2C)
* USART - universal asynchronous reciever/transmitter, bidirectional,
* asynchronous-ready UART
* SAI - serial audio interface
* SDMMC - secure digital multimedia card


## Interrupts

* `SysTick_Handler(void)void SysTick_Handler(void)` is handled by an interrupt
* so is `HardFault_Handler()`
* interrupts procedures cannot use `printf`... why?!
* external event vs external interrupt: events trigger peripheral actions, i.e
  dma's
* HAL_UART_TxCpltCallback is called after HAL_UART_Transmit_IT

## Timers

* `HAL_TIM_Base_Start_IT(*htim),` `HAL_TIM_PeriodElapsedCallback(*htim)`
