#include "PID.h"

void PID_Init(PID_Struct *PID,float Kp,float Ki,float Kd,float maxIntegrator_value,int limMax_Output_value,int limMin_Output_value)
{
    PID->Kp = Kp;
    PID->Ki = Ki;
    PID->Kd = Kd;

    PID->lim_Max_Integrator_value=maxIntegrator_value;
    PID->lim_Min_Integrator_value=-maxIntegrator_value;

    PID->lim_Max_Output_value = limMax_Output_value;
    PID->lim_Min_Output_value = limMin_Output_value;

    PID->error=0;
    PID->Proportional_value=0;
    PID->Differential_value=0;
    PID->Output_Value=0;
    PID->last_error=0;
}

int PID_Run(PID_Struct *PID, int set_point, float measurement)
{
    PID->error=set_point-measurement;
    PID->last_error=PID->error;

    PID->Proportional_value = PID->Kp*PID->error;

    PID->Integrator_value += PID->Ki*PID->error;
    if (PID->Integrator_value > PID->lim_Max_Integrator_value)
    {
        PID->Integrator_value = PID->lim_Max_Integrator_value;
    } else if (PID->Integrator_value < PID->lim_Min_Integrator_value)
    {
        PID->Integrator_value = PID->lim_Min_Integrator_value;
    }

    PID->Differential_value=(PID->error-PID->last_error)*PID->Kd;
    PID->Output_Value = PID->Proportional_value+PID->Differential_value+PID->Integrator_value;
    if(PID->Output_Value > PID->lim_Max_Output_value)
    {
        PID->Output_Value=PID->lim_Max_Output_value;
    }else if(PID->Output_Value<PID->lim_Min_Output_value)
    {
        PID->Output_Value=PID->lim_Min_Output_value;
    }
    return PID->Output_Value;
}
