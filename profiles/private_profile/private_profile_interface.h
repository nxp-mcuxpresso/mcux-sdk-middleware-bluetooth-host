/*! *********************************************************************************
* \defgroup Private profile Service
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file
*
* This file is the interface file for the QPP Service
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef _PRIVATE_PROFILE_INTERFACE_H_
#define _PRIVATE_PROFILE_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "gatt_db_handles.h"
/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! QPP Service - Configuration */
typedef struct qppsConfig_tag
{
    uint16_t    serviceHandle;
} qppsConfig_t;


typedef struct tmcConfig_tag
{
    uint16_t    hService;
    uint16_t    hTxData;
    uint16_t    hTxCccd; 
    uint16_t    hRxData;
} qppConfig_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public prototypes
************************************************************************************* 
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
* \brief        Starts QPP Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Qpp_Start(qppsConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops QPP Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Qpp_Stop(qppsConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the QPP service
*
* \param[in]    pClient  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Qpp_Subscribe(deviceId_t clientDeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the QPP service
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Qpp_Unsubscribe(void);

/*!**********************************************************************************
* \brief        Qpps SendData to Qppc. 
*
* \param[in]    deviceId        Peer device ID.
* \param[in]    serviceHandle   Service handle.
* \param[in]    length          Length of TestData to send .
* \param[in]    testData        TestData to send .
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t Qpp_SendData (uint8_t deviceId, uint16_t serviceHandle, uint16_t length, uint8_t *testData);

#ifdef __cplusplus
}
#endif 

#endif /* _PRIVATE_PROFILE_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */
