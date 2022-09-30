/*! *********************************************************************************
 * \defgroup FSCI_BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* This is a header file for FSCI BLE management.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef FSCI_BLE_GATT_DB_ATT_H
#define FSCI_BLE_GATT_DB_ATT_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_gatt_db_att_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! Macro which indicates if FSCI for GATT Database (ATT) is enabled or not */
#ifndef gFsciBleGattDbAttLayerEnabled_d
    #define gFsciBleGattDbAttLayerEnabled_d         0
#endif /* gFsciBleGattDbAttLayerEnabled_d */

/*! FSCI operation group for GATT Database (ATT) */
#define gFsciBleGattDbAttOpcodeGroup_c              0x47


#if defined(FsciCmdMonitor)
    //#warning "FsciCmdMonitor macro is already defined"
    #undef FsciCmdMonitor
#endif
    
#if defined(FsciStatusMonitor)
    //#warning "FsciStatusMonitor macro is already defined"
    #undef FsciStatusMonitor
#endif

#if defined(FsciEvtMonitor)
    //#warning "FsciEvtMonitor macro is already defined"
    #undef FsciEvtMonitor
#endif

/*! Macros used for monitoring commands, statuses and events */
#if gFsciIncluded_c && gFsciBleGattDbAttLayerEnabled_d && gFsciBleTest_d
    #define FsciCmdMonitor(function, ...)       fsciBleGattDb##function##CmdMonitor(__VA_ARGS__)
    #define FsciStatusMonitor(function, ...)    fsciBleGattDbAttStatusMonitor(__VA_ARGS__)
    #define FsciEvtMonitor(function, ...)       fsciBleGattDb##function##EvtMonitor(__VA_ARGS__)
#else
    #define FsciCmdMonitor(function, ...)
    #define FsciStatusMonitor(function, ...)
    #define FsciEvtMonitor(function, ...)
#endif


/*! *********************************************************************************
* \brief  Allocates a FSCI packet for GATT Database (ATT).
*
* \param[in]    opCode      FSCI GATT Database (ATT) operation code
* \param[in]    dataSize    Size of the payload
*
* \return The allocated FSCI packet
*
********************************************************************************** */
#define fsciBleGattDbAttAllocFsciPacket(opCode,                 \
                                        dataSize)               \
        fsciBleAllocFsciPacket(gFsciBleGattDbAttOpcodeGroup_c,  \
                               (opCode),                          \
                               (dataSize))

/*! *********************************************************************************
* \brief  GattDb_AttFindInformation command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttFindInformationCmdMonitor(deviceId,                 \
                                                  pReqParams,               \
                                                  pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdFindInformationOpCode_c, \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttFindByTypeValue command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttFindByTypeValueCmdMonitor(deviceId,                 \
                                                  pReqParams,               \
                                                  pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdFindByTypeValueOpCode_c, \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttReadByType command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadByTypeCmdMonitor(deviceId,                  \
                                             pReqParams,                \
                                             pOutRspParams,             \
                                             pOutErrorAttributeHandle)  \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdReadByTypeOpCode_c,  \
                                   (deviceId),                            \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttRead command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadCmdMonitor(deviceId,                    \
                                       pReqParams,                  \
                                       pOutRspParams,               \
                                       pOutErrorAttributeHandle)    \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdReadOpCode_c,    \
                                   (deviceId),                        \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttReadBlob command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadBlobCmdMonitor(deviceId,                    \
                                           pReqParams,                  \
                                           pOutRspParams,               \
                                           pOutErrorAttributeHandle)    \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdReadBlobOpCode_c,    \
                                   (deviceId),                            \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttReadMultiple command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadMultipleCmdMonitor(deviceId,                    \
                                               pReqParams,                  \
                                               pOutRspParams,               \
                                               pOutErrorAttributeHandle)    \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdReadMultipleOpCode_c,    \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttReadByGroupType command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadByGroupTypeCmdMonitor(deviceId,                 \
                                                  pReqParams,               \
                                                  pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdReadByGroupTypeOpCode_c, \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttWrite command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttWriteCmdMonitor(deviceId,                   \
                                        pReqParams,                 \
                                        pOutErrorAttributeHandle)   \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdWriteOpCode_c,   \
                                   (deviceId),                        \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttWriteCommand command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
*
********************************************************************************** */
#define fsciBleGattDbAttWriteCommandCmdMonitor(deviceId,                    \
                                               pReqParams)                  \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdWriteCommandOpCode_c,    \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttSignedWriteCommand command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
*
********************************************************************************** */
#define fsciBleGattDbAttSignedWriteCommandCmdMonitor(deviceId,                  \
                                                     pReqParams)                \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdSignedWriteCommandOpCode_c,  \
                                   (deviceId),                                    \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttPrepareWrite command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttPrepareWriteCmdMonitor(deviceId,                    \
                                               pReqParams,                  \
                                               pOutRspParams,               \
                                               pOutErrorAttributeHandle)    \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdPrepareWriteOpCode_c,    \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttExecuteWrite command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttExecuteWriteCmdMonitor(deviceId,                    \
                                               pReqParams,                  \
                                               pOutErrorAttributeHandle)    \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdExecuteWriteOpCode_c,    \
                                   (deviceId),                                \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttExecuteWriteFromQueue command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttExecuteWriteFromQueueCmdMonitor(deviceId,                   \
                                                        pReqParams,                 \
                                                        pOutErrorAttributeHandle)   \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdExecuteWriteFromQueueOpCode_c,   \
                                   (deviceId),                                        \
                                   (pReqParams))

/*! *********************************************************************************
* \brief  GattDb_AttPrepareNotificationIndication command monitoring macro.
*
* \param[in]    deviceId                    The device ID of the requesting ATT Client.
* \param[in]    pReqParams                  The request parameters.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttPrepareNotificationIndicationCmdMonitor(deviceId,                   \
                                                                pParams,                    \
                                                                pOutErrorAttributeHandle)   \
        fsciBleGattDbAttCmdMonitor(gBleGattDbAttCmdPrepareNotificationIndicationOpCode_c,   \
                                   (deviceId),                                                \
                                   (pParams))

/*! *********************************************************************************
* \brief  GattDb_AttFindInformation command out parameters monitoring 
*         function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttFindInformationEvtMonitor(pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtFindInformationOpCode_c, \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttFindByTypeValue command out parameters monitoring 
*         function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttFindByTypeValueEvtMonitor(pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtFindByTypeValueOpCode_c, \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttFindCharValueHandleInService command out parameters monitoring 
*         function.
*
* \param[in]    pOutCharValueHandle     Pointer to the characteristic value handle to be written.
*
********************************************************************************** */
#define fsciBleGattDbAttFindCharValueHandleInServiceEvtMonitor(pOutCharValueHandle)                 \
        fsciBleGattDbAttUint16ParamEvtMonitor(gBleGattDbAttEvtFindCharValueHandleInServiceOpCode_c, \
                                              (pOutCharValueHandle))

/*! *********************************************************************************
* \brief  GattDb_AttReadByType command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadByTypeEvtMonitor(pOutRspParams,                 \
                                             pOutErrorAttributeHandle)      \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtReadByTypeOpCode_c,      \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttRead command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadEvtMonitor(pOutRspParams,               \
                                       pOutErrorAttributeHandle)    \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtReadOpCode_c,    \
                                   (pOutRspParams),                 \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttReadBlob command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadBlobEvtMonitor(pOutRspParams,               \
                                           pOutErrorAttributeHandle)    \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtReadBlobOpCode_c,    \
                                   (pOutRspParams),                     \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttReadMultiple command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadMultipleEvtMonitor(pOutRspParams,               \
                                               pOutErrorAttributeHandle)    \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtReadMultipleOpCode_c,    \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttReadByGroup command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttReadByGroupTypeEvtMonitor(pOutRspParams,            \
                                                  pOutErrorAttributeHandle) \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtReadByGroupTypeOpCode_c, \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttWrite command out parameters monitoring function.
*
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttWriteEvtMonitor(pOutErrorAttributeHandle)   \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtWriteOpCode_c,   \
                                   NULL,                            \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttPrepareWrite command out parameters monitoring function.
*
* \param[in]    pOutRspParams               The pre-allocated response parameter to be filled.
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttPrepareWriteEvtMonitor(pOutRspParams,               \
                                               pOutErrorAttributeHandle)    \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtPrepareWriteOpCode_c,    \
                                   (pOutRspParams),                         \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttExecuteWrite command out parameters monitoring function.
*
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttExecuteWriteEvtMonitor(pOutErrorAttributeHandle)    \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtExecuteWriteOpCode_c,    \
                                   NULL,                                    \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttExecuteWriteFromQueue command out parameters monitoring function.
*
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttExecuteWriteFromQueueEvtMonitor(pOutErrorAttributeHandle)   \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtExecuteWriteFromQueueOpCode_c,   \
                                   NULL,                                            \
                                   (pOutErrorAttributeHandle))

/*! *********************************************************************************
* \brief  GattDb_AttPrepareNotificationIndication command out parameters monitoring 
*         function.
*
* \param[in]    outErrorAttributeHandle     The attribute handle where an error occurred.
*
********************************************************************************** */
#define fsciBleGattDbAttPrepareNotificationIndicationEvtMonitor(pParams,                    \
                                                                pOutErrorAttributeHandle)   \
        fsciBleGattDbAttEvtMonitor(gBleGattDbAttEvtPrepareNotificationIndicationOpCode_c,   \
                                   (pParams),                                                 \
                                   (pOutErrorAttributeHandle))

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! FSCI operation codes for GATT Database (ATT) */
typedef enum
{
    gBleGattDbAttModeSelectOpCode_c             = 0x00,                             /*! GATT Database (ATT) Mode Select operation code */

    gBleGattDbAttCmdFirstOpCode_c               = 0x01,
    gBleGattDbAttCmdFindInformationOpCode_c     = gBleGattDbAttCmdFirstOpCode_c,    /*! GattDb_AttFindInformation command operation code */
    gBleGattDbAttCmdFindByTypeValueOpCode_c,                                        /*! GattDb_AttFindByTypeValue command operation code */
    gBleGattDbAttCmdReadByTypeOpCode_c,                                             /*! GattDb_AttReadByType command operation code */
    gBleGattDbAttCmdReadOpCode_c,                                                   /*! GattDb_AttRead command operation code */
    gBleGattDbAttCmdReadBlobOpCode_c,                                               /*! GattDb_AttReadBlob command operation code */
    gBleGattDbAttCmdReadMultipleOpCode_c,                                           /*! GattDb_AttReadMultiple command operation code */
    gBleGattDbAttCmdReadByGroupTypeOpCode_c,                                        /*! GattDb_AttReadByGroupType command operation code */
    gBleGattDbAttCmdWriteOpCode_c,                                                  /*! GattDb_AttWrite command operation code */
    gBleGattDbAttCmdWriteCommandOpCode_c,                                           /*! GattDb_AttWriteCommand command operation code */
    gBleGattDbAttCmdSignedWriteCommandOpCode_c,                                     /*! GattDb_AttSignedWriteCommand command operation code */
    gBleGattDbAttCmdPrepareWriteOpCode_c,                                           /*! GattDb_AttPrepareWrite command operation code */
    gBleGattDbAttCmdExecuteWriteOpCode_c,                                           /*! GattDb_AttExecuteWrite command operation code */
    gBleGattDbAttCmdExecuteWriteFromQueueOpCode_c,                                  /*! GattDb_AttExecuteWriteFromQueue command operation code */
    gBleGattDbAttCmdPrepareNotificationIndicationOpCode_c,                          /*! GattDb_AttPrepareNotificationIndication command operation code */
    
    gBleGattDbAttStatusOpCode_c                    = 0x80,                          /*! GATT Database (ATT) status operation code */

    gBleGattDbAttEvtFirstOpCode_c                  = 0x81,
    gBleGattDbAttEvtFindInformationOpCode_c        = gBleGattDbAttEvtFirstOpCode_c, /*! GattDb_AttFindInformation command out parameters event operation code */
    gBleGattDbAttEvtFindByTypeValueOpCode_c,                                        /*! GattDb_AttFindByTypeValue command out parameters event operation code */
    gBleGattDbAttEvtReadByTypeOpCode_c,                                             /*! GattDb_AttReadByType command out parameters event operation code */
    gBleGattDbAttEvtReadOpCode_c,                                                   /*! GattDb_AttRead command out parameters event operation code */
    gBleGattDbAttEvtReadBlobOpCode_c,                                               /*! GattDb_AttReadBlob command out parameters event operation code */
    gBleGattDbAttEvtReadMultipleOpCode_c,                                           /*! GattDb_AttReadMultiple command out parameters event operation code */
    gBleGattDbAttEvtReadByGroupTypeOpCode_c,                                        /*! GattDb_AttReadByGroupType command out parameters event operation code */
    gBleGattDbAttEvtWriteOpCode_c,                                                  /*! GattDb_AttWrite command out parameters event operation code */
    gBleGattDbAttEvtPrepareWriteOpCode_c,                                           /*! GattDb_AttPrepareWrite command out parameters event operation code */
    gBleGattDbAttEvtExecuteWriteOpCode_c,                                           /*! GattDb_AttExecuteWrite command out parameters event operation code */
    gBleGattDbAttEvtExecuteWriteFromQueueOpCode_c,                                  /*! GattDb_AttExecuteWriteFromQueue command out parameters event operation code */
    gBleGattDbAttEvtPrepareNotificationIndicationOpCode_c                           /*! GattDb_AttPrepareNotificationIndication command out parameters event operation code */ 
}fsciBleGattDbAttOpCode_t;

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

/*! *********************************************************************************
* \brief  Calls the GATT Database (ATT) function associated with the operation code received 
*         over UART. The GAP function parameters are extracted from the received 
*         FSCI payload.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI 
                                    payload) received over UART   
* \param[in]    param               Pointer given when this function is registered in
                                    FSCI
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received  
*
********************************************************************************** */
void fsciBleGattDbAttHandler
(
    void*       pData, 
    void* param, 
    uint32_t    fsciInterface
);

/*! *********************************************************************************
* \brief  Creates the FSCI packet which contains the status of the last executed GAP 
*         command and sends it over UART.
*
* \param[in]    result      Status of the last executed GATT Database (ATT) command.
*
********************************************************************************** */
void fsciBleGattDbAttStatusMonitor
(
    bleResult_t result
);

/*! *********************************************************************************
* \brief  Function monitor for all GATT Database (ATT) for ATT commands
*
* \param[in]    opCode      GATT Database (ATT) command operation code.
* \param[in]    deviceId    The device ID of the requesting ATT Client.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
void fsciBleGattDbAttCmdMonitor
(
    fsciBleGattDbAttOpCode_t   opCode, 
    deviceId_t                 deviceId, 
    const void*                pParams
);

/*! *********************************************************************************
* \brief  Function monitor for all GATT Database (ATT) for ATT commands out parameters
*
* \param[in]    opCode                  GATT Database (ATT) command operation code.
* \param[in]    pParams                 The response parameters.
* \param[in]    pErrorAttributeHandle   The attribute handle where an error occurred.
*
********************************************************************************** */
void fsciBleGattDbAttEvtMonitor
(
    fsciBleGattDbAttOpCode_t   opCode, 
    void*                      pParams, 
    uint16_t*                  pErrorAttributeHandle
);

#ifdef __cplusplus
}
#endif 

#endif /* FSCI_BLE_GATT_DB_ATT_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
