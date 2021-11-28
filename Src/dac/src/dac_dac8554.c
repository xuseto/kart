/***************************************************************************************************
 * @file dac_dac8554.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 28/11/2021
 * @date Last modification 28/11/2021 by jnieto
 * @brief DAC8554 is digital to analog with 4 channles of 16 BITS by Texas Instruments
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup DAC_DAC8554
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "dac_dac8554.h"
#include <dac/src/dac_thread.h>
#include <def_common.h>

#include "hdwr/spi_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Configure bits of dac select according \ref dac8554_frame_t
 * 
 * @param dac_frame \ref dac8554_select_t
 * @param dac_sel \ref dac8554_frame_t
 */
void dac8554_set_bits_dac_sel(dac8554_frame_t *dac_frame, dac8554_select_t dac_sel);

/* Private functions -----------------------------------------------------------------------------*/
void dac8554_set_bits_dac_sel(dac8554_frame_t *dac_frame, dac8554_select_t dac_sel)
{
    switch (dac_sel)
    {
    case (DAC_A):
        dac_frame->db.select0 = 0;
        dac_frame->db.select1 = 0;
        break;
    case (DAC_B):
        dac_frame->db.select0 = 1;
        dac_frame->db.select1 = 0;
        break;
    case (DAC_C):
        dac_frame->db.select0 = 0;
        dac_frame->db.select1 = 1;
        break;
    case (DAC_D):
        dac_frame->db.select0 = 1;
        dac_frame->db.select1 = 1;
        break;
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t dac_dac8554_write_buffer(void *arg, dac8554_select_t dac_sel, uint16_t *data)
{
    dac_t *dac = (dac_t *)arg;
    ret_code_t ret = RET_PARAM_ERROR;
    dac8554_frame_t dac_frame = {0};

    if (!dac || !data || DAC_MAX <= dac_sel)
    {
        return ret;
    }

    /* DAC Select BITS */
    dac8554_set_bits_dac_sel(&dac_frame, dac_sel);
    /* DAC data */
    dac_frame.db.data = *data;
    /* Broadcast mode */
    dac_frame.db.ld0 = 1;
    dac_frame.db.ld1 = 1;

    /* Send data By SPI */
    ret = spi_enqueue(dac->obj_com, &dac_frame);

    return ret;
}

/**
  * @}
*/

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
