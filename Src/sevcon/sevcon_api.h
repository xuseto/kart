/***************************************************************************************************
 * @file sevcon_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup SEVCON
    @{
    @defgroup SEVCON_API  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_API_H
#define __SEVCON_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdint.h>
#include <stdbool.h>

#include <hdwr/fifo_api.h>
#include <gps/gps_api.h>
#include <sevcon/sevcon_config.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Data every driver secvon */
typedef struct driver_data_s
{
    int32_t vel_rpm;       /** Actual velocity in RPM */
    float vel_m_s;         /** Actual velocity in M\S */
    int16_t temperature;   /** 1 degree C / bit. Only valid if a PTC thermistor is set in 4620h.*/
    int16_t error;         /** Fault ID of currently active highest priority fault */
    uint16_t warning_temp; /** values define WRN_DECREASE_MOTOR_WORKING_LVL_1 and WRN_DECREASE_MOTOR_WORKING_LVL_2 */
} driver_data_t;

/** Configuration of sevcon */
typedef struct sevcon_cfg_s
{
    fifo_cfg_t fifo_cfg;
    gps_cfg_t gps_cfg;
} sevcon_cfg_t;

/** Data of secvon */
typedef struct sevcon_s
{
    char const *name;
    fifo_t fifo_id;
    driver_data_t driver[SEVCON_MAX_DRIVERS];
    gps_id_t gps; /** Struct of GPS */
} sevcon_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief config sevcon drivers
 *
 * @param cfg \ref sevcon_cfg_t
 * @return \ref ret_code_t
 */
ret_code_t sevcon_init(sevcon_cfg_t *cfg);

#endif /* __SEVCON_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
