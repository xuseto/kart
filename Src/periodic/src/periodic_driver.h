/***************************************************************************************************
 * @file periodic_driver.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup PERIODIC_DRIVER  PERIODIC object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __PERIODIC_DRIVER_H
#define __PERIODIC_DRIVER_H

/* Includes --------------------------------------------------------------------------------------*/

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Callback functions every 100 ms
 */
void periodic_driver_every_100ms(void);

/**
 * @brief Callback functions every 200 ms
 */
void periodic_driver_every_200ms(void);

/**
 * @brief Callback functions every 500 ms
 */
void periodic_driver_every_500ms(void);

/**
 * @brief Callback functions every 1 sg
 *
 */
void periodic_driver_every_1000ms(void);

#endif /* __PERIODIC_DRIVER_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
