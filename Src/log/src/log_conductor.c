/***************************************************************************************************
 * @file LOG_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup LOG_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "cmsis_os2.h"
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t log_task_attributes =
    {
        .priority = (osPriority_t)osPriorityLow,
        .name = "LOG",
        .stack_size = 1024,
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void log_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void log_task(void *argument)
{
    while (1)
    {
        osThreadFlagsWait(0x00, osFlagsWaitAny, osWaitForever);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t log_conductor_init(void)
{
    return (osThreadNew(log_task, NULL, &log_task_attributes)
                ? RET_SUCCESS
                : RET_INT_ERROR);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
