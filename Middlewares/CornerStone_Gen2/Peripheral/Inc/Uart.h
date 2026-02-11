/**
* Author: Rian
* Date: 2/10/26.
*/

#ifndef RV_CORNERSTONE_GEN2_UART_H
#define RV_CORNERSTONE_GEN2_UART_H
#include "CommuPeripheral.h"
#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_uart_ex.h"

namespace CornerStone
{
  class Uart : public CommuPeripheral
  {
    public:
    struct UartConfig
    {
      enum class SendConfig
      {
        Normal,
        DMA,
        IT,
      } sendConfig;

      enum class ReceiveConfig
      {
        Normal,
        DMA,
        IT,
        IDLE,
        IdleIT,
        DmaIDLE,
      } receiveConfig;

      uint16_t timeout = 100;
    };

    explicit Uart(UART_HandleTypeDef* huart, const UartConfig& uartConfig);
    ~Uart() override = default;

    void send(uint8_t* data, uint16_t len) override;
    void receive(uint8_t* data, uint16_t len) override;

    private:
    UART_HandleTypeDef* huart;
    UartConfig uartConfig;

    uint8_t rxBuffer[128] = {0};
    uint8_t txBuffer[128] = {0};

    /* only used to Receive to Idle mode */
    uint16_t rxLen = 0;
  };
}

#endif //RV_CORNERSTONE_GEN2_UART_H