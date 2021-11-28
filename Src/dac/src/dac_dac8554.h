/***************************************************************************************************
 * @file dac_dac8554.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 17/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief dac 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup DAC_DAC8554
    @{

*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __DAC_DAC8554_H
#define __DAC_DAC8554_H

/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Frame for DAC8554 */
typedef struct dac8554_frame_s
{
    uint32_t all;
    union
    {
        uint32_t a1 : 1;
        uint32_t a0 : 1;
        uint32_t ld1 : 1;
        uint32_t ld0 : 1;
        uint32_t dc : 1;      /**< Don´t care */
        uint32_t select1 : 1; /**< DAC select 1 */
        uint32_t select0 : 1; /**< DAC select 0 */
        uint32_t pd0 : 1;
        uint32_t data : 16;
        uint32_t free : 8;

    } db;

} dac8554_frame_t;

/** Number of DAC */
typedef enum dac8554_select_e
{
    DAC_A,  /**< DAC Select A */
    DAC_B,  /**< DAC Select B */
    DAC_C,  /**< DAC Select C */
    DAC_D,  /**< DAC Select D */
    DAC_MAX /**< DAC maximum */
} dac8554_select_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief write dac 
 * 
 * @param dac \ref dac_t
 * @param dac_sel \ref dac8554_select_t
 * @param data 
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t dac_dac8554_write_buffer(void *arg, dac8554_select_t dac_sel, uint16_t *data);

#endif /* __DAC_DAC8554_H */
/**
 * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
