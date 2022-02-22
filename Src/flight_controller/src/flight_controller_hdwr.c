/***************************************************************************************************
 * @file flight_controller_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller_hdwr.h"
#include <flight_controller/flight_controller_api.h>
#include <flight_controller/flight_controller_config.h>
#include <def_common.h>
#include <stdbool.h>
#include "hdwr/adc_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
ret_code_t flight_controller_hdwr_init(flight_controller_t *arg)
{
    ret_code_t ret = RET_INT_ERROR;

    ret = RET_SUCCESS;
    return ret;
}

//--------------------------------------------------------------------------------------------------
bool flight_controller_hdwr_check_adc(flight_controller_t *arg)
{
    float adc_temp = 0.0;
    bool ret = false;

    for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
    {
        adc_temp = adc_get_value(arg->cfg->adc_channel[i]);

        if (adc_temp != arg->adc_values[i])
        {
            arg->adc_values[i] = adc_temp;
            ret = true;
        }
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
