#ifndef LANE_CHANGE_LANE_CHANGE_H_
#define LANE_CHANGE_LANE_CHANGE_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Set_Driving_Mode.h"
#include "Ifx_Types.h"
#include "math.h"
#include "IfxStm.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
extern int T1_rotation_flag;
extern boolean T2_straight_flag;
extern boolean T3_rotation_flag;
extern boolean T3_rotation_end_flag;

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void T1_rotation_Right(void);
void T2_straight(void);
void T3_rotation_left(void);
void lc_final_procedure(void);
void isr_lc_T1_stm(void);
void isr_lc_T2_stm(void);
void isr_lc_T3_stm(void);
void init_lc_T1_STM_IT(float32 rotation_time_T1);
void init_lc_T2_STM_IT(float32 travel_time_T2);
void init_lc_T3_STM_IT(float32 rotation_time_T3);
void AdjustRPMDown(void);
float32 calculate_T2_time(void);

#endif /* LANE_CHANGE_LANE_CHANGE_H_ */
