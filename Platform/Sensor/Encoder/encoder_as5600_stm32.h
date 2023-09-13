#ifndef CTRL_STEP_FW_AS5600_STM32_H
#define CTRL_STEP_FW_AS5600_STM32_H

#include "encoder_as5600.h"

class EncoderAS5600 : public EncoderAS5600Base
{
private:
    void SpiInit();

    uint16_t SpiTransmitAndRead16Bits(uint16_t _data);
};

#endif
