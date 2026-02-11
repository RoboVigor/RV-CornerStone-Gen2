//
// Created by rian on 1/6/26.
//

#ifndef RV_CORNERSTONE_GEN2_USART_H
#define RV_CORNERSTONE_GEN2_USART_H
#include "CommuPeripheral.h"
#include "stm32h7xx_hal_usart.h"

namespace CornerStone
{
  class Usart : public CommuPeripheral
  {
    public:
    struct UsartConfig
    {
      enum class SendConfig
      {
        Normal,
        DMA,
        IT,
      } sendConfig;
      enum ReceiveConfig
      {
        Normal,
        DMA,
        IT,
      } receiveConfig;

      uint16_t timeout = 100;
    };

    explicit Usart(USART_HandleTypeDef* usart, UsartConfig config);
    ~Usart() override = default;

    void send(uint8_t* data, uint16_t len) override;
    void receive(uint8_t* data, uint16_t len) override;

    private:
    USART_HandleTypeDef* usart;
    UsartConfig config;

    uint8_t rxBuffer[128] = {0};
    uint8_t txBuffer[128] = {0};
  };
}

#endif //RV_CORNERSTONE_GEN2_USART_H
