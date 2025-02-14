/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <FCA_Interrupt/FCA.h>
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define STM1                           &MODULE_STM1
#define ISR_PRIORITY_FCA_STM           50
#define FCA_TIME_INTERVAL              100 //단위 : ms
#define Safety_Distance                150 //단위 : mm, 감속 시작 거리 450
#define MAX_SPEED                      300
#define MIN_SPEED                      70

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxStm_CompareConfig FCA_STMConf;
Ifx_TickTime g_ticksFor100ms;
boolean FCA_IT_FLAG = FALSE;

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
IFX_INTERRUPT(isrFCA, 0, ISR_PRIORITY_FCA_STM);

void isrFCA(void)
{
    FCA_IT_FLAG = TRUE;
}

void initFCASTM(void)
{
    IfxStm_initCompareConfig(&FCA_STMConf);
    g_ticksFor100ms = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, FCA_TIME_INTERVAL);

    FCA_STMConf.triggerPriority = ISR_PRIORITY_FCA_STM;
    FCA_STMConf.typeOfService = IfxSrc_Tos_cpu0;
    FCA_STMConf.ticks = (uint32)g_ticksFor100ms;
    IfxStm_initCompare(STM1, &FCA_STMConf);
}

void performFCA(void)
{
    uint32_t Front_Distance = get_kalman_val();
    float32 Kp_FCA = 1.0f;
    float32 targetSpeed = 0;

    //거리에 따른 속도 제어
    if(Front_Distance > Safety_Distance)
    {
        targetSpeed = Kp_FCA * (Front_Distance - Safety_Distance);
    }
    else
    {
        targetSpeed = 0;
    }

    //최대속도, 최소속도 설정
    if(targetSpeed > MAX_SPEED)
    {
        targetSpeed = MAX_SPEED;
    }
    else if(Front_Distance > Safety_Distance && targetSpeed < MIN_SPEED)
    {
        targetSpeed = MIN_SPEED;
    }

    setTargetSpeed(targetSpeed);

    FCA_IT_FLAG = FALSE;
    IfxStm_increaseCompare(STM1, FCA_STMConf.comparator, (uint32)g_ticksFor100ms);
}
