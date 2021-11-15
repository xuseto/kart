/***************************************************************************************************
 * @file mcp4728_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 14/11/2021
 * @date Last modification 14/11/2021 by jnieto
 * @brief MCP4728 by Microchip 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup MCP4728
    @{
    @defgroup MCP4728_API  MCP4728 object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __MCP4728_API_H
#define __MCP4728_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <def_common.h>

/* Typedefs --------------------------------------------------------------------------------------*/
typedef struct mcp4728_cfg_s
{
    const char *name;    /**< name of thread */
    uint16_t    id_i2c;  /**< number of i2c configurarted */
}mcp4728_cfg_t;


extern SMBUS_HandleTypeDef hsmbus2;

/* Public Function -------------------------------------------------------------------------------*/
ret_code_t mcp4728_init (mcp4728_cfg_t *cfg);

#endif /* __MCP4728_API_H */

/**
  * @}
  */
/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
