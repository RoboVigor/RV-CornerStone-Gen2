//
// Created by rian on 1/6/26.
//

#ifndef RV_CORNERSTONE_GEN2_COMMUPERIPHERAL_H
#define RV_CORNERSTONE_GEN2_COMMUPERIPHERAL_H
#include "Peripheral.h"
#include "stm32h7xx_hal.h"

namespace CornerStone
{
  class CommuPeripheral : public Peripheral
  {
    public:
    CommuPeripheral() = default;
    ~CommuPeripheral() override = default;

    virtual void send(uint8_t* data, uint16_t len) = 0;
    virtual void receive(uint8_t* data, uint16_t len) = 0;
  };
}
#endif //RV_CORNERSTONE_GEN2_COMMUPERIPHERAL_H