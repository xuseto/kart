/***************************************************************************************************
 * @file dac_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 17/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief dac 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup DAC_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "cmsis_os2.h"
#include <stdlib.h>
#include <def_common.h>
#include <stdio.h>

#include "dac_thread.h"
#include "dac_dac8554.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t dac_task_attributes = {
    .priority = (osPriority_t)osPriorityLow,
    .stack_size = 1024};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 * 
 * @param argument \ref dac_t
 */
void dac_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void dac_task(void *argument)
{
    dac_t *dac = (dac_t *)argument;
    uint32_t flag_thread;
    uint16_t data = 5;

    while (1)
    {
        flag_thread = osThreadFlagsWait(0x00, osFlagsWaitAny, 500);

        dac_dac8554_write_buffer(dac, DAC_A, (uint16_t *)data);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
osThreadId_t dac_create_thread(const char *name_thread, void *arg)
{
    if (!name_thread || !arg)
    {
        return NULL;
    }

    // Make thread
    dac_task_attributes.name = name_thread ? name_thread : "unknown";
    return (osThreadNew(dac_task, arg, &dac_task_attributes));
}

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
