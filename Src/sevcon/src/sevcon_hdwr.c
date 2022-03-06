/***************************************************************************************************
 * @file sevcon_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_hdwr.h"

#include <hdwr/can_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_hdwr_init(sevcon_cfg_t *cfg, sevcon_t *data)
{
    cfg->fifo_cfg.size_msg = sizeof(can_msg_t);

    data->fifo_id = fifo_create_queue(&cfg->fifo_cfg);

    return ((data->fifo_id) ? RET_SUCCESS : RET_INT_ERROR);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
