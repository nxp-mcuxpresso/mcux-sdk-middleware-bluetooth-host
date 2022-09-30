/*! *********************************************************************************
* \addtogroup Private Profile Service
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* All rights reserved.
* 
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "private_profile_interface.h"
#include "gatt_db_handles.h"
/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! Battery Service - Subscribed Client*/
deviceId_t mQpp_SubscribedClientId;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

bleResult_t Qpp_Start (qppsConfig_t *pServiceConfig)
{

    return gBleSuccess_c;
}

bleResult_t Qpp_Stop (qppsConfig_t *pServiceConfig)
{
    mQpp_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Qpp_Subscribe(deviceId_t clientDeviceId)
{
    mQpp_SubscribedClientId = clientDeviceId;
    return gBleSuccess_c;
}

bleResult_t Qpp_Unsubscribe()
{
    mQpp_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Qpp_SendData (uint8_t deviceId, uint16_t serviceHandle,uint16_t length, uint8_t *testData)
{
    uint16_t  handle;
    bleResult_t result;
    uint16_t  handleCccd;
    bool_t isNotifActive;
    
    bleUuid_t uuid;
    FLib_MemCpy(uuid.uuid128, uuid_qpps_characteristics_tx, 16);

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(serviceHandle, gBleUuidType128_c, &uuid, &handle);    
    if (result != gBleSuccess_c)
        return result;
        /* Get handle of CCCD */
    if ((result = GattDb_FindCccdHandleForCharValueHandle(handle, &handleCccd)) != gBleSuccess_c)
        return result;
	
    result = Gap_CheckNotificationStatus(deviceId, handleCccd, &isNotifActive);
    if ((gBleSuccess_c == result) && (TRUE == isNotifActive))
        result = GattServer_SendInstantValueNotification(deviceId, handle, length, testData); 
    
    return result;
}
