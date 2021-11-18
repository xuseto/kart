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
    @addtogroup I2C
    @{
    @defgroup I2C_API I2C object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __I2C_API_H
#define __I2C_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*//** Define el max number of bytes for send by i2c
#define I2C_MAX_LENGTH_DATA 2;

/* Public values ---------------------------------------------------------------------------------*/
/** Enum all posibles I2C */
typedef enum
{
    i2c_a, /** < I2C_A */
    i2c_b, /** < I2C_B */
    i2c_c, /** < I2C_C */
    i2c_d  /** < I2C_D */
}i2c_number_t;

/** Struct of message */
typedef struct i2c_msg_t
{
    uint8_t addr,                       /**< Number address */
    uint8_t data[I2C_MAX_LENGTH_DATA],  /**< Send data */
    uint16_t len,                       /**< number of bytes to write */
}i2c_msg_t;

/* Public functions ------------------------------------------------------------------------------*//**
 * @brief Get pointer of object of I2C protocol
 * 
 * @param i2c_number  \ref i2c_number_t
 * @return void* 
 */
void *i2c_get_instance (i2c_number_t i2c_number);

/**
 * @brief Send new message by I2C
 * 
 * @param handle 
 * @param i2c_msg 
 * @return ret_code_t 
 */
ret_code_t i2c_master_tx (void *handle, i2c_msg_t *i2c_msg);

#endif /* __I2C_API_H */
/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/