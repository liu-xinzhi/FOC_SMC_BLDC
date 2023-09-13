#ifndef CTRL_STEP_FW_AS5047_STM32_H
#define CTRL_STEP_FW_AS5047_STM32_H

#include "encoder_as5047.h"

class EncoderAS5047 : public EncoderAS5047Base
{
private:
    void SpiInit();

    uint16_t SpiTransmitAndRead16Bits(uint16_t _data);
};

#endif
