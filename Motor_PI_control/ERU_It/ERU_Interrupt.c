/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include <PID_Driver/STM_Interrupt.h>
#include "ERU_Interrupt.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define ISR_PRIORITY_SCUERU_INT0   30                       /* Define the SCU ERU interrupt priority                */
#define ISR_PRIORITY_DECEL         33
#define REQ_IN_ACCEL                     &IfxScu_REQ8_P33_7_IN    /* External request pin                                 */
#define REQ_IN_DECEL                     &IfxScu_REQ1_P15_8_IN

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
ERUconfig ACCEL_ERUconfig;                                      /* SCU_ERU global data                                  */
ERUconfig DECEL_ERUconfig;

/*********************************************************************************************************************/
/*----------------------------------------------Function Implementations---------------------------------------------*/
/*********************************************************************************************************************/
/* Macro to define Interrupt Service Routine.
 * This macro makes the following definitions:
 * 1) Define linker section as .intvec_tc<vector number>_<interrupt priority>.
 * 2) Define compiler specific attribute for the interrupt functions.
 * 3) Define the Interrupt Service Routine as ISR function.
 *
 * IFX_INTERRUPT(isr, vectabNum, priority)
 *  - isr: Name of the ISR function.
 *  - vectabNum: Vector table number.
 *  - priority: Interrupt priority. Refer Usage of Interrupt Macro for more details.
 */

boolean volatile ERU_FLAG = FALSE;
IFX_INTERRUPT(SCUERU_Int0_Handler, 0, ISR_PRIORITY_SCUERU_INT0);

/* Interrupt Service Routine */
void SCUERU_Int0_Handler(void)
{
    //IfxPort_setPinState(LED, IfxPort_State_toggled);                        /* Toggle LED                       */
    //ERU_FLAG = TRUE;
    RPM_CMD1 += 500;
}

IFX_INTERRUPT(DECEL_Int0_Handler, 0, ISR_PRIORITY_DECEL);
void DECEL_Int0_Handler(void)
{
    //IfxPort_setPinState(LED, IfxPort_State_toggled);                        /* Toggle LED                       */
    //ERU_FLAG = TRUE;
    RPM_CMD1 -= 500;
}

/* This functions initializes the output pin for the LED and the pin which toggles the state for generating
 * the falling and rising edges which are used to trigger the interrupt.
 * Additionally this function is configuring the ERU module including the service request configuration */
void initPeripheralsAndERU(void)
{
    /* Initialize pins which are used to trigger and visualize the interrupt and set the default states */
    //IfxPort_setPinMode(TRIGGER_PIN, IfxPort_Mode_inputPullDown);              /* Initialize TRIGGER_PIN port pin  */
    //IfxPort_setPinMode(LED, IfxPort_Mode_outputPushPullGeneral);            /* Initialize LED port pin          */
    //IfxPort_setPinState(LED, IfxPort_State_high);                           /* Turn off LED (LED is low-active) */

    /* Trigger pin */
    ACCEL_ERUconfig.reqPin = REQ_IN_ACCEL; /* Select external request pin */

    /* Initialize this pin with pull-down enabled
     * This function will also configure the input multiplexers of the ERU (Register EXISx)
     */
    IfxScuEru_initReqPin(ACCEL_ERUconfig.reqPin, IfxPort_InputMode_pullUp);

    /* Determine input channel depending on input pin */
    ACCEL_ERUconfig.inputChannel = (IfxScuEru_InputChannel) ACCEL_ERUconfig.reqPin->channelId;

    /* Input channel configuration */
    IfxScuEru_enableRisingEdgeDetection(ACCEL_ERUconfig.inputChannel);          /* Interrupt triggers on
                                                                               rising edge (Register RENx) and  */
    //IfxScuEru_enableFallingEdgeDetection(g_ERUconfig.inputChannel);         /* on falling edge (Register FENx)  */

    /* Signal destination */
    ACCEL_ERUconfig.outputChannel = IfxScuEru_OutputChannel_0;                  /* OGU channel 0                    */
    /* Event from input ETL0 triggers output OGU0 (signal TRx0) */
    ACCEL_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_0;

    /* Connecting Matrix, Event Trigger Logic ETL block */
    /* Enable generation of trigger event (Register EIENx) */
    IfxScuEru_enableTriggerPulse(ACCEL_ERUconfig.inputChannel);
    /* Determination of output channel for trigger event (Register INPx) */
    IfxScuEru_connectTrigger(ACCEL_ERUconfig.inputChannel, ACCEL_ERUconfig.triggerSelect);

    /* Configure Output channels, OutputGating Unit OGU (Register IGPy) */
    IfxScuEru_setInterruptGatingPattern(ACCEL_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

    /* Service request configuration */
    /* Get source pointer depending on outputChannel (SRC_SCUERU0 for outputChannel0) */
    ACCEL_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int) ACCEL_ERUconfig.outputChannel % 4];
    IfxSrc_init(ACCEL_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_SCUERU_INT0);
    IfxSrc_enable(ACCEL_ERUconfig.src);

    /*--------------------------------------------------------------------------------------*/
    DECEL_ERUconfig.reqPin = REQ_IN_DECEL; /* Select external request pin */
    IfxScuEru_initReqPin(DECEL_ERUconfig.reqPin, IfxPort_InputMode_pullUp);
    DECEL_ERUconfig.inputChannel = (IfxScuEru_InputChannel) DECEL_ERUconfig.reqPin->channelId;
    IfxScuEru_enableRisingEdgeDetection(DECEL_ERUconfig.inputChannel);
    DECEL_ERUconfig.outputChannel = IfxScuEru_OutputChannel_1;
    DECEL_ERUconfig.triggerSelect = IfxScuEru_InputNodePointer_1;
    IfxScuEru_enableTriggerPulse(DECEL_ERUconfig.inputChannel);
    IfxScuEru_connectTrigger(DECEL_ERUconfig.inputChannel, DECEL_ERUconfig.triggerSelect);
    IfxScuEru_setInterruptGatingPattern(DECEL_ERUconfig.outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);
    DECEL_ERUconfig.src = &MODULE_SRC.SCU.SCU.ERU[(int) DECEL_ERUconfig.outputChannel % 4];
    IfxSrc_init(DECEL_ERUconfig.src, IfxSrc_Tos_cpu0, ISR_PRIORITY_DECEL);
    IfxSrc_enable(DECEL_ERUconfig.src);
}
