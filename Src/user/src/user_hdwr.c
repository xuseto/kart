/***************************************************************************************************
 * @file user_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup USER_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "user_hdwr.h"
#include "user/user_api.h"
#include "user/user_config.h"
#include "hdwr/fifo_api.h"
/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
static uint16_t get_lenght_msg(void);
/* Private functions -----------------------------------------------------------------------------*/
static uint16_t get_lenght_msg(void)
{
#ifdef USER_SIZE_PAYLOAD_RX_ONE_MSG_ONE_DATA
    return USER_SIZE_PAYLOAD_RX_ONE_MSG_ONE_DATA;
#else
    return 0;
#endif
}
/* Public functions ------------------------------------------------------------------------------*/
ret_code_t user_hdwr_init(user_t *obj, user_cfg_t *cfg)
{
    cfg->fifo_cfg.size_msg = get_lenght_msg();

    obj->id_fifo = fifo_create_queue(&cfg->fifo_cfg);

    ret_code_t ret = (obj->id_fifo) ? uart_suscribe_rx_fifo(obj->id_fifo, cfg->fifo_cfg.size_msg, cfg->uart_number) : RET_INT_ERROR;

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
