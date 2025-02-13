/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Set_Driving_Mode.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define STM                     &MODULE_STM1
#define WHEEL_RADIUS            32.5f  // 바퀴 반지름 (단위: mm)
#define WHEEL_BASE              190.0f //휠 베이스 : 190mm
#define MIN_RADIUS              WHEEL_BASE*1.2f //최소회전반경 : 휠베이스 * 1.2
#define MAX_RADIUS              WHEEL_BASE*5.0f //최대회전반경 : 휠베이스 * 5
#define Maximum_RPM             300
#define Minimum_RPM             -300
#define GEAR_RATIO              18.75

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
float32 CurrentTargetSpeed = 0;

/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/


/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void Set_Stop(void)
{
    while(RPM_CMD1 > 0 || RPM_CMD2 > 0)
    {
        RPM_CMD1 -= 5;
        RPM_CMD2 -= 5;

        if(RPM_CMD1 < 0)
        {
            RPM_CMD1 = 0;

        }
        if(RPM_CMD2 < 0)
        {
            RPM_CMD2 = 0;
        }

        //delay_ms(100);
    }

    setMotorControl(0, 0);
    setMotor_B_Control(0, 0);
}

void setTargetSpeed(float32 targetSpeed)
{
    CurrentTargetSpeed = targetSpeed;
}

void Adjust_To_Target_Speed(void)//단위 : m/s
{
    float32 caculatedRPM = (CurrentTargetSpeed * 60.0f)/(2.0f * 3.14159f * WHEEL_RADIUS);
    float32 rampRate = 5.0f;

    //목표 RPM 계산
    if(caculatedRPM > Maximum_RPM)
    {
        caculatedRPM = Maximum_RPM;
    }
    else if(caculatedRPM < Minimum_RPM)
    {
        caculatedRPM = Minimum_RPM;
    }

    //목표 RPM을 점진적으로 변경
    if (RPM_CMD1 < caculatedRPM)
    {
        RPM_CMD1 += rampRate;
        if (RPM_CMD1 > caculatedRPM) // 목표치를 초과하지 않도록 보정
            RPM_CMD1 = caculatedRPM;
    }
    else if (RPM_CMD1 > caculatedRPM)
    {
        RPM_CMD1 -= rampRate;
        if (RPM_CMD1 < caculatedRPM) // 목표치를 초과하지 않도록 보정
            RPM_CMD1 = caculatedRPM;
    }

    RPM_CMD2 = RPM_CMD1;
}

void Set_Turn(Direction direction, float32 turn_angle)
{
    float32 TurnRadius = MIN_RADIUS + (MAX_RADIUS - MIN_RADIUS) * (turn_angle / 180.0f); //각도에 따른 회전반경 계산, turn_angle을 0~1로 정규화
    float32 Base_Speed = 0;
    float32 innerWheelSpeed = 0;
    float32 outerWheelSpeed = 0;
    float32 innerRPM = 0;
    float32 outerRPM = 0;

    Base_Speed = getCurrentSpeed(); //RPM_CMD1, RPM_CMD2의 평균으로 현재 속도를 계산

    //바깥쪽 바퀴 속도 : 현재 속도 * (회전반경 + 휠베이스/2)/회전 반경
    //안쪽 바퀴 속도 : 현재 속도 * (회전반경 - 휠베이스/2)/회전반경
    innerWheelSpeed = Base_Speed * (TurnRadius - WHEEL_BASE/2)/TurnRadius;
    outerWheelSpeed = Base_Speed * (TurnRadius + WHEEL_BASE/2)/TurnRadius;

    //휠 속도를 RPM으로 변환
    innerRPM = (innerWheelSpeed * 60.0f)/(2.0f*3.14159f*WHEEL_RADIUS);
    outerRPM = (outerWheelSpeed * 60.0f)/(2.0f*3.14159f*WHEEL_RADIUS);

    if(innerRPM > 300) innerRPM = 300;
    if(outerRPM > 300) outerRPM = 300;

    if(direction == Right)//오른쪽
    {
        RPM_CMD1 = outerRPM;
        RPM_CMD2 = innerRPM;
    }
    else //왼쪽
    {
        RPM_CMD1 = innerRPM;
        RPM_CMD2 = outerRPM;
    }
}

float32 getCurrentSpeed(void)
{
    float32 MotorA_Current_RPM_Multiplied_By_Ratio = - motor_speed_rpm;
    float32 MotorB_Current_RPM_Multiplied_By_Ratio = Motor_B_motor_speed_rpm;

    float32 MotorA_Current_RPM = MotorA_Current_RPM_Multiplied_By_Ratio / GEAR_RATIO;
    float32 MotorB_Current_RPM = MotorB_Current_RPM_Multiplied_By_Ratio / GEAR_RATIO;

    float32 Current_RPM_AVG = (MotorA_Current_RPM + MotorB_Current_RPM) / 2.0f;
    float32 BASE_SPEED = (Current_RPM_AVG * 2 * 3.14159 * WHEEL_RADIUS) / 60.0f;

    return BASE_SPEED;
}

void delay_ms(uint32 ms)
{
    uint32 ticks = IfxStm_getTicksFromMilliseconds(STM, ms);
    IfxStm_waitTicks(STM, ticks);
}
