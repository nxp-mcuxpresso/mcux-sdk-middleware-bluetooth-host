/*! *********************************************************************************
* \addtogroup FSCI_BLE
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* \file
*
* This is a source file for FSCI BLE management.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble_hci.h"


#if gFsciIncluded_c && gFsciBleHciLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    #define fsciBleHciCallApiFunction(apiFunction)          (void)apiFunction
#endif /* gFsciBleTest_d */

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

#if gFsciBleTest_d
    /* Indicates if FSCI for HCI is enabled or not */
    static bool_t bFsciBleHciEnabled            = FALSE;    

    /* Indicates if the command was initiated by FSCI (to be not monitored) */
    static bool_t bFsciBleHciCmdInitiatedByFsci = FALSE;    
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    static void fsciBleHciCmdOrEvtMonitor(fsciBleHciOpCode_t opCode, hciPacketType_t packetType, void* pPacket, uint16_t packetSize);
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

void Ble_HciSend(hciPacketType_t packetType, void* pPacket, uint16_t packetSize);

void fsciBleHciHandler(void* pData, void* param, uint32_t fsciBleInterfaceId)
{
    clientPacket_t* pClientPacket   = (clientPacket_t*)pData;
    uint8_t*        pBuffer         = &pClientPacket->structured.payload[0];
    
    /* Mark this command as initiated by FSCI */
    bFsciBleHciCmdInitiatedByFsci = TRUE;
    
    /* Verify if the command is Mode Select */
    if(gBleHciModeSelectOpCode_c == pClientPacket->structured.header.opCode)
    {
        fsciBleGetBoolValueFromBuffer(bFsciBleHciEnabled, pBuffer);
        /* Return status */
        fsciBleHciStatusMonitor(gBleSuccess_c);
    }
    else
    {
        /* Verify if FSCI is enabled for this layer */
        if(TRUE == bFsciBleHciEnabled)
        {
            uint16_t packetSize;
            
            /* Get packet size from buffer */
            fsciBleGetUint16ValueFromBuffer(packetSize, pBuffer);
            
            /* Select the HCI function to be called (using the FSCI opcode) */
            switch(pClientPacket->structured.header.opCode)
            {     
                case gBleHciCmdCommandOpCode_c:
                    {
                        /* Consider that the HCI command received from TesTool is formatted as a standard HCI
                        command packet */
                        fsciBleHciCallApiFunction(Ble_HciSend(gHciCommandPacket_c, pBuffer, packetSize));
                    }
                    break;
                    
                case gBleHciCmdDataOpCode_c:
                    {
                        /* Consider that the HCI command received from TesTool is formatted as a standard HCI
                        ACL data packet */
                        fsciBleHciCallApiFunction(Ble_HciSend(gHciDataPacket_c, pBuffer, packetSize));
                    }
                    break;
            
                case gBleHciCmdSynchronousDataOpCode_c:
                    {
                        /* Consider that the HCI command received from TesTool is formatted as a standard HCI
                        Synchronous data packet - Not used in BLE */
                        fsciBleHciCallApiFunction(Ble_HciSend(gHciSynchronousDataPacket_c, pBuffer, packetSize));
                    }
                    break;
                    
                default:
                    {
                        /* Unknown FSCI opcode */
                        fsciBleError(gFsciUnknownOpcode_c, fsciBleInterfaceId);
                    }
                    break;
            }
        }
        else
        {
            /* FSCI SAP disabled */
            fsciBleError(gFsciSAPDisabled_c, fsciBleInterfaceId);
        }
    }
        
    (void)MEM_BufferFree(pData);

    /* Mark the next command as not initiated by FSCI */
    bFsciBleHciCmdInitiatedByFsci = FALSE;
}


void fsciBleHciStatusMonitor(bleResult_t result)
{
    /* If HCI is disabled the status must be not monitored */
    if(TRUE == bFsciBleHciEnabled)
    {
        /* Send status over UART */
        fsciBleStatusMonitor(gFsciBleHciOpcodeGroup_c, gBleHciStatusOpCode_c, result);
    }
}


void fsciBleHciCmdMonitor(hciPacketType_t packetType, void* pPacket, uint16_t packetSize)
{
    fsciBleHciOpCode_t opCode;
    
    /* If HCI is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleHciEnabled) ||
       (TRUE == bFsciBleHciCmdInitiatedByFsci))
    {
        return;
    }
    
    /* Get the FSCI opCode */
    switch(packetType)
    {
        case gHciCommandPacket_c:
            {
                opCode = gBleHciCmdCommandOpCode_c;
            }
            break;
            
        case gHciDataPacket_c:
            {
                opCode = gBleHciCmdDataOpCode_c;
            }
            break;
            
        case gHciSynchronousDataPacket_c:
            {
                opCode = gBleHciCmdSynchronousDataOpCode_c;
            }
            break;
            
        default:
            {
                /* Error - unknown packet type (for command) */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }
    
    /* Monitor the HCI command, data, or synchronous data initiated by the upper layer */
    fsciBleHciCmdOrEvtMonitor(opCode, packetType, pPacket, packetSize);
}


void fsciBleHciEvtMonitor(hciPacketType_t packetType, void* pPacket, uint16_t packetSize)
{
    fsciBleHciOpCode_t opCode;
    
    /* If HCI is disabled, the event must be not monitored */
    if(FALSE == bFsciBleHciEnabled)
    {
        return;
    }
    
    /* Get the FSCI opCode */
    switch(packetType)
    {
        case gHciEventPacket_c:
            {
                opCode = gBleHciEvtEventOpCode_c;
            }
            break;
            
        case gHciDataPacket_c:
            {
                opCode = gBleHciEvtDataOpCode_c;
            }
            break;
            
        case gHciSynchronousDataPacket_c:
            {
                opCode = gBleHciEvtSynchronousDataOpCode_c;
            }
            break;
            
        default:
            {
                /* Error - unknown packet type (for event) */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }
    
    /* Monitor the event, data, or synchronous data received from HCI */
    fsciBleHciCmdOrEvtMonitor(opCode, packetType, pPacket, packetSize);
}

#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

static void fsciBleHciCmdOrEvtMonitor(fsciBleHciOpCode_t opCode, hciPacketType_t packetType, void* pPacket, uint16_t packetSize)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    
    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleHciAllocFsciPacket(opCode, sizeof(uint16_t) + packetSize);
    
    if(NULL == pClientPacket)
    {
        return;
    }
    
    pBuffer = &pClientPacket->payload[0];
    
    /* Set packetSize and the packet in the buffer */
    fsciBleGetBufferFromUint16Value(packetSize, pBuffer);
    fsciBleGetBufferFromArray(pPacket, pBuffer, packetSize);
    
    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(pClientPacket, fsciBleInterfaceId);
}

#endif /* gFsciBleTest_d */

#endif /* gFsciIncluded_c && gFsciBleHciLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
