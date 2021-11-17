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

#include <dac/dac_api.h>
#include "dac_thread.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t dac_task_attributes = {
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 0
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 * 
 * @param argument \ref dac_t
 */
void dac_task ( void *argument );

/* Private functions -----------------------------------------------------------------------------*/
void dac_task ( void *argument )
{
  dac_t *dac = (dac_t *)argument;
  uint32_t flag_thread;

  printf ("Enter thread of DAC \n");
  while (1)
  {
    flag_thread = osThreadFlagsWait (0x00, osFlagsWaitAny, osWaitForever);
  }
}
/* Public functions ------------------------------------------------------------------------------*/
osThreadId_t dac_create_thread (dac_cfg_t *cfg, void *arg)
{
    osThreadId_t ret = NULL;

    if (!cfg || !arg) return ret;

    // Make thread
    dac_task_attributes.name = cfg->name ? cfg->name :  "unknown";
    return ( osThreadNew(dac_task, arg, &dac_task_attributes) );

}

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
