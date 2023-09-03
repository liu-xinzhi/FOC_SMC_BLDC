#include "MyProject.h"
#include "Ctrl/Utils/foc_utils.h"

/******************************************************************************/
void LPF_init(MOTORController *M)
{
	M->LPF_q.Tf=0.02f;    
	M->LPF_q.y_prev=0;
	M->LPF_q.timestamp_prev=micros();
	
	M->LPF_d.Tf=0.02f;
	M->LPF_d.y_prev=0;
	M->LPF_d.timestamp_prev=micros();
	
	M->LPF_vel.Tf=0.02f;
	M->LPF_vel.y_prev=0;
	M->LPF_vel.timestamp_prev=micros();
}
/******************************************************************************/
float LPFoperator(LowPassFilter* LPF,float x)
{
	unsigned long timestamp;
	float dt, alpha, y;
	
	timestamp = micros();
	dt = (timestamp - LPF->timestamp_prev)*1e-6f;
	LPF->timestamp_prev = timestamp;
	if (dt < 0.0f ) dt = 1e-3f;
	else if(dt > 0.3f)   //时间过长，大概是程序刚启动初始化，直接返回
	{
		LPF->y_prev = x;
		return x;
	}
	
	alpha = LPF->Tf/(LPF->Tf + dt);
	y = alpha*LPF->y_prev + (1.0f - alpha)*x;
	LPF->y_prev = y;
	
	return y;
}
/******************************************************************************/

