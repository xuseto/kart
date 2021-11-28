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

#include "hdwr/spi_api.h"
#include "dac/dac_api.h"
#include <dac/src/dac_thread.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t dac_init(dac_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg)
        return ret;

    dac_t *dac = (dac_t *)calloc(1, sizeof(dac_t));
    ret = (dac) ? RET_SUCCESS : RET_INT_ERROR;

    if (RET_SUCCESS == ret)
    {
        dac->id_thread = dac_create_thread(cfg, dac);
        ret = (dac->id_thread) ? RET_SUCCESS : RET_INT_ERROR;
    }

    if (RET_SUCCESS == ret)
    {
        dac->obj_com = spi_init(&cfg->id_spi);
    }

    if (RET_SUCCESS == ret)
    {
        printf("Created thread : %s (0x%x)\n", cfg->name, dac);
    }

    return ret;
}

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
