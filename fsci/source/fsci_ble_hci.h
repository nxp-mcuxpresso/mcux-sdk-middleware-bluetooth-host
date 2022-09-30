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

#ifndef FSCI_BLE_HCI_H
#define FSCI_BLE_HCI_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_hci_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! Macro which indicates if FSCI for HCI is enabled or not */
#ifndef gFsciBleHciLayerEnabled_d
    #define gFsciBleHciLayerEnabled_d           0
#endif /* gFsciBleHciLayerEnabled_d */

/*! FSCI operation group for HCI */
#define gFsciBleHciOpcodeGroup_c                0x40


#if defined(FsciCmdMonitor)
    #warning "FsciCmdMonitor macro is already defined"
    #undef FsciCmdMonitor
#endif
    
#if defined(FsciStatusMonitor)
    #warning "FsciStatusMonitor macro is already defined"
    #undef FsciStatusMonitor
#endif

#if defined(FsciEvtMonitor)
    #warning "FsciEvtMonitor macro is already defined"
    #undef FsciEvtMonitor
#endif

/*! Macros used for monitoring commands, statuses and events */
#if gFsciIncluded_c && gFsciBleHciLayerEnabled_d && gFsciBleTest_d
    #define FsciCmdMonitor(function, ...)       fsciBleHciCmdMonitor(__VA_ARGS__)
    #define FsciStatusMonitor(function, ...)    fsciBleHciStatusMonitor(__VA_ARGS__)
    #define FsciEvtMonitor(function, ...)       fsciBleHciEvtMonitor(__VA_ARGS__)
#else
    #define FsciCmdMonitor(function, ...)
    #define FsciStatusMonitor(function, ...)
    #define FsciEvtMonitor(function, ...)
#endif

/*! *********************************************************************************
* \brief  Allocates a FSCI packet for HCI.
*
* \param[in]    opCode      FSCI HCI operation code
* \param[in]    dataSize    Size of the payload
*
* \return The allocated FSCI packet
*
********************************************************************************** */
#define fsciBleHciAllocFsciPacket(opCode,                   \
                                  dataSize)                 \
        fsciBleAllocFsciPacket(gFsciBleHciOpcodeGroup_c,    \
                               (opCode),                    \
                               (dataSize))

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! FSCI operation codes for HCI */
typedef enum
{
    gBleHciModeSelectOpCode_c                   = 0x00,                     /*! HCI Mode Select operation code */

    gBleHciCmdFirstOpCode_c                     = 0x01, 
    gBleHciCmdCommandOpCode_c                   = gBleHciCmdFirstOpCode_c,  /*! HCI command operation code */
    gBleHciCmdDataOpCode_c,                                                 /*! HCI data operation code */
    gBleHciCmdSynchronousDataOpCode_c,                                      /*! HCI synchronous data operation code */
    
    gBleHciStatusOpCode_c                       = 0x80,                     /*! HCI status operation code */ 

    gBleHciEvtFirstOpCode_c                     = 0x81, 
    gBleHciEvtEventOpCode_c                     = gBleHciEvtFirstOpCode_c,  /*! HCI event operation code */
    gBleHciEvtDataOpCode_c,                                                 /*! HCI data operation code */
    gBleHciEvtSynchronousDataOpCode_c                                       /*! HCI synchronous data operation code */
}fsciBleHciOpCode_t;

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
* \brief  Calls the HCI function associated with the operation code received over UART.
*         The HCI function parameters are extracted from the received FSCI payload.
*
* \param[in]    pData               Packet (containing FSCI header and FSCI 
                                    payload) received over UART   
* \param[in]    param               Pointer given when this function is registered in
                                    FSCI
* \param[in]    fsciInterfaceId     FSCI interface on which the packet was received  
*
********************************************************************************** */
void fsciBleHciHandler
(
    void*       pData, 
    void*       param, 
    uint32_t    fsciInterface
);

/*! *********************************************************************************
* \brief  Creates the FSCI packet which contains the status of the last executed HCI 
*         command and sends it over UART.
*
* \param[in]    result      Status of the last executed HCI command.
*
********************************************************************************** */
void fsciBleHciStatusMonitor
(
    bleResult_t result
);

/*! *********************************************************************************
* \brief  Monitoring function for HCI commands.
*
* \param[in]    packetType      HCI packet type.
* \param[in]    pPacket         HCI packet.
* \param[in]    packetSize      HCI packet size.
*
********************************************************************************** */
void fsciBleHciCmdMonitor
(
    hciPacketType_t packetType, 
    void*           pPacket, 
    uint16_t        packetSize
);

/*! *********************************************************************************
* \brief  Monitoring function for HCI events.
*
* \param[in]    packetType      HCI packet type.
* \param[in]    pPacket         HCI packet.
* \param[in]    packetSize      HCI packet size.
*
********************************************************************************** */
void fsciBleHciEvtMonitor
(
    hciPacketType_t packetType, 
    void*           pPacket, 
    uint16_t        packetSize
);

#ifdef __cplusplus
}
#endif 

#endif /* FSCI_BLE_HCI_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
