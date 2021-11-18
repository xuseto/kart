/***************************************************************************************************
 * @file heartbeat_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 11/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief HeartBeat 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup HEARTBEAT_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include <heartbeat/heartbeat_api.h>
#include "cmsis_os2.h"
#include <stdlib.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** data of heartbeat */
typedef struct heartbeat_s
{
  gpio_out_t gpio;      /**< Fixed the GPIO of LED */
  uint32_t delay_ms;  /**< Time of delay for toggle led, in ms */
  osThreadId_t id_thread; /**< ID of thread */
} heartbeat_t;

/** Definitions for defaultTask */
osThreadAttr_t heartbeat_task_attributes = {
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 0
};
/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run task of heartbeat thread
 *  
 * @param argument \ref heartbeat_t
 */
void heartbeat_task ( void *argument );

/* Private functions -----------------------------------------------------------------------------*/
void heartbeat_task ( void *argument )
{
  heartbeat_t *heartbeat = (heartbeat_t *)argument;

  while (1)
  {
    osDelay(heartbeat->delay_ms);

    gpio_toggle (heartbeat->gpio);
  }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t heartbeat_init (heartbeat_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg) return ret;

    heartbeat_t *heartbeat = (heartbeat_t *)calloc (1, sizeof(heartbeat_t));
    ret = (heartbeat) ? RET_SUCCESS : RET_INT_ERROR;

    if (RET_SUCCESS == ret)
    {
      heartbeat->delay_ms = cfg->delay_ms;
      heartbeat->gpio = cfg->gpio;
      
      // Make thread
      heartbeat_task_attributes.name = cfg->name ? cfg->name :  "unknown";
      heartbeat->id_thread = osThreadNew(heartbeat_task, heartbeat, &heartbeat_task_attributes);
      ret = (heartbeat->id_thread) ? RET_SUCCESS : RET_INT_ERROR ;
    }

    if (RET_SUCCESS == ret)
    {
      printf ("Created thread : %s \n", cfg->name);
    }
     
    return ret;

}

<<<<<<< HEAD
//--------------------------------------------------------------------------------------------------
void heartbeat_task ( void *argument )
{
  heartbeat_t *heartbeat = (heartbeat_t *)argument;
  uint32_t flag_thread;

  while (1)
  {
    
    flag_thread = osThreadFlagsWait (0x00, osFlagsWaitAny, heartbeat->delay_ms);

    if ((uint32_t)osErrorTimeout == flag_thread)
    {
        gpio_toggle (heartbeat->gpio);
    }
  }
}


=======
>>>>>>> i2c
/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
