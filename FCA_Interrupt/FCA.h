#ifndef FCA_INTERRUPT_FCA_H_
#define FCA_INTERRUPT_FCA_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxStm.h"
#include "Bsp.h"
#include "KALMAN_FILT.h"
#include "Set_Driving_Mode.h"
#include "STM_Interrupt.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
extern boolean FCA_IT_FLAG;

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void isrFCA(void);
void initFCASTM(void);
void performFCA(void);

#endif /* FCA_INTERRUPT_FCA_H_ */
