#include "encoder_as5600_stm32.h"
#include "spi.h"

void EncoderAS5600::SpiInit()
{
    MX_SPI3_Init();
}


uint16_t EncoderAS5600::SpiTransmitAndRead16Bits(uint16_t _dataTx)
{
    uint16_t dataRx;

    GPIOA->BSRR = GPIO_PIN_4; // Chip select
    HAL_SPI_TransmitReceive(&hspi3, (uint8_t*) &_dataTx, (uint8_t*) &dataRx, 1, HAL_MAX_DELAY);
    GPIOA->BSRR = GPIO_PIN_4;

    return dataRx;
}
