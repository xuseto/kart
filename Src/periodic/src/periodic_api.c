/***************************************************************************************************
 * @file periodic_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PERIODIC_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "periodic/periodic_api.h"
#include "periodic/src/periodic_conductor.h"

/* Defines ---------------------------------------------------------------------------------------*/
/** Typedef internal struct periodic */
#define periodic_id_t uint32_t

/** Typedef function callback in the module peridic */
typedef void periodic_cllbck(void *arg);

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t periodic_init(void)
{
    return periodic_conductor_init();
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
