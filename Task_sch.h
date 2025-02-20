#ifndef TASK_SCH_H_
#define TASK_SCH_H_

#include <stdint.h>
#include "IfxStm.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort_regdef.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"

/* Define macros for task intervals */
#define STM_MODULE         &MODULE_STM0
#define ISR_PRIORITY_STM   10
#define TICKS_10MS              (IfxStm_getTicksFromMilliseconds(STM_MODULE, 10))

/* Function prototypes */
void stm0ISR(void);

void initCanTaskScheduler (void);

extern void handle10msTask(void);
extern void handle30msTask(void);
extern void handle50msTask(void);
extern void handle100msTask(void);
extern void handle500msTask(void);
extern void handle1sTask(void);

boolean toggle_BCW_Flag(void);

#endif /* TASK_SCH_H_ */
