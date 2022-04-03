/***************************************************************************************************
 * @file user_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup USER_CONFIG  USER config module
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclUSERion ---------------------------------------------------------*/
#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

/* Includes --------------------------------------------------------------------------------------*/

/* Defines ---------------------------------------------------------------------------------------*/
#define USER_SIZE_PAYLOAD_TX 5 // ID (1 BYTE) + PAYLOAD (4 BYTES)

#define USER_SIZE_PAYLOAD_RX_ONE_MSG_ONE_DATA USER_SIZE_PAYLOAD_TX

#endif /* __USER_CONFIG_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
