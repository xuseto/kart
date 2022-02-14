/***************************************************************************************************
 * @file flight_controller_hdwr.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup FLIGHT_CONTROLLER_HDWR  PERIODIC object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FLIGHT_CONTROLLER_HDWR_H
#define __FLIGHT_CONTROLLER_HDWR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <periodic/periodic_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Callback functions every 100 ms
 */
void FLIGHT_CONTROLLER_HDWR_every_100ms(void);

/**
 * @brief Callback functions every 200 ms
 */
void FLIGHT_CONTROLLER_HDWR_every_200ms(void);

/**
 * @brief Callback functions every 500 ms
 */
void FLIGHT_CONTROLLER_HDWR_every_500ms(void);

/**
 * @brief Callback functions every 1 sg
 *
 */
void FLIGHT_CONTROLLER_HDWR_every_1000ms(void);

/**
 * @brief Add new function to periodic
 *
 * @param timers \ref periodic_timers_t
 * @param cllbck \ref periodic_cllbck
 * @param arg pointer data of the function callback
 * @return periodic_id_t
 */
periodic_id_t FLIGHT_CONTROLLER_HDWR_register(periodic_timers_t timers, periodic_cllbck cllbck, void *arg);

ret_code_t FLIGHT_CONTROLLER_HDWR_unregister(periodic_id_t periodic_id);

ret_code_t FLIGHT_CONTROLLER_HDWR_enable_function(periodic_id_t periodic_id, uint8_t enable);

#endif /* __FLIGHT_CONTROLLER_HDWR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
