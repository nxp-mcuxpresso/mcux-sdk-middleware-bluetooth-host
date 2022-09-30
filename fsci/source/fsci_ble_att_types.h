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

#ifndef FSCI_BLE_ATT_TYPES_H
#define FSCI_BLE_ATT_TYPES_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

#include "fsci_ble.h"
#include "att_types.h"
#include "att_errors.h"
#include "att_params.h"
#include "att_interface.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

#define fsciBleAttGetErrorResponseParamsBufferSize(pErrorResponseParams)                                                    (sizeof(attOpcode_t) + sizeof(uint16_t) + \
                                                                                                                            sizeof(attErrorCode_t))

#define fsciBleAttGetFindInformationRequestParamsBufferSize(pFindInformationRequestParams)                                  (sizeof(uint16_t) + sizeof(uint16_t))

#define fsciBleAttGetFindInfoHandleUuid16PairBufferSize(pFindInfoHandleUuid16Pair)                                          (sizeof(uint16_t) + sizeof(uint16_t))

#define fsciBleAttGetFindInfoHandleUuid128PairBufferSize(pFindInfoHandleUuid16Pair)                                         (sizeof(uint16_t) + 16 * sizeof(uint8_t))

#define fsciBleAttGetFindByTypeValueRequestParamsBufferSize(pFindByTypeValueRequestParams)                                  (sizeof(uint16_t) + sizeof(uint16_t) + \
                                                                                                                            sizeof(uint16_t) + \
                                                                                                                            (pFindByTypeValueRequestParams)->attributeLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))

#define fsciBleAttGetFindByTypeValueResponseParamsBufferSize(pFindByTypeValueResponseParams)                                (sizeof(uint16_t) + ((pFindByTypeValueResponseParams)->groupCount * \
                                                                                                                            fsciBleAttGetFindByTypeValueHandleGroupPairBufferSize(&(pFindByTypeValueResponseParams)->handleGroup[0])))

#define fsciBleAttGetReadByTypeResponseParamsBufferSize(pReadByTypeResponseParams)                                          (sizeof(uint8_t) + \
                                                                                                                            (pReadByTypeResponseParams)->attributeDataListLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))

#define fsciBleAttGetReadBlobRequestParamsBufferSize(pReadBlobRequestParams)                                                (sizeof(uint16_t) + sizeof(uint16_t))

#define fsciBleAttGetReadMultipleRequestParamsBufferSize(pReadMultipleRequestParams)                                        ((pReadMultipleRequestParams)->handleCount * sizeof(uint16_t) + \
                                                                                                                            sizeof(uint16_t))                                                                                      

#define fsciBleAttGetWriteRequestAndCommandParamsBufferSize(pWriteRequestAndCommandParams)                                  (sizeof(uint16_t) + \
                                                                                                                            (pWriteRequestAndCommandParams)->attributeLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))                                                                                               

#define fsciBleAttGetSignedWriteCommandParamsBufferSize(pSignedWriteCommandParams)                                          (sizeof(uint16_t) + \
                                                                                                                            (pSignedWriteCommandParams)->attributeLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t) + gAttAuthSignatureSize_d)

#define fsciBleAttGetPrepareWriteRequestResponseParamsBufferSize(pPrepareWriteRequestResponseParams)                        (sizeof(uint16_t) + sizeof(uint16_t) + \
                                                                                                                            (pPrepareWriteRequestResponseParams)->attributeLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))

#define fsciBleAttGetExchangeMtuRequestParamsBufferSize(pExchangeMtuRequestParams)                                          sizeof(uint16_t)
#define fsciBleAttGetExchangeMtuRequestParamsFromBuffer(pExchangeMtuRequestParams, ppBuffer)                                fsciBleGetUint16ValueFromBuffer((pExchangeMtuRequestParams)->clientRxMtu, *(ppBuffer))
#define fsciBleAttGetBufferFromExchangeMtuRequestParams(pExchangeMtuRequestParams, ppBuffer)                                fsciBleGetBufferFromUint16Value((pExchangeMtuRequestParams)->clientRxMtu, *(ppBuffer))

#define fsciBleAttGetExchangeMtuResponseParamsBufferSize(pExchangeMtuResponseParams)                                        sizeof(uint16_t)
#define fsciBleAttGetExchangeMtuResponseParamsFromBuffer(pExchangeMtuResponseParams, ppBuffer)                              fsciBleGetUint16ValueFromBuffer((pExchangeMtuResponseParams)->serverRxMtu, *(ppBuffer))
#define fsciBleAttGetBufferFromExchangeMtuResponseParams(pExchangeMtuResponseParams, ppBuffer)                              fsciBleGetBufferFromUint16Value((pExchangeMtuResponseParams)->serverRxMtu, *(ppBuffer))

#define fsciBleAttGetFindByTypeValueHandleGroupPairBufferSize(pFindByTypeValueHandleGroupPair)                              fsciBleAttGetFindInformationRequestParamsBufferSize((attFindInformationRequestParams_t*)(pFindByTypeValueHandleGroupPair))
#define fsciBleAttGetFindByTypeValueHandleGroupPairFromBuffer(pFindByTypeValueHandleGroupPair, ppBuffer)                    fsciBleAttGetFindInformationRequestParamsFromBuffer((attFindInformationRequestParams_t*)(pFindByTypeValueHandleGroupPair), (ppBuffer))
#define fsciBleAttGetBufferFromFindByTypeValueHandleGroupPair(pFindByTypeValueHandleGroupPair, ppBuffer)                    fsciBleAttGetBuffFromFindInfoRequestParams((attFindInformationRequestParams_t*)(pFindByTypeValueHandleGroupPair), (ppBuffer))

#define fsciBleAttGetReadRequestParamsBufferSize(pReadRequestParams)                                                        sizeof(uint16_t)
#define fsciBleAttGetReadRequestParamsFromBuffer(pReadRequestParams, ppBuffer)                                              fsciBleGetUint16ValueFromBuffer((pReadRequestParams)->attributeHandle, *(ppBuffer))
#define fsciBleAttGetBufferFromReadRequestParams(pReadRequestParams, ppBuffer)                                              fsciBleGetBufferFromUint16Value((pReadRequestParams)->attributeHandle, *(ppBuffer))

#define fsciBleAttGetReadResponseParamsBufferSize(pReadResponseParams)                                                      ((pReadResponseParams)->attributeLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))                                                                                                
#define fsciBleAttGetReadResponseParamsFromBuffer(pReadResponse, ppBuffer)                                                  fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&(pReadResponse)->attributeLength, (pReadResponse)->attributeValue, (ppBuffer))
#define fsciBleAttGetBufferFromReadResponseParams(pReadResponse, ppBuffer)                                                  fsciBleAttGetBufferFromUint16ValueLengthAndArray(&(pReadResponse)->attributeLength, (pReadResponse)->attributeValue, (ppBuffer))

#define fsciBleAttGetReadBlobResponseParamsBufferSize(pReadBlobResponseParams)                                              fsciBleAttGetReadResponseParamsBufferSize((attReadResponseParams_t*)(pReadBlobResponseParams))         
#define fsciBleAttGetReadBlobResponseParamsFromBuffer(pReadBlobResponseParams, ppBuffer)                                    fsciBleAttGetReadResponseParamsFromBuffer((attReadResponseParams_t*)(pReadBlobResponseParams), (ppBuffer))
#define fsciBleAttGetBufferFromReadBlobResponseParams(pReadBlobResponseParams, ppBuffer)                                    fsciBleAttGetBufferFromReadResponseParams((attReadResponseParams_t*)(pReadBlobResponseParams), (ppBuffer))

#define fsciBleAttGetReadMultipleResponseParamsBufferSize(pReadMultipleResponseParams)                                      ((pReadMultipleResponseParams)->listLength * sizeof(uint8_t) + \
                                                                                                                            sizeof(uint16_t))                                                                                     
#define fsciBleAttGetReadMultipleResponseParamsFromBuffer(pReadMultipleResponseParams, ppBuffer)                            fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(&(pReadMultipleResponseParams)->listLength, (pReadMultipleResponseParams)->listOfValues, (ppBuffer))
#define fsciBleAttGetBufferFromReadMultipleResponseParams(pReadMultipleResponseParams, ppBuffer)                            fsciBleAttGetBufferFromUint16ValueLengthAndArray(&(pReadMultipleResponseParams)->listLength, (pReadMultipleResponseParams)->listOfValues, (ppBuffer))

#define fsciBleAttGetReadByGroupTypeRequestParamsBufferSize(pReadByGroupTypeRequestParams)                                  fsciBleAttGetRdByTypeReqParamsBuffSize((attReadByTypeRequestParams_t*)(pReadByGroupTypeRequestParams))
#define fsciBleAttGetReadByGroupTypeRequestParamsFromBuffer(pReadByGroupTypeRequestParams, ppBuffer)                        fsciBleAttGetRdByTypeReqParamsFromBuffer((attReadByTypeRequestParams_t*)(pReadByGroupTypeRequestParams), (ppBuffer))
#define fsciBleAttGetBufferFromReadByGroupTypeRequestParams(pReadByGroupTypeRequestParams, ppBuffer)                        fsciBleAttGetBuffFromReadByTypeReqParams((attReadByTypeRequestParams_t*)(pReadByGroupTypeRequestParams), (ppBuffer))
                                                                                                
#define fsciBleAttGetReadByGroupTypeResponseParamsBufferSize(pReadByGroupTypeResponseParams)                                fsciBleAttGetReadByTypeResponseParamsBufferSize((attReadByTypeResponseParams_t*)(pReadByGroupTypeResponseParams))
#define fsciBleAttGetReadByGroupTypeResponseParamsFromBuffer(pReadByGroupTypeResponseParams, ppBuffer)                      fsciBleAttGetReadByTypeResponseParamsFromBuffer((attReadByTypeResponseParams_t*)(pReadByGroupTypeResponseParams), (ppBuffer))
#define fsciBleAttGetBufferFromReadByGroupTypeResponseParams(pReadByGroupTypeResponseParams, ppBuffer)                      fsciBleAttGetBuffFromRdByTypeRespParams((attReadByTypeResponseParams_t*)(pReadByGroupTypeResponseParams), (ppBuffer))

#define fsciBleAttGetExecuteWriteRequestParamsBufferSize(pExecuteWriteRequestParams)                                        sizeof(attExecuteWriteRequestFlags_t)
#define fsciBleAttGetExecuteWriteRequestParamsFromBuffer(pExecuteWriteRequestParams, ppBuffer)                              fsciBleGetEnumValueFromBuffer((pExecuteWriteRequestParams)->flags, *(ppBuffer), attExecuteWriteRequestFlags_t)
#define fsciBleAttGetBufferFromExecuteWriteRequestParams(pExecuteWriteRequestParams, ppBuffer)                              fsciBleGetBufferFromEnumValue((pExecuteWriteRequestParams)->flags, *(ppBuffer), attExecuteWriteRequestFlags_t)

#define fsciBleAttGetHandleValueNotificationIndicationParamsBufferSize(pHandleValueNotificationIndicationParams)            fsciBleAttGetWriteRequestAndCommandParamsBufferSize((attWriteRequestAndCommandParams_t*)(pHandleValueNotificationIndicationParams))
#define fsciBleAttGetHandleValueNotificationIndicationParamsFromBuffer(pHandleValueNotificationIndicationParams, ppBuffer)  fsciBleAttGetWriteRequestAndCommandParamsFromBuffer((attWriteRequestAndCommandParams_t*)(pHandleValueNotificationIndicationParams), (ppBuffer))
#define fsciBleAttGetBufferFromHandleValueNotificationIndicationParams(pHandleValueNotificationIndicationParams, ppBuffer)  fsciBleAttGetBufferFromWriteRequestAndCommandParams((attWriteRequestAndCommandParams_t*)(pHandleValueNotificationIndicationParams), (ppBuffer))

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

void fsciBleAttGetErrorResponseParamsFromBuffer(attErrorResponseParams_t* pErrorResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromErrorResponseParams(attErrorResponseParams_t* pErrorResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetFindInformationRequestParamsFromBuffer(attFindInformationRequestParams_t* pFindInformationRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromFindInfoRequestParams(attFindInformationRequestParams_t* pFindInformationRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetFindInfoHdlUuid16PairFromBuffer(attFindInfoHandleUuid16Pair_t* pFindInfoHandleUuid16Pair, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromInfoHdlUuid16Pair(attFindInfoHandleUuid16Pair_t* pFindInfoHandleUuid16Pair, uint8_t** ppBuffer);

void fsciBleAttGetFindInfoHdlUuid128PairFromBuffer(attFindInfoHandleUuid128Pair_t* pFindInfoHandleUuid128Pair, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromFindInfoHdlUuid128Pair(attFindInfoHandleUuid128Pair_t* pFindInfoHandleUuid128Pair, uint8_t** ppBuffer);

uint16_t fsciBleAttGetFindInformationResponseParamsBufferSize(attFindInformationResponseParams_t* pFindInformationResponseParams);

void fsciBleAttGetFindInfoResponseParamsFromBuffer(attFindInformationResponseParams_t* pFindInformationResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromInfoResponseParams(attFindInformationResponseParams_t* pFindInformationResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetFindByTypeValueRequestParamsFromBuffer(attFindByTypeValueRequestParams_t* pFindByTypeValueRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromFindByTypeValueRequestParams(attFindByTypeValueRequestParams_t* pFindByTypeValueRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetFindByTypeValueResponseParamsFromBuffer(attFindByTypeValueResponseParams_t* pFindByTypeValueResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromFindByTypeValResponseParams(attFindByTypeValueResponseParams_t* pFindByTypeValueResponseParams, uint8_t** ppBuffer);

uint16_t fsciBleAttGetRdByTypeReqParamsBuffSize(attReadByTypeRequestParams_t* pReadByTypeRequestParams);

void fsciBleAttGetRdByTypeReqParamsFromBuffer(attReadByTypeRequestParams_t* pReadByTypeRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromReadByTypeReqParams(attReadByTypeRequestParams_t* pReadByTypeRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetReadByTypeResponseParamsFromBuffer(attReadByTypeResponseParams_t* pReadByTypeResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetBuffFromRdByTypeRespParams(attReadByTypeResponseParams_t* pReadByTypeResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetReadBlobRequestParamsFromBuffer(attReadBlobRequestParams_t* pReadBlobRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromReadBlobRequestParams(const attReadBlobRequestParams_t* pReadBlobRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetReadMultipleRequestParamsFromBuffer(attReadMultipleRequestParams_t* pReadMultipleRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromReadMultipleRequestParams(attReadMultipleRequestParams_t* pReadMultipleRequestParams, uint8_t** ppBuffer);

void fsciBleAttGetWriteRequestAndCommandParamsFromBuffer(attWriteRequestAndCommandParams_t* pWriteRequestAndCommandParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromWriteRequestAndCommandParams(attWriteRequestAndCommandParams_t* pWriteRequestAndCommandParams, uint8_t** ppBuffer);

void fsciBleAttGetSignedWriteCommandParamsFromBuffer(attSignedWriteCommandParams_t* pSignedWriteCommandParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromSignedWriteCommandParams(attSignedWriteCommandParams_t* pSignedWriteCommandParams, uint8_t** ppBuffer);

void fsciBleAttGetPrepareWriteRequestResponseParamsFromBuffer(attPrepareWriteRequestResponseParams_t* pPrepareWriteRequestResponseParams, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromPrepareWriteRequestResponseParams(attPrepareWriteRequestResponseParams_t* pPrepareWriteRequestResponseParams, uint8_t** ppBuffer);


void fsciBleAttGetUint16ValueLengthAndArrayFromBuffer(uint16_t* pLength, uint8_t* pArray, uint8_t** ppBuffer);

void fsciBleAttGetBufferFromUint16ValueLengthAndArray(uint16_t* pLength, uint8_t* pArray, uint8_t** ppBuffer);

#ifdef __cplusplus
}
#endif 

#endif /* FSCI_BLE_ATT_TYPES_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
