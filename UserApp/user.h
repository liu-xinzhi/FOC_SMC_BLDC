#ifndef MYUSER_H
#define MYUSER_H

#include "Ctrl/Sensor/Encoder/encoder_base.h"

typedef struct 
{
	float Tf; //!< Low pass filter time constant
	float y_prev; //!< filtered value in previous execution step 
	unsigned long timestamp_prev;  //!< Last execution timestamp
} LowPassFilter;

typedef struct 
{
	float P; //!< Proportional gain 
	float I; //!< Integral gain 
	float D; //!< Derivative gain 
	float output_ramp; //!< Maximum speed of change of the output value
	float limit; //!< Maximum output value
	float error_prev; //!< last tracking error value
	float output_prev;  //!< last pid output value
	float integral_prev; //!< last integral component value
	unsigned long timestamp_prev; //!< Last execution timestamp
} PIDController;

typedef enum
{
	Type_voltage, //!< Torque control using voltage
	Type_dc_current, //!< Torque control using DC current (one current magnitude)
	Type_foc_current //!< torque control using dq currents
} TorqueControlType;

typedef enum
{
	Type_torque,//!< Torque control
	Type_velocity,//!< Velocity motion control
	Type_angle,//!< Position/angle motion control
	Type_velocity_openloop,
	Type_angle_openloop
} MotionControlType;

/******************************************************************************/
typedef struct 
{
	int  enable;     //零点校准如果电机不正常，enable=0，主循环中对应电机不占用资源
	char id;         //=0为M0,=1为M1
	char str[4];     //定义结构体的名字 "M1"或者"M2"
	
	float voltage_limit;
	float voltage_sensor_align;
	int  pole_pairs;
	float velocity_limit;
	float current_limit;
	unsigned long open_loop_timestamp;
	float target;
	
	LowPassFilter  LPF_q,LPF_d,LPF_vel;
	PIDController  PID_q,PID_d,PID_vel,P_ang;
	
	int pinA,pinB,pinC;
	float gain_a,gain_b,gain_c;
	float offset_ia,offset_ib,offset_ic;
	float phA,phB,phC;
	
	TorqueControlType torque_controller;
	MotionControlType controller;
	Direction sensor_direction;
	
	float zero_electric_angle;
	float shaft_angle;//!< current motor angle
	float electrical_angle;
	float shaft_velocity;
	float current_sp;
	float shaft_velocity_sp;
	float shaft_angle_sp;
	
	char  index_found;
	char  Index_needsSearch;
	unsigned short  pulse_pre;
	long  pulse_total;
	long  cpr;
	float full_rotation_offset;
	long  angle_data_prev;
	float angle_prev;
	unsigned long velocity_calc_timestamp;
} MOTORController;

extern MOTORController M0,M1;
/******************************************************************************/
#endif

