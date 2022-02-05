
/***************************************************************************************************
 * @file pwm_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/12/2021
 * @date Last modification 27/12/2021 by jnieto
 * @brief PWM
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PWM_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/pwm_api.h"
#include <stm32l5xx_hal.h>
#include <stdlib.h>

#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/
#define CLOCK_FREQ 110000000 // 110 MHz

/* Private values --------------------------------------------------------------------------------*/
extern TIM_HandleTypeDef htim1 __attribute__((weak));
extern TIM_HandleTypeDef htim2 __attribute__((weak));
extern TIM_HandleTypeDef htim3 __attribute__((weak));
extern TIM_HandleTypeDef htim4 __attribute__((weak));
extern TIM_HandleTypeDef htim5 __attribute__((weak));
extern TIM_HandleTypeDef htim6 __attribute__((weak));
extern TIM_HandleTypeDef htim7 __attribute__((weak));
extern TIM_HandleTypeDef htim8 __attribute__((weak));
extern TIM_HandleTypeDef htim15 __attribute__((weak));
extern TIM_HandleTypeDef htim17 __attribute__((weak));
extern TIM_HandleTypeDef htim16 __attribute__((weak));

/** Structure of datas by PWMs */
typedef struct pwm_hal_s
{
    uint32_t duty;
    TIM_HandleTypeDef *htim;
} pwm_hal_t;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Get internal handler by stm32
 *
 * @param pwm \ref pwm_number_t
 * @return TIM_HandleTypeDef*
 */
TIM_HandleTypeDef *pwm_get_handle_hal(pwm_number_t pwm);

/* Private functions -----------------------------------------------------------------------------*/
TIM_HandleTypeDef *pwm_get_handle_hal(pwm_number_t pwm)
{
    TIM_HandleTypeDef *handler = NULL;

    switch (pwm)
    {
    case (PWM_1):
        handler = &htim1;
        break;
    case (PWM_2):
        handler = &htim2;
        break;
    case (PWM_3):
        handler = &htim3;
        break;
    case (PWM_4):
        handler = &htim4;
        break;
    case (PWM_5):
        handler = &htim5;
        break;
    case (PWM_6):
        handler = &htim6;
        break;
    case (PWM_7):
        handler = &htim7;
        break;
    case (PWM_8):
        handler = &htim8;
        break;
    case (PWM_15):
        handler = &htim15;
        break;
    case (PWM_16):
        handler = &htim16;
        break;
    case (PWM_17):
        handler = &htim17;
        break;
    }

    return handler;
}
/* Public functions ------------------------------------------------------------------------------*/
pwm_id_t pwm_create(pwm_cfg_t *cfg)
{
    pwm_id_t ret = NULL;

    if (!cfg)
        return NULL;
    if (PWM_CHANNEL_MAX < cfg->channel)
        return NULL;
    if (PWM_MAX < cfg->pwm)
        return NULL;

    TIM_HandleTypeDef *handler = pwm_get_handle_hal(cfg->pwm);
    if (!handler)
    {
        return NULL;
    }

    pwm_hal_t *pwm = calloc(1, sizeof(pwm_hal_t));
    if (pwm)
    {
        pwm->htim = handler;
        pwm->duty = cfg->duty;

        /** Calculate frequency */
        uint32_t new_freq = CLOCK_FREQ / cfg->frequency;
        uint32_t new_duty = new_freq * ((float)cfg->duty / 100.0);

        __HAL_TIM_SET_AUTORELOAD(pwm->htim, new_freq);

        __HAL_TIM_SET_COMPARE(pwm->htim, TIM_CHANNEL_1, new_duty);

        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

        //__HAL_TIM_SET_COMPARE(pwm->htim, TIM_CHANNEL_1, new_duty);
    }

    ret = pwm ? (pwm_id_t)pwm : NULL;
    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/