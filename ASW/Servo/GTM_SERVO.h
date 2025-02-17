#ifndef GTM_SERVO_H_
#define GTM_SERVO_H_


#include "Ifx_Types.h"
#include "IfxGtm_Atom_Pwm.h"
#include "Bsp.h"
#include "stdlib.h"

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/
void initGtmServo(void);
void seatSwing(int);
//void seatFold(int);

void setServoDuty(uint32 dutyCycle);
void updateCurrAndSetServoDuty(int newCurr);

#endif /* GTM_SERVO_H_ */
