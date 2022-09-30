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

#ifndef FSCI_BLE_L2CAP_H
#define FSCI_BLE_L2CAP_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_l2cap_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! Macro which indicates if FSCI for L2CAP is enabled or not */
#ifndef gFsciBleL2capLayerEnabled_d
    #define gFsciBleL2capLayerEnabled_d         0
#endif /* gFsciBleL2capLayerEnabled_d */

/*! FSCI operation group for L2CAP */
#define gFsciBleL2capOpcodeGroup_c              0x41


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
#if gFsciIncluded_c && gFsciBleL2capLayerEnabled_d

    #if gFsciBleHost_d || gFsciBleTest_d
        #define FsciCmdMonitor(function, ...)       fsciBleL2cap##function##CmdMonitor(__VA_ARGS__)
    #else
        #define FsciCmdMonitor(function, ...)
    #endif 

    #if gFsciBleBBox_d || gFsciBleTest_d
        #define FsciStatusMonitor(function, ...)    fsciBleL2capStatusMonitor(__VA_ARGS__)
        #define FsciEvtMonitor(function, ...)       fsciBleL2cap##function##EvtMonitor(__VA_ARGS__)
    #else
        #define FsciStatusMonitor(function, ...)
        #define FsciEvtMonitor(function, ...)
    #endif

#else
    #define FsciCmdMonitor(function, ...)
    #define FsciStatusMonitor(function, ...)
    #define FsciEvtMonitor(function, ...)
#endif

/*! *********************************************************************************
* \brief  Allocates a FSCI packet for L2CAP.
*
* \param[in]    opCode      FSCI L2CAP operation code.
* \param[in]    dataSize    Size of the payload.
*
* \return The allocated FSCI packet
*
********************************************************************************** */
#define fsciBleL2capAllocFsciPacket(opCode,                 \
                                    dataSize)               \
        fsciBleAllocFsciPacket(gFsciBleL2capOpcodeGroup_c,  \
                               (opCode),                    \
                               (dataSize))

/*! *********************************************************************************
* \brief  L2ca_Init command monitoring macro.
*
********************************************************************************** */
#define fsciBleL2capInitCmdMonitor()  \
        fsciBleL2capNoParamCmdMonitor(gBleL2capCmdInitOpCode_c)

/*! *********************************************************************************
* \brief  L2ca_SendAttData command monitoring macro.
*
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    pPacket             Data buffer to be transmitted.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capSendAttDataCmdMonitor(deviceId,                     \
                                          pPacket,                      \
                                          packetLength)                 \
        fsciBleL2capGenericCmdMonitor(gBleL2capCmdSendAttDataOpCode_c,  \
                                      (deviceId),                       \
                                      (pPacket),                        \
                                      (packetLength))

/*! *********************************************************************************
* \brief  L2ca_SendSmpData command monitoring macro.
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    pPacket             Data buffer to be transmitted.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capSendSmpDataCmdMonitor(deviceId,                     \
                                          pPacket,                      \
                                          packetLength)                 \
        fsciBleL2capGenericCmdMonitor(gBleL2capCmdSendSmpDataOpCode_c,  \
                                      (deviceId),                       \
                                      (pPacket),                        \
                                      (packetLength))

/*! *********************************************************************************
* \brief  L2ca_SendSignalingData command monitoring macro.
*
* \param[in]    deviceId            The DeviceID for which the command is intended
* \param[in]    pPacket             Data buffer to be transmitted.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capSendSignalingDataCmdMonitor(deviceId,                       \
                                                pPacket,                        \
                                                packetLength)                   \
        fsciBleL2capGenericCmdMonitor(gBleL2capCmdSendSignalingDataOpCode_c,    \
                                      (deviceId),                               \
                                      (pPacket),                                \
                                      (packetLength))

/*! *********************************************************************************
* \brief  L2ca_RegisterAttCallback command monitoring macro.
*
* \param[in]    pCallback           Callback function for uplink data.
*
********************************************************************************** */
#define fsciBleL2capRegisterAttCallbackCmdMonitor(pCallback) \
        fsciBleL2capNoParamCmdMonitor(gBleL2capCmdRegisterAttCallbackOpCode_c)

/*! *********************************************************************************
* \brief  L2ca_RegisterSmpCallback command monitoring macro.
*
* \param[in]    pCallback           Callback function for uplink data.
*
********************************************************************************** */
#define fsciBleL2capRegisterSmpCallbackCmdMonitor(pCallback) \
        fsciBleL2capNoParamCmdMonitor(gBleL2capCmdRegisterSmpCallbackOpCode_c)
          
/*! *********************************************************************************
* \brief  l2caAttChannelCallback event monitoring macro.
*
* \param[in]    deviceId            The DeviceID from which ATT data is received.
* \param[in]    pPacket             Received data buffer.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capAttChannelEvtMonitor(deviceId,                          \
                                         pPacket,                           \
                                         packetLength)                      \
        fsciBleL2capGenericCmdOrEvtMonitor(gBleL2capEvtAttChannelOpCode_c,  \
                                           (deviceId),                      \
                                           (pPacket),                       \
                                           (packetLength))

/*! *********************************************************************************
* \brief  l2caSmpChannelCallback event monitoring macro.
*
* \param[in]    deviceId            The DeviceID from which SMP data is received.
* \param[in]    pPacket             Received data buffer.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capSmpChannelEvtMonitor(deviceId,                          \
                                         pPacket,                           \
                                         packetLength)                      \
        fsciBleL2capGenericCmdOrEvtMonitor(gBleL2capEvtSmpChannelOpCode_c,  \
                                           (deviceId),                      \
                                           (pPacket),                       \
                                           (packetLength))

/*! *********************************************************************************
* \brief  signaling data event monitoring macro.
*
* \param[in]    deviceId            The DeviceID from which signaling data is received.
* \param[in]    pPacket             Received data buffer.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
#define fsciBleL2capSignalingChannelEvtMonitor(deviceId,                    \
                                               pPacket,                     \
                                               packetLength)                \
        fsciBleL2capGenericCmdOrEvtMonitor(gBleL2capEvtSignalingChannelOpCode_c,  \
                                           (deviceId),                      \
                                           (pPacket),                       \
                                           (packetLength))

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! FSCI operation codes for L2CAP */
typedef enum
{
    gBleL2capModeSelectOpCode_c                 = 0x00,                         /*! L2CAP Mode Select operation code */
    gBleL2capCmdFirstOpCode_c                   = 0x01, 
    gBleL2capCmdInitOpCode_c                    = gBleL2capCmdFirstOpCode_c,    /*! L2ca_Init command operation code */ 
    gBleL2capCmdConfigOpCode_c,                                                 /*! L2ca_Config command operation code */
    gBleL2capCmdSendAttDataOpCode_c,                                            /*! L2ca_SendAttData command operation code */
    gBleL2capCmdSendSmpDataOpCode_c,                                            /*! L2ca_SendSmpData command operation code */
    gBleL2capCmdSendSignalingDataOpCode_c,                                      /*! L2ca_SendSignalingData command operation code */
    gBleL2capCmdRegisterAttCallbackOpCode_c,                                    /*! L2ca_RegisterAttCallback command operation code */
    gBleL2capCmdRegisterSmpCallbackOpCode_c,                                    /*! L2ca_RegisterSmpCallback command operation code */
    
    gBleL2capStatusOpCode_c                     = 0x80,                         /*! L2CAP status operation code */
    
    /* Events */
    gBleL2capEvtFirstOpCode_c                   = 0x81, 
    gBleL2capEvtAttChannelOpCode_c              = gBleL2capEvtFirstOpCode_c,    /*! l2caAttChannelCallback event operation code */ 
    gBleL2capEvtSmpChannelOpCode_c,                                             /*! l2caSmpChannelCallback event operation code */
    gBleL2capEvtSignalingChannelOpCode_c,                                       /*! signaling data event operation code */
}fsciBleL2capOpCode_t;

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
* \brief  Calls the L@CAP function associated with the operation code received over UART.
*         The L2CAP function parameters are extracted from the received FSCI payload.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI. 
                                    payload) received over UART.  
* \param[in]    param               Pointer given when this function is registered in
                                    FSCI.
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received.
*
********************************************************************************** */
void fsciBleL2capHandler
(
    void*       pData, 
    void*       param, 
    uint32_t    fsciInterface
);

/*! *********************************************************************************
* \brief  Creates the FSCI packet which contains the status of the last executed L2CAP 
*         command and sends it over UART.
*
* \param[in]    result      Status of the last executed L2CAP command.
*
********************************************************************************** */
void fsciBleL2capStatusMonitor
(
    bleResult_t result
);

/*! *********************************************************************************
* \brief  Creates a L2CAP FSCI packet without payload and sends it over UART.
*
* \param[in]    opCode      L2CAP command operation code.
*
********************************************************************************** */
void fsciBleL2capNoParamCmdMonitor
(
    fsciBleL2capOpCode_t opCode
);

/*! *********************************************************************************
* \brief  L2ca_SendAttData and L2ca_SendSmpData commands monitoring function.
*
* \param[in]    opCode              L2CAP command operation code.
* \param[in]    deviceId            The DeviceID for which the command is intended.
* \param[in]    pPacket             Data buffer to be transmitted.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
void fsciBleL2capGenericCmdMonitor
(
    fsciBleL2capOpCode_t    opCode, 
    deviceId_t              deviceId, 
    const uint8_t*          pPacket, 
    uint16_t                packetLength
);

/*! *********************************************************************************
* \brief  L2ca_Config command monitoring function.
*
* \param[in]    pConfigStruct   Configuration information.
*
********************************************************************************** */
void fsciBleL2capConfigCmdMonitor
(
    const l2caConfigStruct_t* pConfigStruct
);

/*! *********************************************************************************
* \brief  l2caAttChannelCallback and l2caSmpChannelCallback events monitoring function.
*
* \param[in]    opCode              L2CAP command operation code.
* \param[in]    deviceId            The DeviceID from which ATT data is received.
* \param[in]    pPacket             Received data buffer.
* \param[in]    packetLength        Length of the data buffer.
*
********************************************************************************** */
void fsciBleL2capGenericCmdOrEvtMonitor
(
    fsciBleL2capOpCode_t    opCode, 
    deviceId_t              deviceId, 
    const uint8_t*          pPacket, 
    uint16_t                packetLength
);

#ifdef __cplusplus
}
#endif 

#endif /* FSCI_BLE_L2CAP_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
