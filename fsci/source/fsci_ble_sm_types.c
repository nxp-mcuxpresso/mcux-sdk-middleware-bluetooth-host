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

#include "fsci_ble_sm_types.h"


#if gFsciIncluded_c && gFsciBleSmLayerEnabled_d

/************************************************************************************
*************************************************************************************
* Private constants & macros
*************************************************************************************
************************************************************************************/

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

void fsciBleSmGetAuthReqParamsFromBuffer(smAuthReqParams_t* pAuthReqParams, uint8_t** ppBuffer)
{
    /* Read smAuthReqParams_t fields from buffer */ 
    fsciBleGetEnumValueFromBuffer(pAuthReqParams->bondingFlags, *ppBuffer, smpAuthReqBondingFlags_t);
    fsciBleGetEnumValueFromBuffer(pAuthReqParams->mitm, *ppBuffer, smpAuthReqMitm_t);
    fsciBleGetEnumValueFromBuffer(pAuthReqParams->sc, *ppBuffer, smpAuthReqSc_t);
    fsciBleGetEnumValueFromBuffer(pAuthReqParams->keypress, *ppBuffer, smpAuthReqKeypress_t);
}


void fsciBleSmGetBufferFromAuthReqParams(smAuthReqParams_t* pAuthReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smAuthReqParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pAuthReqParams->bondingFlags, *ppBuffer, smpAuthReqBondingFlags_t);
    fsciBleGetBufferFromEnumValue(pAuthReqParams->mitm, *ppBuffer, smpAuthReqMitm_t);
    fsciBleGetBufferFromEnumValue(pAuthReqParams->sc, *ppBuffer, smpAuthReqSc_t);
    fsciBleGetBufferFromEnumValue(pAuthReqParams->keypress, *ppBuffer, smpAuthReqKeypress_t);  
}
    

void fsciBleSmGetKeyDistParamsFromBuffer(smKeyDistParams_t* pKeyDistParams, uint8_t** ppBuffer)
{
    /* Read smKeyDistParams_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pKeyDistParams->params.enckey, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pKeyDistParams->params.idKey, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pKeyDistParams->params.sign, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pKeyDistParams->params.LinkKey, *ppBuffer);    
    fsciBleGetUint8ValueFromBuffer(pKeyDistParams->params.reserved, *ppBuffer);
}


void fsciBleSmGetBufferFromKeyDistParams(smKeyDistParams_t* pKeyDistParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smKeyDistParams_t fields */ 
    fsciBleGetBufferFromBoolValue(pKeyDistParams->params.enckey, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pKeyDistParams->params.idKey, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pKeyDistParams->params.sign, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pKeyDistParams->params.LinkKey, *ppBuffer);   
    fsciBleGetBufferFromUint8Value(pKeyDistParams->params.reserved, *ppBuffer);
}


void fsciBleSmGetKeyDistPayloadFromBuffer(smKeyDistPayload_t* pKeyDistPayload, uint8_t** ppBuffer)
{
    /* Read smKeyDistPayload_t fields from buffer */
    fsciBleGetArrayFromBuffer(pKeyDistPayload->ltk, *ppBuffer, gSmpLtkSize_c);
    fsciBleGetIrkFromBuffer(pKeyDistPayload->irk, *ppBuffer);
    fsciBleGetCsrkFromBuffer(pKeyDistPayload->csrk, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pKeyDistPayload->ediv, *ppBuffer);
    fsciBleGetArrayFromBuffer(pKeyDistPayload->rand, *ppBuffer, gSmpLlEncryptionRandSize_c);   
    fsciBleGetAddressFromBuffer(pKeyDistPayload->bdAddr, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pKeyDistPayload->bdAddrType, *ppBuffer, bleAddressType_t);
}


void fsciBleSmGetBuffFromKeyDistPayload(smKeyDistPayload_t* pKeyDistPayload, uint8_t** ppBuffer)
{
    /* Write in buffer all the smKeyDistPayload_t fields */ 
    fsciBleGetBufferFromArray(pKeyDistPayload->ltk, *ppBuffer, gSmpLtkSize_c);
    fsciBleGetBufferFromIrk(pKeyDistPayload->irk, *ppBuffer);
    fsciBleGetBufferFromCsrk(pKeyDistPayload->csrk, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pKeyDistPayload->ediv, *ppBuffer);
    fsciBleGetBufferFromArray(pKeyDistPayload->rand, *ppBuffer, gSmpLlEncryptionRandSize_c); 
    fsciBleGetBufferFromAddress(pKeyDistPayload->bdAddr, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pKeyDistPayload->bdAddrType, *ppBuffer, bleAddressType_t);
}
    

void fsciBleSmGetPairingParamsFromBuffer(smPairingParams_t* pPairingParams, uint8_t** ppBuffer)
{
    /* Read smPairingParams_t fields from buffer */ 
    fsciBleGetEnumValueFromBuffer(pPairingParams->ioCap, *ppBuffer, smpPairingIoCapability_t);
    fsciBleGetEnumValueFromBuffer(pPairingParams->oobDataFlag, *ppBuffer, smpPairingOobDataFlag_t);
    fsciBleSmGetAuthReqParamsFromBuffer(&pPairingParams->authReq, ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pPairingParams->maxEncKeySize, *ppBuffer);
    fsciBleSmGetKeyDistParamsFromBuffer(&pPairingParams->initiatorKeyDist, ppBuffer);
    fsciBleSmGetKeyDistParamsFromBuffer(&pPairingParams->responderKeyDist, ppBuffer);
}


void fsciBleSmGetBufferFromPairingParams(smPairingParams_t* pPairingParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPairingParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pPairingParams->ioCap, *ppBuffer, smpPairingIoCapability_t);
    fsciBleGetBufferFromEnumValue(pPairingParams->oobDataFlag, *ppBuffer, smpPairingOobDataFlag_t);
    fsciBleSmGetBufferFromAuthReqParams(&pPairingParams->authReq, ppBuffer);
    fsciBleGetBufferFromUint8Value(pPairingParams->maxEncKeySize, *ppBuffer);
    fsciBleSmGetBufferFromKeyDistParams(&pPairingParams->initiatorKeyDist, ppBuffer);
    fsciBleSmGetBufferFromKeyDistParams(&pPairingParams->responderKeyDist, ppBuffer);
}


uint16_t fsciBleSmGetPasskeyReqReplyParamsBufferSize(smPasskeyReqReplyParams_t* pPasskeyReqReplyParams)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = sizeof(smKeyType_t);
    
    /* Get the variable size for the needed buffer */
    switch(pPasskeyReqReplyParams->passKeyType)
    {
        case smKeyTypePasskey_c:
            {
                /* Passkey */
                bufferSize += sizeof(uint32_t);
            }
            break;
          
        case smKeyTypeOob_c: 
            {
                /* OOB */
                bufferSize += gSmpMaxKeySize_c;
            }
            break;
       
        default:
            break;
    }
    
    /* Return the needed buffer size */
    return bufferSize;
}


void fsciBleSmGetPasskeyReqReplParamsFromBuffer(smPasskeyReqReplyParams_t* pPasskeyReqReplyParams, uint8_t** ppBuffer)
{
    /* Read smPasskeyReqReplyParams_t fields from buffer */ 
    fsciBleGetEnumValueFromBuffer(pPasskeyReqReplyParams->passKeyType, *ppBuffer, smKeyType_t);
    
    switch(pPasskeyReqReplyParams->passKeyType)
    {
        case smKeyTypePasskey_c:
            {
                /* Passkey */
                fsciBleGetArrayFromBuffer(pPasskeyReqReplyParams->key, *ppBuffer, sizeof(uint32_t));
            }
            break;
          
        case smKeyTypeOob_c: 
            {
                /* OOB */
                fsciBleGetArrayFromBuffer(pPasskeyReqReplyParams->key, *ppBuffer, gSmpMaxKeySize_c);
            }
            break;
       
        default:
            break;
    }    
}


void fsciBleSmGetBufferFromPasskeyReqReplyParams(smPasskeyReqReplyParams_t* pPasskeyReqReplyParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPasskeyReqReplyParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pPasskeyReqReplyParams->passKeyType, *ppBuffer, smKeyType_t);
    
    switch(pPasskeyReqReplyParams->passKeyType)
    {
        case smKeyTypePasskey_c:
            {
                /* Passkey */
                fsciBleGetBufferFromArray(pPasskeyReqReplyParams->key, *ppBuffer, sizeof(uint32_t));
            }
            break;
          
        case smKeyTypeOob_c: 
            {
                /* OOB */
                fsciBleGetBufferFromArray(pPasskeyReqReplyParams->key, *ppBuffer, gSmpMaxKeySize_c);
            }
            break;
       
        default:
            break;
    }
}


void fsciBleSmGetPairingKeysetRequestReplyParamsFromBuffer(smPairingKeysetRequestReplyParams_t* pPairingKeysetRequestReplyParams, uint8_t** ppBuffer)
{
    /* Read smPairingKeysetRequestReplyParams_t fields from buffer */
    fsciBleSmGetKeyDistPayloadFromBuffer(&pPairingKeysetRequestReplyParams->keyDistPayload, ppBuffer);
    fsciBleSmGetKeyDistParamsFromBuffer(&pPairingKeysetRequestReplyParams->sentKeys, ppBuffer);
}


void fsciBleSmGetBuffInPairKeysetReqReplyParams(smPairingKeysetRequestReplyParams_t* pPairingKeysetRequestReplyParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPairingKeysetRequestReplyParams_t fields */ 
    fsciBleSmGetBuffFromKeyDistPayload(&pPairingKeysetRequestReplyParams->keyDistPayload, ppBuffer);
    fsciBleSmGetBufferFromKeyDistParams(&pPairingKeysetRequestReplyParams->sentKeys, ppBuffer);   
}


void fsciBleSmGetPairingKeysetReqParamsFromBuffer(smPairingKeysetReqParams_t* pPairingKeysetReqParams, uint8_t** ppBuffer)
{
    /* Read smPairingKeysetReqParams_t fields from buffer */
    fsciBleSmGetKeyDistParamsFromBuffer(&pPairingKeysetReqParams->requestedKeys, ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pPairingKeysetReqParams->encKeySize, *ppBuffer);
}


void fsciBleSmGetBuffFromPairKeysetReqParams(smPairingKeysetReqParams_t* pPairingKeysetReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPairingKeysetReqParams_t fields */ 
    fsciBleSmGetBufferFromKeyDistParams(&pPairingKeysetReqParams->requestedKeys, ppBuffer);  
    fsciBleGetBufferFromUint8Value(pPairingKeysetReqParams->encKeySize, *ppBuffer);
}


void fsciBleSmGetPairingKeysetReceivedParamsFromBuffer(smPairingKeysetReceivedParams_t* pPairingKeysetReceivedParams, uint8_t** ppBuffer)
{
    /* Read smPairingKeysetReceivedParams_t fields from buffer */
    fsciBleSmGetKeyDistPayloadFromBuffer(&pPairingKeysetReceivedParams->keyDistPayload, ppBuffer);
    fsciBleSmGetKeyDistParamsFromBuffer(&pPairingKeysetReceivedParams->receivedKeys, ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pPairingKeysetReceivedParams->encKeySize, *ppBuffer);
}


void fsciBleSmGetBufferFromPairingKeysetReceivedParams(smPairingKeysetReceivedParams_t* pPairingKeysetReceivedParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPairingKeysetReceivedParams_t fields */ 
    fsciBleSmGetBuffFromKeyDistPayload(&pPairingKeysetReceivedParams->keyDistPayload, ppBuffer);
    fsciBleSmGetBufferFromKeyDistParams(&pPairingKeysetReceivedParams->receivedKeys, ppBuffer);  
    fsciBleGetBufferFromUint8Value(pPairingKeysetReceivedParams->encKeySize, *ppBuffer);
}


void fsciBleSmGetPairingCompleteParamsFromBuffer(smPairingCompleteParams_t* pPairingCompleteParams, uint8_t** ppBuffer)
{
    /* Read smPairingCompleteParams_t fields from buffer */
    fsciBleGetUint8ValueFromBuffer(pPairingCompleteParams->encKeySize, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pPairingCompleteParams->mitmProtection, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pPairingCompleteParams->bonding, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pPairingCompleteParams->leSc, *ppBuffer);
    fsciBleGetArrayFromBuffer(pPairingCompleteParams->leScLtk, *ppBuffer, gSmpLtkSize_c);    
}


void fsciBleSmGetBufferFromPairingCompleteParams(smPairingCompleteParams_t* pPairingCompleteParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smPairingCompleteParams_t fields */ 
    fsciBleGetBufferFromUint8Value(pPairingCompleteParams->encKeySize, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pPairingCompleteParams->mitmProtection, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pPairingCompleteParams->bonding, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pPairingCompleteParams->leSc, *ppBuffer);
    fsciBleGetBufferFromArray(pPairingCompleteParams->leScLtk, *ppBuffer, gSmpLtkSize_c);
}


void fsciBleSmGetLlStartEncryptionParamsFromBuffer(smLlStartEncryptionParams_t* pLlStartEncryptionParams, uint8_t** ppBuffer)
{
    /* Read smLlStartEncryptionParams_t fields from buffer */
    fsciBleGetArrayFromBuffer(pLlStartEncryptionParams->randomNumber, *ppBuffer, gSmpLlEncryptionRandSize_c);    
    fsciBleGetUint16ValueFromBuffer(pLlStartEncryptionParams->encryptedDiversifier, *ppBuffer);
    fsciBleGetArrayFromBuffer(pLlStartEncryptionParams->longTermKey, *ppBuffer, gSmpLtkSize_c);
}


void fsciBleSmGetBufferFromLlStartEncryptionParams(smLlStartEncryptionParams_t* pLlStartEncryptionParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlStartEncryptionParams_t fields */ 
    fsciBleGetBufferFromArray(pLlStartEncryptionParams->randomNumber, *ppBuffer, gSmpLlEncryptionRandSize_c);    
    fsciBleGetBufferFromUint16Value(pLlStartEncryptionParams->encryptedDiversifier, *ppBuffer);
    fsciBleGetBufferFromArray(pLlStartEncryptionParams->longTermKey, *ppBuffer, gSmpLtkSize_c);
}
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
void fsciBleSmGetLlEncryptReqParamsFromBuffer(smLlEncryptReqParams_t* pLlEncryptReqParams, uint8_t** ppBuffer)
{
    /* Read smLlEncryptReqParams_t fields from buffer */
    fsciBleGetArrayFromBuffer(pLlEncryptReqParams->key, *ppBuffer, gSmpLlEncryptBlockSize_c);    
    fsciBleGetArrayFromBuffer(pLlEncryptReqParams->plaintextData, *ppBuffer, gSmpLlEncryptBlockSize_c);
}


void fsciBleSmGetBufferFromLlEncryptReqParams(smLlEncryptReqParams_t* pLlEncryptReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlEncryptReqParams_t fields */ 
    fsciBleGetBufferFromArray(pLlEncryptReqParams->key, *ppBuffer, gSmpLlEncryptBlockSize_c);    
    fsciBleGetBufferFromArray(pLlEncryptReqParams->plaintextData, *ppBuffer, gSmpLlEncryptBlockSize_c);
}
#endif

void fsciBleSmGetLlLtkRequestParamsFromBuffer(smLlLtkRequestParams_t* pLlLtkRequestParams, uint8_t** ppBuffer)
{
    /* Read smLlLtkRequestParams_t fields from buffer */
    fsciBleGetArrayFromBuffer(pLlLtkRequestParams->randomNumber, *ppBuffer, gSmpLlEncryptionRandSize_c);    
    fsciBleGetUint16ValueFromBuffer(pLlLtkRequestParams->encryptedDiversifier, *ppBuffer);
}


void fsciBleSmGetBufferFromLlLtkRequestParams(smLlLtkRequestParams_t* pLlLtkRequestParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlLtkRequestParams_t fields */ 
    fsciBleGetBufferFromArray(pLlLtkRequestParams->randomNumber, *ppBuffer, gSmpLlEncryptionRandSize_c);    
    fsciBleGetBufferFromUint16Value(pLlLtkRequestParams->encryptedDiversifier, *ppBuffer);
}


void fsciBleSmGetLlEncryptionStatusParamsFromBuffer(smLlEncryptionStatusParams_t* pLlEncryptionStatusParams, uint8_t** ppBuffer)
{
    /* Read smLlEncryptionStatusParams_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pLlEncryptionStatusParams->llStatus, *ppBuffer, bleResult_t);    
    fsciBleGetEnumValueFromBuffer(pLlEncryptionStatusParams->encryptionState, *ppBuffer, smLlEncryptionState_t);
    fsciBleGetEnumValueFromBuffer(pLlEncryptionStatusParams->encKeyType, *ppBuffer, smLlEncKeyType_t);
}


void fsciBleSmGetBuffFromLlEncrStatusParams(smLlEncryptionStatusParams_t* pLlEncryptionStatusParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlEncryptionStatusParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pLlEncryptionStatusParams->llStatus, *ppBuffer, bleResult_t);    
    fsciBleGetBufferFromEnumValue(pLlEncryptionStatusParams->encryptionState, *ppBuffer, smLlEncryptionState_t);
    fsciBleGetBufferFromEnumValue(pLlEncryptionStatusParams->encKeyType, *ppBuffer, smLlEncKeyType_t);
}

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
void fsciBleSmGetLlEncryptResParamsFromBuffer(smLlEncryptResParams_t* pLlEncryptResParams, uint8_t** ppBuffer)
{
    /* Read smLlEncryptResParams_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pLlEncryptResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetArrayFromBuffer(pLlEncryptResParams->encryptedData, *ppBuffer, gSmpLlEncryptBlockSize_c);
}


void fsciBleSmGetBuffFromLlEncrResParams(smLlEncryptResParams_t* pLlEncryptResParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlEncryptResParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pLlEncryptResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetBufferFromArray(pLlEncryptResParams->encryptedData, *ppBuffer, gSmpLlEncryptBlockSize_c);
}
#endif

#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
void fsciBleSmGetLlRandResParamsFromBuffer(smLlRandResParams_t* pLlRandResParams, uint8_t** ppBuffer)
{
    /* Read smLlRandResParams_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pLlRandResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetArrayFromBuffer(pLlRandResParams->randomNumber, *ppBuffer, gSmpLlRandSize_c);
}


void fsciBleSmGetBufferFromLlRandResParams(smLlRandResParams_t* pLlRandResParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLlRandResParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pLlRandResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetBufferFromArray(pLlRandResParams->randomNumber, *ppBuffer, gSmpLlRandSize_c);
}
#endif

smTbCreateRandomDeviceAddrReqParams_t* fsciBleSmAllocTbCreateRandomDeviceAddrReqParamsForBuffer(uint8_t* pBuffer)
{
    smBleRandomDevAddType_t                 addrType;
    bool_t                                  bRandIncluded   = FALSE;
    uint8_t                                 dataSize        = sizeof(smTbCreateRandomDeviceAddrReqParams_t);
    smTbCreateRandomDeviceAddrReqParams_t*  pTbCreateRandomDeviceAddrReqParams;
    
    /* Get address type from buffer */
    fsciBleGetEnumValueFromBuffer(addrType, pBuffer, smBleRandomDevAddType_t);
    
    if(smBleResolvablePrivate_Addr_c == addrType)
    {
        /* IRK is present */
        dataSize += gSmpIrkSize_c;
        
        /* Go to random part information in buffer */
        pBuffer += gSmpIrkSize_c;
        
        /* Verify if random part is included or not */
        fsciBleGetBoolValueFromBuffer(bRandIncluded, pBuffer);
        
        if(TRUE == bRandIncluded)
        {
            /* Random part is included */
            dataSize += 3;
        }
    }
    
    /* Allocate buffer */
    pTbCreateRandomDeviceAddrReqParams = (smTbCreateRandomDeviceAddrReqParams_t*)MEM_BufferAlloc(dataSize);
    
    if(NULL == pTbCreateRandomDeviceAddrReqParams)
    {
        /* No memory */
        return NULL;
    }
    
    /* Set pointers in smTbCreateRandomDeviceAddrReqParams_t structure to NULL */
    pTbCreateRandomDeviceAddrReqParams->pIrk    = NULL;
    pTbCreateRandomDeviceAddrReqParams->pRand   = NULL;
    
    if(smBleResolvablePrivate_Addr_c == addrType)
    {
        /* Set IRK pointer */
        pTbCreateRandomDeviceAddrReqParams->pIrk = (uint8_t*)pTbCreateRandomDeviceAddrReqParams + sizeof(smTbCreateRandomDeviceAddrReqParams_t);
        
        if(TRUE == bRandIncluded)
        {
            /* Set random part pointer */
            pTbCreateRandomDeviceAddrReqParams->pRand = (uint8_t*)pTbCreateRandomDeviceAddrReqParams->pIrk + gSmpIrkSize_c;
        }
    }
    
    return pTbCreateRandomDeviceAddrReqParams;
}


uint8_t fsciBleSmGetTbCreateRandomDeviceAddrReqParamsBufferSize(smTbCreateRandomDeviceAddrReqParams_t* pTbCreateRandomDeviceAddrReqParams)
{
    /* Get the constant size for the needed buffer */
    uint8_t bufferSize = sizeof(smBleRandomDevAddType_t);
    
    /* Get the variable size for the needed buffer */
    if(smBleResolvablePrivate_Addr_c == pTbCreateRandomDeviceAddrReqParams->addrType)
    {
        /* IRK is present */
        bufferSize += gSmpIrkSize_c;
        
        /* bRandIncluded */
        bufferSize += sizeof(bool_t);
        
        if(NULL != pTbCreateRandomDeviceAddrReqParams->pRand)
        {
            /* Random part is present */
            bufferSize += 3;
        }
    }
    
    /* Return the size needed for the buffer */
    return bufferSize;
}

    
void fsciBleSmGetTbCreateRndmDevAddrReqParamsFromBuffer(smTbCreateRandomDeviceAddrReqParams_t* pTbCreateRandomDeviceAddrReqParams, uint8_t** ppBuffer)
{
    /* Read smTbCreateRandomDeviceAddrReqParams_t fields from buffer */
    
    /* Read address type from buffer */
    fsciBleGetEnumValueFromBuffer(pTbCreateRandomDeviceAddrReqParams->addrType, *ppBuffer, smBleRandomDevAddType_t);
    
    if(smBleResolvablePrivate_Addr_c == pTbCreateRandomDeviceAddrReqParams->addrType)
    {
        bool_t bRandIncluded;
    
        /* Get IRK from buffer */
        fsciBleGetArrayFromBuffer(pTbCreateRandomDeviceAddrReqParams->pIrk, *ppBuffer, gSmpIrkSize_c);  
        
        /* Verify is random part is present */
        fsciBleGetBoolValueFromBuffer(bRandIncluded, *ppBuffer);
        
        if(TRUE == bRandIncluded)
        {
            /* Random part is present */
            fsciBleGetArrayFromBuffer(pTbCreateRandomDeviceAddrReqParams->pRand, *ppBuffer, 3);
        }
    }
}


void fsciBleSmGetBufferFromTbCreateRandomDeviceAddrReqParams(smTbCreateRandomDeviceAddrReqParams_t* pTbCreateRandomDeviceAddrReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbCreateRandomDeviceAddrReqParams_t fields */ 
    
    /* Set address type in buffer */
    fsciBleGetBufferFromEnumValue(pTbCreateRandomDeviceAddrReqParams->addrType, *ppBuffer, smBleRandomDevAddType_t);
    
    if(smBleResolvablePrivate_Addr_c == pTbCreateRandomDeviceAddrReqParams->addrType)
    {
        bool_t bRandIncluded = (NULL == pTbCreateRandomDeviceAddrReqParams->pRand) ? FALSE : TRUE;
        
        /* Set IRK in buffer */
        fsciBleGetBufferFromArray(pTbCreateRandomDeviceAddrReqParams->pIrk, *ppBuffer, gSmpIrkSize_c);
        
        /* Specify if random part is NULL or not */
        fsciBleGetBufferFromBoolValue(bRandIncluded, *ppBuffer);
    
        if(TRUE == bRandIncluded)
        {
            /* Random part is not NULL and must be set in buffer */
            fsciBleGetBufferFromArray(pTbCreateRandomDeviceAddrReqParams->pRand, *ppBuffer, 3);
        }
    }
}


void fsciBleSmGetTbCrtRndmDevAddrResParamsFromBuffer(smTbCreateRandomDeviceAddrResParams_t* pTbCreateRandomDeviceAddrResParams, uint8_t** ppBuffer)
{
    /* Read smTbCreateRandomDeviceAddrResParams_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pTbCreateRandomDeviceAddrResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetEnumValueFromBuffer(pTbCreateRandomDeviceAddrResParams->addrType, *ppBuffer, smBleRandomDevAddType_t);  
    fsciBleGetAddressFromBuffer(pTbCreateRandomDeviceAddrResParams->addr, *ppBuffer);
}


void fsciBleSmGetBuffFromTbCreateRndmDevAddrResParams(smTbCreateRandomDeviceAddrResParams_t* pTbCreateRandomDeviceAddrResParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbCreateRandomDeviceAddrResParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pTbCreateRandomDeviceAddrResParams->status, *ppBuffer, bleResult_t);
    fsciBleGetBufferFromEnumValue(pTbCreateRandomDeviceAddrResParams->addrType, *ppBuffer, smBleRandomDevAddType_t);  
    fsciBleGetBufferFromAddress(pTbCreateRandomDeviceAddrResParams->addr, *ppBuffer);
}


void fsciBleSmGetTbCheckResolvablePrivateAddrReqParamsFromBuffer(smTbCheckResolvablePrivateAddrReqParams_t* pTbCheckResolvablePrivateAddrReqParams, uint8_t** ppBuffer)
{
    /* Read smTbCheckResolvablePrivateAddrReqParams_t fields from buffer */
    fsciBleGetIrkFromBuffer(pTbCheckResolvablePrivateAddrReqParams->irk, *ppBuffer);  
    fsciBleGetAddressFromBuffer(pTbCheckResolvablePrivateAddrReqParams->addr, *ppBuffer);
}


void fsciBleSmGetBufferFromTbCheckResolvablePrivateAddrReqParams(smTbCheckResolvablePrivateAddrReqParams_t* pTbCheckResolvablePrivateAddrReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbCheckResolvablePrivateAddrReqParams_t fields */ 
    fsciBleGetBufferFromIrk(pTbCheckResolvablePrivateAddrReqParams->irk, *ppBuffer);  
    fsciBleGetBufferFromAddress(pTbCheckResolvablePrivateAddrReqParams->addr, *ppBuffer);
}


smTbSignDataReqParams_t* fsciBleSmAllocTbSignDataReqParamsForBuffer(uint8_t* pBuffer)
{
    uint16_t                    dataLength;
    smTbSignDataReqParams_t*    pTbSignDataReqParams;
    
    /* Go to data length in buffer */
    pBuffer += gSmpCsrkSize_c;
    
    /* Get data length from buffer */
    fsciBleGetUint16ValueFromBuffer(dataLength, pBuffer);
    
    /* Allocate buffer */
    pTbSignDataReqParams = (smTbSignDataReqParams_t*)MEM_BufferAlloc(sizeof(smTbSignDataReqParams_t) + dataLength);
    
    if(NULL == pTbSignDataReqParams)
    {
        /* No memory */
        return NULL;
    }
    
    /* Set pointers in smTbSignDataReqParams_t structure */
    if(0 == dataLength)
    {
        pTbSignDataReqParams->pData = NULL;
    }
    else
    {
        pTbSignDataReqParams->pData = (uint8_t*)pTbSignDataReqParams + sizeof(smTbSignDataReqParams_t);
    }
    
    return pTbSignDataReqParams;
}


void fsciBleSmGetTbSignDataReqParamsFromBuffer(smTbSignDataReqParams_t* pTbSignDataReqParams, uint8_t** ppBuffer)
{
    /* Read smTbSignDataReqParams_t fields from buffer */
    fsciBleGetCsrkFromBuffer(pTbSignDataReqParams->csrk, *ppBuffer);  
    fsciBleGetUint16ValueFromBuffer(pTbSignDataReqParams->dataLength, *ppBuffer);
    if(0 < pTbSignDataReqParams->dataLength)
    {
        fsciBleGetArrayFromBuffer(pTbSignDataReqParams->pData, *ppBuffer, pTbSignDataReqParams->dataLength);
    }
}


void fsciBleSmGetBufferFromTbSignDataReqParams(smTbSignDataReqParams_t* pTbSignDataReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbSignDataReqParams_t fields */ 
    fsciBleGetBufferFromCsrk(pTbSignDataReqParams->csrk, *ppBuffer);  
    fsciBleGetBufferFromUint16Value(pTbSignDataReqParams->dataLength, *ppBuffer);
    if(0 < pTbSignDataReqParams->dataLength)
    {
        fsciBleGetBufferFromArray(pTbSignDataReqParams->pData, *ppBuffer, pTbSignDataReqParams->dataLength);
    }
}


void fsciBleSmGetTbSignDataResParamsFromBuffer(smTbSignDataResParams_t* pTbSignDataResParams, uint8_t** ppBuffer)
{
    /* Read smTbSignDataResParams_t fields from buffer */
    fsciBleGetEnumValueFromBuffer(pTbSignDataResParams->status, *ppBuffer, bleResult_t);  
    fsciBleGetArrayFromBuffer(pTbSignDataResParams->signature, *ppBuffer, gSmpAuthSignatureLength_c);
}


void fsciBleSmGetBuffFromTbSignDataResParams(smTbSignDataResParams_t* pTbSignDataResParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbSignDataResParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pTbSignDataResParams->status, *ppBuffer, bleResult_t);  
    fsciBleGetBufferFromArray(pTbSignDataResParams->signature, *ppBuffer, gSmpAuthSignatureLength_c);
}

smTbVerifyDataSignatureReqParams_t* fsciBleSmAllocTbVerifyDataSignatureReqParamsForBuffer(uint8_t* pBuffer)
{
    uint16_t                            dataLength;
    smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams;
    
    /* Go to data length in buffer */
    pBuffer += gSmpCsrkSize_c;
    
    /* Get data length from buffer */
    fsciBleGetUint16ValueFromBuffer(dataLength, pBuffer);
    
    /* Allocate buffer */
    pTbVerifyDataSignatureReqParams = (smTbVerifyDataSignatureReqParams_t*)MEM_BufferAlloc(sizeof(smTbVerifyDataSignatureReqParams_t) + dataLength);
    
    if(NULL == pTbVerifyDataSignatureReqParams)
    {
        /* No memory */
        return NULL;
    }
    
    /* Set pointers in smTbSignDataReqParams_t structure */
    if(0 == dataLength)
    {
        pTbVerifyDataSignatureReqParams->pData = NULL;
    }
    else
    {
        pTbVerifyDataSignatureReqParams->pData = (uint8_t*)pTbVerifyDataSignatureReqParams + sizeof(smTbVerifyDataSignatureReqParams_t);
    }
    
    return pTbVerifyDataSignatureReqParams;
}


void fsciBleSmGetTbVerifyDataSignatureReqParamsFromBuffer(smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams, uint8_t** ppBuffer)
{
    /* Read smTbVerifyDataSignatureReqParams_t fields from buffer */
    fsciBleGetCsrkFromBuffer(pTbVerifyDataSignatureReqParams->csrk, *ppBuffer); 
    fsciBleGetUint16ValueFromBuffer(pTbVerifyDataSignatureReqParams->dataLength, *ppBuffer);
    if(0 < pTbVerifyDataSignatureReqParams->dataLength)
    {
        fsciBleGetArrayFromBuffer(pTbVerifyDataSignatureReqParams->pData, *ppBuffer, pTbVerifyDataSignatureReqParams->dataLength);  
    }
    fsciBleGetArrayFromBuffer(pTbVerifyDataSignatureReqParams->signature, *ppBuffer, gSmpAuthSignatureLength_c);
}


void fsciBleSmGetBufferFromTbVerifyDataSignatureReqParams(smTbVerifyDataSignatureReqParams_t* pTbVerifyDataSignatureReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smTbVerifyDataSignatureReqParams_t fields */ 
    fsciBleGetBufferFromCsrk(pTbVerifyDataSignatureReqParams->csrk, *ppBuffer); 
    fsciBleGetBufferFromUint16Value(pTbVerifyDataSignatureReqParams->dataLength, *ppBuffer);
    if(0 < pTbVerifyDataSignatureReqParams->dataLength)
    {
        fsciBleGetBufferFromArray(pTbVerifyDataSignatureReqParams->pData, *ppBuffer, pTbVerifyDataSignatureReqParams->dataLength);  
    }
    fsciBleGetBufferFromArray(pTbVerifyDataSignatureReqParams->signature, *ppBuffer, gSmpAuthSignatureLength_c);
}



void fsciBleSmGetLeScOobDataRequestReplyParamsFromBuffer(smLeScOobDataParams_t* pLeScOobDataRequestReplyReqParams, uint8_t** ppBuffer)
{
    /* Read smLeScOobDataParams_t fields from buffer */
    fsciBleGetArrayFromBuffer(pLeScOobDataRequestReplyReqParams->rValue, *ppBuffer, gSmpLeScRandomValueSize_c);
    fsciBleGetArrayFromBuffer(pLeScOobDataRequestReplyReqParams->crValue, *ppBuffer, gSmpLeScRandomConfirmValueSize_c);
    fsciBleGetAddressFromBuffer(pLeScOobDataRequestReplyReqParams->addr, *ppBuffer);
}


void fsciBleSmGetBufferFromCmdLeScOobDataRequestReplyParams(smLeScOobDataParams_t* pLeScOobDataRequestReplyReqParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smLeScOobDataParams_t fields */
    fsciBleGetBufferFromArray(pLeScOobDataRequestReplyReqParams->rValue, *ppBuffer, gSmpLeScRandomValueSize_c);
    fsciBleGetBufferFromArray(pLeScOobDataRequestReplyReqParams->crValue, *ppBuffer, gSmpLeScRandomConfirmValueSize_c);
    fsciBleGetBufferFromAddress(pLeScOobDataRequestReplyReqParams->addr, *ppBuffer);
}

void fsciBleSmGetSetMinPairingSecurityPropertiesParamsFromBuffer(smSetMinPairingSecurityPropertiesParams_t* pSetMinPairingSecurityPropertiesParams, uint8_t** ppBuffer)
{
    /* Read smSetMinParingSecurityPropertiesParams_t fields from buffer */
    fsciBleGetBoolValueFromBuffer(pSetMinPairingSecurityPropertiesParams->mitmProtection, *ppBuffer);
    fsciBleGetBoolValueFromBuffer(pSetMinPairingSecurityPropertiesParams->leSc, *ppBuffer);
    fsciBleGetUint8ValueFromBuffer(pSetMinPairingSecurityPropertiesParams->minEncKeySize, *ppBuffer);
}

void fsciBleSmGetBufferFromSetMinPairingSecurityPropertiesParams(smSetMinPairingSecurityPropertiesParams_t* pSetMinPairingSecurityPropertiesParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the smSetMinParingSecurityPropertiesParams_t fields */ 
    fsciBleGetBufferFromBoolValue(pSetMinPairingSecurityPropertiesParams->mitmProtection, *ppBuffer);
    fsciBleGetBufferFromBoolValue(pSetMinPairingSecurityPropertiesParams->leSc, *ppBuffer);
    fsciBleGetBufferFromUint8Value(pSetMinPairingSecurityPropertiesParams->minEncKeySize, *ppBuffer);
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c && gFsciBleSmLayerEnabled_d */


/*! *********************************************************************************
* @}
********************************************************************************** */
