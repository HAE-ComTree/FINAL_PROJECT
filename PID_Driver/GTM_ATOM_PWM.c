/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "GTM_ATOM_PWM.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_ATOM  20
#define LED                IfxGtm_ATOM1_1_TOUT1_P02_1_OUT
#define Motor_B_PWM        IfxGtm_ATOM1_3_TOUT105_P10_3_OUT
#define PWM_PERIOD         5000
#define CLK_FREQ           1000000.0f
#define PWMA_PIN &MODULE_P02,1   // Motor_A PWM 핀 (P2.1)
#define BRAKEA_PIN &MODULE_P02,7 // Motor_A 브레이크 핀 (P2.7)
#define DIRA_PIN &MODULE_P10,1   // Motor_A 방향 제어 핀 (P10.1)
#define Motor_B_PWMA_PIN &MODULE_P10,3 //Motor_B PWM 핀(P10,3)
#define Motor_B_BRAKE_PIN &MODULE_P02,6 //Motor_B 브레이크 핀(P2.6)
#define Motor_B_DIR_PIN &MODULE_P10,2   //Motor_B 방향 제어 핀(P10.2)

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxGtm_Atom_Pwm_Config g_atomConfig;                            /* Timer configuration structure                    */
IfxGtm_Atom_Pwm_Config Motor_B_g_atomConfig;
IfxGtm_Atom_Pwm_Driver g_atomDriver;                            /* Timer Driver structure                           */
IfxGtm_Atom_Pwm_Driver Motor_B_g_atomDriver;
uint32 g_PWMValue = 0;                                         /* Initialization of the fade value                 */

/*********************************************************************************************************************/
/*-----------------------------------------------Function Prototypes-------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*--------------------------------------------Function Implementations-----------------------------------------------*/
/*********************************************************************************************************************/
/* This function initializes the ATOM */
void initGtmATomPwm(void)
{
    IfxGtm_enable(&MODULE_GTM); /* Enable GTM */

    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, CLK_FREQ);        /* Set the CMU clock 0 frequency    */
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);                /* Enable the CMU clock 0           */

    IfxGtm_Atom_Pwm_initConfig(&g_atomConfig, &MODULE_GTM);                     /* Initialize default parameters    */
    IfxGtm_Atom_Pwm_initConfig(&Motor_B_g_atomConfig, &MODULE_GTM);

    g_atomConfig.atom = LED.atom;                                       /* Select the ATOM depending on the LED     */
    g_atomConfig.atomChannel = LED.channel;                             /* Select the channel depending on the LED  */
    g_atomConfig.period = PWM_PERIOD;                                   /* Set timer period                         */
    g_atomConfig.pin.outputPin = &LED;                                  /* Set LED as output                        */
    g_atomConfig.synchronousUpdateEnabled = TRUE;                       /* Enable synchronous update                */

    Motor_B_g_atomConfig.atom = Motor_B_PWM.atom;
    Motor_B_g_atomConfig.atomChannel = Motor_B_PWM.channel;
    Motor_B_g_atomConfig.period = PWM_PERIOD;
    Motor_B_g_atomConfig.pin.outputPin = &Motor_B_PWM;
    Motor_B_g_atomConfig.synchronousUpdateEnabled = TRUE;

    IfxGtm_Atom_Pwm_init(&g_atomDriver, &g_atomConfig);
    IfxGtm_Atom_Pwm_start(&g_atomDriver, TRUE);

    IfxGtm_Atom_Pwm_init(&Motor_B_g_atomDriver, &Motor_B_g_atomConfig);
    IfxGtm_Atom_Pwm_start(&Motor_B_g_atomDriver, TRUE);
}

void PWM_set(uint32 g_PWMValue)
{
    if(g_PWMValue >= PWM_PERIOD)
    {
        g_PWMValue = PWM_PERIOD; /* Set the direction of the fade */
    }
    else if(g_PWMValue <= 0)
    {
        g_PWMValue = 0;  /* Set the direction of the fade */
    }
    setDutyCycle(g_PWMValue); /* Call the function which is setting the duty cycle of the PWM */
}

void PWM_Motor_B_set(uint32 g_PWMValue)
{
    if(g_PWMValue >= PWM_PERIOD)
    {
        g_PWMValue = PWM_PERIOD; /* Set the direction of the fade */
    }
    else if(g_PWMValue <= 0)
    {
        g_PWMValue = 0;  /* Set the direction of the fade */
    }
    setMotor_B_DutyCycle(g_PWMValue); /* Call the function which is setting the duty cycle of the PWM */
}

/* This function sets the duty cycle of the PWM */
void setDutyCycle(uint32 dutyCycle)
{
    g_atomConfig.dutyCycle = dutyCycle;                 /* Set duty cycle        */
    IfxGtm_Atom_Pwm_init(&g_atomDriver, &g_atomConfig); /* Re-initialize the PWM */
}

void setMotor_B_DutyCycle(uint32 dutyCycle)
{
    Motor_B_g_atomConfig.dutyCycle = dutyCycle;
    IfxGtm_Atom_Pwm_init(&Motor_B_g_atomDriver, &Motor_B_g_atomConfig);
}

// 모터 제어 함수
void setMotorControl(uint8 direction, uint8 enable)
{
    // 브레이크 설정
    if (enable == 0)
    {
        IfxPort_setPinState(BRAKEA_PIN, IfxPort_State_high); // 브레이크 활성화

        // PWM 출력 중지
        GTM_ATOM1_AGC_GLB_CTRL.B.UPEN_CTRL1 = 0;

        return;
    }
    else
    {
        IfxPort_setPinState(BRAKEA_PIN, IfxPort_State_low); // 브레이크 비활성화

        //GTM_TOM0_TGC0_GLB_CTRL.B.UPEN_CTRL1 = 2;
        GTM_ATOM1_AGC_GLB_CTRL.B.UPEN_CTRL1 = 2;
    }

    // 방향 설정
    if (direction == 0)
    {
        IfxPort_setPinState(DIRA_PIN, IfxPort_State_low); // 정방향
    }
    else
    {
        IfxPort_setPinState(DIRA_PIN, IfxPort_State_high); // 역방향
    }
}

void setMotor_B_Control(uint8 direction, uint8 enable)
{
    // 브레이크 설정
    if (enable == 0)
    {
        IfxPort_setPinState(Motor_B_BRAKE_PIN, IfxPort_State_high); // 브레이크 활성화

        // PWM 출력 중지
        GTM_ATOM1_AGC_GLB_CTRL.B.UPEN_CTRL3 = 0;

        return;
    }
    else
    {
        IfxPort_setPinState(Motor_B_BRAKE_PIN, IfxPort_State_low); // 브레이크 비활성화

        //GTM_TOM0_TGC0_GLB_CTRL.B.UPEN_CTRL1 = 2;
        GTM_ATOM1_AGC_GLB_CTRL.B.UPEN_CTRL3 = 2;
    }

    // 방향 설정
    if (direction == 0)
    {
        IfxPort_setPinState(Motor_B_DIR_PIN, IfxPort_State_low); // 정방향
    }
    else
    {
        IfxPort_setPinState(Motor_B_DIR_PIN, IfxPort_State_high); // 역방향
    }
}

void initPins(void)
{
    // 방향 핀 초기화
    IfxPort_setPinMode(DIRA_PIN, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinState(DIRA_PIN, IfxPort_State_low);

    IfxPort_setPinMode(Motor_B_DIR_PIN, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinState(Motor_B_DIR_PIN, IfxPort_State_low);

    // 브레이크 핀 초기화
    IfxPort_setPinMode(BRAKEA_PIN, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinState(BRAKEA_PIN, IfxPort_State_low);

    IfxPort_setPinMode(Motor_B_BRAKE_PIN, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinState(Motor_B_BRAKE_PIN, IfxPort_State_low);
}
