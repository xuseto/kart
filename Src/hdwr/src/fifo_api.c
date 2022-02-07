
/***************************************************************************************************
 * @file fifo_api.c 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 28/11/2021
 * @date Last modification 28/11/2021 by jnieto
 * @brief Cretated FIFOs with CMSIS
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FIFO_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/fifo_api.h"

#include <string.h>
#include <cmsis_os2.h>

#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Maximum char for name fifos */
#define FIFO_MAX_NAME 20

/** Init name queue fifos */
#define FIFO_INIT_NAME "FIFO_"

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
fifo_t fifo_create_queue(fifo_cfg_t *cfg)
{
    osMessageQueueAttr_t attr;
    char name_fifo[FIFO_MAX_NAME];

    if (!cfg)
    {
        return NULL;
    }

    /* Create name fifo */
    strncat(name_fifo, FIFO_INIT_NAME, sizeof(FIFO_INIT_NAME) - 1);
    if (cfg->name)
    {
        strncat(name_fifo, cfg->name, sizeof(cfg->name));
    }
    attr.name = name_fifo;

    return (osMessageQueueNew(cfg->num_msg, cfg->size_msg, &attr));
}

//--------------------------------------------------------------------------------------------------
ret_code_t fifo_enqueue_msg(fifo_t fifo, void *msg)
{
    ret_code_t ret = RET_PARAM_ERROR;

    if (!fifo || !msg)
    {
        return ret;
    }

    return ((osOK == osMessageQueuePut(fifo, msg, NULL, NULL)) ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
void *fifo_dequeue_msg(fifo_t fifo)
{
  void *msg = {0};

    if (!fifo)
    {
        return NULL;
    }

    if (osOK != osMessageQueueGet(fifo, msg, NULL, NULL))
    {
        msg = NULL;
    }

    return msg;
}

//--------------------------------------------------------------------------------------------------
uint32_t fifo_get_space(fifo_t fifo)
{

    if (!fifo)
    {
        return NULL;
    }

    return osMessageQueueGetSpace(fifo);
}

//--------------------------------------------------------------------------------------------------
ret_code_t fifo_reset(fifo_t fifo)
{

    if (!fifo)
    {
        return RET_PARAM_ERROR;
    }

    return (osOK == osMessageQueueReset(fifo)) ? RET_SUCCESS : RET_PARAM_ERROR;
}

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/