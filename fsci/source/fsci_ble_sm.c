/*! *********************************************************************************
* \addtogroup FSCI_BLE
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
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

#include "fsci_ble_sm.h"


#if gFsciIncluded_c && gFsciBleSmLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    #define fsciBleSmCallApiFunction(apiFunction)           (void)apiFunction
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* External memory declarations
*************************************************************************************
************************************************************************************/
#if (gSmTestHarnessEnabled_d == 1)
    extern smGenerateNewEcdhPkSkPairReqType_t gSmTestHarnessPublicKeyType;
#endif

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    /* Indicates if FSCI for SM is enabled or not */
    static bool_t bFsciBleSmEnabled             = FALSE;

    /* Indicates if the command was initiated by FSCI (to be not monitored) */
    static bool_t bFsciBleSmCmdInitiatedByFsci  = FALSE;
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d
    static bleResult_t fsciBleSmUserEventCallback(deviceId_t sourceDevId, bleSmEvent_t eventType, uint16_t eventLength, void* pEventPayload);
#endif /* gFsciBleTest_d */

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

#if gFsciBleTest_d

void fsciBleSmHandler(void* pData, void* param, uint32_t fsciBleInterfaceId)
{
    clientPacket_t* pClientPacket   = (clientPacket_t*)pData;
    uint8_t*        pBuffer         = &pClientPacket->structured.payload[0];

    /* Mark this command as initiated by FSCI */
    bFsciBleSmCmdInitiatedByFsci = TRUE;

    /* Verify if the command is Mode Select */
    if(gBleSmModeSelectOpCode_c == pClientPacket->structured.header.opCode)
    {
        fsciBleGetBoolValueFromBuffer(bFsciBleSmEnabled, pBuffer);
        /* Return status */
        fsciBleSmStatusMonitor(gBleSuccess_c);
    }
    else
    {
        /* Verify if FSCI is enabled for this layer */
        if(TRUE == bFsciBleSmEnabled)
        {
            /* Select the SM function to be called (using the FSCI opcode) */
            switch(pClientPacket->structured.header.opCode)
            {
                case gBleSmCmdInitOpCode_c:
                    {
                        fsciBleSmCallApiFunction(Sm_Init(fsciBleSmUserEventCallback));
                    }
                    break;

                case gBleSmCmdRegisterUserCallbackOpCode_c:
                    {
                        fsciBleSmCallApiFunction(Sm_RegisterUserCallback(fsciBleSmUserEventCallback));
                    }
                    break;

                case gBleSmCmdInitiatorStartPairingOpCode_c:
                    {
                        deviceId_t          destDevId;
                        smPairingParams_t   pairingParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetPairingParamsFromBuffer(&pairingParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_InitiatorStartPairing(destDevId, &pairingParams));
                    }
                    break;

                case gBleSmCmdSendSecurityRequestOpCode_c:
                    {
                        deviceId_t              destDevId;
                        smSecurityReqParams_t   securityReqParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetSecurityReqParamsFromBuffer(&securityReqParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_SendSecurityRequest(destDevId, &securityReqParams));
                    }
                    break;

                case gBleSmCmdTerminatePairingOpCode_c:
                    {
                        deviceId_t                  destDevId;
                        smTerminatePairingParams_t  terminatePairingParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetTerminatePairingParamsFromBuffer(&terminatePairingParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_TerminatePairing(destDevId, &terminatePairingParams));
                    }
                    break;

                case gBleSmCmdPairingRequestReplyOpCode_c:
                    {
                        deviceId_t          destDevId;
                        smPairingParams_t   pairingParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetPairingParamsFromBuffer(&pairingParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_PairingRequestReply(destDevId, &pairingParams));
                    }
                    break;

                case gBleSmCmdPasskeyRequestReplyOpCode_c:
                    {
                        deviceId_t                  destDevId;
                        smPasskeyReqReplyParams_t   passkeyReqReplyParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetPasskeyReqReplParamsFromBuffer(&passkeyReqReplyParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_PasskeyRequestReply(destDevId, &passkeyReqReplyParams));
                    }
                    break;

                case gBleSmCmdPairingKeysetRequestReplyOpCode_c:
                    {
                        deviceId_t                          destDevId;
                        smPairingKeysetRequestReplyParams_t pairingKeysetRequestReplyParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetPairingKeysetRequestReplyParamsFromBuffer(&pairingKeysetRequestReplyParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_PairingKeysetRequestReply(destDevId, &pairingKeysetRequestReplyParams));
                    }
                    break;

                case gBleSmCmdLlStartEncryptionOpCode_c:
                    {
                        deviceId_t                  destDevId;
                        smLlStartEncryptionParams_t llStartEncryptionParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetLlStartEncryptionParamsFromBuffer(&llStartEncryptionParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_LlStartEncryption(destDevId, &llStartEncryptionParams));
                    }
                    break;

                case gBleSmCmdLlLtkRequestReplyOpCode_c:
                    {
                        deviceId_t                  destDevId;
                        smLlLtkRequestReplyParams_t llLtkRequestReplyParams;

                        /* Get the function parameters from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        fsciBleSmGetLlLtkRequestReplyParamsFromBuffer(&llLtkRequestReplyParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_LlLtkRequestReply(destDevId, &llLtkRequestReplyParams));
                    }
                    break;

                case gBleSmCmdLlLtkRequestNegativeReplyOpCode_c:
                    {
                        deviceId_t destDevId;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_LlLtkRequestNegativeReply(destDevId));
                    }
                    break;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
                case gBleSmCmdLlEncryptReqOpCode_c:
                    {
                        smLlEncryptReqParams_t llEncryptReqParams;

                        /* Get llEncryptReqParams parameter from the received buffer */
                        fsciBleSmGetLlEncryptReqParamsFromBuffer(&llEncryptReqParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_LlEncryptRequest(&llEncryptReqParams));
                    }
                    break;
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
                case gBleSmCmdLlRandReqOpCode_c:
                    {
                        fsciBleSmCallApiFunction(Sm_LlRandRequest());
                    }
                    break;
#endif
                case gBleSmCmdTbCreateRandomDeviceAddrReqOpCode_c:
                    {
                        smTbCreateRandomDeviceAddrReqParams_t* pTbCreateRandomDeviceAddrReqParams;

                        /* Allocate memory buffer */
                        pTbCreateRandomDeviceAddrReqParams = fsciBleSmAllocTbCreateRandomDeviceAddrReqParamsForBuffer(pBuffer);

                        if(NULL == pTbCreateRandomDeviceAddrReqParams)
                        {
                            /* No memory - the SM command can not be executed */
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                        else
                        {
                            /* Get pTbCreateRandomDeviceAddrReqParams parameter from the received buffer */
                            fsciBleSmGetTbCreateRndmDevAddrReqParamsFromBuffer(pTbCreateRandomDeviceAddrReqParams, &pBuffer);

                            fsciBleSmCallApiFunction(Sm_TbCreateRandomDeviceAddressRequest(pTbCreateRandomDeviceAddrReqParams));

                            /* Free the allocated memory buffer */
                            fsciBleSmFreeTbCreateRandomDeviceAddrReqParams(pTbCreateRandomDeviceAddrReqParams);
                        }
                    }
                    break;

                case gBleSmCmdTbCheckResolvablePrivateAddrReqOpCode_c:
                    {
                        smTbCheckResolvablePrivateAddrReqParams_t tbCheckResolvablePrivateAddrReqParams;

                        /* Get tbCheckResolvablePrivateAddrReqParams parameter from the received buffer */
                        fsciBleSmGetTbCheckResolvablePrivateAddrReqParamsFromBuffer(&tbCheckResolvablePrivateAddrReqParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_TbCheckResolvablePrivateAddressRequest(&tbCheckResolvablePrivateAddrReqParams));
                    }
                    break;

                case gBleSmCmdTbSignDataReqOpCode_c:
                    {
                        smTbSignDataReqParams_t* pTbSignDataReqParams;

                        /* Allocate memory buffer */
                        pTbSignDataReqParams = fsciBleSmAllocTbSignDataReqParamsForBuffer(pBuffer);

                        if(NULL == pTbSignDataReqParams)
                        {
                            /* No memory - the SM command can not be executed */
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                        else
                        {
                            /* Get pTbSignDataReqParams parameter from the received buffer */
                            fsciBleSmGetTbSignDataReqParamsFromBuffer(pTbSignDataReqParams, &pBuffer);

                            fsciBleSmCallApiFunction(Sm_TbSignDataRequest(pTbSignDataReqParams));

                            /* Free the allocated memory buffer */
                            fsciBleSmFreeTbSignDataReqParams(pTbSignDataReqParams);
                        }
                    }
                    break;

                case gBleSmCmdTbVerifyDataSignatureReqOpCode_c:
                    {
                        smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams;

                        /* Allocate memory buffer */
                        pTbVerifyDataSignatureReqParams = fsciBleSmAllocTbVerifyDataSignatureReqParamsForBuffer(pBuffer);

                        if(NULL == pTbVerifyDataSignatureReqParams)
                        {
                            /* No memory - the SM command can not be executed */
                            fsciBleError(gFsciOutOfMessages_c, fsciBleInterfaceId);
                        }
                        else
                        {
                            /* Get pTbVerifyDataSignatureReqParams parameter from the received buffer */
                            fsciBleSmGetTbVerifyDataSignatureReqParamsFromBuffer(pTbVerifyDataSignatureReqParams, &pBuffer);

                            fsciBleSmCallApiFunction(Sm_TbVerifyDataSignatureRequest(pTbVerifyDataSignatureReqParams));

                            /* Free the allocated memory buffer */
                            fsciBleSmFreeTbVerifyDataSignatureReqParams(pTbVerifyDataSignatureReqParams);
                        }
                    }
                    break;

                case gBleSmCmdDevConnectNotificationOpCode_c:
                    {
                        deviceId_t destDevId;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_DeviceConnectNotification(destDevId));
                    }
                    break;

                case gBleSmCmdDevDisconnectNotificationOpCode_c:
                    {
                        deviceId_t destDevId;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_DeviceDisconnectNotification(destDevId));
                    }
                    break;

                case gBleSmCmdSetDefaultPasskeyOpCode_c:
                    {
                        smSetDefaultPasskeyParams_t setDefaultPasskeyParams;

                        /* Get setDefaultPasskeyParams parameter from the received buffer */
                        fsciBleSmGetSetDefaultPasskeyParamsFromBuffer(&setDefaultPasskeyParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_SetDefaultPasskey(&setDefaultPasskeyParams));
                    }
                    break;

                case gBleSmCmdSetOobMitmProtectionOpCode_c:
                    {
                        smSetOobMitmProtectionParams_t setOobMitmProtectionParams;

                        /* Get setOobMitmProtectionParams parameter from the received buffer */
                        fsciBleSmGetSetOobMitmProtectionParamsFromBuffer(&setOobMitmProtectionParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_SetOobMitmProtection(&setOobMitmProtectionParams));
                    }
                    break;

                case gBleSmCmdSendKeypressNotificationOpCode_c:
                    {
                        deviceId_t                     destDevId;
                        smKeypressNotificationParams_t sendKeypressNotificationParams;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        /* Get sendKeypressNotificationParams parameter from the received buffer */
                        fsciBleSmGetSendKeypressNotificationParamsFromBuffer(&sendKeypressNotificationParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_SendKeypressNotification(destDevId, &sendKeypressNotificationParams));
                    }
                    break;

                case gBleSmCmdNcDisplayConfirmOpCode_c:
                    {
                        deviceId_t                 destDevId;
                        smNcDisplayConfirmParams_t ncDisplayConfirmParams;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        /* Get ncDisplayConfirmParams parameter from the received buffer */
                        fsciBleSmGetNcDisplayConfirmParamsFromBuffer(&ncDisplayConfirmParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_NcDisplayConfirm(destDevId, &ncDisplayConfirmParams));
                    }
                    break;

                case gBleSmCmdLeScOobDataRequestReplyOpCode_c:
                    {
                        deviceId_t            destDevId;
                        smLeScOobDataParams_t leScOobDataRequestReplyParams;

                        /* Get destDevId parameter from the received buffer */
                        fsciBleGetDeviceIdFromBuffer(&destDevId, &pBuffer);
                        /* Get leScOobDataRequestReplyParams parameter from the received buffer */
                        fsciBleSmGetLeScOobDataRequestReplyParamsFromBuffer(&leScOobDataRequestReplyParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_LeScOobDataRequestReply(destDevId, &leScOobDataRequestReplyParams));
                    }
                    break;

                case gBleSmCmdLocalLeScOobDataRequestOpCode_c:
                    {
                        fsciBleSmCallApiFunction(Sm_LocalLeScOobDataRequest());
                    }
                    break;

                case gBleSmCmdGenerateNewEcdhPkSkPairReqOpCode_c:
                    {
#if (gSmTestHarnessEnabled_d == 1)
                        if (pClientPacket->structured.header.len == sizeof(smGenerateNewEcdhPkSkPairReqType_t))
                        {
                            /* Get Public Key Type parameter from the received buffer */
                            fsciBleGetEnumValueFromBuffer(gSmTestHarnessPublicKeyType, pBuffer,
                                                          smGenerateNewEcdhPkSkPairReqType_t);
                        }
#endif
                        fsciBleSmCallApiFunction(Sm_GenerateNewEcdhPkSkPair());
                    }
                    break;

                case gBleSmCmdSetMinPairingSecurityPropertiesOpCode_c:
                    {
                        smSetMinPairingSecurityPropertiesParams_t setMinPairingSecurityPropertiesParams;

                        /* Get setOobMitmProtectionParams parameter from the received buffer */
                        fsciBleSmGetSetMinPairingSecurityPropertiesParamsFromBuffer(&setMinPairingSecurityPropertiesParams, &pBuffer);

                        fsciBleSmCallApiFunction(Sm_SetMinPairingSecurityProperties(&setMinPairingSecurityPropertiesParams));
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
    bFsciBleSmCmdInitiatedByFsci = FALSE;
}


void fsciBleSmStatusMonitor(bleResult_t result)
{
    /* If SM is disabled the status must be not monitored */
    if(TRUE == bFsciBleSmEnabled)
    {
        /* Send status over UART */
        fsciBleStatusMonitor(gFsciBleSmOpcodeGroup_c, gBleSmStatusOpCode_c, result);
    }
}


void fsciBleSmNoParamCmdMonitor(fsciBleSmOpCode_t opCode)
{
    /* If SM is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleSmEnabled) ||
       (TRUE == bFsciBleSmCmdInitiatedByFsci))
    {
        return;
    }

    /* Call the generic FSCI BLE monitor for commands or events that have no parameters */
    fsciBleNoParamCmdOrEvtMonitor(gFsciBleSmOpcodeGroup_c, opCode);
}


void fsciBleSmSendCmdCmdMonitor(deviceId_t destDevId, bleSmCommand_t commandCode, uint16_t commandDataLength, void* pCommandData)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    fsciBleSmOpCode_t           opCode;
    uint16_t                    dataSize;

    /* If SM is disabled or if the command was initiated by FSCI it must be not monitored */
    if((FALSE == bFsciBleSmEnabled) ||
       (TRUE == bFsciBleSmCmdInitiatedByFsci))
    {
        return;
    }

    /* Get the SM command code and the size of the payload that will be sent over UART */
    switch(commandCode)
    {
        case gBleSmCmdDHKeyComputedNotification_c:
            {
                opCode      = gBleSmCmdDHKeyComputedOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId);
            }
            break;

        case gBleSmCmdInitiatorStartPairing_c:
            {
                opCode      = gBleSmCmdInitiatorStartPairingOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetPairingParamsBufferSize((smPairingParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdSendSecurityRequest_c:
            {
                opCode      = gBleSmCmdSendSecurityRequestOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetSecurityReqParamsBufferSize((smSecurityReqParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdTerminatePairing_c:
            {
                opCode      = gBleSmCmdTerminatePairingOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetTerminatePairingParamsBufferSize((smTerminatePairingParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdPairingRequestReply_c:
            {
                opCode      = gBleSmCmdPairingRequestReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetPairingParamsBufferSize((smPairingParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdPasskeyRequestReply_c:
            {
                opCode      = gBleSmCmdPasskeyRequestReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetPasskeyReqReplyParamsBufferSize((smPasskeyReqReplyParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdPairingKeysetRequestReply_c:
            {
                opCode      = gBleSmCmdPairingKeysetRequestReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetPairingKeysetRequestReplyParamsBufferSize((smPairingKeysetRequestReplyParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdLlStartEncryption_c:
            {
                opCode      = gBleSmCmdLlStartEncryptionOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetLlStartEncryptionParamsBufferSize((smLlStartEncryptionParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdLlLtkRequestReply_c:
            {
                opCode      = gBleSmCmdLlLtkRequestReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetLlLtkRequestReplyParamsBufferSize((smLlLtkRequestReplyParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdLlLtkRequestNegativeReply_c:
            {
                opCode      = gBleSmCmdLlLtkRequestNegativeReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId);
            }
            break;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
        case gBleSmCmdLlEncryptReq_c:
            {
                opCode      = gBleSmCmdLlEncryptReqOpCode_c;
                dataSize    = fsciBleSmGetLlEncryptReqParamsBufferSize((smLlEncryptReqParams_t*)pCommandData);
            }
            break;
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
        case gBleSmCmdLlRandReq_c:
            {
                opCode      = gBleSmCmdLlRandReqOpCode_c;
                dataSize    = 0;
            }
            break;
#endif
        case gBleSmCmdTbCreateRandomDeviceAddrReq_c:
            {
                opCode      = gBleSmCmdTbCreateRandomDeviceAddrReqOpCode_c;
                dataSize    = fsciBleSmGetTbCreateRandomDeviceAddrReqParamsBufferSize((smTbCreateRandomDeviceAddrReqParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdTbCheckResolvablePrivateAddrReq_c:
            {
                opCode      = gBleSmCmdTbCheckResolvablePrivateAddrReqOpCode_c;
                dataSize    = fsciBleSmGetTbCheckResolvablePrivateAddrReqParamsBufferSize((smTbCheckResolvablePrivateAddrReqParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdTbSignDataReq_c:
            {
                opCode      = gBleSmCmdTbSignDataReqOpCode_c;
                dataSize    = fsciBleSmGetTbSignDataReqParamsBufferSize((smTbSignDataReqParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdTbVerifyDataSignatureReq_c:
            {
                opCode      = gBleSmCmdTbVerifyDataSignatureReqOpCode_c;
                dataSize    = fsciBleSmGetTbVerifyDataSignatureReqParamsBufferSize((smTbVerifyDataSignatureReqParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdDevConnectNotification_c:
            {
                opCode      = gBleSmCmdDevConnectNotificationOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId);
            }
            break;

        case gBleSmCmdDevDisconnectNotification_c:
            {
                opCode      = gBleSmCmdDevDisconnectNotificationOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId);
            }
            break;

        case gBleSmCmdSetDefaultPasskey_c:
            {
                opCode      = gBleSmCmdSetDefaultPasskeyOpCode_c;
                dataSize    = fsciBleSmGetSetDefaultPasskeyParamsBufferSize((smSetDefaultPasskeyParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdSetOobMitmProtection_c:
            {
                opCode      = gBleSmCmdSetOobMitmProtectionOpCode_c;
                dataSize    = fsciBleSmGetSetOobMitmProtectionParamsBufferSize((smSetOobMitmProtectionParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdSendKeypressNotification_c:
            {
                opCode      = gBleSmCmdSendKeypressNotificationOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetSendKeypressNotificationParamsBufferSize((smKeypressNotificationParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdNcDisplayConfirm_c:
            {
                opCode      = gBleSmCmdNcDisplayConfirmOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetNcDisplayConfirmParamsBufferSize((smNcDisplayConfirmParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdLeScOobDataRequestReply_c:
            {
                opCode      = gBleSmCmdLeScOobDataRequestReplyOpCode_c;
                dataSize    = fsciBleGetDeviceIdBufferSize(&destDevId) +
                              fsciBleSmGetLeScOobDataRequestReplyParamsBufferSize((smLeScOobDataParams_t*)pCommandData);
            }
            break;

        case gBleSmCmdLocalLeScOobDataRequest_c:
            {
                opCode      = gBleSmCmdLocalLeScOobDataRequestOpCode_c;
                dataSize    = 0;
            }
            break;

        case gBleSmCmdGenerateNewEcdhPkSkPairReq_c:
            {
                opCode      = gBleSmCmdGenerateNewEcdhPkSkPairReqOpCode_c;
                dataSize    = 0;
            }
            break;

        case gBleSmCmdSetMinPairingSecurityProperties_c:
            {
                opCode      = gBleSmCmdSetMinPairingSecurityPropertiesOpCode_c;
                dataSize    = fsciBleSmGetSetMinPairingSecurityPropertiesParamsBufferSize((smSetMinPairingSecurityPropertiesParams_t*)pCommandData);
            }
            break;

        default:
            {
                /* Unknown SM command code */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
                return;
            }
    }

    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleSmAllocFsciPacket(opCode, dataSize);

    if(NULL == pClientPacket)
    {
        return;
    }

    pBuffer = &pClientPacket->payload[0];

    /* Set command parameters in the buffer */
    switch(commandCode)
    {
        case gBleSmCmdDHKeyComputedNotification_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
            }
            break;

        case gBleSmCmdInitiatorStartPairing_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromPairingParams((smPairingParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdSendSecurityRequest_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromSecurityReqParams((smSecurityReqParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdTerminatePairing_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromTerminatePairingParams((smTerminatePairingParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdPairingRequestReply_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromPairingParams((smPairingParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdPasskeyRequestReply_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromPasskeyReqReplyParams((smPasskeyReqReplyParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdPairingKeysetRequestReply_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBuffInPairKeysetReqReplyParams((smPairingKeysetRequestReplyParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdLlStartEncryption_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromLlStartEncryptionParams((smLlStartEncryptionParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdLlLtkRequestReply_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromLlLtkRequestReplyParams((smLlLtkRequestReplyParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdLlLtkRequestNegativeReply_c:
        case gBleSmCmdDevConnectNotification_c:
        case gBleSmCmdDevDisconnectNotification_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
            }
            break;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
        case gBleSmCmdLlEncryptReq_c:
            {
                fsciBleSmGetBufferFromLlEncryptReqParams((smLlEncryptReqParams_t*)pCommandData, &pBuffer);
            }
            break;
#endif
        case gBleSmCmdTbCreateRandomDeviceAddrReq_c:
            {
                fsciBleSmGetBufferFromTbCreateRandomDeviceAddrReqParams((smTbCreateRandomDeviceAddrReqParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdTbCheckResolvablePrivateAddrReq_c:
            {
                fsciBleSmGetBufferFromTbCheckResolvablePrivateAddrReqParams((smTbCheckResolvablePrivateAddrReqParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdTbSignDataReq_c:
            {
                fsciBleSmGetBufferFromTbSignDataReqParams((smTbSignDataReqParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdTbVerifyDataSignatureReq_c:
            {
                fsciBleSmGetBufferFromTbVerifyDataSignatureReqParams((smTbVerifyDataSignatureReqParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdSetDefaultPasskey_c:
            {
                fsciBleSmGetBufferFromSetDefaultPasskeyParams((smSetDefaultPasskeyParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdSetOobMitmProtection_c:
            {
                fsciBleSmGetBufferFromSetOobMitmProtectionParams((smSetOobMitmProtectionParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdSendKeypressNotification_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromSendKeypressNotificationParams((smKeypressNotificationParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdNcDisplayConfirm_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromNcDisplayConfirmParams((smNcDisplayConfirmParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdLeScOobDataRequestReply_c:
            {
                fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);
                fsciBleSmGetBufferFromCmdLeScOobDataRequestReplyParams((smLeScOobDataParams_t*)pCommandData, &pBuffer);
            }
            break;

        case gBleSmCmdSetMinPairingSecurityProperties_c:
            {
                fsciBleSmGetBufferFromSetMinPairingSecurityPropertiesParams((smSetMinPairingSecurityPropertiesParams_t*)pCommandData, &pBuffer);
            }
            break;

        default:
             break;
    }

    /* Transmit the packet over UART */
    fsciBleTransmitFormatedPacket(pClientPacket, fsciBleInterfaceId);
}


void fsciBleSmUserEventEvtMonitor(deviceId_t destDevId, bleSmEvent_t eventCode, uint16_t eventDataLength, void* pEventData)
{
    clientPacketStructured_t*   pClientPacket;
    uint8_t*                    pBuffer;
    fsciBleSmOpCode_t           opCode;
    uint16_t                    dataSize = fsciBleGetDeviceIdBufferSize(&destDevId);

    /* If SM is disabled the event must be not monitored */
    if(FALSE == bFsciBleSmEnabled)
    {
        return;
    }

    /* Get the SM event code and the size of the payload that will be sent over UART */
    switch(eventCode)
    {
        case gBleSmEventStatus_c:
            {
                opCode      = gBleSmEvtStatusOpCode_c;
                dataSize   += fsciBleSmGetStatusParamsBufferSize((smStatusParams_t*)pEventData);
            }
            break;

        case gBleSmEventRemoteSecurityRequest_c:
            {
                opCode      = gBleSmEvtRemoteSecurityRequestOpCode_c;
                dataSize   += fsciBleSmGetSecurityReqParamsBufferSize((smSecurityReqParams_t*)pEventData);
            }
            break;

        case gBleSmEventRemotePairingRequest_c:
            {
                opCode      = gBleSmEvtRemotePairingRequestOpCode_c;
                dataSize   += fsciBleSmGetPairingParamsBufferSize((smPairingParams_t*)pEventData);
            }
            break;

        case gBleSmEventRemotePairingResponse_c:
            {
                opCode      = gBleSmEvtRemotePairingResponseOpCode_c;
                dataSize   += fsciBleSmGetPairingParamsBufferSize((smPairingParams_t*)pEventData);
            }
            break;

        case gBleSmEventPasskeyDisplayRequest_c:
            {
                opCode      = gBleSmEvtPasskeyDisplayRequestOpCode_c;
                dataSize   += fsciBleSmGetPasskeyDisplayReqParamsBufferSize((smPasskeyDisplayReqParams_t*)pEventData);
            }
            break;

        case gBleSmEventPasskeyRequest_c:
            {
                opCode      = gBleSmEvtPasskeyRequestOpCode_c;
                dataSize   += fsciBleSmGetPasskeyReqParamsBufferSize((smPasskeyReqParams_t*)pEventData);
            }
            break;

        case gBleSmEventPairingKeysetRequest_c:
            {
                opCode      = gBleSmEvtPairingKeysetRequestOpCode_c;
                dataSize   += fsciBleSmGetPairingKeysetReqParamsBufferSize((smPairingKeysetReqParams_t*)pEventData);
            }
            break;

        case gBleSmEventPairingKeysetReceived_c:
            {
                opCode      = gBleSmEvtPairingKeysetReceivedOpCode_c;
                dataSize   += fsciBleSmGetPairingKeysetReceivedParamsBufferSize((smPairingKeysetReceivedParams_t*)pEventData);
            }
            break;

        case gBleSmEventPairingComplete_c:
            {
                opCode      = gBleSmEvtPairingCompleteOpCode_c;
                dataSize   += fsciBleSmGetPairingCompleteParamsBufferSize((smPairingCompleteParams_t*)pEventData);
            }
            break;

        case gBleSmEventPairingFailed_c:
            {
                opCode      = gBleSmEvtPairingFailedOpCode_c;
                dataSize   += fsciBleSmGetPairingFailedParamsBufferSize((smPairingFailedParams_t*)pEventData);
            }
            break;

        case gBleSmEventRemotePairingFailed_c:
            {
                opCode      = gBleSmEvtRemotePairingFailedOpCode_c;
                dataSize   += fsciBleSmGetPairingFailedParamsBufferSize((smPairingFailedParams_t*)pEventData);
            }
            break;

        case gBleSmEventLlLtkRequest_c:
            {
                opCode      = gBleSmEvtLlLtkRequestOpCode_c;
                dataSize   += fsciBleSmGetLlLtkRequestParamsBufferSize((smLlLtkRequestParams_t*)pEventData);
            }
            break;

        case gBleSmEventLlEncryptionStatus_c:
            {
                opCode      = gBleSmEvtLlEncryptionStatusOpCode_c;
                dataSize   += fsciBleSmGetLlEncryptionStatusParamsBufferSize((smLlEncryptionStatusParams_t*)pEventData);
            }
            break;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
        case gBleSmEventLlEncryptRes_c:
            {
                opCode      = gBleSmEvtLlEncryptResOpCode_c;
                dataSize   += fsciBleSmGetLlEncryptResParamsBufferSize((smLlEncryptResParams_t*)pEventData);
            }
            break;
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
        case gBleSmEventLlRandRes_c:
            {
                opCode      = gBleSmEvtLlRandResOpCode_c;
                dataSize   += fsciBleSmGetLlRandResParamsBufferSize((smLlRandResParams_t*)pEventData);
            }
            break;
#endif
        case gBleSmEventTbCreateRandomDeviceAddrRes_c:
            {
                opCode      = gBleSmEvtTbCreateRandomDeviceAddrResOpCode_c;
                dataSize   += fsciBleSmGetTbCreateRandomDeviceAddrResParamsBufferSize((smTbCreateRandomDeviceAddrResParams_t*)pEventData);
            }
            break;

        case gBleSmEventTbCheckResolvalePrivateAddrRes_c:
            {
                opCode      = gBleSmEvtTbCheckResolvalePrivateAddrResOpCode_c;
                dataSize   += fsciBleSmGetTbCheckResolvablePrivateAddrResParamsBufferSize((smTbCheckResolvablePrivateAddrResParams_t*)pEventData);
            }
            break;

        case gBleSmEventTbSignDataRes_c:
            {
                opCode      = gBleSmEvtTbSignDataResOpCode_c;
                dataSize   += fsciBleSmGetTbSignDataResParamsBufferSize((smTbSignDataResParams_t*)pEventData);
            }
            break;

        case gBleSmEventTbVerifyDataSignatureRes_c:
            {
                opCode      = gBleSmEvtTbVerifyDataSignatureResOpCode_c;
                dataSize   += fsciBleSmGetTbVerifyDataSignatureResParamsBufferSize((smTbVerifyDataSignatureResParams_t*)pEventData);
            }
            break;

        case gBleSmEventRemoteKeypressNotification_c:
            {
                opCode      = gBleSmEvtRemoteKeypressNotificationOpCode_c;
                dataSize   += fsciBleSmGetRemoteKeypressNotificationParamsBufferSize((smKeypressNotificationParams_t*)pEventData);
            }
            break;

        case gBleSmEventNcDisplayRequest_c:
            {
                opCode      = gBleSmEvtNcDisplayRequestOpCode_c;
                dataSize   += fsciBleSmGetNcDisplayRequestParamsBufferSize((smNcDisplayReqParams_t*)pEventData);
            }
            break;

        case gBleSmEventLeScOobDataRequest_c:
            {
                opCode      = gBleSmEvtLeScOobDataRequestOpCode_c;
            }
            break;

        case gBleSmEventLocalLeScOobData_c:
            {
                opCode      = gBleSmEvtLocalLeScOobDataOpCode_c;
                dataSize   += fsciBleSmGetLocalLeScOobDataParamsBufferSize((smLeScOobDataParams_t*)pEventData);
            }
            break;

        case gBleSmEventGenerateNewEcdhPkSkPairRes_c:
            {
                opCode      = gBleSmEvtGenerateNewEcdhPkSkPairResOpCode_c;
                dataSize   += fsciBleSmGetGenerateNewEcdhPkSkPairResParamsBufferSize((smGenerateNewEcdhPkSkPairResParams_t*)pEventData);
            }
            break;

        default:
            {
                /* Unknown SM event code */
                fsciBleError(gFsciError_c, fsciBleInterfaceId);
            }
            return;
    }

    /* Allocate the packet to be sent over UART */
    pClientPacket = fsciBleSmAllocFsciPacket(opCode, dataSize);

    if(NULL == pClientPacket)
    {
        return;
    }

    pBuffer = &pClientPacket->payload[0];

    /* Set event parameters in the buffer */
    fsciBleGetBufferFromDeviceId(&destDevId, &pBuffer);

    switch(eventCode)
    {
        case gBleSmEventStatus_c:
            {
                fsciBleSmGetBufferFromStatusParams((smStatusParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventRemoteSecurityRequest_c:
            {
                fsciBleSmGetBufferFromSecurityReqParams((smSecurityReqParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventRemotePairingRequest_c:
            {
                fsciBleSmGetBufferFromPairingParams((smPairingParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventRemotePairingResponse_c:
            {
                fsciBleSmGetBufferFromPairingParams((smPairingParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPasskeyDisplayRequest_c:
            {
                fsciBleSmGetBufferFromPasskeyDisplayReqParams((smPasskeyDisplayReqParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPasskeyRequest_c:
            {
                fsciBleSmGetBufferFromPasskeyReqParams((smPasskeyReqParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPairingKeysetRequest_c:
            {
                fsciBleSmGetBuffFromPairKeysetReqParams((smPairingKeysetReqParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPairingKeysetReceived_c:
            {
                fsciBleSmGetBufferFromPairingKeysetReceivedParams((smPairingKeysetReceivedParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPairingComplete_c:
            {
                fsciBleSmGetBufferFromPairingCompleteParams((smPairingCompleteParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventPairingFailed_c:
            {
                fsciBleSmGetBufferFromPairingFailedParams((smPairingFailedParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventRemotePairingFailed_c:
            {
                fsciBleSmGetBufferFromPairingFailedParams((smPairingFailedParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventLlLtkRequest_c:
            {
                fsciBleSmGetBufferFromLlLtkRequestParams((smLlLtkRequestParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventLlEncryptionStatus_c:
            {
                fsciBleSmGetBuffFromLlEncrStatusParams((smLlEncryptionStatusParams_t*)pEventData, &pBuffer);
            }
            break;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
        case gBleSmEventLlEncryptRes_c:
            {
                fsciBleSmGetBuffFromLlEncrResParams((smLlEncryptResParams_t*)pEventData, &pBuffer);
            }
            break;
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
        case gBleSmEventLlRandRes_c:
            {
                fsciBleSmGetBufferFromLlRandResParams((smLlRandResParams_t*)pEventData, &pBuffer);
            }
            break;
#endif
        case gBleSmEventTbCreateRandomDeviceAddrRes_c:
            {
                fsciBleSmGetBuffFromTbCreateRndmDevAddrResParams((smTbCreateRandomDeviceAddrResParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventTbCheckResolvalePrivateAddrRes_c:
            {
                fsciBleSmGetBufferFromTbCheckResolvablePrivateAddrResParams((smTbCheckResolvablePrivateAddrResParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventTbSignDataRes_c:
            {
                fsciBleSmGetBuffFromTbSignDataResParams((smTbSignDataResParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventTbVerifyDataSignatureRes_c:
            {
                fsciBleSmGetBufferFromTbVerifyDataSignatureResParams((smTbVerifyDataSignatureResParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventRemoteKeypressNotification_c:
            {
                fsciBleSmGetBufferFromRemoteKeypressNotificationParams((smKeypressNotificationParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventNcDisplayRequest_c:
            {
                fsciBleSmGetBufferFromNcDisplayRequestParams((smNcDisplayReqParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventLocalLeScOobData_c:
            {
                fsciBleSmGetBufferFromLocalLeScOobDataParams((smLeScOobDataParams_t*)pEventData, &pBuffer);
            }
            break;

        case gBleSmEventGenerateNewEcdhPkSkPairRes_c:
            {
                fsciBleSmGetBufferFromGenerateNewEcdhPkSkPairResParams((smGenerateNewEcdhPkSkPairResParams_t*)pEventData, &pBuffer);
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

#if gFsciBleTest_d

static bleResult_t fsciBleSmUserEventCallback(deviceId_t sourceDevId, bleSmEvent_t eventType, uint16_t eventLength, void* pEventPayload)
{
    return gBleSuccess_c;
}

#endif /* gFsciBleTest_d */

#endif /* gFsciIncluded_c && gFsciBleSmLayerEnabled_d */

/*! *********************************************************************************
* @}
********************************************************************************** */
