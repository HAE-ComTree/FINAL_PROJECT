#ifndef GTM_HANDLE_H_
#define GTM_HANDLE_H_


#include "Ifx_Types.h"
#include "IfxGtm_Atom_Pwm.h"
#include "Bsp.h"
#include "stdlib.h"

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void initHANDLEServo(void);
void HandleAngle(float32_t RPM_Diff);

void setHANDLEDuty(uint32 dutyCycle);
void updateHANDLEServoDuty(int newCurr);

#endif /* GTM_HANDLE_H_ */
