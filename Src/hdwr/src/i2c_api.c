
/***************************************************************************************************
 * @file i2c_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 15/11/2021
 * @date Last modification 15/11/2021 by jnieto
 * @brief I2C
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup I2C_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hwdr/i2c_api.h"
#include "main.h"
#include <stm32l5xx_hal_i2c.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
__attribute__((weak)) extern I2C_HandleTypeDef hi2c1;
__attribute__((weak)) extern I2C_HandleTypeDef hi2c2;
__attribute__((weak)) extern I2C_HandleTypeDef hi2c3;
__attribute__((weak)) extern I2C_HandleTypeDef hi2c4;

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void *i2c_get_instance (i2c_number_t i2c_number)
{
    I2C_HandleTypeDef *ret = 0x00;

    switch (i2c_number)
    {
    case i2c_a:
        ret = &hi2c1;
        break;
    case i2c_b:
        ret = &hi2c2;
        break;
    case i2c_c:
        ret = &hi2c3;
        break; 
    case i2c_d:
        ret = &hi2c4;
        break;
    
    default:
        break;
    }

    return ret; 
}

//--------------------------------------------------------------------------------------------------
ret_code_t i2c_master_tx (void *handle, i2c_msg_t *i2c_msg)
{
    if (!handle || i2c_msg) return RET_INT_ERROR;

    return ((HAL_OK !=  HAL_I2C_Master_Transmit(&hi2c1, i2c_msg->addr, 
                                                i2c_msg->data, i2c_msg->len, 
                                                HAL_MAX_DELAY)) 
            ? RET_SUCCESS : RET_INT_ERROR);
}

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/