
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

#include <def_common.h>
#include <stdbool.h>

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
    pwm_channel_t channel; /** Numbewr of channel of PWM */
    uint32_t freq;         /** Frequency of PWM */
} pwm_hal_t;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Get internal handler by stm32
 *
 * @param pwm \ref pwm_number_t
 * @return TIM_HandleTypeDef*
 */
TIM_HandleTypeDef *pwm_get_handle_hal(pwm_number_t pwm);

/**
 * @brief Check if exist channel
 *
 * @param ch \ref pwm_channel_t
 * @return true Channle OK
 * @return false Channel no exist
 */
bool pwm_check_channel(pwm_channel_t ch);

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

//--------------------------------------------------------------------------------------------------
bool pwm_check_channel(pwm_channel_t ch)
{
    if (ch == PWM_CHANNEL_1 || ch == PWM_CHANNEL_2 || ch == PWM_CHANNEL_3 ||
        ch == PWM_CHANNEL_4 || ch == PWM_CHANNEL_5 || ch == PWM_CHANNEL_6)
    {
        return true;
    }

    return false;
}

/* Public functions ------------------------------------------------------------------------------*/
pwm_id_t pwm_create(pwm_cfg_t *cfg)
{
    pwm_id_t ret = NULL;

    if (!cfg)
    {
        return NULL;
    }
    if (PWM_CHANNEL_MAX < cfg->channel)
    {
        return NULL;
    }
    if (PWM_MAX < cfg->pwm)
    {
        return NULL;
    }

    pwm_hal_t *pwm = calloc(1, sizeof(pwm_hal_t));

    if (pwm && pwm_check_channel(cfg->channel))
    {
        pwm->duty = cfg->duty;
        pwm->channel = cfg->channel;
        pwm->htim = pwm_get_handle_hal(cfg->pwm);
    }

    if (pwm->htim)
    {
        /** Calculate frequency */
        pwm->freq = CLOCK_FREQ / cfg->frequency;
        uint32_t new_duty = pwm->freq * (uint32_t)((float)cfg->duty / 100.0);

        __HAL_TIM_SET_AUTORELOAD(pwm->htim, pwm->freq);

        __HAL_TIM_SET_COMPARE(pwm->htim, pwm->channel, new_duty);
    }
    // HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    //__HAL_TIM_SET_COMPARE(pwm->htim, TIM_CHANNEL_1, new_duty);

    ret = pwm && pwm->htim ? (pwm_id_t)pwm : NULL;
    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t pwm_start(pwm_id_t arg)
{
    if (!arg)
    {
        return RET_INT_ERROR;
    }

    pwm_hal_t *pwm = (pwm_hal_t *)arg;

    return (HAL_OK == HAL_TIM_PWM_Start(pwm->htim, pwm->channel) ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
ret_code_t pwm_set_new_duty(pwm_id_t arg, uint16_t duty)
{
    if (!arg)
    {
        return RET_INT_ERROR;
    }

    pwm_hal_t *pwm = (pwm_hal_t *)arg;

    __HAL_TIM_SET_COMPARE(pwm->htim, pwm->channel, duty);

    return RET_SUCCESS;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/