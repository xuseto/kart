/***************************************************************************************************
 * @file dac_thread.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 17/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief dac 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup DAC_THREAD
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "cmsis_os2.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Object of configuration of dac */
typedef struct
{
    osThreadId_t id_thread; /**< ID of thread */
    void *obj_com;          /**< Obj of SPI */
} dac_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Create the thread for dac
 * 
 * @param name_thread name for thread
 * @param arg \ref dac_t
 * @return osThreadId_t 
 */
osThreadId_t dac_create_thread(const char *name_thread, void *arg);

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
