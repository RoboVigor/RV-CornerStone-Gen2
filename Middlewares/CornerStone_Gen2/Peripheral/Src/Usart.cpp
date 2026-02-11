/**
* Author: Rian
* Date: 2/9/26.
*/

#include "Usart.h"
#include <cstring>

namespace CornerStone
{
  Usart::Usart(USART_HandleTypeDef* usart, const UsartConfig config)
    :usart(usart), config(config){
  }

  void Usart::send(uint8_t* data, const uint16_t len)
  {
    if (this->usart->State == HAL_USART_STATE_BUSY_TX) return;
    memcpy(this->txBuffer, data, len);
    switch (this->config.sendConfig)
    {
    case UsartConfig::SendConfig::Normal:
      HAL_USART_Transmit(this->usart, this->txBuffer, len, this->config.timeout);
      break;

    case UsartConfig::SendConfig::DMA:
      HAL_USART_Transmit_DMA(this->usart, this->txBuffer, len);
      break;

    case UsartConfig::SendConfig::IT:
      HAL_USART_Transmit_IT(this->usart, this->txBuffer, len);
      break;

    default:
      return;
    }
  }

  void Usart::receive(uint8_t* data, const uint16_t len)
  {
    if (this->usart->State == HAL_USART_STATE_BUSY_RX) return;

    switch (this->config.receiveConfig)
    {
      case UsartConfig::ReceiveConfig::Normal:
        HAL_USART_Receive(this->usart, this->rxBuffer, len, this->config.timeout);
        break;
      case UsartConfig::ReceiveConfig::DMA:
        HAL_USART_Receive_DMA(this->usart, this->rxBuffer, len);
        break;
      case UsartConfig::ReceiveConfig::IT:
        HAL_USART_Receive_IT(this->usart, this->rxBuffer, len);
        break;
      default:
      return;
    }

    memcpy(data, this->rxBuffer, len);
  }
}
