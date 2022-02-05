/***************************************************************************************************
 * @file periodic_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PERIODIC_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "periodic_driver.h"
#include <stdio.h>
/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void periodic_driver_every_100ms(void)
{
    printf(">    %s <<\n", __FUNCTION__);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_200ms(void)
{
    printf(">>   %s <<\n", __FUNCTION__);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_500ms(void)
{
    printf(">>>  %s <<\n", __FUNCTION__);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_1000ms(void)
{
    printf(">>>> %s <<\n", __FUNCTION__);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
