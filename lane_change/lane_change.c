/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "lane_change.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

#define ISR_PRIORITY_LC_T1_STM      55
#define ISR_PRIORITY_LC_T2_STM      57
#define ISR_PRIORITY_LC_T3_STM      59
#define LANE_WIDTH                  250

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStm_CompareConfig LC_T1_STMConf;
IfxStm_CompareConfig LC_T2_STMConf;
IfxStm_CompareConfig LC_T3_STMConf;

int T1_rotation_flag = FALSE;
boolean T2_straight_flag = FALSE;
boolean T3_rotation_flag = FALSE;
boolean T3_rotation_end_flag = FALSE;

static const float32 TARGET_ANGLE_DEGREE = 30.0f; //단위 : 도
static const float32 TARGET_ANGLE_RADIAN = 30.0f * (IFX_PI/180); //단위 : 라디안
static const float32 ANGULAR_VELOCITY_DEGREE = 10.0f; //단위 : 도/초
static const float32 ANGULAR_VELOCITY_RADIAN = 10.0f * (IFX_PI/180); //단위 : 라디안/초


uint32 rotation_time_T1_ticks;
float32 turn_radius = 0;

float32 rotation_time_T1;
float32 travel_time_T2 = 0;

float32 origin_RPM_CMD1 = 0;
float32 origin_RPM_CMD2 = 0;

int it_dist_FLAG = 0;


/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
IFX_INTERRUPT(isr_lc_T1_stm, 0, ISR_PRIORITY_LC_T1_STM);
IFX_INTERRUPT(isr_lc_T2_stm, 0, ISR_PRIORITY_LC_T2_STM);
IFX_INTERRUPT(isr_lc_T3_stm, 0, ISR_PRIORITY_LC_T3_STM);

void T1_rotation_Right(void)
{
    T1_rotation_flag = FALSE;

    //목표 각도를 달성할 만큼 고정된 각속도로 회전해야하는 시간 계산
    float32 angular_velocity_radian = 0;

    //FCA 기능 정지
    IfxStm_disableComparatorInterrupt(&MODULE_STM1, IfxStm_Comparator_0);
    FCA_ENABLE_FLAG = FALSE;

    origin_RPM_CMD1 = RPM_CMD1;
    origin_RPM_CMD2 = RPM_CMD2;

    float32 Base_Speed = getCurrentSpeed();
    turn_radius = set_turn(Right, TARGET_ANGLE_RADIAN);
    angular_velocity_radian = Base_Speed / turn_radius;

    rotation_time_T1 = (TARGET_ANGLE_RADIAN / angular_velocity_radian) + 2; //단위 : 초

    it_dist_FLAG++;

    init_lc_T1_STM_IT(rotation_time_T1);
}

void T2_straight(void)
{
    T2_straight_flag = FALSE;

    adjust_RPM_equal();

    travel_time_T2 = 0.2;//calculate_T2_time();

    uint32 travel_time_T2_ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, (uint32)(travel_time_T2*1000));

    //init_lc_T2_STM_IT(travel_time_T2);

    it_dist_FLAG++;

    IfxStm_increaseCompare(&MODULE_STM2, LC_T1_STMConf.comparator, (uint32)travel_time_T2_ticks);
}

void T3_rotation_left(void)
{
    T3_rotation_flag = FALSE;

    //float32 rotation_time_T3 = TARGET_ANGLE_RADIAN / ANGULAR_VELOCITY_RADIAN;

    set_turn(Left, ANGULAR_VELOCITY_RADIAN);

    uint32 travel_time_T3_ticks = 2;//IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, (uint32)(rotation_time_T1*1000));

    it_dist_FLAG++;

    //init_lc_T3_STM_IT(rotation_time_T1);
    IfxStm_increaseCompare(&MODULE_STM2, LC_T1_STMConf.comparator, (uint32)travel_time_T3_ticks);
}

void lc_final_procedure(void)
{
    T3_rotation_end_flag = FALSE;

    it_dist_FLAG = 0;

    IfxStm_enableComparatorInterrupt(&MODULE_STM1, IfxStm_Comparator_0);
    FCA_ENABLE_FLAG = TRUE;
}

void isr_lc_T1_stm(void)
{
    if(it_dist_FLAG == 1)
    {
        T2_straight_flag = TRUE;
    }

    if(it_dist_FLAG == 2)
    {
        T3_rotation_flag = TRUE;
    }

    if(it_dist_FLAG == 3)
    {
        T3_rotation_end_flag = TRUE;
    }

}

void isr_lc_T2_stm(void)
{
    T3_rotation_flag = TRUE;
}

void isr_lc_T3_stm(void)
{
    T3_rotation_end_flag = TRUE;
}

void init_lc_T1_STM_IT(float32 rotation_time_T1)
{
    IfxStm_initCompareConfig(&LC_T1_STMConf);
    rotation_time_T1_ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, (uint32)(rotation_time_T1*1000));

    LC_T1_STMConf.triggerPriority = ISR_PRIORITY_LC_T1_STM;
    LC_T1_STMConf.typeOfService = IfxSrc_Tos_cpu0;
    LC_T1_STMConf.ticks = (uint32)rotation_time_T1_ticks;
    IfxStm_initCompare(&MODULE_STM2, &LC_T1_STMConf);
}

void init_lc_T2_STM_IT(float32 travel_time_T2)
{
    IfxStm_initCompareConfig(&LC_T2_STMConf);
    uint32 travel_time_T2_ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, (uint32)(travel_time_T2*1000));

    LC_T2_STMConf.triggerPriority = ISR_PRIORITY_LC_T2_STM;
    LC_T2_STMConf.typeOfService = IfxSrc_Tos_cpu0;
    LC_T2_STMConf.ticks = (uint32)travel_time_T2_ticks;
    IfxStm_initCompare(&MODULE_STM2, &LC_T2_STMConf);
}

void init_lc_T3_STM_IT(float32 rotation_time_T3)
{
    IfxStm_initCompareConfig(&LC_T3_STMConf);
    uint32 travel_time_T3_ticks = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, (uint32)(rotation_time_T3*1000));

    LC_T3_STMConf.triggerPriority = ISR_PRIORITY_LC_T3_STM;
    LC_T3_STMConf.typeOfService = IfxSrc_Tos_cpu0;
    LC_T3_STMConf.ticks = (uint32)travel_time_T3_ticks;
    IfxStm_initCompare(&MODULE_STM2, &LC_T3_STMConf);
}

void adjust_RPM_equal(void)
{
    RPM_CMD1 = origin_RPM_CMD1;
    RPM_CMD2 = origin_RPM_CMD2;
}

float32 calculate_T2_time(void)
{
    float32 current_speed = getCurrentSpeed();

    float32 vertical_distance = LANE_WIDTH - 2*(turn_radius - turn_radius*cos(TARGET_ANGLE_DEGREE));

    float32 diagonal_distance = vertical_distance / sin(TARGET_ANGLE_DEGREE);

    float32 travel_time_T2 = diagonal_distance / current_speed;

    return travel_time_T2;
}


