/*! *********************************************************************************
 * \defgroup FSCI_BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* \file
*
* This is a header file for FSCI BLE management.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef FSCI_BLE_SM_TYPES_H
#define FSCI_BLE_SM_TYPES_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble.h"
#include "sm_config.h"
#include "sm_params.h"
#include "sm_interface.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

#if gBLE42_d
#define fsciBleSmGetAuthReqParamsBufferSize(pAuthReqParams)             \
        (sizeof(smpAuthReqBondingFlags_t) + sizeof(smpAuthReqMitm_t) +  \
         sizeof(smpAuthReqSc_t) + sizeof(smpAuthReqKeypress_t))
#else
#define fsciBleSmGetAuthReqParamsBufferSize(pAuthReqParams) \
        (sizeof(smpAuthReqBondingFlags_t) + sizeof(smpAuthReqMitm_t))
#endif

#if gBLE42_d
#define fsciBleSmGetKeyDistParamsBufferSize(pKeyDistParams) \
        (sizeof(bool_t) + sizeof(bool_t) + sizeof(bool_t) + sizeof(bool_t) + sizeof(uint8_t))
#else
#define fsciBleSmGetKeyDistParamsBufferSize(pKeyDistParams) \
        (sizeof(bool_t) + sizeof(bool_t) + sizeof(bool_t) + sizeof(bool_t))
#endif

#define fsciBleSmGetKeyDistPayloadBufferSize(pKeyDistParams)    \
        (gSmpLtkSize_c + gSmpIrkSize_c + gSmpCsrkSize_c +       \
        gcBleDeviceAddressSize_c + sizeof(uint16_t) + gSmpLlEncryptionRandSize_c)

#define fsciBleSmGetPairingParamsBufferSize(pPairingParams)                                 \
        (sizeof(smpPairingIoCapability_t) + sizeof(smpPairingOobDataFlag_t) +               \
        fsciBleSmGetAuthReqParamsBufferSize(&(pPairingParams)->authReq) + sizeof(uint8_t) + \
        fsciBleSmGetKeyDistParamsBufferSize(&(pPairingParams)->initiatorKeyDist) +          \
        fsciBleSmGetKeyDistParamsBufferSize(&(pPairingParams)->responderKeyDist))

#define fsciBleSmGetStatusParamsBufferSize(pStatusParams)   \
        sizeof(bleResult_t)

#define fsciBleSmGetStatusParamsFromBuffer(pStatusParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pStatusParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetBufferFromStatusParams(pStatusParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pStatusParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetSecurityReqParamsBufferSize(pSecurityReqParams) \
        fsciBleSmGetAuthReqParamsBufferSize(&(pSecurityReqParams)->authReq)

#define fsciBleSmGetSecurityReqParamsFromBuffer(pSecurityReqParams, ppBuffer)   \
        fsciBleSmGetAuthReqParamsFromBuffer(&(pSecurityReqParams)->authReq, (ppBuffer))

#define fsciBleSmGetBufferFromSecurityReqParams(pSecurityReqParams, ppBuffer)   \
        fsciBleSmGetBufferFromAuthReqParams(&(pSecurityReqParams)->authReq, (ppBuffer))

#define fsciBleSmGetTerminatePairingParamsBufferSize(pTerminatePairingParams)   \
        sizeof(smpPairingFailedReason_t)

#define fsciBleSmGetTerminatePairingParamsFromBuffer(pTerminatePairingParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pTerminatePairingParams)->reason, *(ppBuffer), smpPairingFailedReason_t)

#define fsciBleSmGetBufferFromTerminatePairingParams(pTerminatePairingParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pTerminatePairingParams)->reason, *(ppBuffer), smpPairingFailedReason_t)

#define fsciBleSmGetPairingKeysetRequestReplyParamsBufferSize(pPairingKeysetRequestReplyParams)     \
        (fsciBleSmGetKeyDistPayloadBufferSize((pPairingKeysetRequestReplyParams)->keyDistPayload) + \
        fsciBleSmGetKeyDistParamsBufferSize((pPairingKeysetRequestReplyParams)->sentKeys))

#define fsciBleSmGetPasskeyDisplayReqParamsBufferSize(pPasskeyDisplayReqParams) \
        sizeof(uint32_t)

#define fsciBleSmGetPasskeyDisplayReqParamsFromBuffer(pPasskeyDisplayReqParams, ppBuffer)   \
        fsciBleGetUint32ValueFromBuffer((pPasskeyDisplayReqParams)->passKey, *(ppBuffer))

#define fsciBleSmGetBufferFromPasskeyDisplayReqParams(pPasskeyDisplayReqParams, ppBuffer)   \
        fsciBleGetBufferFromUint32Value((pPasskeyDisplayReqParams)->passKey, *(ppBuffer))

#define fsciBleSmGetPasskeyReqParamsBufferSize(pPasskeyReqParams)   \
        sizeof(smKeyType_t)

#define fsciBleSmGetPasskeyReqParamsFromBuffer(pPasskeyReqParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pPasskeyReqParams)->passKeyType, *(ppBuffer), smKeyType_t)

#define fsciBleSmGetBufferFromPasskeyReqParams(pPasskeyReqParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pPasskeyReqParams)->passKeyType, *(ppBuffer), smKeyType_t)

#define fsciBleSmGetPairingKeysetReqParamsBufferSize(pPairingKeysetReqParams)               \
        (fsciBleSmGetKeyDistParamsBufferSize((pPairingKeysetReqParams)->requestedKeys) +    \
        sizeof(uint8_t))

#define fsciBleSmGetPairingKeysetReceivedParamsBufferSize(pPairingKeysetReceivedParams)         \
        (fsciBleSmGetKeyDistPayloadBufferSize((pPairingKeysetReceivedParams)->keyDistPayload) + \
        fsciBleSmGetKeyDistParamsBufferSize((pPairingKeysetReceivedParams)->receivedKeys) +     \
        sizeof(uint8_t))

#if (gBLE42_d == TRUE)
#define fsciBleSmGetPairingCompleteParamsBufferSize(pPairingCompleteParams) \
        (sizeof(uint8_t) + sizeof(bool_t) + sizeof(bool_t) + sizeof(bool_t) + gSmpLtkSize_c)
#else
#define fsciBleSmGetPairingCompleteParamsBufferSize(pPairingCompleteParams) \
        (sizeof(uint8_t) + sizeof(bool_t) + sizeof(bool_t))
#endif

#define fsciBleSmGetPairingFailedParamsBufferSize(pPairingFailedParams) \
        sizeof(smpPairingFailedReason_t)

#define fsciBleSmGetPairingFailedParamsFromBuffer(pPairingFailedParams, ppBuffer)   \
        fsciBleGetEnumValueFromBuffer((pPairingFailedParams)->reason, *(ppBuffer), smpPairingFailedReason_t)

#define fsciBleSmGetBufferFromPairingFailedParams(pPairingFailedParams, ppBuffer)   \
        fsciBleGetBufferFromEnumValue((pPairingFailedParams)->reason, *(ppBuffer), smpPairingFailedReason_t)

#define fsciBleSmGetLlStartEncryptionParamsBufferSize(pLlStartEncryptionParams) \
        (gSmpLlEncryptionRandSize_c + sizeof(uint16_t) + gSmpLtkSize_c)

#define fsciBleSmGetLlLtkRequestReplyParamsBufferSize(pLlLtkRequestReplyParams) \
        gSmpLtkSize_c

#define fsciBleSmGetLlLtkRequestReplyParamsFromBuffer(pLlLtkRequestReplyParams, ppBuffer)   \
        fsciBleGetArrayFromBuffer((pLlLtkRequestReplyParams)->longTermKey, *(ppBuffer), gSmpLtkSize_c)

#define fsciBleSmGetBufferFromLlLtkRequestReplyParams(pLlLtkRequestReplyParams, ppBuffer)   \
        fsciBleGetBufferFromArray((pLlLtkRequestReplyParams)->longTermKey, *(ppBuffer), gSmpLtkSize_c)

#define fsciBleSmGetLlEncryptReqParamsBufferSize(pLlEncryptReqParams)   \
        (gSmpLlEncryptBlockSize_c + gSmpLlEncryptBlockSize_c)

#define fsciBleSmGetLlLtkRequestParamsBufferSize(pLlLtkRequestParams)   \
        (gSmpLlEncryptionRandSize_c + sizeof(uint16_t))

#define fsciBleSmGetLlEncryptionStatusParamsBufferSize(pLlEncryptionStatusParams)   \
        (sizeof(bleResult_t) + sizeof(smLlEncryptionState_t) + sizeof(smLlEncKeyType_t))

#define fsciBleSmGetLlEncryptResParamsBufferSize(pLlEncryptResParams)   \
        (sizeof(bleResult_t) + sizeof(uint8_t) * gSmpLlEncryptBlockSize_c)

#define fsciBleSmGetLlRandResParamsBufferSize(pLlRandResParams) \
        (sizeof(bleResult_t) + sizeof(uint8_t) * gSmpLlRandSize_c)

#define fsciBleSmGetTbCreateRandomDeviceAddrResParamsBufferSize(pParams)    \
        (sizeof(bleResult_t) + sizeof(smBleRandomDevAddType_t) +            \
        gcBleDeviceAddressSize_c)

#define fsciBleSmFreeTbCreateRandomDeviceAddrReqParams(pTbCreateRandomDeviceAddrReqParams)  \
        MEM_BufferFree(pTbCreateRandomDeviceAddrReqParams)

#define fsciBleSmGetTbCheckResolvablePrivateAddrReqParamsBufferSize(pParams)    \
        (gSmpIrkSize_c + gcBleDeviceAddressSize_c)

#define fsciBleSmGetTbCheckResolvablePrivateAddrResParamsBufferSize(pParams)    \
        sizeof(bleResult_t)

#define fsciBleSmGetTbCheckResolvablePrivateAddrResParamsFromBuffer(pParams, ppBuffer)  \
        fsciBleGetEnumValueFromBuffer((pParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetBufferFromTbCheckResolvablePrivateAddrResParams(pParams, ppBuffer)  \
        fsciBleGetBufferFromEnumValue((pParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetTbSignDataReqParamsBufferSize(pTbSignDataReqParams) \
        (gSmpCsrkSize_c + sizeof(bleResult_t) + (pTbSignDataReqParams)->dataLength)

#define fsciBleSmFreeTbSignDataReqParams(pTbSignDataReqParams)  \
        MEM_BufferFree(pTbSignDataReqParams)

#define fsciBleSmGetTbSignDataResParamsBufferSize(pTbSignDataResParams) \
        (sizeof(bleResult_t) + gSmpAuthSignatureLength_c)

#define fsciBleSmGetTbVerifyDataSignatureReqParamsBufferSize(pTbVerifyDataSignatureReqParams)   \
        (gSmpCsrkSize_c + sizeof(uint16_t) + (pTbVerifyDataSignatureReqParams)->dataLength +    \
        gSmpAuthSignatureLength_c)

#define fsciBleSmFreeTbVerifyDataSignatureReqParams(pTbVerifyDataSignatureReqParams)    \
        MEM_BufferFree(pTbVerifyDataSignatureReqParams)

#define fsciBleSmGetTbVerifyDataSignatureResParamsBufferSize(pParams)   \
        sizeof(bleResult_t)

#define fsciBleSmGetTbVerifyDataSignatureResParamsFromBuffer(pParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetBufferFromTbVerifyDataSignatureResParams(pParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pParams)->status, *(ppBuffer), bleResult_t)

#define fsciBleSmGetSetDefaultPasskeyParamsBufferSize(pSetDefaultPasskeyParams) \
        sizeof(uint32_t)

#define fsciBleSmGetSetDefaultPasskeyParamsFromBuffer(pSetDefaultPasskeyParams, ppBuffer) \
        fsciBleGetUint32ValueFromBuffer((pSetDefaultPasskeyParams)->defaultPasskey, *(ppBuffer))

#define fsciBleSmGetBufferFromSetDefaultPasskeyParams(pSetDefaultPasskeyParams, ppBuffer) \
        fsciBleGetBufferFromUint32Value((pSetDefaultPasskeyParams)->defaultPasskey, *(ppBuffer))

#if (gBLE42_d == TRUE)

#define fsciBleSmGetSetOobMitmProtectionParamsBufferSize(pSetOobMitmProtectionParams) \
        sizeof(smOobMitmProtection_t)

#define fsciBleSmGetSetOobMitmProtectionParamsFromBuffer(pSetOobMitmProtectionParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pSetOobMitmProtectionParams)->oobMitmProt, *(ppBuffer), smOobMitmProtection_t)

#define fsciBleSmGetBufferFromSetOobMitmProtectionParams(pSetOobMitmProtectionParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pSetOobMitmProtectionParams)->oobMitmProt, *(ppBuffer), smOobMitmProtection_t)

#define fsciBleSmGetSendKeypressNotificationParamsBufferSize(pSendKeypressNotificationParams) \
        sizeof(smKeypressNotificationParams_t)

#define fsciBleSmGetSendKeypressNotificationParamsFromBuffer(pSendKeypressNotificationParams, ppBuffer) \
        fsciBleGetEnumValueFromBuffer((pSendKeypressNotificationParams)->keypressNotifType, *(ppBuffer), smpKeypressNotificationType_t)

#define fsciBleSmGetBufferFromSendKeypressNotificationParams(pSendKeypressNotificationParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pSendKeypressNotificationParams)->keypressNotifType, *(ppBuffer), smpKeypressNotificationType_t)

#define fsciBleSmGetNcDisplayConfirmParamsBufferSize(pGetNcDisplayConfirmParams) \
        sizeof(smNcDisplayConfirmParams_t)

#define fsciBleSmGetNcDisplayConfirmParamsFromBuffer(pNcDisplayConfirmParams, ppBuffer) \
        fsciBleGetBoolValueFromBuffer((pNcDisplayConfirmParams)->ncValueConfirm, *(ppBuffer))

#define fsciBleSmGetBufferFromNcDisplayConfirmParams(pNcDisplayConfirmParams, ppBuffer) \
        fsciBleGetBufferFromBoolValue((pNcDisplayConfirmParams)->ncValueConfirm, *(ppBuffer))

#define fsciBleSmGetLeScOobDataRequestReplyParamsBufferSize(pLeScOobDataParams) \
        (gSmpLeScRandomValueSize_c + gSmpLeScRandomConfirmValueSize_c + gcBleDeviceAddressSize_c)

#define fsciBleSmGetRemoteKeypressNotificationParamsBufferSize(pRemoteKeypressNotificationParams) \
        sizeof(smKeypressNotificationParams_t)

#define fsciBleSmGetBufferFromRemoteKeypressNotificationParams(pRemoteKeypressNotificationParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pRemoteKeypressNotificationParams)->keypressNotifType, *(ppBuffer), smpKeypressNotificationType_t)

#define fsciBleSmGetNcDisplayRequestParamsBufferSize(pNcDisplayRequestParams) \
        sizeof(smNcDisplayReqParams_t)

#define fsciBleSmGetBufferFromNcDisplayRequestParams(pNcDisplayRequestParams, ppBuffer) \
        fsciBleGetBufferFromUint32Value((pNcDisplayRequestParams)->ncValue, *(ppBuffer))

#define fsciBleSmGetLocalLeScOobDataParamsBufferSize(pLocalLeScOobDataParams) \
        fsciBleSmGetLeScOobDataRequestReplyParamsBufferSize(pLocalLeScOobDataParams)

#define fsciBleSmGetBufferFromLocalLeScOobDataParams(pLocalLeScOobDataParams, ppBuffer) \
        fsciBleSmGetBufferFromCmdLeScOobDataRequestReplyParams(pLocalLeScOobDataParams, ppBuffer)

#define fsciBleSmGetGenerateNewEcdhPkSkPairResParamsBufferSize(pGenerateNewEcdhPkSkPairResParams) \
        sizeof(smGenerateNewEcdhPkSkPairResParams_t)

#define fsciBleSmGetBufferFromGenerateNewEcdhPkSkPairResParams(pGenerateNewEcdhPkSkPairResParams, ppBuffer) \
        fsciBleGetBufferFromEnumValue((pGenerateNewEcdhPkSkPairResParams)->status, *(ppBuffer), bleResult_t)

#endif /* (gBLE42_d == TRUE) */

#if (gBLE42_d == TRUE)
#define fsciBleSmGetSetMinPairingSecurityPropertiesParamsBufferSize(pSetMinPairingSecurityPropertiesParams) \
        (sizeof(bool_t) + sizeof(bool_t) + sizeof(uint8_t))
#else
#define fsciBleSmGetSetMinPairingSecurityPropertiesParamsBufferSize(pSetMinPairingSecurityPropertiesParams) \
        (sizeof(bool_t) + sizeof(uint8_t))
#endif /* (gBLE42_d == TRUE) */


/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

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

void fsciBleSmGetAuthReqParamsFromBuffer
(
    smAuthReqParams_t*  pAuthReqParams,
    uint8_t**           ppBuffer
);

void fsciBleSmGetBufferFromAuthReqParams
(
    smAuthReqParams_t*  pAuthReqParams,
    uint8_t**           ppBuffer
);

void fsciBleSmGetKeyDistParamsFromBuffer
(
    smKeyDistParams_t*  pKeyDistParams,
    uint8_t**           ppBuffer
);

void fsciBleSmGetBufferFromKeyDistParams
(
    smKeyDistParams_t*  pKeyDistParams,
    uint8_t**           ppBuffer
);

void fsciBleSmGetKeyDistPayloadFromBuffer
(
    smKeyDistPayload_t* pKeyDistPayload,
    uint8_t**           ppBuffer
);

void fsciBleSmGetBuffFromKeyDistPayload
(
    smKeyDistPayload_t* pKeyDistPayload,
    uint8_t**           ppBuffer
);

void fsciBleSmGetPairingParamsFromBuffer
(
    smPairingParams_t*  pPairingParams,
    uint8_t**           ppBuffer
);

void fsciBleSmGetBufferFromPairingParams
(
    smPairingParams_t*  pPairingParams,
    uint8_t**           ppBuffer
);

uint16_t fsciBleSmGetPasskeyReqReplyParamsBufferSize
(
    smPasskeyReqReplyParams_t* pPasskeyReqReplyParams
);

void fsciBleSmGetPasskeyReqReplParamsFromBuffer
(
    smPasskeyReqReplyParams_t*  pPasskeyReqReplyParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetBufferFromPasskeyReqReplyParams
(
    smPasskeyReqReplyParams_t*  pPasskeyReqReplyParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetPairingKeysetRequestReplyParamsFromBuffer
(
    smPairingKeysetRequestReplyParams_t*    pPairingKeysetRequestReplyParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetBuffInPairKeysetReqReplyParams
(
    smPairingKeysetRequestReplyParams_t*    pPairingKeysetRequestReplyParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetPairingKeysetReqParamsFromBuffer
(
    smPairingKeysetReqParams_t* pPairingKeysetReqParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetBuffFromPairKeysetReqParams
(
    smPairingKeysetReqParams_t* pPairingKeysetReqParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetPairingKeysetReceivedParamsFromBuffer
(
    smPairingKeysetReceivedParams_t*    pPairingKeysetReceivedParams,
    uint8_t**                           ppBuffer
);

void fsciBleSmGetBufferFromPairingKeysetReceivedParams
(
    smPairingKeysetReceivedParams_t*    pPairingKeysetReceivedParams,
    uint8_t**                           ppBuffer
);

void fsciBleSmGetPairingCompleteParamsFromBuffer
(
    smPairingCompleteParams_t*  pPairingCompleteParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetBufferFromPairingCompleteParams
(
    smPairingCompleteParams_t*  pPairingCompleteParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetLlStartEncryptionParamsFromBuffer
(
    smLlStartEncryptionParams_t*    pLlStartEncryptionParams,
    uint8_t**                       ppBuffer
);

void fsciBleSmGetBufferFromLlStartEncryptionParams
(
    smLlStartEncryptionParams_t*    pLlStartEncryptionParams,
    uint8_t**                       ppBuffer
);

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
void fsciBleSmGetLlEncryptReqParamsFromBuffer
(
    smLlEncryptReqParams_t* pLlEncryptReqParams,
    uint8_t**               ppBuffer
);

void fsciBleSmGetBufferFromLlEncryptReqParams
(
    smLlEncryptReqParams_t* pLlEncryptReqParams,
    uint8_t**               ppBuffer
);
#endif

void fsciBleSmGetLlLtkRequestParamsFromBuffer
(
    smLlLtkRequestParams_t* pLlLtkRequestParams,
    uint8_t**               ppBuffer
);

void fsciBleSmGetBufferFromLlLtkRequestParams
(
    smLlLtkRequestParams_t* pLlLtkRequestParams,
    uint8_t**               ppBuffer
);

void fsciBleSmGetLlEncryptionStatusParamsFromBuffer
(
    smLlEncryptionStatusParams_t*   pLlEncryptionStatusParams,
    uint8_t**                       ppBuffer
);

void fsciBleSmGetBuffFromLlEncrStatusParams
(
    smLlEncryptionStatusParams_t*   pLlEncryptionStatusParams,
    uint8_t**                       ppBuffer
);

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
void fsciBleSmGetLlEncryptResParamsFromBuffer
(
    smLlEncryptResParams_t* pLlEncryptResParams,
    uint8_t**               ppBuffer
);

void fsciBleSmGetBuffFromLlEncrResParams
(
    smLlEncryptResParams_t* pLlEncryptResParams,
    uint8_t**               ppBuffer
);
#endif

#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
void fsciBleSmGetLlRandResParamsFromBuffer
(
    smLlRandResParams_t*    pLlRandResParams,
    uint8_t**               ppBuffer
);

void fsciBleSmGetBufferFromLlRandResParams
(
    smLlRandResParams_t*    pLlRandResParams,
    uint8_t**               ppBuffer
);
#endif

smTbCreateRandomDeviceAddrReqParams_t* fsciBleSmAllocTbCreateRandomDeviceAddrReqParamsForBuffer
(
    uint8_t* pBuffer
);

uint8_t fsciBleSmGetTbCreateRandomDeviceAddrReqParamsBufferSize
(
    smTbCreateRandomDeviceAddrReqParams_t* pTbCreateRandomDeviceAddrReqParams
);

void fsciBleSmGetTbCreateRndmDevAddrReqParamsFromBuffer
(
    smTbCreateRandomDeviceAddrReqParams_t*  pTbCreateRandomDeviceAddrReqParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetBufferFromTbCreateRandomDeviceAddrReqParams
(
    smTbCreateRandomDeviceAddrReqParams_t*  pTbCreateRandomDeviceAddrReqParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetTbCrtRndmDevAddrResParamsFromBuffer
(
    smTbCreateRandomDeviceAddrResParams_t*  pTbCreateRandomDeviceAddrResParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetBuffFromTbCreateRndmDevAddrResParams
(
    smTbCreateRandomDeviceAddrResParams_t*  pTbCreateRandomDeviceAddrResParams,
    uint8_t**                               ppBuffer
);

void fsciBleSmGetTbCheckResolvablePrivateAddrReqParamsFromBuffer
(
    smTbCheckResolvablePrivateAddrReqParams_t*  pTbCheckResolvablePrivateAddrReqParams,
    uint8_t**                                   ppBuffer
);

void fsciBleSmGetBufferFromTbCheckResolvablePrivateAddrReqParams
(
    smTbCheckResolvablePrivateAddrReqParams_t*  pTbCheckResolvablePrivateAddrReqParams,
    uint8_t**                                   ppBuffer
);

smTbSignDataReqParams_t* fsciBleSmAllocTbSignDataReqParamsForBuffer
(
    uint8_t* pBuffer
);

void fsciBleSmGetTbSignDataReqParamsFromBuffer
(
    smTbSignDataReqParams_t*    pTbSignDataReqParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetBufferFromTbSignDataReqParams
(
    smTbSignDataReqParams_t*    pTbSignDataReqParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetTbSignDataResParamsFromBuffer
(
    smTbSignDataResParams_t*    pTbSignDataResParams,
    uint8_t**                   ppBuffer
);

void fsciBleSmGetBuffFromTbSignDataResParams
(
    smTbSignDataResParams_t*    pTbSignDataResParams,
    uint8_t**                   ppBuffer
);

smTbVerifyDataSignatureReqParams_t* fsciBleSmAllocTbVerifyDataSignatureReqParamsForBuffer
(
    uint8_t* pBuffer
);

void fsciBleSmGetTbVerifyDataSignatureReqParamsFromBuffer
(
    smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams,
    uint8_t**                           ppBuffer
);

void fsciBleSmGetBufferFromTbVerifyDataSignatureReqParams
(
    smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams,
    uint8_t**                           ppBuffer
);

#if (gBLE42_d == TRUE)
void fsciBleSmGetLeScOobDataRequestReplyParamsFromBuffer
(
    smLeScOobDataParams_t* pLeScOobDataRequestReplyReqParams,
    uint8_t**              ppBuffer
);

void fsciBleSmGetBufferFromCmdLeScOobDataRequestReplyParams
(
    smLeScOobDataParams_t* pLeScOobDataRequestReplyReqParams,
    uint8_t**              ppBuffer
);
#endif /* (gBLE42_d == TRUE) */

void fsciBleSmGetSetMinPairingSecurityPropertiesParamsFromBuffer
(
    smSetMinPairingSecurityPropertiesParams_t*  pSetMinPairingSecurityPropertiesParams,
    uint8_t**                                   ppBuffer
);

void fsciBleSmGetBufferFromSetMinPairingSecurityPropertiesParams
(
    smSetMinPairingSecurityPropertiesParams_t*  pSetMinPairingSecurityPropertiesParams,
    uint8_t**                                   ppBuffer
);

#ifdef __cplusplus
}
#endif

#endif /* FSCI_BLE_SM_TYPES_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
