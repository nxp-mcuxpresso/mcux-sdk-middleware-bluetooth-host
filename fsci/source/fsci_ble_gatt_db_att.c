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

#include "fsci_ble_gatt_db_att.h"


#if gFsciIncluded_c && gFsciBleGattDbAttLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    #define fsciBleGattDbAttCallApiFunction(apiFunction)        (void)apiFunction
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
    /* Indicates if FSCI for GATT Database (ATT) is enabled or not */
    static bool_t bFsciBleGattDbAttEnabled              = FALSE;    

    /* Indicates if the command was initiated by FSCI (to be not monitored) */
    static bool_t bFsciBleGattDbAttCmdInitiatedByFsci   = FALSE;    
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

void fsciBleGattDbAttHandler(void* pData, void* pParam, uint32_t fsciBleInterfaceId)
{
    clientPacket_t* pClientPacket   = (clientPacket_t*)pData;
    uint8_t*        pBuffer         = &pClientPacket->structured.payload[0];
    
    /* Mark this command as initiated by FSCI */
    bFsciBleGattDbAttCmdInitiatedByFsci = TRUE;
    
    /* Verify if the command is Mode Select */
    if(gBleGattDbAttModeSelectOpCode_c == pClientPacket->structured.header.opCode)
    {
        fsciBleGetBoolValueFromBuffer(bFsciBleGattDbAttEnabled, pBuffer);
        /* Return status */
        fsciBleGattDbAttStatusMonitor(gBleSuccess_c);
    }
    else
    {
        /* Verify if FSCI is enabled for this layer */
        if(TRUE == bFsciBleGattDbAttEnabled)
        {
            deviceId_t  deviceId;
            uint16_t    errorAttributeHandle;
            
            /* Get deviceId parameter from buffer */
            fsciBleGetDeviceIdFromBuffer(&deviceId, &pBuffer);
            
            /* Select the GATT Database (ATT) function to be called (using the FSCI opcode) */
            switch(pClientPacket->structured.header.opCode)
            {
                case gBleGattDbAttCmdFindInformationOpCode_c:
                    {
                        attFindInformationRequestParams_t   reqParams;
                        attFindInformationResponseParams_t  rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetFindInformationRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttFindInformation(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    }
                    break;
                    
                case gBleGattDbAttCmdFindByTypeValueOpCode_c:
                    {
                        attFindByTypeValueRequestParams_t   reqParams;
                        attFindByTypeValueResponseParams_t  rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetFindByTypeValueRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttFindByTypeValue(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdReadByTypeOpCode_c:
                    {
                        attReadByTypeRequestParams_t    reqParams;
                        attReadByTypeResponseParams_t   rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetRdByTypeReqParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttReadByType(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdReadOpCode_c:
                    {
                        attReadRequestParams_t  reqParams;
                        attReadResponseParams_t rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetReadRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttRead(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdReadBlobOpCode_c:
                    {
                        attReadBlobRequestParams_t  reqParams;
                        attReadBlobResponseParams_t rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetReadBlobRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttReadBlob(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                   
                    }
                    break;
                    
                case gBleGattDbAttCmdReadMultipleOpCode_c:
                    {
                        attReadMultipleRequestParams_t  reqParams;
                        attReadMultipleResponseParams_t rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetReadMultipleRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttReadMultiple(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdReadByGroupTypeOpCode_c:
                    {
                        attReadByGroupTypeRequestParams_t   reqParams;
                        attReadByGroupTypeResponseParams_t  rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetReadByGroupTypeRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttReadByGroupType(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdWriteOpCode_c:
                    {
                        attWriteRequestAndCommandParams_t reqParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetWriteRequestAndCommandParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttWrite(deviceId, &reqParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdWriteCommandOpCode_c:
                    {
                        attWriteRequestAndCommandParams_t reqParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetWriteRequestAndCommandParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttWriteCommand(deviceId, &reqParams));
                     
                    }
                    break;
                    
                case gBleGattDbAttCmdSignedWriteCommandOpCode_c:
                    {
                        attSignedWriteCommandParams_t reqParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetSignedWriteCommandParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttSignedWriteCommand(deviceId, &reqParams));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdPrepareWriteOpCode_c:
                    {
                        attPrepareWriteRequestResponseParams_t  reqParams;
                        attPrepareWriteRequestResponseParams_t  rspParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttPrepareWrite(deviceId, &reqParams, &rspParams, &errorAttributeHandle));
                     
                    }
                    break;
                    
                case gBleGattDbAttCmdExecuteWriteOpCode_c:
                    {
                        attExecuteWriteRequestParams_t reqParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetExecuteWriteRequestParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttExecuteWrite(deviceId, &reqParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdExecuteWriteFromQueueOpCode_c:
                    {
                        attPrepareWriteRequestResponseParams_t reqParams;
                        
                        /* Get command parameter from buffer */
                        fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(&reqParams, &pBuffer);
                        
                        fsciBleGattDbAttCallApiFunction(GattDb_AttExecuteWriteFromQueue(deviceId, &reqParams, &errorAttributeHandle));
                    
                    }
                    break;
                    
                case gBleGattDbAttCmdPrepareNotificationIndicationOpCode_c:
                    {
                        attVarHandleValueNotificationIndicationParams_t* pAttHandleValueNotificationIndicationParams;
                        pAttHandleValueNotificationIndicationParams = (attVarHandleValueNotificationIndicationParams_t*)MEM_BufferAlloc(sizeof(attVarHandleValueNotificationIndicationParams_t) + gAttMaxWriteDataSize_d(gAttMaxMtu_c) - 1);
                        
                        if( NULL != pAttHandleValueNotificationIndicationParams )
                        {
                            /* Get command parameter from buffer */
                            fsciBleAttGetHandleValueNotificationIndicationParamsFromBuffer(pAttHandleValueNotificationIndicationParams, &pBuffer);
                            
                            fsciBleGattDbAttCallApiFunction(GattDb_AttPrepareNotificationIndication(deviceId, pAttHandleValueNotificationIndicationParams, &errorAttributeHandle));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
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
    bFsciBleGattDbAttCmdInitiatedByFsci = FALSE;
}


void fsciBleGattDbAttStatusMonitor(bleResult_t result)
{
    /* If GATT Database (ATT) is disabled the status must be not monitored */
    if(TRUE == bFsciBleGattDbAttEnabled)
    {
        fsciBleStatusMonitor(gFsciBleGattDbAttOpcodeGroup_c, gBleGattDbAttStatusOpCode_c, result);
    }
}


void fsciBleGattDbAttCmdMonitor(fsciBleGattDbAttOpCode_t opCode, deviceId_t deviceId, const void* pParams)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    uint16_t                    dataSize = fsciBleGetDeviceIdBufferSize(&deviceId);
    
    /* If GATT Database (ATT) is disabled or if the command was initiated by FSCI it 
    must be not monitored */
    if((FALSE == bFsciBleGattDbAttEnabled) ||
       (TRUE == bFsciBleGattDbAttCmdInitiatedByFsci))
    {
        return;
    }
    
    /* Get the needed data size for the buffer to be sent over UART */
    switch(opCode)
    {
        case gBleGattDbAttCmdFindInformationOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationRequestParamsBufferSize((attFindInformationRequestParams_t*)(attParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdFindByTypeValueOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueRequestParamsBufferSize((attFindByTypeValueRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdReadByTypeOpCode_c:
            {
                dataSize += fsciBleAttGetRdByTypeReqParamsBuffSize((attReadByTypeRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdReadOpCode_c:
            {
                dataSize += fsciBleAttGetReadRequestParamsBufferSize((attReadRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdReadBlobOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobRequestParamsBufferSize((attReadBlobRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdReadMultipleOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleRequestParamsBufferSize((attReadMultipleRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdReadByGroupTypeOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeRequestParamsBufferSize((attReadByGroupTypeRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdWriteOpCode_c:
            {
                dataSize += fsciBleAttGetWriteRequestAndCommandParamsBufferSize((attWriteRequestAndCommandParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetWriteRequestAndCommandParamsBufferSize((attWriteRequestAndCommandParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdSignedWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetSignedWriteCommandParamsBufferSize((attSignedWriteCommandParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdPrepareWriteOpCode_c:
            {
                dataSize += fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize((attPrepareWriteRequestResponseParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdExecuteWriteOpCode_c:
            {
                dataSize += fsciBleAttGetExecuteWriteRequestParamsBufferSize((attExecuteWriteRequestParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdExecuteWriteFromQueueOpCode_c:
            {
                dataSize += fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize((attPrepareWriteRequestResponseParams_t*)pParams);
            }
            break;
            
        case gBleGattDbAttCmdPrepareNotificationIndicationOpCode_c:
            {
                dataSize += fsciBleAttGetHandleValueNotificationIndicationParamsBufferSize((attHandleValueNotificationIndicationParams_t*)pParams);
            }
            break;
            
        default:
            {
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }
    
    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleGattDbAttAllocFsciPacket(opCode, dataSize);
    
    if(NULL == pClientPacket)
    {
        return;
    }
    
    pBuffer = &pClientPacket->payload[0];
    
    /* Set deviceId in buffer */
    fsciBleGetBufferFromDeviceId(&deviceId, &pBuffer);
    
    /* Set command parameters in the buffer */
    switch(opCode)
    {
        case gBleGattDbAttCmdFindInformationOpCode_c:
            {
                fsciBleAttGetBuffFromFindInfoRequestParams((attFindInformationRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdFindByTypeValueOpCode_c:
            {
                fsciBleAttGetBufferFromFindByTypeValueRequestParams((attFindByTypeValueRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdReadByTypeOpCode_c:
            {
                fsciBleAttGetBuffFromReadByTypeReqParams((attReadByTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdReadOpCode_c:
            {
                fsciBleAttGetBufferFromReadRequestParams((attReadRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdReadBlobOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobRequestParams((attReadBlobRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdReadMultipleOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleRequestParams((attReadMultipleRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdReadByGroupTypeOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeRequestParams((attReadByGroupTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdWriteOpCode_c:
            {
                fsciBleAttGetBufferFromWriteRequestAndCommandParams((attWriteRequestAndCommandParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromWriteRequestAndCommandParams((attWriteRequestAndCommandParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdSignedWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromSignedWriteCommandParams((attSignedWriteCommandParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdPrepareWriteOpCode_c:
            {
                fsciBleAttGetBufferFromPrepareWriteRequestResponseParams((attPrepareWriteRequestResponseParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdExecuteWriteOpCode_c:
            {
                fsciBleAttGetBufferFromExecuteWriteRequestParams((attExecuteWriteRequestParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdExecuteWriteFromQueueOpCode_c:
            {
                fsciBleAttGetBufferFromPrepareWriteRequestResponseParams((attPrepareWriteRequestResponseParams_t*)pParams, &pBuffer);
            }
            break;
            
        case gBleGattDbAttCmdPrepareNotificationIndicationOpCode_c:
            {
                fsciBleAttGetBufferFromHandleValueNotificationIndicationParams((attHandleValueNotificationIndicationParams_t*)pParams, &pBuffer);
            }
            break;
            
        default:
            break;
    }
    
    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(pClientPacket, fsciBleInterfaceId);
}


void fsciBleGattDbAttEvtMonitor(fsciBleGattDbAttOpCode_t opCode, void* pParams, uint16_t* pErrorAttributeHandle)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    uint16_t                    dataSize = sizeof(uint16_t);
    
    /* If GATT Database (ATT) is disabled the event must be not monitored */
    if(FALSE == bFsciBleGattDbAttEnabled)
    {
        return;
    }
    
    /* Get the needed data size for the buffer to be sent over UART */
    switch(opCode)
    {
        case gBleGattDbAttEvtWriteOpCode_c:
        case gBleGattDbAttEvtExecuteWriteOpCode_c:
        case gBleGattDbAttEvtExecuteWriteFromQueueOpCode_c:
            {
                
            }
            break;
                
        case gBleGattDbAttEvtFindInformationOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationResponseParamsBufferSize((attFindInformationResponseParams_t*)pParams); 
            }
            break;
            
        case gBleGattDbAttEvtFindByTypeValueOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueResponseParamsBufferSize((attFindByTypeValueResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtReadByTypeOpCode_c:
            {
                dataSize += fsciBleAttGetReadByTypeResponseParamsBufferSize((attReadByTypeResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtReadOpCode_c:
            {
                dataSize += fsciBleAttGetReadResponseParamsBufferSize((attReadResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtReadBlobOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobResponseParamsBufferSize((attReadBlobResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtReadMultipleOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleResponseParamsBufferSize((attReadMultipleResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtReadByGroupTypeOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeResponseParamsBufferSize((attReadByGroupTypeResponseParams_t*)pParams); 
            }
            break;
        
        case gBleGattDbAttEvtPrepareWriteOpCode_c:
            {
                dataSize += fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize((attPrepareWriteRequestResponseParams_t*)pParams); 
            }
            break;
            
        case gBleGattDbAttEvtPrepareNotificationIndicationOpCode_c:
            {
                dataSize += fsciBleAttGetHandleValueNotificationIndicationParamsBufferSize((attHandleValueNotificationIndicationParams_t*)pParams);
            }
            break;
          
        default:
            {
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }    
    
    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleGattDbAttAllocFsciPacket(opCode, dataSize);
    
    if(NULL == pClientPacket)
    {
        return;
    }
    
    pBuffer = &pClientPacket->payload[0];
    
    /* Set event parameters in the buffer */
    switch(opCode)
    {
        case gBleGattDbAttEvtFindInformationOpCode_c:
            {
                fsciBleAttGetBuffFromInfoResponseParams((attFindInformationResponseParams_t*)pParams, &pBuffer); 
            }
            break;
            
        case gBleGattDbAttEvtFindByTypeValueOpCode_c:
            {
                fsciBleAttGetBuffFromFindByTypeValResponseParams((attFindByTypeValueResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtReadByTypeOpCode_c:
            {
                fsciBleAttGetBuffFromRdByTypeRespParams((attReadByTypeResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtReadOpCode_c:
            {
                fsciBleAttGetBufferFromReadResponseParams((attReadResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtReadBlobOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobResponseParams((attReadBlobResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtReadMultipleOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleResponseParams((attReadMultipleResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtReadByGroupTypeOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeResponseParams((attReadByGroupTypeResponseParams_t*)pParams, &pBuffer); 
            }
            break;
        
        case gBleGattDbAttEvtPrepareWriteOpCode_c:
            {
                fsciBleAttGetBufferFromPrepareWriteRequestResponseParams((attPrepareWriteRequestResponseParams_t*)pParams, &pBuffer); 
            }
            break;
            
        case gBleGattDbAttEvtPrepareNotificationIndicationOpCode_c:
            {
                fsciBleAttGetBufferFromHandleValueNotificationIndicationParams((attHandleValueNotificationIndicationParams_t*)pParams, &pBuffer);
            }
            break;
        
        default:
            break;
    }    
    
    fsciBleGetBufferFromUint16Value(*pErrorAttributeHandle, pBuffer);
    
    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(pClientPacket, fsciBleInterfaceId);
}

#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c && gFsciBleGattDbAttLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
