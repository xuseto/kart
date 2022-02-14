/***************************************************************************************************
 * @file adc_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 12/02/2022
 * @date Last modification 12/02/2022 by jnieto
 * @brief ADC
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup ADC
    @{
    @defgroup ADC_API  ADC object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __ADC_API_H
#define __ADC_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>
#include "def_common.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Enum ADCs configurated */
typedef enum
{
    ADC_IN1,
    ADC_IN2,
    ADC_IN4,
    ADC_IN5,
    ADC_T_MICRO,
    ADC_MAX
} adc_stm32_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init ADC module
 *
 * @return \ref ret_code_t
 */
ret_code_t adc_init(void);

/**
 * @brief get value adc
 *
 * @param adc_ch \ref adc_stm32_t
 * @return float 0-3.3 V
 */
float adc_get_value(adc_stm32_t adc_ch);

#endif

/* __ADC_API_H */
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/