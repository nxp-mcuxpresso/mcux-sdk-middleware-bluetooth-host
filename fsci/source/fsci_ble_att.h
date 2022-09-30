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

#ifndef FSCI_BLE_ATT_H
#define FSCI_BLE_ATT_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_att_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! Macro which indicates if FSCI for ATT is enabled or not */
#ifndef gFsciBleAttLayerEnabled_d
    #define gFsciBleAttLayerEnabled_d           0
#endif /* gFsciBleAttLayerEnabled_d */

/*! FSCI operation group for ATT */
#define gFsciBleAttOpcodeGroup_c                0x44


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
#if gFsciIncluded_c && gFsciBleAttLayerEnabled_d && gFsciBleTest_d
    #define FsciCmdMonitor(function, ...)       fsciBleAtt##function##CmdMonitor(__VA_ARGS__)
    #define FsciStatusMonitor(function, ...)    fsciBleAttStatusMonitor(__VA_ARGS__)
    #define FsciEvtMonitor(function, ...)       fsciBleAtt##function##EvtMonitor(__VA_ARGS__)
#else
    #define FsciCmdMonitor(function, ...)
    #define FsciStatusMonitor(function, ...)
    #define FsciEvtMonitor(function, ...)
#endif


/*! *********************************************************************************
* \brief  Allocates a FSCI packet for ATT.
*
* \param[in]    opCode      FSCI ATT operation code
* \param[in]    dataSize    Size of the payload
*
* \return The allocated FSCI packet
*
********************************************************************************** */
#define fsciBleAttAllocFsciPacket(opCode,                   \
                                  dataSize)                 \
        fsciBleAllocFsciPacket(gFsciBleAttOpcodeGroup_c,    \
                               (opCode),                    \
                               (dataSize))

/*! *********************************************************************************
* \brief  Att_Init command monitoring macro.
*
********************************************************************************** */
#define fsciBleAttInitCmdMonitor() \
        fsciBleAttNoParamCmdMonitor(gBleAttCmdInitOpCode_c)

/*! *********************************************************************************
* \brief  Att_NotifyConnection command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttNotifyConnectionCmdMonitor(deviceId)                  \
        fsciBleAttGenericCmdMonitor(gBleAttCmdNotifyConnectionOpCode_c, \
                                    (deviceId),                         \
                                    NULL)

/*! *********************************************************************************
* \brief  Att_NotifyDisconnection command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttNotifyDisconnectionCmdMonitor(deviceId)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdNotifyDisconnectionOpCode_c,  \
                                    (deviceId),                             \
                                    NULL)

/*! *********************************************************************************
* \brief  Att_SetMtu command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    mtu         The new MTU value.
*
********************************************************************************** */
#define fsciBleAttSetMtuCmdMonitor(deviceId,                    \
                                   mtu)                         \
        fsciBleAttGenericCmdMonitor(gBleAttCmdSetMtuOpCode_c,   \
                                    (deviceId),                 \
                                    &(mtu))

/*! *********************************************************************************
* \brief  Att_GetMtu command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pOutMtu     The address to store the MTU value into.
*
********************************************************************************** */
#define fsciBleAttGetMtuCmdMonitor(deviceId,                    \
                                   pOutMtu)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdGetMtuOpCode_c,   \
                                    (deviceId),                 \
                                    NULL)

/*! *********************************************************************************
* \brief  Att_RegisterUnsupportedOpcodeCallback command monitoring macro.
*
* \param[in]    unsupportedOpcodeCallback       Callback function for unsupported attributes.
*
********************************************************************************** */
#define fsciBleAttRegisterUnsupportedOpcodeCallbackCmdMonitor(unsupportedOpcodeCallback) \
        fsciBleAttNoParamCmdMonitor(gBleAttCmdRegisterUnsupportedOpcodeCallbackOpCode_c)

/*! *********************************************************************************
* \brief  Att_RegisterTimeoutCallback command monitoring macro.
*
* \param[in]    timeoutCallback     Callback function to be used when timeout occurred.
*
********************************************************************************** */
#define fsciBleAttRegisterTimeoutCallbackCmdMonitor(timeoutCallback) \
        fsciBleAttNoParamCmdMonitor(gBleAttCmdRegisterTimeoutCallbackOpCode_c)

/*! *********************************************************************************
* \brief  AttServer_SendErrorResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendErrorResponseCmdMonitor(deviceId,                   \
                                                    pParams)                    \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendErrorResponseOpCode_c,  \
                                    (deviceId),                                 \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendExchangeMtuRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendExchangeMtuRequestCmdMonitor(deviceId,                  \
                                                         pParams)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendExchangeMtuRequestOpCode_c, \
                                    (deviceId),                                     \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendExchangeMtuResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendExchangeMtuResponseCmdMonitor(deviceId,                     \
                                                          pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendExchangeMtuResponseOpCode_c,    \
                                    (deviceId),                                         \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendFindInformationRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendFindInformationRequestCmdMonitor(deviceId,                  \
                                                            pParams)                    \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendFindInformationRequestOpCode_c, \
                                    (deviceId),                                         \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendFindInformationResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendFindInformationResponseCmdMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendFindInformationResponseOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendFindByTypeValueRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendFindByTypeValueRequestCmdMonitor(deviceId,                  \
                                                             pParams)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendFindByTypeValueRequestOpCode_c, \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendFindByTypeValueResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendFindByTypeValueResponseCmdMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendFindByTypeValueResponseOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendReadByTypeRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendReadByTypeRequestCmdMonitor(deviceId,                   \
                                                        pParams)                    \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendReadByTypeRequestOpCode_c,  \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendReadByTypeResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendReadByTypeResponseCmdMonitor(deviceId,                  \
                                                         pParams)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendReadByTypeResponseOpCode_c, \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendReadRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendReadRequestCmdMonitor(deviceId,                         \
                                                  pParams)                          \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendReadRequestOpCode_c,        \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendReadResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendReadResponseCmdMonitor(deviceId,                        \
                                                   pParams)                         \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendReadResponseOpCode_c,       \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendReadBlobRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendReadBlobRequestCmdMonitor(deviceId,                     \
                                                      pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendReadBlobRequestOpCode_c,    \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendReadBlobResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendReadBlobResponseCmdMonitor(deviceId,                    \
                                                       pParams)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendReadBlobResponseOpCode_c,   \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendReadMultipleRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendReadMultipleRequestCmdMonitor(deviceId,                     \
                                                          pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendReadMultipleRequestOpCode_c,    \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendReadMultipleResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendReadMultipleResponseCmdMonitor(deviceId,                    \
                                                           pParams)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendReadMultipleResponseOpCode_c,   \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendReadByGroupTypeRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendReadByGroupTypeRequestCmdMonitor(deviceId,                  \
                                                             pParams)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendReadByGroupTypeRequestOpCode_c, \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendReadByGroupTypeResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendReadByGroupTypeResponseCmdMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendReadByGroupTypeResponseOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendWriteRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendWriteRequestCmdMonitor(deviceId,                    \
                                                   pParams)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendWriteRequestOpCode_c,   \
                                    (deviceId),                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendWriteResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttServerSendWriteResponseCmdMonitor(deviceId)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendWriteResponseOpCode_c,  \
                                    (deviceId),                                   \
                                    NULL)

/*! *********************************************************************************
* \brief  AttClient_SendWriteCommand command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendWriteCommandCmdMonitor(deviceId,                    \
                                                   pParams)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendWriteCommandOpCode_c,   \
                                    (deviceId),                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  Att_SendSignedWriteCommand command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendSignedWriteCommandCmdMonitor(deviceId,                  \
                                                         pParams)                   \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendSignedWriteCommandOpCode_c, \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendPrepareWriteRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendPrepareWriteRequestCmdMonitor(deviceId,                     \
                                                          pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendPrepareWriteRequestOpCode_c,    \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendPrepareWriteResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendPrepareWriteResponseCmdMonitor(deviceId,                    \
                                                           pParams)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendPrepareWriteResponseOpCode_c,   \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendExecuteWriteRequest command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttClientSendExecuteWriteRequestCmdMonitor(deviceId,                     \
                                                          pParams)                      \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendExecuteWriteRequestOpCode_c,    \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendExecuteWriteResponse command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttServerSendExecuteWriteResponseCmdMonitor(deviceId)                    \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendExecuteWriteResponseOpCode_c,   \
                                    (deviceId),                                           \
                                    NULL)                                               \

/*! *********************************************************************************
* \brief  AttServer_SendHandleValueNotification command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendHandleValueNotificationCmdMonitor(deviceId,                 \
                                                              pParams)                  \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendHandleValueNotificationOpCode_c,\
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttServer_SendHandleValueIndication command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The request parameters.
*
********************************************************************************** */
#define fsciBleAttServerSendHandleValueIndicationCmdMonitor(deviceId,                   \
                                                            pParams)                    \
        fsciBleAttGenericCmdMonitor(gBleAttCmdServerSendHandleValueIndicationOpCode_c,  \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  AttClient_SendHandleValueConfirmation command monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttClientSendHandleValueConfirmationCmdMonitor(deviceId)                     \
        fsciBleAttGenericCmdMonitor(gBleAttCmdClientSendHandleValueConfirmationOpCode_c,    \
                                    (deviceId),                                               \
                                    NULL)                                                   \

/*! *********************************************************************************
* \brief  Att_GetMtu command out parameter monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pOutMtu     The address where is stored the MTU value.
*
********************************************************************************** */
#define fsciBleAttGetMtuEvtMonitor(deviceId, pOutMtu)            \
        fsciBleAttGenericEvtMonitor(gBleAttEvtGetMtuOpCode_c, \
                                    (deviceId),                           \
                                    pMtu)                               \

/*! *********************************************************************************
* \brief  attIncomingServerErrorResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerErrorResponseEvtMonitor(deviceId,                   \
                                                        pParams)                    \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerErrorResponseOpCode_c,  \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientExchangeMtuRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientExchangeMtuRequestEvtMonitor(deviceId,                  \
                                                             pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientExchangeMtuRequestOpCode_c, \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerExchangeMtuResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerExchangeMtuResponseEvtMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerExchangeMtuResponseOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientFindInformationRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientFindInformationRequestEvtMonitor(deviceId,                  \
                                                                 pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientFindInformationRequestOpCode_c, \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerFindInformationResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerFindInformationResponseEvtMonitor(deviceId,                     \
                                                                  pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerFindInformationResponseOpCode_c,    \
                                    (deviceId),                                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientFindByTypeValueRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientFindByTypeValueRequestEvtMonitor(deviceId,                  \
                                                                 pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientFindByTypeValueRequestOpCode_c, \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerFindByTypeValueResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerFindByTypeValueResponseEvtMonitor(deviceId,                     \
                                                                  pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerFindByTypeValueResponseOpCode_c,    \
                                    (deviceId),                                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientReadByTypeRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientReadByTypeRequestEvtMonitor(deviceId,                   \
                                                            pParams)                    \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientReadByTypeRequestOpCode_c,  \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerReadByTypeResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerReadByTypeResponseEvtMonitor(deviceId,                  \
                                                             pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerReadByTypeResponseOpCode_c, \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientReadRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientReadRequestEvtMonitor(deviceId,                     \
                                                      pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientReadRequestOpCode_c,    \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerReadResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerReadResponseEvtMonitor(deviceId,                    \
                                                       pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerReadResponseOpCode_c,   \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientReadBlobRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientReadBlobRequestEvtMonitor(deviceId,                     \
                                                          pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientReadBlobRequestOpCode_c,    \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerReadBlobResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerReadBlobResponseEvtMonitor(deviceId,                    \
                                                           pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerReadBlobResponseOpCode_c,   \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientReadMultipleRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientReadMultipleRequestEvtMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientReadMultipleRequestOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerReadMultipleResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerReadMultipleResponseEvtMonitor(deviceId,                    \
                                                               pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerReadMultipleResponseOpCode_c,   \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientReadByGroupTypeRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientReadByGroupTypeRequestEvtMonitor(deviceId,                  \
                                                                 pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientReadByGroupTypeRequestOpCode_c, \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerReadByGroupTypeResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerReadByGroupTypeResponseEvtMonitor(deviceId,                     \
                                                                  pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerReadByGroupTypeResponseOpCode_c,    \
                                    (deviceId),                                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientWriteRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientWriteRequestEvtMonitor(deviceId,                    \
                                                       pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientWriteRequestOpCode_c,   \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerWriteResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerWriteResponseEvtMonitor(deviceId)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerWriteResponseOpCode_c,  \
                                    (deviceId),                                       \
                                    NULL)                                           \

/*! *********************************************************************************
* \brief  attIncomingClientWriteCommandCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientWriteCommandEvtMonitor(deviceId,                    \
                                                       pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientWriteCommandOpCode_c,   \
                                    (deviceId),                                       \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientSignedWriteCommandCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientSignedWriteCommandEvtMonitor(deviceId,                  \
                                                             pParams)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientSignedWriteCommandOpCode_c, \
                                    (deviceId),                                           \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientPrepareWriteRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientPrepareWriteRequestEvtMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientPrepareWriteRequestOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerPrepareWriteResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerPrepareWriteResponseEvtMonitor(deviceId,                    \
                                                               pParams)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerPrepareWriteResponseOpCode_c,   \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientExecuteWriteRequestCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingClientExecuteWriteRequestEvtMonitor(deviceId,                     \
                                                              pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientExecuteWriteRequestOpCode_c,    \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerExecuteWriteResponseCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttIncomingServerExecuteWriteResponseEvtMonitor(deviceId)                    \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerExecuteWriteResponseOpCode_c,   \
                                    (deviceId),                                               \
                                    NULL)                                                   \

/*! *********************************************************************************
* \brief  attIncomingServerHandleValueNotificationCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerHandleValueNotificationEvtMonitor(deviceId,                     \
                                                                  pParams)                      \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerHandleValueNotificationOpCode_c,    \
                                    (deviceId),                                                   \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingServerHandleValueIndicationCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    pParams     The response parameters.
*
********************************************************************************** */
#define fsciBleAttIncomingServerHandleValueIndicationEvtMonitor(deviceId,                   \
                                                                pParams)                    \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingServerHandleValueIndicationOpCode_c,  \
                                    (deviceId),                                               \
                                    (pParams))

/*! *********************************************************************************
* \brief  attIncomingClientHandleValueConfirmationCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttIncomingClientHandleValueConfirmationEvtMonitor(deviceId)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtIncomingClientHandleValueConfirmationOpCode_c,    \
                                    (deviceId),                                                   \
                                    NULL)                                                       \

/*! *********************************************************************************
* \brief  attUnsupportedOpcodeCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    opcode      The unsupported attribute opcode.
*
********************************************************************************** */
#define fsciBleAttUnsupportedOpcodeEvtMonitor(deviceId,                     \
                                    opcode)                                 \
        fsciBleAttGenericEvtMonitor(gBleAttEvtUnsupportedOpcodeOpCode_c,    \
                                    (deviceId),                               \
                                    &(opcode))                                \

/*! *********************************************************************************
* \brief  attTimeoutCallback event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
*
********************************************************************************** */
#define fsciBleAttTimeoutEvtMonitor(deviceId)                   \
        fsciBleAttGenericEvtMonitor(gBleAttEvtTimeoutOpCode_c,  \
                                    (deviceId),                   \
                                    NULL)                       \

/*! *********************************************************************************
* \brief  attInvalidPduReceived event monitoring macro.
*
* \param[in]    deviceId    The device ID of the connected peer.
* \param[in]    opcode      The invalid attribute opcode.
*
********************************************************************************** */
#define fsciBleAttInvalidPduReceivedEvtMonitor(deviceId,                   \
                                               opcode)                     \
        fsciBleAttGenericEvtMonitor(gBleAttEvtInvalidPduReceivedOpCode_c,  \
                                    (deviceId),                   \
                                     &(opcode))                       \
/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! FSCI operation codes for ATT */
typedef enum
{
    gBleAttModeSelectOpCode_c                   = 0x00,                     /*! ATT Mode Select operation code */

    gBleAttCmdFirstOpCode_c                     = 0x01,
    gBleAttCmdInitOpCode_c                      = gBleAttCmdFirstOpCode_c,  /*! Att_Init command operation code */
    gBleAttCmdNotifyConnectionOpCode_c,                                     /*! Att_NotifyConnection command operation code */
    gBleAttCmdNotifyDisconnectionOpCode_c,                                  /*! Att_NotifyDisconnection command operation code */
    gBleAttCmdSetMtuOpCode_c,                                               /*! Att_SetMtu command operation code */
    gBleAttCmdGetMtuOpCode_c,                                               /*! Att_GetMtu command operation code */
    gBleAttCmdRegisterOpcodeCallbackOpCode_c,                               /*! Att_RegisterOpcodeCallback command operation code */
    gBleAttCmdRegisterUnsupportedOpcodeCallbackOpCode_c,                    /*! Att_RegisterUnsupportedOpcodeCallback command operation code */
    gBleAttCmdRegisterTimeoutCallbackOpCode_c,                              /*! Att_RegisterTimeoutCallback command operation code */
    gBleAttCmdServerSendErrorResponseOpCode_c,                              /*! AttServer_SendErrorResponse command operation code */
    gBleAttCmdClientSendExchangeMtuRequestOpCode_c,                         /*! AttClient_SendExchangeMtuRequest command operation code */
    gBleAttCmdServerSendExchangeMtuResponseOpCode_c,                        /*! AttServer_SendExchangeMtuResponse command operation code */
    gBleAttCmdClientSendFindInformationRequestOpCode_c,                     /*! AttClient_SendFindInformationRequest command operation code */
    gBleAttCmdServerSendFindInformationResponseOpCode_c,                    /*! AttServer_SendFindInformationResponse command operation code */
    gBleAttCmdClientSendFindByTypeValueRequestOpCode_c,                     /*! AttClient_SendFindByTypeValueRequest command operation code */
    gBleAttCmdServerSendFindByTypeValueResponseOpCode_c,                    /*! AttServer_SendFindByTypeValueResponse command operation code */
    gBleAttCmdClientSendReadByTypeRequestOpCode_c,                          /*! AttClient_SendReadByTypeRequest command operation code */
    gBleAttCmdServerSendReadByTypeResponseOpCode_c,                         /*! AttServer_SendReadByTypeResponse command operation code */
    gBleAttCmdClientSendReadRequestOpCode_c,                                /*! AttClient_SendReadRequest command operation code */
    gBleAttCmdServerSendReadResponseOpCode_c,                               /*! AttServer_SendReadResponse command operation code */
    gBleAttCmdClientSendReadBlobRequestOpCode_c,                            /*! AttClient_SendReadBlobRequest command operation code */
    gBleAttCmdServerSendReadBlobResponseOpCode_c,                           /*! AttServer_SendReadBlobResponse command operation code */
    gBleAttCmdClientSendReadMultipleRequestOpCode_c,                        /*! AttClient_SendReadMultipleRequest command operation code */
    gBleAttCmdServerSendReadMultipleResponseOpCode_c,                       /*! AttServer_SendReadMultipleResponse command operation code */
    gBleAttCmdClientSendReadByGroupTypeRequestOpCode_c,                     /*! AttClient_SendReadByGroupTypeRequest command operation code */
    gBleAttCmdServerSendReadByGroupTypeResponseOpCode_c,                    /*! AttServer_SendReadByGroupTypeResponse command operation code */
    gBleAttCmdClientSendWriteRequestOpCode_c,                               /*! AttClient_SendWriteRequest command operation code */
    gBleAttCmdServerSendWriteResponseOpCode_c,                              /*! AttServer_SendWriteResponse command operation code */
    gBleAttCmdClientSendWriteCommandOpCode_c,                               /*! AttClient_SendWriteCommand command operation code */
    gBleAttCmdClientSendSignedWriteCommandOpCode_c,                         /*! AttClient_SendSignedWriteCommand command operation code */
    gBleAttCmdClientSendPrepareWriteRequestOpCode_c,                        /*! AttClient_SendPrepareWriteRequest command operation code */
    gBleAttCmdServerSendPrepareWriteResponseOpCode_c,                       /*! AttServer_SendPrepareWriteResponse command operation code */
    gBleAttCmdClientSendExecuteWriteRequestOpCode_c,                        /*! AttClient_SendExecuteWriteRequest command operation code */
    gBleAttCmdServerSendExecuteWriteResponseOpCode_c,                       /*! AttServer_SendExecuteWriteResponse command operation code */
    gBleAttCmdServerSendHandleValueNotificationOpCode_c,                    /*! AttServer_SendHandleValueNotification command operation code */
    gBleAttCmdServerSendHandleValueIndicationOpCode_c,                      /*! AttServer_SendHandleValueIndication command operation code */
    gBleAttCmdClientSendHandleValueConfirmationOpCode_c,                    /*! AttClient_SendHandleValueConfirmation command operation code */

    gBleAttStatusOpCode_c                       = 0x80,                     /*! ATT status operation code */

    gBleAttEvtFirstOpCode_c                     = 0x81,
    gBleAttEvtGetMtuOpCode_c                    = gBleAttEvtFirstOpCode_c,  /*! Att_GetMtu command out parameter event operation code */
    gBleAttEvtIncomingServerErrorResponseOpCode_c,                          /*! attIncomingServerErrorResponseCallback event operation code */
    gBleAttEvtIncomingClientExchangeMtuRequestOpCode_c,                     /*! attIncomingClientExchangeMtuRequestCallback event operation code */
    gBleAttEvtIncomingServerExchangeMtuResponseOpCode_c,                    /*! attIncomingServerExchangeMtuResponseCallback event operation code */
    gBleAttEvtIncomingClientFindInformationRequestOpCode_c,                 /*! attIncomingClientFindInformationRequestCallback event operation code */
    gBleAttEvtIncomingServerFindInformationResponseOpCode_c,                /*! attIncomingServerFindInformationResponseCallback event operation code */
    gBleAttEvtIncomingClientFindByTypeValueRequestOpCode_c,                 /*! attIncomingClientFindByTypeValueRequestCallback event operation code */
    gBleAttEvtIncomingServerFindByTypeValueResponseOpCode_c,                /*! attIncomingServerFindByTypeValueResponseCallback event operation code */
    gBleAttEvtIncomingClientReadByTypeRequestOpCode_c,                      /*! attIncomingClientReadByTypeRequestCallback event operation code */
    gBleAttEvtIncomingServerReadByTypeResponseOpCode_c,                     /*! attIncomingServerReadByTypeResponseCallback event operation code */
    gBleAttEvtIncomingClientReadRequestOpCode_c,                            /*! attIncomingClientReadRequestCallback event operation code */
    gBleAttEvtIncomingServerReadResponseOpCode_c,                           /*! attIncomingServerReadResponseCallback event operation code */
    gBleAttEvtIncomingClientReadBlobRequestOpCode_c,                        /*! attIncomingClientReadBlobRequestCallback event operation code */
    gBleAttEvtIncomingServerReadBlobResponseOpCode_c,                       /*! attIncomingServerReadBlobResponseCallback event operation code */
    gBleAttEvtIncomingClientReadMultipleRequestOpCode_c,                    /*! attIncomingClientReadMultipleRequestCallback event operation code */
    gBleAttEvtIncomingServerReadMultipleResponseOpCode_c,                   /*! attIncomingServerReadMultipleResponseCallback event operation code */
    gBleAttEvtIncomingClientReadByGroupTypeRequestOpCode_c,                 /*! attIncomingClientReadByGroupTypeRequestCallback event operation code */
    gBleAttEvtIncomingServerReadByGroupTypeResponseOpCode_c,                /*! attIncomingServerReadByGroupTypeResponseCallback event operation code */
    gBleAttEvtIncomingClientWriteRequestOpCode_c,                           /*! attIncomingClientWriteRequestCallback event operation code */
    gBleAttEvtIncomingServerWriteResponseOpCode_c,                          /*! attIncomingServerWriteResponseCallback event operation code */
    gBleAttEvtIncomingClientWriteCommandOpCode_c,                           /*! attIncomingClientWriteCommandCallback event operation code */
    gBleAttEvtIncomingClientSignedWriteCommandOpCode_c,                     /*! attIncomingClientSignedWriteCommandCallback event operation code */
    gBleAttEvtIncomingClientPrepareWriteRequestOpCode_c,                    /*! attIncomingClientPrepareWriteRequestCallback event operation code */
    gBleAttEvtIncomingServerPrepareWriteResponseOpCode_c,                   /*! attIncomingServerPrepareWriteResponseCallback event operation code */
    gBleAttEvtIncomingClientExecuteWriteRequestOpCode_c,                    /*! attIncomingClientExecuteWriteRequestCallback event operation code */
    gBleAttEvtIncomingServerExecuteWriteResponseOpCode_c,                   /*! attIncomingServerExecuteWriteResponseCallback event operation code */
    gBleAttEvtIncomingServerHandleValueNotificationOpCode_c,                /*! attIncomingServerHandleValueNotificationCallback event operation code */
    gBleAttEvtIncomingServerHandleValueIndicationOpCode_c,                  /*! attIncomingServerHandleValueIndicationCallback event operation code */
    gBleAttEvtIncomingClientHandleValueConfirmationOpCode_c,                /*! attIncomingClientHandleValueConfirmationCallback event operation code */
    gBleAttEvtUnsupportedOpcodeOpCode_c,                                    /*! attUnsupportedOpcodeCallback event operation code */
    gBleAttEvtTimeoutOpCode_c,                                              /*! attTimeoutCallback event operation code */
    gBleAttEvtInvalidPduReceivedOpCode_c                                    /*! attInvalidPduReceived event operation code */
}fsciBleAttOpCode_t;


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
* \brief  Calls the ATT function associated with the operation code received over UART.
*         The ATT function parameters are extracted from the received FSCI payload.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI
                                    payload) received over UART
* \param[in]    param               Pointer given when this function is registered in
                                    FSCI
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received
*
********************************************************************************** */
void fsciBleAttHandler
(
    void*       pData,
    void* param,
    uint32_t    fsciInterface
);

/*! *********************************************************************************
* \brief  Creates the FSCI packet which contains the status of the last executed ATT
*         command and sends it over UART.
*
* \param[in]    result      Status of the last executed ATT command.
*
********************************************************************************** */
void fsciBleAttStatusMonitor
(
    bleResult_t result
);

/*! *********************************************************************************
* \brief  Creates a ATT FSCI packet without payload and sends it over UART.
*
* \param[in]    opCode      ATT command operation code.
*
********************************************************************************** */
void fsciBleAttNoParamCmdMonitor
(
    fsciBleAttOpCode_t opCode
);

/*! *********************************************************************************
* \brief  ATT commands monitoring function.
*
* \param[in]  cmdOpCode     ATT command operation code.
* \param[in]  deviceId      The device ID of the peer.
* \param[in]  pParams       The request parameters.
*
********************************************************************************** */
void fsciBleAttGenericCmdMonitor
(
    fsciBleAttOpCode_t  cmdOpCode,
    deviceId_t          deviceId,
    const void*         pParams
);

/*! *********************************************************************************
* \brief  ATT events monitoring function.
*
* \param[in]  evtOpCode     ATT event operation code.
* \param[in]  deviceId      The device ID of the peer.
* \param[in]  pParams       The request parameters.
*
********************************************************************************** */
void fsciBleAttGenericEvtMonitor
(
    fsciBleAttOpCode_t  evtOpCode,
    deviceId_t          deviceId,
    const void*         pParams
);

#ifdef __cplusplus
}
#endif

#endif /* FSCI_BLE_ATT_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
