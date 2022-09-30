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

#include "fsci_ble_att_types.h"


#if gFsciIncluded_c && (gFsciBleAttLayerEnabled_d || gFsciBleGattDbAttLayerEnabled_d)

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

void fsciBleAttGetErrorResponseParamsFromBuffer(attErrorResponseParams_t* pErrorResponseParams, uint8_t** ppBuffer)
{
    /* Read attErrorResponseParams_t fields from buffer */ 
    fsciBleGetEnumValueFromBuffer(pErrorResponseParams->requestOpcodeInError, *ppBuffer, attOpcode_t);
    fsciBleGetUint16ValueFromBuffer(pErrorResponseParams->attributeHandleInError, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pErrorResponseParams->errorCode, *ppBuffer, attErrorCode_t);
}


void fsciBleAttGetBufferFromErrorResponseParams(attErrorResponseParams_t* pErrorResponseParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attErrorResponseParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pErrorResponseParams->requestOpcodeInError, *ppBuffer, attOpcode_t);
    fsciBleGetBufferFromUint16Value(pErrorResponseParams->attributeHandleInError, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pErrorResponseParams->errorCode, *ppBuffer, attErrorCode_t);
}


void fsciBleAttGetFindInformationRequestParamsFromBuffer(attFindInformationRequestParams_t* pFindInformationRequestParams, uint8_t** ppBuffer)
{
    /* Read attFindInformationRequestParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pFindInformationRequestParams->startingHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pFindInformationRequestParams->endingHandle, *ppBuffer);
}


void fsciBleAttGetBuffFromFindInfoRequestParams(attFindInformationRequestParams_t* pFindInformationRequestParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attFindInformationRequestParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pFindInformationRequestParams->startingHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pFindInformationRequestParams->endingHandle, *ppBuffer);
}


void fsciBleAttGetFindInfoHdlUuid16PairFromBuffer(attFindInfoHandleUuid16Pair_t* pFindInfoHandleUuid16Pair, uint8_t** ppBuffer)
{
    /* Read attFindInfoHandleUuid16Pair_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pFindInfoHandleUuid16Pair->handle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pFindInfoHandleUuid16Pair->uuid16, *ppBuffer);
}


void fsciBleAttGetBuffFromInfoHdlUuid16Pair(attFindInfoHandleUuid16Pair_t* pFindInfoHandleUuid16Pair, uint8_t** ppBuffer)
{
    /* Write in buffer all the attFindInfoHandleUuid16Pair_t fields */ 
    fsciBleGetBufferFromUint16Value(pFindInfoHandleUuid16Pair->handle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pFindInfoHandleUuid16Pair->uuid16, *ppBuffer);
}


void fsciBleAttGetFindInfoHdlUuid128PairFromBuffer(attFindInfoHandleUuid128Pair_t* pFindInfoHandleUuid128Pair, uint8_t** ppBuffer)
{
    /* Read attFindInfoHandleUuid128Pair_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pFindInfoHandleUuid128Pair->handle, *ppBuffer);
    fsciBleGetUint128ValueFromBuffer(pFindInfoHandleUuid128Pair->uuid128, *ppBuffer);
}


void fsciBleAttGetBuffFromFindInfoHdlUuid128Pair(attFindInfoHandleUuid128Pair_t* pFindInfoHandleUuid128Pair, uint8_t** ppBuffer)
{
    /* Write in buffer all the attFindInfoHandleUuid128Pair_t fields */ 
    fsciBleGetBufferFromUint16Value(pFindInfoHandleUuid128Pair->handle, *ppBuffer);
    fsciBleGetBufferFromUint128Value(pFindInfoHandleUuid128Pair->uuid128, *ppBuffer);
}


uint16_t fsciBleAttGetFindInformationResponseParamsBufferSize(attFindInformationResponseParams_t* pFindInformationResponseParams)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = sizeof(attUuidFormat_t) + sizeof(uint8_t);
    
    /* Get the variable size for the needed buffer */
    switch(pFindInformationResponseParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                bufferSize += pFindInformationResponseParams->handleUuidPairCount *
                              fsciBleAttGetFindInfoHandleUuid16PairBufferSize(&pFindInformationResponseParams->informationData.handleUuid16[0]);
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                bufferSize += pFindInformationResponseParams->handleUuidPairCount *
                              fsciBleAttGetFindInfoHandleUuid128PairBufferSize(&pFindInformationResponseParams->informationData.handleUuid128[0]);
            }
            break;
            
        default:
            break;
    }
    
    /* Return the needed buffer size */
    return bufferSize;
}
    

void fsciBleAttGetFindInfoResponseParamsFromBuffer(attFindInformationResponseParams_t* pFindInformationResponseParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Read attFindInformationResponseParams_t fields from buffer */ 
    fsciBleGetEnumValueFromBuffer(pFindInformationResponseParams->format, *ppBuffer, attUuidFormat_t);
    fsciBleGetUint8ValueFromBuffer(pFindInformationResponseParams->handleUuidPairCount, *ppBuffer);
    
    /* Get the pairs (handle + UUID) from buffer */
    switch(pFindInformationResponseParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                for(iCount = 0; iCount < pFindInformationResponseParams->handleUuidPairCount; iCount++)
                {
                    fsciBleAttGetFindInfoHdlUuid16PairFromBuffer(&pFindInformationResponseParams->informationData.handleUuid16[iCount], ppBuffer);
                }
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                for(iCount = 0; iCount < pFindInformationResponseParams->handleUuidPairCount; iCount++)
                {
                    fsciBleAttGetFindInfoHdlUuid128PairFromBuffer(&pFindInformationResponseParams->informationData.handleUuid128[iCount], ppBuffer);
                }
            }
            break;
            
        default:
            break;
    }
}


void fsciBleAttGetBuffFromInfoResponseParams(attFindInformationResponseParams_t* pFindInformationResponseParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Write in buffer all the attFindInformationResponseParams_t fields */ 
    fsciBleGetBufferFromEnumValue(pFindInformationResponseParams->format, *ppBuffer, attUuidFormat_t);
    fsciBleGetBufferFromUint8Value(pFindInformationResponseParams->handleUuidPairCount, *ppBuffer);
    
    /* Set the pairs (handle + UUID) in buffer */
    switch(pFindInformationResponseParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                for(iCount = 0; iCount < pFindInformationResponseParams->handleUuidPairCount; iCount++)
                {
                    fsciBleAttGetBuffFromInfoHdlUuid16Pair(&pFindInformationResponseParams->informationData.handleUuid16[iCount], ppBuffer);
                }
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                for(iCount = 0; iCount < pFindInformationResponseParams->handleUuidPairCount; iCount++)
                {
                    fsciBleAttGetBuffFromFindInfoHdlUuid128Pair(&pFindInformationResponseParams->informationData.handleUuid128[iCount], ppBuffer);
                }
            }
            break;
            
        default:
            break;
    }
}


void fsciBleAttGetFindByTypeValueRequestParamsFromBuffer(attFindByTypeValueRequestParams_t* pFindByTypeValueRequestParams, uint8_t** ppBuffer)
{
    /* Read attFindByTypeValueRequestParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pFindByTypeValueRequestParams->startingHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pFindByTypeValueRequestParams->endingHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pFindByTypeValueRequestParams->attributeType, *ppBuffer);
    fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&pFindByTypeValueRequestParams->attributeLength, pFindByTypeValueRequestParams->attributeValue, ppBuffer);
}


void fsciBleAttGetBufferFromFindByTypeValueRequestParams(attFindByTypeValueRequestParams_t* pFindByTypeValueRequestParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attFindByTypeValueRequestParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pFindByTypeValueRequestParams->startingHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pFindByTypeValueRequestParams->endingHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pFindByTypeValueRequestParams->attributeType, *ppBuffer);
    fsciBleAttGetBufferFromUint16ValueLengthAndArray(&pFindByTypeValueRequestParams->attributeLength, pFindByTypeValueRequestParams->attributeValue, ppBuffer);   
}


void fsciBleAttGetFindByTypeValueResponseParamsFromBuffer(attFindByTypeValueResponseParams_t* pFindByTypeValueResponseParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Read attFindByTypeValueResponseParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pFindByTypeValueResponseParams->groupCount, *ppBuffer);
    
    for(iCount = 0; iCount < pFindByTypeValueResponseParams->groupCount; iCount++)
    {
        fsciBleAttGetFindByTypeValueHandleGroupPairFromBuffer(&pFindByTypeValueResponseParams->handleGroup[iCount], ppBuffer);
    }
}


void fsciBleAttGetBuffFromFindByTypeValResponseParams(attFindByTypeValueResponseParams_t* pFindByTypeValueResponseParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Write in buffer all the attFindByTypeValueResponseParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pFindByTypeValueResponseParams->groupCount, *ppBuffer);
    
    for(iCount = 0; iCount < pFindByTypeValueResponseParams->groupCount; iCount++)
    {
        fsciBleAttGetBufferFromFindByTypeValueHandleGroupPair(&pFindByTypeValueResponseParams->handleGroup[iCount], ppBuffer);
    }
}


uint16_t fsciBleAttGetRdByTypeReqParamsBuffSize(attReadByTypeRequestParams_t* pReadByTypeRequestParams)
{
    /* Get the constant size for the needed buffer */
    uint16_t bufferSize = sizeof(uint16_t) + sizeof(uint16_t) + sizeof(attUuidFormat_t);
    
    /* Get the variable size for the needed buffer */
    switch(pReadByTypeRequestParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                bufferSize += sizeof(uint16_t);
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                bufferSize += 16 * sizeof(uint8_t);
            }
            break;
            
        default:
            break;
    }
    
    /* Return the needed buffer size */
    return bufferSize;
}


void fsciBleAttGetRdByTypeReqParamsFromBuffer(attReadByTypeRequestParams_t* pReadByTypeRequestParams, uint8_t** ppBuffer)
{
    /* Read attReadByTypeRequestParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pReadByTypeRequestParams->startingHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pReadByTypeRequestParams->endingHandle, *ppBuffer);
    fsciBleGetEnumValueFromBuffer(pReadByTypeRequestParams->format, *ppBuffer, attUuidFormat_t);
    
   /* Get the UUID from buffer */
    switch(pReadByTypeRequestParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                fsciBleGetUint16ValueFromBuffer(pReadByTypeRequestParams->attributeType.uuid16, *ppBuffer);
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                fsciBleGetUint128ValueFromBuffer(pReadByTypeRequestParams->attributeType.uuid128, *ppBuffer);
            }
            break;
            
        default:
            break;
    }
}


void fsciBleAttGetBuffFromReadByTypeReqParams(attReadByTypeRequestParams_t* pReadByTypeRequestParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attReadByTypeRequestParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pReadByTypeRequestParams->startingHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pReadByTypeRequestParams->endingHandle, *ppBuffer);
    fsciBleGetBufferFromEnumValue(pReadByTypeRequestParams->format, *ppBuffer, attUuidFormat_t);
    
    /* Set the UUID in buffer */
    switch(pReadByTypeRequestParams->format)
    {
        case gAttUuid16BitFormat_c:
            {
                /* UUID 16 bits format */
                fsciBleGetBufferFromUint16Value(pReadByTypeRequestParams->attributeType.uuid16, *ppBuffer);
            }
            break;
            
        case gAttUuid128BitFormat_c:
            {
                /* UUID 128 bits format */
                fsciBleGetBufferFromUint128Value(pReadByTypeRequestParams->attributeType.uuid128, *ppBuffer);
            }
            break;
            
        default:
            break;
    }
}


void fsciBleAttGetReadByTypeResponseParamsFromBuffer(attReadByTypeResponseParams_t* pReadByTypeResponseParams, uint8_t** ppBuffer)
{
    /* Read attReadByTypeResponseParams_t fields from buffer */ 
    fsciBleGetUint8ValueFromBuffer(pReadByTypeResponseParams->length, *ppBuffer);
    fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&pReadByTypeResponseParams->attributeDataListLength, pReadByTypeResponseParams->attributeDataList, ppBuffer);
}


void fsciBleAttGetBuffFromRdByTypeRespParams(attReadByTypeResponseParams_t* pReadByTypeResponseParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attReadByTypeResponseParams_t fields */ 
    fsciBleGetBufferFromUint8Value(pReadByTypeResponseParams->length, *ppBuffer);
    fsciBleAttGetBufferFromUint16ValueLengthAndArray(&pReadByTypeResponseParams->attributeDataListLength, pReadByTypeResponseParams->attributeDataList, ppBuffer);
}


void fsciBleAttGetReadBlobRequestParamsFromBuffer(attReadBlobRequestParams_t* pReadBlobRequestParams, uint8_t** ppBuffer)
{
    /* Read attReadBlobRequestParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pReadBlobRequestParams->attributeHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pReadBlobRequestParams->valueOffset, *ppBuffer);
}


void fsciBleAttGetBufferFromReadBlobRequestParams(const attReadBlobRequestParams_t* pReadBlobRequestParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attReadBlobRequestParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pReadBlobRequestParams->attributeHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pReadBlobRequestParams->valueOffset, *ppBuffer);
}


void fsciBleAttGetReadMultipleRequestParamsFromBuffer(attReadMultipleRequestParams_t* pReadMultipleRequestParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Read attReadMultipleRequestParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pReadMultipleRequestParams->handleCount, *ppBuffer);
    
    /* Get the handles from buffer */
    for(iCount = 0; iCount < pReadMultipleRequestParams->handleCount; iCount ++)
    {
        fsciBleGetUint16ValueFromBuffer(pReadMultipleRequestParams->listOfHandles[iCount], *ppBuffer);
    }
}


void fsciBleAttGetBufferFromReadMultipleRequestParams(attReadMultipleRequestParams_t* pReadMultipleRequestParams, uint8_t** ppBuffer)
{
    uint32_t iCount;
    
    /* Write in buffer all the attReadMultipleRequestParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pReadMultipleRequestParams->handleCount, *ppBuffer);
    
    /* Set the handles in buffer */
    for(iCount = 0; iCount < pReadMultipleRequestParams->handleCount; iCount ++)
    {
        fsciBleGetBufferFromUint16Value(pReadMultipleRequestParams->listOfHandles[iCount], *ppBuffer);
    }
}


void fsciBleAttGetWriteRequestAndCommandParamsFromBuffer(attWriteRequestAndCommandParams_t* pWriteRequestAndCommandParams, uint8_t** ppBuffer)
{
    /* Read attWriteRequestAndCommandParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pWriteRequestAndCommandParams->attributeHandle, *ppBuffer);
    fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&pWriteRequestAndCommandParams->attributeLength, pWriteRequestAndCommandParams->attributeValue, ppBuffer);
}


void fsciBleAttGetBufferFromWriteRequestAndCommandParams(attWriteRequestAndCommandParams_t* pWriteRequestAndCommandParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attWriteRequestAndCommandParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pWriteRequestAndCommandParams->attributeHandle, *ppBuffer);
    fsciBleAttGetBufferFromUint16ValueLengthAndArray(&pWriteRequestAndCommandParams->attributeLength, pWriteRequestAndCommandParams->attributeValue, ppBuffer);
}


void fsciBleAttGetSignedWriteCommandParamsFromBuffer(attSignedWriteCommandParams_t* pSignedWriteCommandParams, uint8_t** ppBuffer)
{
    /* Read attSignedWriteCommandParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pSignedWriteCommandParams->attributeHandle, *ppBuffer);
    fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&pSignedWriteCommandParams->attributeLength, &pSignedWriteCommandParams->signedValue[gAttSignedHdrSize_d], ppBuffer);
    fsciBleGetArrayFromBuffer(pSignedWriteCommandParams->authenticationSignature, *ppBuffer, gAttAuthSignatureSize_d);
}


void fsciBleAttGetBufferFromSignedWriteCommandParams(attSignedWriteCommandParams_t* pSignedWriteCommandParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attSignedWriteCommandParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pSignedWriteCommandParams->attributeHandle, *ppBuffer);
    fsciBleAttGetBufferFromUint16ValueLengthAndArray(&pSignedWriteCommandParams->attributeLength, &pSignedWriteCommandParams->signedValue[gAttSignedHdrSize_d], ppBuffer);
    fsciBleGetBufferFromArray(pSignedWriteCommandParams->authenticationSignature, *ppBuffer, gAttAuthSignatureSize_d);
}


void fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(attPrepareWriteRequestResponseParams_t* pPrepareWriteRequestResponseParams, uint8_t** ppBuffer)
{
    /* Read attPrepareWriteRequestResponseParams_t fields from buffer */ 
    fsciBleGetUint16ValueFromBuffer(pPrepareWriteRequestResponseParams->attributeHandle, *ppBuffer);
    fsciBleGetUint16ValueFromBuffer(pPrepareWriteRequestResponseParams->valueOffset, *ppBuffer);
    fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&pPrepareWriteRequestResponseParams->attributeLength, pPrepareWriteRequestResponseParams->attributeValue, ppBuffer);
}


void fsciBleAttGetBufferFromPrepareWriteRequestResponseParams(attPrepareWriteRequestResponseParams_t* pPrepareWriteRequestResponseParams, uint8_t** ppBuffer)
{
    /* Write in buffer all the attPrepareWriteRequestResponseParams_t fields */ 
    fsciBleGetBufferFromUint16Value(pPrepareWriteRequestResponseParams->attributeHandle, *ppBuffer);
    fsciBleGetBufferFromUint16Value(pPrepareWriteRequestResponseParams->valueOffset, *ppBuffer);
    fsciBleAttGetBufferFromUint16ValueLengthAndArray(&pPrepareWriteRequestResponseParams->attributeLength, pPrepareWriteRequestResponseParams->attributeValue, ppBuffer);
}


void fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(uint16_t* pLength, uint8_t* pArray, uint8_t** ppBuffer)
{
    /* Read the array length from buffer */ 
    fsciBleGetUint16ValueFromBuffer(*pLength, *ppBuffer);
    /* Read the array from buffer */ 
    fsciBleGetArrayFromBuffer(pArray, *ppBuffer, *pLength);   
}


void fsciBleAttGetBufferFromUint16ValueLengthAndArray(uint16_t* pLength, uint8_t* pArray, uint8_t** ppBuffer)
{
    /* Write the array length in buffer */ 
    fsciBleGetBufferFromUint16Value(*pLength, *ppBuffer);
    /* Write the array in buffer */ 
    fsciBleGetBufferFromArray(pArray, *ppBuffer, *pLength);   
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c && (gFsciBleAttLayerEnabled_d || gFsciBleGattDbAttLayerEnabled_d) */

/*! *********************************************************************************
* @}
********************************************************************************** */
