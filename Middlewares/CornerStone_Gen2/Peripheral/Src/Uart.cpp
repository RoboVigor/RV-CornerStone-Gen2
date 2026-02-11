/**
* Author: Rian
* Date: 2/10/26.
*/

#include "Uart.h"
#include <cstring>

namespace CornerStone
{
  Uart::Uart(UART_HandleTypeDef* huart, const UartConfig& uartConfig)
    :huart(huart),uartConfig(uartConfig){

  }

  void Uart::send(uint8_t* data, const uint16_t len)
  {
    if (this->huart->gState == HAL_UART_STATE_BUSY_TX) return;
    memcpy(this->txBuffer, data, len);
    switch (this->uartConfig.sendConfig)
    {
    case UartConfig::SendConfig::Normal:
      HAL_UART_Transmit(this->huart, this->txBuffer, len, this->uartConfig.timeout);
      break;
    case UartConfig::SendConfig::DMA:
      HAL_UART_Transmit_DMA(this->huart, this->txBuffer, len);
      break;
    case UartConfig::SendConfig::IT:
      HAL_UART_Transmit_IT(this->huart, this->txBuffer, len);
      break;
    default:
      return;
    }
  }

  void Uart::receive(uint8_t* data, const uint16_t len)
  {
    if (this->huart->RxState == HAL_UART_STATE_BUSY_RX) return;
    switch (this->uartConfig.receiveConfig)
    {
      case UartConfig::ReceiveConfig::Normal:
        HAL_UART_Receive(this->huart, this->rxBuffer, len, this->uartConfig.timeout);
        break;
      case UartConfig::ReceiveConfig::DMA:
        HAL_UART_Receive_DMA(this->huart, this->rxBuffer, len);
        break;
      case UartConfig::ReceiveConfig::IT:
        HAL_UART_Receive_IT(this->huart, this->rxBuffer, len);
        break;
      case UartConfig::ReceiveConfig::IDLE:
        HAL_UARTEx_ReceiveToIdle(this->huart, this->rxBuffer, len, &this->rxLen,this->uartConfig.timeout);
        break;
      case UartConfig::ReceiveConfig::IdleIT:
        HAL_UARTEx_ReceiveToIdle(this->huart, this->rxBuffer, len, &this->rxLen, this->uartConfig.timeout);
        break;
      case UartConfig::ReceiveConfig::DmaIDLE:
        HAL_UARTEx_ReceiveToIdle_DMA(this->huart, this->rxBuffer, len);
        break;
      default:
        return;
    }
  }
}
