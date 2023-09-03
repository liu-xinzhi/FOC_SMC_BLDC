#ifndef INLINE_CS_LIB_H
#define INLINE_CS_LIB_H

#include "user.h"


/******************************************************************************/
void LowsideCurrentSense(MOTORController *M,float _shunt_resistor, float _gain, int _pinA, int _pinB, int _pinC);
void ADC_Init_synch(void);
void LowsideCurrentSense_Init(MOTORController *M);
PhaseCurrent_s getPhaseCurrents(MOTORController *M);
/******************************************************************************/


#endif

