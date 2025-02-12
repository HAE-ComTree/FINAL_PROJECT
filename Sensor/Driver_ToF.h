#ifndef DEVICEDRIVER_DRIVER_TOF_H_
#define DEVICEDRIVER_DRIVER_TOF_H_


/***********************************************************************/
/*Include*/
/***********************************************************************/
#include "IfxPort_reg.h"
#include "IfxPort_bf.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "IfxAsclin_reg.h"
#include "IfxAsclin_bf.h"
#include "IfxAsclin_Asc.h"
#include "IfxSrc_reg.h"
#include "Platform_Types.h"

/***********************************************************************/
/*Typedef*/
/***********************************************************************/

/***********************************************************************/
/*Define*/
/***********************************************************************/
#define ASC1_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC1_RX_BUFFER_SIZE          256
#define ASC1_BAUDRATE                921600

#define ISR_PRIORITY_ASCLIN1_TX     0x21    /* Priority for interrupt ASCLIN1 Transmit  */
#define ISR_PRIORITY_ASCLIN1_RX     0x20    /* Priority for interrupt ASCLIN1 Receive   */
#define ISR_PRIORITY_ASCLIN1_ER     0x22    /* Priority for interrupt ASCLIN1 Errors    */

/***********************************************************************/
/*External Variable*/
/***********************************************************************/
extern uint32_t tof_distance;
/***********************************************************************/
/*Global Function Prototype*/
/***********************************************************************/


void init_tof(void);
uint32 get_tof_distance(void);


#endif /* DEVICEDRIVER_DRIVER_TOF_H_ */
