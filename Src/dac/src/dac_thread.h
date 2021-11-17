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

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Object of configuration of dac */ 
typedef struct  
{
  osThreadId_t id_thread; /**< ID of thread */
  void *id_spi;           /**< Obj of SPI */
} dac_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Create the thread for dac
 * 
 * @param cfg \ref dac_cfg_t
 * @param arg \ref dac_t
 * @return osThreadId_t 
 */
osThreadId_t dac_create_thread (dac_cfg_t *cfg, void *arg);

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
