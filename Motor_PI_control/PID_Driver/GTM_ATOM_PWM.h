#ifndef PID_DRIVER_GTM_ATOM_PWM_H_
#define PID_DRIVER_GTM_ATOM_PWM_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxGtm_Atom_Pwm.h"
#include "IfxGtm_reg.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void initGtmATomPwm(void);
void PWM_set(uint32 g_PWMValue);
void PWM_Motor_B_set(uint32 g_PWMValue);
void setDutyCycle(uint32 dutyCycle);
void setMotor_B_DutyCycle(uint32 dutyCycle);
void setMotorControl(uint8 direction, uint8 enable);
void setMotor_B_Control(uint8 direction, uint8 enable);
void initPins(void);

#endif /* PID_DRIVER_GTM_ATOM_PWM_H_ */
