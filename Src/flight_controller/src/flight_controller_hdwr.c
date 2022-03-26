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
#include <stdint.h>
#include "hdwr/adc_api.h"

/* Defines ---------------------------------------------------------------------------------------*/
#define DIFF_ADC_SET_NEW_VALUE 0.1
/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values declaration --------------------------------------------------------------------*/
static float getter_diff_abs(float value1, float value2);

/* Private functions -----------------------------------------------------------------------------*/
static float getter_diff_abs(float value1, float value2)
{

    return ((value1 > value2) ? value1 - value2 : value2 - value1);
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_hdwr_init(flight_controller_t *arg)
{
    ret_code_t ret = RET_SUCCESS;

    for (uint8_t i = 0x00; i < MAX_NUM_CONTROLLER && RET_SUCCESS == ret; i++)
    {
        arg->dac_id[i] = pwm_create(&arg->cfg->dac_cfg[i]);
        ret = (arg->dac_id[i]) ? RET_SUCCESS : RET_INT_ERROR;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
bool flight_controller_hdwr_check_adc(flight_controller_t *arg)
{
    bool ret = false;

    for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
    {
        float adc_temp = adc_get_value(arg->cfg->adc_channel[i]) - arg->adc_offset[i];

        if (getter_diff_abs(adc_temp, arg->adc_values[i]) > DIFF_ADC_SET_NEW_VALUE)
        {
            arg->adc_values[i] = adc_temp;
            ret = true;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_hdwr_start(flight_controller_t *arg)
{
    ret_code_t ret = RET_SUCCESS;

    for (uint8_t i = 0x00; i < MAX_NUM_CONTROLLER && RET_SUCCESS == ret; i++)
    {
        arg->adc_offset[i] = adc_get_value(arg->cfg->adc_channel[i]);
        ret = (RET_SUCCESS == pwm_start(arg->dac_id[i])) ? RET_SUCCESS : RET_INT_ERROR;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_hdwr_set_dac(pwm_id_t arg, uint16_t value_dac)
{
    return pwm_set_new_duty(arg, value_dac);
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
