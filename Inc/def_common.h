/***************************************************************************************************
 * @file def_common.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 11/11/2021
 * @date Last modification 11/11/2021 by jnieto
 * @brief Define common 
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup def_common
    @{

    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __DEF_COMMON_H
#define __DEF_COMMON_H

/** Definitions for returns all functions */
typedef enum ret_code_s
{
  RET_SUCCESS,     /**< Return ok */
  RET_INT_ERROR,   /**< Return internal error */
  RET_PARAM_ERROR  /**< Return if it has the bad parameters */
} ret_code_t;

#endif /* __DEF_COMMON_H */

/**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/