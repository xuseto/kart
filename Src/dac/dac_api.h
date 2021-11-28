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
#include <hdwr/spi_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/** Object of configuration of dac */
typedef struct
{
    const char *name; /**< name of thread */
    spi_cfg_t id_spi; /**< number of SPI */
} dac_cfg_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init DAC module
 * 
 * @param cfg \ref dac_cfg_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t dac_init(dac_cfg_t *cfg);

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
