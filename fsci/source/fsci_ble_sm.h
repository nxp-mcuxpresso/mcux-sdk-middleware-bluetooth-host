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

#ifndef FSCI_BLE_SM_H
#define FSCI_BLE_SM_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_sm_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! Macro which indicates if FSCI for SM is enabled or not */
#ifndef gFsciBleSmLayerEnabled_d
    #define gFsciBleSmLayerEnabled_d            0
#endif /* gFsciBleSmLayerEnabled_d */

/*! FSCI operation group for SM */
#define gFsciBleSmOpcodeGroup_c                 0x43


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
#if gFsciIncluded_c && gFsciBleSmLayerEnabled_d && gFsciBleTest_d
    #define FsciCmdMonitor(function, ...)       fsciBleSm##function##CmdMonitor(__VA_ARGS__)
    #define FsciStatusMonitor(function, ...)    fsciBleSmStatusMonitor(__VA_ARGS__)
    #define FsciEvtMonitor(function, ...)       fsciBleSm##function##EvtMonitor(__VA_ARGS__)
#else
    #define FsciCmdMonitor(function, ...)
    #define FsciStatusMonitor(function, ...)
    #define FsciEvtMonitor(function, ...)
#endif


/*! *********************************************************************************
* \brief  Allocates a FSCI packet for SM.
*
* \param[in]    opCode      FSCI SM operation code.
* \param[in]    dataSize    Size of the payload.
*
* \return The allocated FSCI packet
*
********************************************************************************** */
#define fsciBleSmAllocFsciPacket(opCode,                    \
                                 dataSize)                  \
        fsciBleAllocFsciPacket(gFsciBleSmOpcodeGroup_c,     \
                               (opCode),                      \
                               (dataSize))

/*! *********************************************************************************
* \brief  Sm_Init command monitoring macro.
*
* \param[in]  userMsgCB  Callback function pointer used by the SM to send messages to
*                        the upper layer.
*
********************************************************************************** */
#define fsciBleSmInitCmdMonitor(userEventCB) \
        fsciBleSmNoParamCmdMonitor(gBleSmCmdInitOpCode_c)

/*! *********************************************************************************
* \brief  Sm_RegisterUserCallback command monitoring macro.
*
* \param[in]  userEventCB   Callback function pointer used by the SM to send events to
*                           the upper layer.
*
********************************************************************************** */
#define fsciBleSmRegisterUserCallbackCmdMonitor(userEventCB) \
        fsciBleSmNoParamCmdMonitor(gBleSmCmdRegisterUserCallbackOpCode_c)

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! FSCI operation codes for SM */
typedef enum
{
    gBleSmModeSelectOpCode_c                    = 0x00,                     /*! SM Mode Select operation code */

    gBleSmCmdFirstOpCode_c                      = 0x01,
    gBleSmCmdInitOpCode_c                       = gBleSmCmdFirstOpCode_c,   /*! Sm_Init command operation code */
    gBleSmCmdRegisterUserCallbackOpCode_c,                                  /*! Sm_RegisterUserCallback command operation code */
    gBleSmCmdInitiatorStartPairingOpCode_c,                                 /*! Sm_SendCmd (cmdCode == gBleSmCmdInitiatorStartPairing_c) command operation code */
    gBleSmCmdSendSecurityRequestOpCode_c,                                   /*! Sm_SendCmd (cmdCode == gBleSmCmdSendSecurityRequest_c) command operation code */
    gBleSmCmdTerminatePairingOpCode_c,                                      /*! Sm_SendCmd (cmdCode == gBleSmCmdTerminatePairing_c) command operation code */
    gBleSmCmdPairingRequestReplyOpCode_c,                                   /*! Sm_SendCmd (cmdCode == gBleSmCmdPairingRequestReply_c) command operation code */
    gBleSmCmdPasskeyRequestReplyOpCode_c,                                   /*! Sm_SendCmd (cmdCode == gBleSmCmdPasskeyRequestReply_c) command operation code */
    gBleSmCmdPairingKeysetRequestReplyOpCode_c,                             /*! Sm_SendCmd (cmdCode == gBleSmCmdPairingKeysetRequestReply_c) command operation code */
    gBleSmCmdLlStartEncryptionOpCode_c,                                     /*! Sm_SendCmd (cmdCode == gBleSmCmdLlStartEncryption_c) command operation code */
    gBleSmCmdLlLtkRequestReplyOpCode_c,                                     /*! Sm_SendCmd (cmdCode == gBleSmCmdLlLtkRequestReply_c) command operation code */
    gBleSmCmdLlLtkRequestNegativeReplyOpCode_c,                             /*! Sm_SendCmd (cmdCode == gBleSmCmdLlLtkRequestNegativeReply_c) command operation code */
    gBleSmCmdLlEncryptReqOpCode_c,                                          /*! Sm_SendCmd (cmdCode == gBleSmCmdLlEncryptReq_c) command operation code */
    gBleSmCmdLlRandReqOpCode_c,                                             /*! Sm_SendCmd (cmdCode == gBleSmCmdLlRandReq_c) command operation code */
    gBleSmCmdTbCreateRandomDeviceAddrReqOpCode_c,                           /*! Sm_SendCmd (cmdCode == gBleSmCmdTbCreateRandomDeviceAddrReq_c) command operation code */
    gBleSmCmdTbCheckResolvablePrivateAddrReqOpCode_c,                       /*! Sm_SendCmd (cmdCode == gBleSmCmdTbCheckResolvablePrivateAddrReq_c) command operation code */
    gBleSmCmdTbSignDataReqOpCode_c,                                         /*! Sm_SendCmd (cmdCode == gBleSmCmdTbSignDataReq_c) command operation code */
    gBleSmCmdTbVerifyDataSignatureReqOpCode_c,                              /*! Sm_SendCmd (cmdCode == gBleSmCmdTbVerifyDataSignatureReq_c) command operation code */
    gBleSmCmdDevConnectNotificationOpCode_c,                                /*! Sm_SendCmd (cmdCode == gBleSmCmdDevConnectNotification_c) command operation code */
    gBleSmCmdDevDisconnectNotificationOpCode_c,                             /*! Sm_SendCmd (cmdCode == gBleSmCmdDevDisconnectNotification_c) command operation code */
    gBleSmCmdSetDefaultPasskeyOpCode_c,                                     /*! Sm_SendCmd (cmdCode == gBleSmCmdSetDefaultPasskey_c) command operation code */
    gBleSmCmdSetOobMitmProtectionOpCode_c,                                  /*! Sm_SendCmd (cmdCode == gBleSmCmdSetOobMitmProtection_c) command operation code */
    gBleSmCmdSendKeypressNotificationOpCode_c,                              /*! Sm_SendCmd (cmdCode == gBleSmCmdSendKeypressNotification_c) command operation code */
    gBleSmCmdNcDisplayConfirmOpCode_c,                                      /*! Sm_SendCmd (cmdCode == gBleSmCmdNcDisplayConfirm_c) command operation code */
    gBleSmCmdLeScOobDataRequestReplyOpCode_c,                               /*! Sm_SendCmd (cmdCode == gBleSmCmdLeScOobDataRequestReply_c) command operation code */
    gBleSmCmdLocalLeScOobDataRequestOpCode_c,                               /*! Sm_SendCmd (cmdCode == gBleSmCmdLocalLeScOobDataRequest_c) command operation code */
    gBleSmCmdGenerateNewEcdhPkSkPairReqOpCode_c,                            /*! Sm_SendCmd (cmdCode == gBleSmCmdGenerateNewEcdhPkSkPairReq_c) command operation code */
    gBleSmCmdSetMinPairingSecurityPropertiesOpCode_c,                       /*! Sm_SendCmd (cmdCode == gBleSmCmdSetMinPairingSecurityProperties_c) command operation code */
    gBleSmCmdDHKeyComputedOpCode_c,                                         /*! Sm_SendCmd (cmdCode == gBleSmCmdDHKeyComputedOpCode_c) command operation code */

    gBleSmStatusOpCode_c                        = 0x80,                     /*! SM status operation code */

    gBleSmEvtFirstOpCode_c                      = 0x81,
    gBleSmEvtStatusOpCode_c                     = gBleSmEvtFirstOpCode_c,   /*! fpSmUserEventCB (eventType == gBleSmEventStatus_c) event operation code */
    gBleSmEvtRemoteSecurityRequestOpCode_c,                                 /*! fpSmUserEventCB (eventType == gBleSmEventRemoteSecurityRequest_c) event operation code */
    gBleSmEvtRemotePairingRequestOpCode_c,                                  /*! fpSmUserEventCB (eventType == gBleSmEventRemotePairingRequest_c) event operation code */
    gBleSmEvtRemotePairingResponseOpCode_c,                                 /*! fpSmUserEventCB (eventType == gBleSmEventRemotePairingResponse_c) event operation code */
    gBleSmEvtPasskeyDisplayRequestOpCode_c,                                 /*! fpSmUserEventCB (eventType == gBleSmEventPasskeyDisplayRequest_c) event operation code */
    gBleSmEvtPasskeyRequestOpCode_c,                                        /*! fpSmUserEventCB (eventType == gBleSmEventPasskeyRequest_c) event operation code */
    gBleSmEvtPairingKeysetRequestOpCode_c,                                  /*! fpSmUserEventCB (eventType == gBleSmEventPairingKeysetRequest_c) event operation code */
    gBleSmEvtPairingKeysetReceivedOpCode_c,                                 /*! fpSmUserEventCB (eventType == gBleSmEventPairingKeysetReceived_c) event operation code */
    gBleSmEvtPairingCompleteOpCode_c,                                       /*! fpSmUserEventCB (eventType == gBleSmEventPairingComplete_c) event operation code */
    gBleSmEvtPairingFailedOpCode_c,                                         /*! fpSmUserEventCB (eventType == gBleSmEventPairingFailed_c) event operation code */
    gBleSmEvtRemotePairingFailedOpCode_c,                                   /*! fpSmUserEventCB (eventType == gBleSmEventRemotePairingFailed_c) event operation code */
    gBleSmEvtLlLtkRequestOpCode_c,                                          /*! fpSmUserEventCB (eventType == gBleSmEventLlLtkRequest_c) event operation code */
    gBleSmEvtLlEncryptionStatusOpCode_c,                                    /*! fpSmUserEventCB (eventType == gBleSmEventLlEncryptionStatus_c) event operation code */
    gBleSmEvtLlEncryptResOpCode_c,                                          /*! fpSmUserEventCB (eventType == gBleSmEventLlEncryptRes_c) event operation code */
    gBleSmEvtLlRandResOpCode_c,                                             /*! fpSmUserEventCB (eventType == gBleSmEventLlRandRes_c) event operation code */
    gBleSmEvtTbCreateRandomDeviceAddrResOpCode_c,                           /*! fpSmUserEventCB (eventType == gBleSmEventTbCreateRandomDeviceAddrRes_c) event operation code */
    gBleSmEvtTbCheckResolvalePrivateAddrResOpCode_c,                        /*! fpSmUserEventCB (eventType == gBleSmEventTbCheckResolvalePrivateAddrRes_c) event operation code */
    gBleSmEvtTbSignDataResOpCode_c,                                         /*! fpSmUserEventCB (eventType == gBleSmEventTbSignDataRes_c) event operation code */
    gBleSmEvtTbVerifyDataSignatureResOpCode_c,                              /*! fpSmUserEventCB (eventType == gBleSmEventTbVerifyDataSignatureRes_c) event operation code */
    gBleSmEvtRemoteKeypressNotificationOpCode_c,                            /*! fpSmUserEventCB (eventType == gBleSmEventRemoteKeypressNotification_c) event operation code */
    gBleSmEvtNcDisplayRequestOpCode_c,                                      /*! fpSmUserEventCB (eventType == gBleSmEventNcDisplayRequest_c) event operation code */
    gBleSmEvtLeScOobDataRequestOpCode_c,                                    /*! fpSmUserEventCB (eventType == gBleSmEventLeScOobDataRequest_c) event operation code */
    gBleSmEvtLocalLeScOobDataOpCode_c,                                      /*! fpSmUserEventCB (eventType == gBleSmEventLocalLeScOobData_c) event operation code */
    gBleSmEvtGenerateNewEcdhPkSkPairResOpCode_c,                            /*! fpSmUserEventCB (eventType == gBleSmEventGenerateNewEcdhPkSkPairRes_c) event operation code */
}fsciBleSmOpCode_t;

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
* \brief  Calls the SM function associated with the operation code received over UART.
*         The SM function parameters are extracted from the received FSCI payload.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI
                                    payload) received over UART
* \param[in]    param               Pointer given when this function is registered in
                                    FSCI
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received
*
********************************************************************************** */
void fsciBleSmHandler
(
    void*       pData,
    void*       param,
    uint32_t    fsciInterface
);

/*! *********************************************************************************
* \brief  Creates the FSCI packet which contains the status of the last executed SM
*         command and sends it over UART.
*
* \param[in]    result      Status of the last executed SM command.
*
********************************************************************************** */
void fsciBleSmStatusMonitor
(
    bleResult_t result
);

/*! *********************************************************************************
* \brief  Creates a SM FSCI packet without payload and sends it over UART.
*
* \param[in]    opCode      SM command operation code.
*
********************************************************************************** */
void fsciBleSmNoParamCmdMonitor
(
    fsciBleSmOpCode_t opCode
);

/*! *********************************************************************************
* \brief  Sm_SendCmd command monitoring function.
*
* \param[in]  destDevId         Device Id of the destination device.
* \param[in]  cmdCode           Type of the of the command. See the \ref bleSmCommand_t enumeration.
* \param[in]  cmdLength         Length of the command.
* \param[in]  pCmdPayload       Pointer to the payload of the command.
*
********************************************************************************** */
void fsciBleSmSendCmdCmdMonitor
(
    deviceId_t      destDevId,
    bleSmCommand_t  cmdCode,
    uint16_t        cmdLength,
    void*           pCmdPayload
);

/*! *********************************************************************************
* \brief  fpSmUserEventCB event monitoring function.
*
* \param[in]  sourceDevId       Device Id corresponding to the event.
* \param[in]  eventType         Type of the of the event. See the \ref bleSmEvent_t enumeration.
* \param[in]  eventLength       Length of the event message.
* \param[in]  pEventPayload     Pointer to the payload of the event.
*
********************************************************************************** */
void fsciBleSmUserEventEvtMonitor
(
    deviceId_t      destDevId,
    bleSmEvent_t    eventType,
    uint16_t        eventLength,
    void*           pEventPayload
);

#ifdef __cplusplus
}
#endif

#endif /* FSCI_BLE_SM_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
