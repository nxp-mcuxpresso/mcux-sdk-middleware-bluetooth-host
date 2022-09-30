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

#include "fsci_ble_att.h"


#if gFsciIncluded_c && gFsciBleAttLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    #define fsciBleAttCallApiFunction(apiFunction)          (void)apiFunction
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

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    /* Indicates if FSCI for ATT is enabled or not */
    static bool_t bFsciBleAttEnabled            = FALSE;

    /* Indicates if the command was initiated by FSCI (to be not monitored) */
    static bool_t bFsciBleAttCmdInitiatedByFsci = FALSE;
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

void fsciBleAttHandler(void* pData, void* pParam, uint32_t fsciBleInterfaceId)
{
    clientPacket_t* pClientPacket   = (clientPacket_t*)pData;
    uint8_t*        pBuffer         = &pClientPacket->structured.payload[0];
    deviceId_t      deviceId;

    /* Mark this command as initiated by FSCI */
    bFsciBleAttCmdInitiatedByFsci = TRUE;

    /* Verify if the command is Mode Select */
    if(gBleAttModeSelectOpCode_c == pClientPacket->structured.header.opCode)
    {
        /* Get the new FSCI for ATT status (enabled or disabled) */
        fsciBleGetBoolValueFromBuffer(bFsciBleAttEnabled, pBuffer);
        /* Return status */
        fsciBleAttStatusMonitor(gBleSuccess_c);
    }
    else
    {
        /* Verify if FSCI is enabled for this layer */
        if(TRUE == bFsciBleAttEnabled)
        {
            /* All ATT functions, except Att_RegisterOpcodeCallback, have
            deviceId as first parameter */
            if(gBleAttCmdRegisterOpcodeCallbackOpCode_c != pClientPacket->structured.header.opCode)
            {
                /* Get deviceId */
                fsciBleGetDeviceIdFromBuffer(&deviceId, &pBuffer);
            }

            /* Select the ATT function to be called (using the FSCI opcode) */
            switch(pClientPacket->structured.header.opCode)
            {
                case gBleAttCmdInitOpCode_c:
                    {
                        fsciBleAttCallApiFunction(Att_Init());
                    }
                    break;

                case gBleAttCmdNotifyConnectionOpCode_c:
                    {
                        fsciBleAttCallApiFunction(Att_NotifyConnection(deviceId));
                    }
                    break;

                case gBleAttCmdNotifyDisconnectionOpCode_c:
                    {
                        fsciBleAttCallApiFunction(Att_NotifyDisconnection(deviceId));
                    }
                    break;

                case gBleAttCmdSetMtuOpCode_c:
                    {
                        uint16_t mtu;

                        /* Get the new MTU value from the received buffer */
                        fsciBleGetUint16ValueFromBuffer(mtu, pBuffer);

                        fsciBleAttCallApiFunction(Att_SetMtu(deviceId, mtu));
                    }
                    break;

                case gBleAttCmdGetMtuOpCode_c:
                    {
                        uint16_t mtu;

                        fsciBleAttCallApiFunction(Att_GetMtu(deviceId, &mtu));
                    }
                    break;


                case gBleAttCmdServerSendErrorResponseOpCode_c:
                    {
                        attErrorResponseParams_t attErrorResponseParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetErrorResponseParamsFromBuffer(&attErrorResponseParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttServer_SendErrorResponse(deviceId, &attErrorResponseParams));
                    }
                    break;

                case gBleAttCmdClientSendExchangeMtuRequestOpCode_c:
                    {
                        attExchangeMtuRequestParams_t attExchangeMtuRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetExchangeMtuRequestParamsFromBuffer(&attExchangeMtuRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendExchangeMtuRequest(deviceId, &attExchangeMtuRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendExchangeMtuResponseOpCode_c:
                    {
                        attExchangeMtuResponseParams_t attExchangeMtuResponseParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetExchangeMtuResponseParamsFromBuffer(&attExchangeMtuResponseParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttServer_SendExchangeMtuResponse(deviceId, &attExchangeMtuResponseParams));
                    }
                    break;

                case gBleAttCmdClientSendFindInformationRequestOpCode_c:
                    {
                        attFindInformationRequestParams_t attFindInformationRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetFindInformationRequestParamsFromBuffer(&attFindInformationRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendFindInformationRequest(deviceId, &attFindInformationRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendFindInformationResponseOpCode_c:
                    {
                        attFindInformationResponseParams_t* pAttFindInformationResponseParams;
                        pAttFindInformationResponseParams = (attFindInformationResponseParams_t*)MEM_BufferAlloc(sizeof(attFindInformationResponseParams_t));

                        if( NULL != pAttFindInformationResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetFindInfoResponseParamsFromBuffer(pAttFindInformationResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendFindInformationResponse(deviceId, pAttFindInformationResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendFindByTypeValueRequestOpCode_c:
                    {
                        attFindByTypeValueRequestParams_t* pAttFindByTypeValueRequestParams;
                        pAttFindByTypeValueRequestParams = (attFindByTypeValueRequestParams_t*)MEM_BufferAlloc(sizeof(attFindByTypeValueRequestParams_t));

                        if( NULL != pAttFindByTypeValueRequestParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetFindByTypeValueRequestParamsFromBuffer(pAttFindByTypeValueRequestParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendFindByTypeValueRequest(deviceId, pAttFindByTypeValueRequestParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdServerSendFindByTypeValueResponseOpCode_c:
                    {
                        attFindByTypeValueResponseParams_t* pAttFindByTypeValueResponseParams;
                        pAttFindByTypeValueResponseParams = (attFindByTypeValueResponseParams_t*)MEM_BufferAlloc(sizeof(attFindByTypeValueResponseParams_t));

                        if( NULL != pAttFindByTypeValueResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetFindByTypeValueResponseParamsFromBuffer(pAttFindByTypeValueResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendFindByTypeValueResponse(deviceId, pAttFindByTypeValueResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendReadByTypeRequestOpCode_c:
                    {
                        attReadByTypeRequestParams_t attReadByTypeRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetRdByTypeReqParamsFromBuffer(&attReadByTypeRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendReadByTypeRequest(deviceId, &attReadByTypeRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendReadByTypeResponseOpCode_c:
                    {
                        attReadByTypeResponseParams_t* pAttReadByTypeResponseParams;
                        pAttReadByTypeResponseParams = (attReadByTypeResponseParams_t*)MEM_BufferAlloc(sizeof(attReadByTypeResponseParams_t));

                        if( NULL != pAttReadByTypeResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadByTypeResponseParamsFromBuffer(pAttReadByTypeResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendReadByTypeResponse(deviceId, pAttReadByTypeResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendReadRequestOpCode_c:
                    {
                        attReadRequestParams_t attReadRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetReadRequestParamsFromBuffer(&attReadRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendReadRequest(deviceId, &attReadRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendReadResponseOpCode_c:
                    {
                        attReadResponseParams_t* pAttReadResponseParams;
                        pAttReadResponseParams = (attReadResponseParams_t*)MEM_BufferAlloc(sizeof(attReadResponseParams_t));

                        if( NULL != pAttReadResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadResponseParamsFromBuffer(pAttReadResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendReadResponse(deviceId, pAttReadResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendReadBlobRequestOpCode_c:
                    {
                        attReadBlobRequestParams_t attReadBlobRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetReadBlobRequestParamsFromBuffer(&attReadBlobRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendReadBlobRequest(deviceId, &attReadBlobRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendReadBlobResponseOpCode_c:
                    {
                        attReadBlobResponseParams_t* pAttReadBlobResponseParams;
                        pAttReadBlobResponseParams = (attReadBlobResponseParams_t*)MEM_BufferAlloc(sizeof(attReadBlobResponseParams_t));

                        if( NULL != pAttReadBlobResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadBlobResponseParamsFromBuffer(pAttReadBlobResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendReadBlobResponse(deviceId, pAttReadBlobResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendReadMultipleRequestOpCode_c:
                    {
                        attReadMultipleRequestParams_t* pAttReadMultipleRequestParams;
                        pAttReadMultipleRequestParams = (attReadMultipleRequestParams_t*)MEM_BufferAlloc(sizeof(attReadMultipleRequestParams_t));

                        if( NULL != pAttReadMultipleRequestParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadMultipleRequestParamsFromBuffer(pAttReadMultipleRequestParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendReadMultipleRequest(deviceId, pAttReadMultipleRequestParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdServerSendReadMultipleResponseOpCode_c:
                    {
                        attReadMultipleResponseParams_t* pAttReadMultipleResponseParams;
                        pAttReadMultipleResponseParams = (attReadMultipleResponseParams_t*)MEM_BufferAlloc(sizeof(attReadMultipleResponseParams_t));

                        if( NULL != pAttReadMultipleResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadMultipleResponseParamsFromBuffer(pAttReadMultipleResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendReadMultipleResponse(deviceId, pAttReadMultipleResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendReadByGroupTypeRequestOpCode_c:
                    {
                        attReadByGroupTypeRequestParams_t attReadByGroupTypeRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetReadByGroupTypeRequestParamsFromBuffer(&attReadByGroupTypeRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendReadByGroupTypeRequest(deviceId, &attReadByGroupTypeRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendReadByGroupTypeResponseOpCode_c:
                    {
                        attReadByGroupTypeResponseParams_t* pAttReadByGroupTypeResponseParams;
                        pAttReadByGroupTypeResponseParams = (attReadByGroupTypeResponseParams_t*)MEM_BufferAlloc(sizeof(attReadByGroupTypeResponseParams_t));

                        if( NULL != pAttReadByGroupTypeResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetReadByGroupTypeResponseParamsFromBuffer(pAttReadByGroupTypeResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendReadByGroupTypeResponse(deviceId, pAttReadByGroupTypeResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendWriteRequestOpCode_c:
                    {
                        attVarWriteRequestAndCommandParams_t* pAttWriteRequestAndCommandParams;
                        pAttWriteRequestAndCommandParams = (attVarWriteRequestAndCommandParams_t*)MEM_BufferAlloc(sizeof(attVarWriteRequestAndCommandParams_t) - 1U + gAttMaxWriteDataSize_d(gAttMaxMtu_c));

                        if( NULL != pAttWriteRequestAndCommandParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetWriteRequestAndCommandParamsFromBuffer((attWriteRequestAndCommandParams_t*)pAttWriteRequestAndCommandParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendWriteRequest(deviceId, pAttWriteRequestAndCommandParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdServerSendWriteResponseOpCode_c:
                    {
                        fsciBleAttCallApiFunction(AttServer_SendWriteResponse(deviceId));
                    }
                    break;

                case gBleAttCmdClientSendWriteCommandOpCode_c:
                    {
                        attVarWriteRequestAndCommandParams_t* pAttWriteRequestAndCommandParams;
                        pAttWriteRequestAndCommandParams = (attVarWriteRequestAndCommandParams_t*)MEM_BufferAlloc(sizeof(attVarWriteRequestAndCommandParams_t) - 1U + gAttMaxWriteDataSize_d(gAttMaxMtu_c));

                        if( NULL != pAttWriteRequestAndCommandParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetWriteRequestAndCommandParamsFromBuffer((attWriteRequestAndCommandParams_t*)pAttWriteRequestAndCommandParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendWriteCommand(deviceId, pAttWriteRequestAndCommandParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendSignedWriteCommandOpCode_c:
                    {
                        attSignedWriteCommandParams_t* pAttSignedWriteCommandParams;
                        pAttSignedWriteCommandParams = (attSignedWriteCommandParams_t*)MEM_BufferAlloc(sizeof(attSignedWriteCommandParams_t));

                        if( NULL != pAttSignedWriteCommandParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetSignedWriteCommandParamsFromBuffer(pAttSignedWriteCommandParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendSignedWriteCommand(deviceId, pAttSignedWriteCommandParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendPrepareWriteRequestOpCode_c:
                    {
                        attPrepareWriteRequestResponseParams_t* pAttPrepareWriteRequestResponseParams;
                        pAttPrepareWriteRequestResponseParams = (attPrepareWriteRequestResponseParams_t*)MEM_BufferAlloc(sizeof(attPrepareWriteRequestResponseParams_t));

                        if( NULL != pAttPrepareWriteRequestResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(pAttPrepareWriteRequestResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttClient_SendPrepareWriteRequest(deviceId, pAttPrepareWriteRequestResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdServerSendPrepareWriteResponseOpCode_c:
                    {
                        attPrepareWriteRequestResponseParams_t* pAttPrepareWriteRequestResponseParams;
                        pAttPrepareWriteRequestResponseParams = (attPrepareWriteRequestResponseParams_t*)MEM_BufferAlloc(sizeof(attPrepareWriteRequestResponseParams_t));

                        if( NULL != pAttPrepareWriteRequestResponseParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(pAttPrepareWriteRequestResponseParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendPrepareWriteResponse(deviceId, pAttPrepareWriteRequestResponseParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendExecuteWriteRequestOpCode_c:
                    {
                        attExecuteWriteRequestParams_t attExecuteWriteRequestParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleAttGetExecuteWriteRequestParamsFromBuffer(&attExecuteWriteRequestParams, &pBuffer);

                        fsciBleAttCallApiFunction(AttClient_SendExecuteWriteRequest(deviceId, &attExecuteWriteRequestParams));
                    }
                    break;

                case gBleAttCmdServerSendExecuteWriteResponseOpCode_c:
                    {
                        fsciBleAttCallApiFunction(AttServer_SendExecuteWriteResponse(deviceId));
                    }
                    break;

                case gBleAttCmdServerSendHandleValueNotificationOpCode_c:
                    {
                        attVarHandleValueNotificationIndicationParams_t* pAttHandleValueNotificationIndicationParams;
                        pAttHandleValueNotificationIndicationParams = (attVarHandleValueNotificationIndicationParams_t*)MEM_BufferAlloc(sizeof(attVarHandleValueNotificationIndicationParams_t) + gAttMaxWriteDataSize_d(gAttMaxMtu_c) - 1U);

                        if( NULL != pAttHandleValueNotificationIndicationParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetHandleValueNotificationIndicationParamsFromBuffer(pAttHandleValueNotificationIndicationParams, &pBuffer);
                            fsciBleAttCallApiFunction(AttServer_SendHandleValueNotification(deviceId, pAttHandleValueNotificationIndicationParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdServerSendHandleValueIndicationOpCode_c:
                    {
                        attVarHandleValueNotificationIndicationParams_t* pAttHandleValueNotificationIndicationParams;
                        pAttHandleValueNotificationIndicationParams = (attVarHandleValueNotificationIndicationParams_t*)MEM_BufferAlloc(sizeof(attVarHandleValueNotificationIndicationParams_t) + gAttMaxWriteDataSize_d(gAttMaxMtu_c) - 1U);

                        if( NULL != pAttHandleValueNotificationIndicationParams )
                        {
                            /* Get the function parameters from the received buffer */
                            fsciBleAttGetHandleValueNotificationIndicationParamsFromBuffer(pAttHandleValueNotificationIndicationParams, &pBuffer);

                            fsciBleAttCallApiFunction(AttServer_SendHandleValueIndication(deviceId, pAttHandleValueNotificationIndicationParams));
                        }
                        else
                        {
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                    }
                    break;

                case gBleAttCmdClientSendHandleValueConfirmationOpCode_c:
                    {
                        fsciBleAttCallApiFunction(AttClient_SendHandleValueConfirmation(deviceId));
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
    bFsciBleAttCmdInitiatedByFsci = FALSE;
}


void fsciBleAttStatusMonitor(bleResult_t result)
{
    /* If ATT is disabled the status must be not monitored */
    if(TRUE == bFsciBleAttEnabled)
    {
        /* Send status over UART */
        fsciBleStatusMonitor(gFsciBleAttOpcodeGroup_c, gBleAttStatusOpCode_c, result);
    }
}


void fsciBleAttNoParamCmdMonitor(fsciBleAttOpCode_t opCode)
{
    /* If ATT is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleAttEnabled) ||
       (TRUE == bFsciBleAttCmdInitiatedByFsci))
    {
        return;
    }

    /* Call the generic FSCI BLE monitor for commands or events that have no parameters */
    fsciBleNoParamCmdOrEvtMonitor(gFsciBleAttOpcodeGroup_c, opCode);
}


void fsciBleAttGenericCmdMonitor(fsciBleAttOpCode_t cmdOpCode, deviceId_t deviceId, const void* pParams)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    uint16_t                    dataSize = fsciBleGetDeviceIdBufferSize(&deviceId);

    /* If ATT is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleAttEnabled) ||
       (TRUE == bFsciBleAttCmdInitiatedByFsci))
    {
        return;
    }

    /* Compute the size of the payload that will be sent over UART */
    switch(cmdOpCode)
    {
        case gBleAttCmdNotifyConnectionOpCode_c:
        case gBleAttCmdNotifyDisconnectionOpCode_c:
        case gBleAttCmdGetMtuOpCode_c:
        case gBleAttCmdServerSendWriteResponseOpCode_c:
        case gBleAttCmdServerSendExecuteWriteResponseOpCode_c:
        case gBleAttCmdClientSendHandleValueConfirmationOpCode_c:
            {
            }
            break;

        case gBleAttCmdSetMtuOpCode_c:
            {
                dataSize += sizeof(uint16_t);
            }
            break;

        case gBleAttCmdServerSendErrorResponseOpCode_c:
            {
                dataSize += fsciBleAttGetErrorResponseParamsBufferSize((attErrorResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendExchangeMtuRequestOpCode_c:
            {
                dataSize += fsciBleAttGetExchangeMtuRequestParamsBufferSize((attExchangeMtuRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendExchangeMtuResponseOpCode_c:
            {
                dataSize += fsciBleAttGetExchangeMtuResponseParamsBufferSize((attExchangeMtuResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendFindInformationRequestOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationRequestParamsBufferSize((attFindInformationRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendFindInformationResponseOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationResponseParamsBufferSize((attFindInformationResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendFindByTypeValueRequestOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueRequestParamsBufferSize((attFindByTypeValueRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendFindByTypeValueResponseOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueResponseParamsBufferSize((attFindByTypeValueResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendReadByTypeRequestOpCode_c:
            {
                dataSize += fsciBleAttGetRdByTypeReqParamsBuffSize((attReadByTypeRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendReadByTypeResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadByTypeResponseParamsBufferSize((attReadByTypeResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendReadRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadRequestParamsBufferSize((attReadRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendReadResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadResponseParamsBufferSize((attReadResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendReadBlobRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobRequestParamsBufferSize((attReadBlobRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendReadBlobResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobResponseParamsBufferSize((attReadBlobResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendReadMultipleRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleRequestParamsBufferSize((attReadMultipleRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendReadMultipleResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleResponseParamsBufferSize((attReadMultipleResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendReadByGroupTypeRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeRequestParamsBufferSize((attReadByGroupTypeRequestParams_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendReadByGroupTypeResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeResponseParamsBufferSize((attReadByGroupTypeResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendWriteRequestOpCode_c:
        case gBleAttCmdClientSendWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetWriteRequestAndCommandParamsBufferSize((attWriteRequestAndCommandParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendSignedWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetSignedWriteCommandParamsBufferSize((attSignedWriteCommandParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendPrepareWriteRequestOpCode_c:
        case gBleAttCmdServerSendPrepareWriteResponseOpCode_c:
            {
                dataSize += fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize((attPrepareWriteRequestResponseParams_t*)pParams);
            }
            break;

        case gBleAttCmdClientSendExecuteWriteRequestOpCode_c:
            {
                dataSize += fsciBleAttGetExecuteWriteRequestParamsBufferSize((attExecuteWriteRequest_t*)pParams);
            }
            break;

        case gBleAttCmdServerSendHandleValueNotificationOpCode_c:
        case gBleAttCmdServerSendHandleValueIndicationOpCode_c:
            {
                dataSize += fsciBleAttGetHandleValueNotificationIndicationParamsBufferSize((attHandleValueNotificationIndicationParams_t*)pParams);
            }
            break;

        default:
            {
                /* Unknown FSCI opcode */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }

    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleAttAllocFsciPacket(cmdOpCode, dataSize);

    if(NULL == pClientPacket)
    {
        return;
    }

    pBuffer = &pClientPacket->payload[0];

    /* Set command parameters in the buffer */
    fsciBleGetBufferFromDeviceId(&deviceId, &pBuffer);

    switch(cmdOpCode)
    {
        case gBleAttCmdSetMtuOpCode_c:
            {
                fsciBleGetBufferFromUint16Value(*(uint16_t*)pParams, pBuffer);
            }
            break;

        case gBleAttCmdServerSendErrorResponseOpCode_c:
            {
                fsciBleAttGetBufferFromErrorResponseParams((attErrorResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendExchangeMtuRequestOpCode_c:
            {
                fsciBleAttGetBufferFromExchangeMtuRequestParams((attExchangeMtuRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendExchangeMtuResponseOpCode_c:
            {
                fsciBleAttGetBufferFromExchangeMtuResponseParams((attExchangeMtuResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendFindInformationRequestOpCode_c:
            {
                fsciBleAttGetBuffFromFindInfoRequestParams((attFindInformationRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendFindInformationResponseOpCode_c:
            {
                fsciBleAttGetBuffFromInfoResponseParams((attFindInformationResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendFindByTypeValueRequestOpCode_c:
            {
                fsciBleAttGetBufferFromFindByTypeValueRequestParams((attFindByTypeValueRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendFindByTypeValueResponseOpCode_c:
            {
                fsciBleAttGetBuffFromFindByTypeValResponseParams((attFindByTypeValueResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendReadByTypeRequestOpCode_c:
            {
                fsciBleAttGetBuffFromReadByTypeReqParams((attReadByTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendReadByTypeResponseOpCode_c:
            {
                fsciBleAttGetBuffFromRdByTypeRespParams((attReadByTypeResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendReadRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadRequestParams((attReadRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendReadResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadResponseParams((attReadResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendReadBlobRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobRequestParams((attReadBlobRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendReadBlobResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobResponseParams((attReadBlobResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendReadMultipleRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleRequestParams((attReadMultipleRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendReadMultipleResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleResponseParams((attReadMultipleResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendReadByGroupTypeRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeRequestParams((attReadByGroupTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendReadByGroupTypeResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeResponseParams((attReadByGroupTypeResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendWriteRequestOpCode_c:
        case gBleAttCmdClientSendWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromWriteRequestAndCommandParams((attWriteRequestAndCommandParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendSignedWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromSignedWriteCommandParams((attSignedWriteCommandParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendPrepareWriteRequestOpCode_c:
        case gBleAttCmdServerSendPrepareWriteResponseOpCode_c:
            {
                fsciBleAttGetBufferFromPrepareWriteRequestResponseParams((attPrepareWriteRequestResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdClientSendExecuteWriteRequestOpCode_c:
            {
                fsciBleAttGetBufferFromExecuteWriteRequestParams((attExecuteWriteRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttCmdServerSendHandleValueNotificationOpCode_c:
        case gBleAttCmdServerSendHandleValueIndicationOpCode_c:
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


void fsciBleAttGenericEvtMonitor(fsciBleAttOpCode_t evtOpCode, deviceId_t deviceId, const void* pParams)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    uint16_t                    dataSize = fsciBleGetDeviceIdBufferSize(&deviceId);

    /* If ATT is disabled, the event must be not monitored */
    if(FALSE == bFsciBleAttEnabled)
    {
        return;
    }

    /* Compute the size of the payload that will be sent over UART */
    switch(evtOpCode)
    {
        case gBleAttEvtIncomingServerWriteResponseOpCode_c:
        case gBleAttEvtIncomingServerExecuteWriteResponseOpCode_c:
        case gBleAttEvtIncomingClientHandleValueConfirmationOpCode_c:
        case gBleAttEvtTimeoutOpCode_c:
            {

            }
            break;

        case gBleAttEvtGetMtuOpCode_c:
            {
                dataSize += sizeof(uint16_t);
            }
            break;

        case gBleAttEvtIncomingServerErrorResponseOpCode_c:
            {
                dataSize += fsciBleAttGetErrorResponseParamsBufferSize((attErrorResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientExchangeMtuRequestOpCode_c:
            {
                dataSize += fsciBleAttGetExchangeMtuRequestParamsBufferSize((attExchangeMtuRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerExchangeMtuResponseOpCode_c:
            {
                dataSize += fsciBleAttGetExchangeMtuResponseParamsBufferSize((attExchangeMtuResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientFindInformationRequestOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationRequestParamsBufferSize((attFindInformationRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerFindInformationResponseOpCode_c:
            {
                dataSize += fsciBleAttGetFindInformationResponseParamsBufferSize((attFindInformationResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientFindByTypeValueRequestOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueRequestParamsBufferSize((attFindByTypeValueRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerFindByTypeValueResponseOpCode_c:
            {
                dataSize += fsciBleAttGetFindByTypeValueResponseParamsBufferSize((attFindByTypeValueResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientReadByTypeRequestOpCode_c:
            {
                dataSize += fsciBleAttGetRdByTypeReqParamsBuffSize((attReadByTypeRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerReadByTypeResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadByTypeResponseParamsBufferSize((attReadByTypeResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientReadRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadRequestParamsBufferSize((attReadRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerReadResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadResponseParamsBufferSize((attReadResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientReadBlobRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobRequestParamsBufferSize((attReadBlobRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerReadBlobResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadBlobResponseParamsBufferSize((attReadBlobResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientReadMultipleRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleRequestParamsBufferSize((attReadMultipleRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerReadMultipleResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadMultipleResponseParamsBufferSize((attReadMultipleResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientReadByGroupTypeRequestOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeRequestParamsBufferSize((attReadByGroupTypeRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerReadByGroupTypeResponseOpCode_c:
            {
                dataSize += fsciBleAttGetReadByGroupTypeResponseParamsBufferSize((attReadByGroupTypeResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientWriteRequestOpCode_c:
        case gBleAttEvtIncomingClientWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetWriteRequestAndCommandParamsBufferSize((attWriteRequestAndCommandParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientSignedWriteCommandOpCode_c:
            {
                dataSize += fsciBleAttGetSignedWriteCommandParamsBufferSize((attSignedWriteCommandParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientPrepareWriteRequestOpCode_c:
        case gBleAttEvtIncomingServerPrepareWriteResponseOpCode_c:
            {
                dataSize += fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize((attPrepareWriteRequestResponseParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingClientExecuteWriteRequestOpCode_c:
            {
                dataSize += fsciBleAttGetExecuteWriteRequestParamsBufferSize((attExecuteWriteRequestParams_t*)pParams);
            }
            break;

        case gBleAttEvtIncomingServerHandleValueNotificationOpCode_c:
        case gBleAttEvtIncomingServerHandleValueIndicationOpCode_c:
            {
                dataSize += fsciBleAttGetHandleValueNotificationIndicationParamsBufferSize((attHandleValueNotificationIndicationParams_t*)pParams);
            }
            break;

        case gBleAttEvtUnsupportedOpcodeOpCode_c:
        case gBleAttEvtInvalidPduReceivedOpCode_c:
            {
                dataSize += sizeof(uint8_t);
            }
            break;

        default:
            {
                /* Unknown FSCI opcode */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }

    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleAttAllocFsciPacket(evtOpCode, dataSize);

    if(NULL == pClientPacket)
    {
        return;
    }

    pBuffer = &pClientPacket->payload[0];

    /* Set event parameters in the buffer */
    fsciBleGetBufferFromDeviceId(&deviceId, &pBuffer);

    switch(evtOpCode)
    {
        case gBleAttEvtGetMtuOpCode_c:
            {
                fsciBleGetBufferFromUint16Value(*(uint16_t*)pParams, pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerErrorResponseOpCode_c:
            {
                fsciBleAttGetBufferFromErrorResponseParams((attErrorResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientExchangeMtuRequestOpCode_c:
            {
                fsciBleAttGetBufferFromExchangeMtuRequestParams((attExchangeMtuRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerExchangeMtuResponseOpCode_c:
            {
                fsciBleAttGetBufferFromExchangeMtuResponseParams((attExchangeMtuResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientFindInformationRequestOpCode_c:
            {
                fsciBleAttGetBuffFromFindInfoRequestParams((attFindInformationRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerFindInformationResponseOpCode_c:
            {
                fsciBleAttGetBuffFromInfoResponseParams((attFindInformationResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientFindByTypeValueRequestOpCode_c:
            {
                fsciBleAttGetBufferFromFindByTypeValueRequestParams((attFindByTypeValueRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerFindByTypeValueResponseOpCode_c:
            {
                fsciBleAttGetBuffFromFindByTypeValResponseParams((attFindByTypeValueResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientReadByTypeRequestOpCode_c:
            {
                fsciBleAttGetBuffFromReadByTypeReqParams((attReadByTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerReadByTypeResponseOpCode_c:
            {
                fsciBleAttGetBuffFromRdByTypeRespParams((attReadByTypeResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientReadRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadRequestParams((attReadRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerReadResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadResponseParams((attReadResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientReadBlobRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobRequestParams((attReadBlobRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerReadBlobResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadBlobResponseParams((attReadBlobResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientReadMultipleRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleRequestParams((attReadMultipleRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerReadMultipleResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadMultipleResponseParams((attReadMultipleResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientReadByGroupTypeRequestOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeRequestParams((attReadByGroupTypeRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerReadByGroupTypeResponseOpCode_c:
            {
                fsciBleAttGetBufferFromReadByGroupTypeResponseParams((attReadByGroupTypeResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientWriteRequestOpCode_c:
        case gBleAttEvtIncomingClientWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromWriteRequestAndCommandParams((attWriteRequestAndCommandParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientSignedWriteCommandOpCode_c:
            {
                fsciBleAttGetBufferFromSignedWriteCommandParams((attSignedWriteCommandParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientPrepareWriteRequestOpCode_c:
        case gBleAttEvtIncomingServerPrepareWriteResponseOpCode_c:
            {
                fsciBleAttGetBufferFromPrepareWriteRequestResponseParams((attPrepareWriteRequestResponseParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingClientExecuteWriteRequestOpCode_c:
            {
                fsciBleAttGetBufferFromExecuteWriteRequestParams((attExecuteWriteRequestParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtIncomingServerHandleValueNotificationOpCode_c:
        case gBleAttEvtIncomingServerHandleValueIndicationOpCode_c:
            {
                fsciBleAttGetBufferFromHandleValueNotificationIndicationParams((attHandleValueNotificationIndicationParams_t*)pParams, &pBuffer);
            }
            break;

        case gBleAttEvtUnsupportedOpcodeOpCode_c:
        case gBleAttEvtInvalidPduReceivedOpCode_c:
            {
                fsciBleGetBufferFromUint8Value(*(uint8_t*)pParams, pBuffer);
            }
            break;

        default:
            break;
    }

    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(pClientPacket, fsciBleInterfaceId);
}

#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c && gFsciBleSmLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
