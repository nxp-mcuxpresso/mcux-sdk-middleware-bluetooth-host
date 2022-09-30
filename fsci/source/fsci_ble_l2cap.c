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

#include "fsci_ble_l2cap.h"
extern bleResult_t L2ca_Init( void );
extern bleResult_t L2ca_Config(const l2caConfigStruct_t* pConfigStruct);

#if gFsciIncluded_c && gFsciBleL2capLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    #define fsciBleL2capCallApiFunction(apiFunction)        (void)apiFunction
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    static void fsciBleL2capAttChannelCallback(deviceId_t deviceId, uint8_t* pPacket, uint16_t packetLength);
    static void fsciBleL2capSmpChannelCallback(deviceId_t deviceId, uint8_t* pPacket, uint16_t packetLength);
#endif /* gFsciBleTest_d */
    
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    /* Indicates if FSCI for L2CAP is enabled or not */
    static bool_t bFsciBleL2capEnabled          	= FALSE;    

    /* Indicates if the command was initiated by FSCI (to be not monitored) */
    static bool_t bFsciBleL2capCmdInitiatedByFsci   = FALSE;    
#endif /* gFsciBleTest_d */


/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

void fsciBleL2capHandler(void* pData, void* param, uint32_t fsciBleInterfaceId)
{
    clientPacket_t* pClientPacket   = (clientPacket_t*)pData;
    uint8_t*        pBuffer         = &pClientPacket->structured.payload[0];
    
    /* Mark this command as initiated by FSCI */
    bFsciBleL2capCmdInitiatedByFsci = TRUE;
    
    /* Verify if the command is Mode Select */
    if(gBleL2capModeSelectOpCode_c == pClientPacket->structured.header.opCode)
    {
        fsciBleGetBoolValueFromBuffer(bFsciBleL2capEnabled, pBuffer);
        /* Return status */
        fsciBleL2capStatusMonitor(gBleSuccess_c);
    }
    else
    {
        /* Verify if FSCI is enabled for this layer */
        if(TRUE == bFsciBleL2capEnabled)
        {
            /* Select the L2CAP function to be called (using the FSCI opcode) */
            switch(pClientPacket->structured.header.opCode)
            {
                case gBleL2capCmdInitOpCode_c: 
                    {
                        fsciBleL2capCallApiFunction(L2ca_Init());
                    }
                    break;
                    
                case gBleL2capCmdConfigOpCode_c:
                    {
                        l2caConfigStruct_t configStruct;
                        
                        /* Get configStruct fields from the received packet */
                        fsciBleL2capGetConfigStructFromBuffer(&configStruct, &pBuffer);
                        
                        fsciBleL2capCallApiFunction(L2ca_Config(&configStruct));
                    }
                    break;
                    
                case gBleL2capCmdSendAttDataOpCode_c:
                    {
                        deviceId_t  deviceId; 
                        uint16_t    packetLength; 
                        uint8_t*    pPacket;
                        
                        /* Get deviceId and packetLength parameters from the received packet */
                        fsciBleGetDeviceIdFromBuffer(&deviceId, &pBuffer);
                        fsciBleGetUint16ValueFromBuffer(packetLength, pBuffer); 
                        
                        /* Allocate buffer for pPacket - consider that packetLength is bigger than 0 */
                        pPacket = MEM_BufferAlloc(packetLength);
                        
                        if(NULL != pPacket)
                        {
                            /* Get pPacket parameter from the received packet */
                            fsciBleGetArrayFromBuffer(pPacket, pBuffer, packetLength); 
                            
                            fsciBleL2capCallApiFunction(L2ca_SendAttData(deviceId, pPacket, packetLength));
                            
                            /* Free the buffer allocated for pPacket */
                            (void)MEM_BufferFree(pPacket);
                        }
                        else
                        {
                            /* No buffer available - the L2CAP command can not be 
                            executed */
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;
                    
                case gBleL2capCmdSendSmpDataOpCode_c:
                    {
                        deviceId_t  deviceId; 
                        uint16_t    packetLength; 
                        uint8_t*    pPacket;
                        
                        /* Get deviceId and packetLength parameters from the received packet */
                        fsciBleGetDeviceIdFromBuffer(&deviceId, &pBuffer);
                        fsciBleGetUint16ValueFromBuffer(packetLength, pBuffer); 
                        
                        /* Allocate buffer for pPacket - consider that packetLength is bigger than 0 */
                        pPacket = MEM_BufferAlloc(packetLength);
                        
                        if(NULL != pPacket)
                        {
                            /* Get pPacket parameter from the received packet */
                            fsciBleGetArrayFromBuffer(pPacket, pBuffer, packetLength); 
                            
                            fsciBleL2capCallApiFunction(L2ca_SendSmpData(deviceId, pPacket, packetLength));
                            
                            /* Free the buffer allocated for pPacket */
                            (void)MEM_BufferFree(pPacket);
                        } 
                        else
                        {
                            /* No buffer available - the L2CAP command can not be 
                            executed */
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;
                    
                case gBleL2capCmdRegisterAttCallbackOpCode_c:
                    {
                        fsciBleL2capCallApiFunction(L2ca_RegisterAttCallback(fsciBleL2capAttChannelCallback));
                    }
                    break;
                    
                case gBleL2capCmdRegisterSmpCallbackOpCode_c:
                    {
                        fsciBleL2capCallApiFunction(L2ca_RegisterSmpCallback(fsciBleL2capSmpChannelCallback));
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
    
    /* Mark the next command as not initiated by FSCI */
    bFsciBleL2capCmdInitiatedByFsci = FALSE;

    (void)MEM_BufferFree(pData);
}


void fsciBleL2capStatusMonitor(bleResult_t result)
{
    /* If L2CAP is disabled the status must be not monitored */
    if(FALSE == bFsciBleL2capEnabled)
    {
        return;
    }
    
    /* Send status over UART */
    fsciBleStatusMonitor(gFsciBleL2capOpcodeGroup_c, gBleL2capStatusOpCode_c, result);
}


void fsciBleL2capNoParamCmdMonitor(fsciBleL2capOpCode_t opCode)
{
    /* If L2CAP is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleL2capEnabled) ||
       (TRUE == bFsciBleL2capCmdInitiatedByFsci))
    {
        return;
    }
    
    /* Call the generic FSCI BLE monitor for commands or events that have no parameters */
    fsciBleNoParamCmdOrEvtMonitor(gFsciBleL2capOpcodeGroup_c, opCode);    
}


void fsciBleL2capConfigCmdMonitor(const l2caConfigStruct_t* pConfigStruct)
{
    union
    {
        clientPacket_t*             pClientPacketTemp;
        clientPacketStructured_t*   pClientPacketStructuredTemp;
    }clientPacketVars;
    uint8_t*                    pBuffer;
    
    /* If L2CAP is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleL2capEnabled) ||
       (TRUE == bFsciBleL2capCmdInitiatedByFsci))
    {
        return;
    }
    
    /* Allocate the packet to be sent over UART */
    clientPacketVars.pClientPacketStructuredTemp = fsciBleL2capAllocFsciPacket(gBleL2capCmdConfigOpCode_c, fsciBleL2capGetConfigStructBufferSize(pConfigStruct));
    
    if(NULL == clientPacketVars.pClientPacketStructuredTemp)
    {
        return;
    }
    
    pBuffer = &clientPacketVars.pClientPacketStructuredTemp->payload[0];
    
    /* Set command parameters in the buffer */
    fsciBleL2capGetBufferFromConfigStruct(pConfigStruct, &pBuffer);
    
    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(clientPacketVars.pClientPacketTemp, fsciBleInterfaceId);
}


void fsciBleL2capGenericCmdMonitor(fsciBleL2capOpCode_t opCode, deviceId_t deviceId, const uint8_t* pPacket, uint16_t packetLength)
{
    /* If the command was initiated by FSCI it must be not monitored */
    if(TRUE == bFsciBleL2capCmdInitiatedByFsci)
    {
        return;
    }

    fsciBleL2capGenericCmdOrEvtMonitor(opCode, deviceId, pPacket, packetLength);    
}
    
    
void fsciBleL2capGenericCmdOrEvtMonitor(fsciBleL2capOpCode_t opCode, deviceId_t deviceId, const uint8_t* pPacket, uint16_t packetLength)
{
    union
    {
        clientPacket_t*             pClientPacketTemp;
        clientPacketStructured_t*   pClientPacketStructuredTemp;
    }clientPacketVars;
    uint8_t*                    pBuffer;
    
    /* If L2CAP is disabled the event must be not monitored */
    if(FALSE == bFsciBleL2capEnabled)
    {
        return;
    }
    
    /* Allocate the packet to be sent over UART */
    clientPacketVars.pClientPacketStructuredTemp = fsciBleL2capAllocFsciPacket(opCode, fsciBleGetDeviceIdBufferSize(&deviceId) + 
                                                        sizeof(uint16_t) + packetLength);
    
    if(NULL == clientPacketVars.pClientPacketStructuredTemp)
    {
        return;
    }
    
    pBuffer = &clientPacketVars.pClientPacketStructuredTemp->payload[0];
    
    /* Set event parameters in the buffer */
    fsciBleGetBufferFromDeviceId(&deviceId, &pBuffer);
    fsciBleGetBufferFromUint16Value(packetLength, pBuffer);
    fsciBleGetBufferFromArray(pPacket, pBuffer, packetLength);
    
    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(clientPacketVars.pClientPacketTemp, fsciBleInterfaceId);
}

#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

static void fsciBleL2capAttChannelCallback(deviceId_t deviceId, uint8_t* pPacket, uint16_t packetLength)
{

}


static void fsciBleL2capSmpChannelCallback(deviceId_t deviceId, uint8_t* pPacket, uint16_t packetLength)
{

}

#endif /* gFsciBleTest_d */

#endif /* gFsciIncluded_c && gFsciBleL2capLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
