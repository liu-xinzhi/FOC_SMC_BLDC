#include "spi.h"

/*****************************************************************************/
void SPI3_Init_()
{
    // 手动调整
//	SPI_InitStructure.SPI_CRCPolynomial = 7;   //CRC 值计算的多项式
    MX_SPI3_Init();
}
/*****************************************************************************/
uint16_t SPIx_ReadWriteByte(uint16_t byte)
{
    uint16_t dataRx;
    HAL_SPI_TransmitReceive(&hspi3, (uint8_t*) &byte, (uint8_t*) &dataRx, 1, HAL_MAX_DELAY);
    return dataRx;
}
/******************************************************************************/

