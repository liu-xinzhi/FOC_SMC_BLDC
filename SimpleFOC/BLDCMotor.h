#ifndef BLDCMotor_H
#define BLDCMotor_H

#include "user.h"

/******************************************************************************/
extern  float voltage_power_supply;
/******************************************************************************/
void Motor_init(MOTORController *M);
void Motor_initFOC(MOTORController *M,float zero_electric_offset, Direction _sensor_direction);
void loopFOC(MOTORController *M);
void move(MOTORController *M,float new_target);
void setPhaseVoltage(MOTORController *M,float Uq, float Ud, float angle_el);
/******************************************************************************/

#endif
