/***************************************************************************************************
 * @file mcp4728_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 11/11/2021
 * @date Last modification 11/11/2021 by jnieto
 * @brief mcp4728 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup MCP4728_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <mcp4728/mcp4728_api.h>
#include "cmsis_os2.h"
#include <stdlib.h>

#include "stm32l5xx_hal_i2c.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** data of mcp4728 */
typedef struct mcp4728_s
{
  void *obj_com;      /**< Ptr obj of comunication */
  osThreadId_t id_thread; /**< ID of thread */
} mcp4728_t;

/** Definitions for defaultTask */
osThreadAttr_t mcp4728_task_attributes = {
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048
};

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run task of MCP4728 thread
 * 
 * @param argument \ref mcp4728_t
 */
void mcp4728_task (void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void mcp4728_task (void *argument)
{
  HAL_
 
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t mcp4728_init (mcp4728_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg) return ret;

    mcp4728_t *mcp4728 = (mcp4728_t *)calloc (1, sizeof(mcp4728_t));
    ret = (mcp4728) ? RET_SUCCESS : RET_INT_ERROR;

    if (mcp4728)
    {
      // Make thread
      mcp4728_task_attributes.name = cfg->name ? cfg->name :  "unknown";
      mcp4728->id_thread = osThreadNew(mcp4728_task, mcp4728, &mcp4728_task_attributes);
      ret = (mcp4728->id_thread) ? RET_SUCCESS : RET_INT_ERROR ;
    }

    return ret;
}

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
