#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"
#include "IfxStm.h"
#include "Ifx_Types.h"
#include "Ifx_DateTime.h"
#include "SysSe/Bsp/Bsp.h"
#include "Encoder.h"
#include "GTM_ATOM_PWM.h"
#include "STM_Interrupt.h"
#include "ERU_Interrupt.h"
#include "It_Handler.h"
#include "Set_Driving_Mode.h"

IfxCpu_syncEvent g_cpuSyncEvent = 0;

int core0_main(void)
{
    int CountForStop = 0;
    // Initialize system
    IfxCpu_enableInterrupts();

    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    initIncrEnc();
    initGtmATomPwm();
    initPins();
    initPeripherals();
    initPeripheralsAndERU();

    while(1)
    {
        if(CountForStop == 10000000)
        {
            //Car_Change_Direction_Right();
        }

        if(STM_IT_FLAG == TRUE)
        {
            Enc_10ms_Handler();
        }

        if(RPM_CMD1 > 0 && RPM_CMD2 > 0)
        {
            CountForStop++;
        }
    }

    return 0;
}
