
#ifndef __PID_H_
#define __PID_H_

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float error;

    float Proportional_value;
    float Integrator_value;
    float Differential_value;
    int Output_Value;

    float lim_Max_Integrator_value;
    float lim_Min_Integrator_value;

    int lim_Max_Output_value;
    int lim_Min_Output_value;

    float last_error;

}PID_Struct;

void PID_Init(PID_Struct *PID,float Kp,float Ki,float Kd,float maxIntegrator_value,int limMax_Output_value,int limMin_Output_value);
int PID_Run(PID_Struct *PID, int set_point, float measurement);

#endif
