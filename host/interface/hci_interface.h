/*! *********************************************************************************
* \defgroup HCI HCI
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
* Copyright 2016-2022 NXP
* All rights reserved.
*
* \file
*
* This file is the interface file for the HCI module
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef HCI_INTERFACE_H
#define HCI_INTERFACE_H

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_general.h"
#include "hci_types.h"

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*******************************************************************************
*   COMMANDS and EVENTS parameters
***************************************************************************** */
/*! HCI Commands and Events for ************************************************
*   OGF : 0x01 : Link Control Commands
***************************************************************************** */

/*! OCF 0x0006 */
/*! HCI_Disconnect */
typedef struct
{
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciDisconnectCommand_t;
/*! Disconnection Complete Event : 0x05 */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciDisconnectionCompleteEvent_t;

/*! OCF 0x001D */
/*! HCI_Read_Remote_Version_Information */
typedef struct
{
    uint16_t            connectionHandle;
} hciReadRemoteVersionInformationCommand_t;
/*! Read Remote Version Information Complete Event : 0x0C */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             version;
    uint16_t            manufacturerName;
    uint16_t            subversion;
} hciReadRemoteVersionInformationCompleteEvent_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x03 : Controller & Baseband Commands
***************************************************************************** */
/*! OCF 0x0001 */
/*! HCI_Set_Event_Mask - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciSetEventMaskCommandComplete_t;

/*! Command Status Event : 0x0F */
typedef struct
{
    hciErrorCode_t          status;
    uint8_t                 numHciCommandPackets;
    hciCommandOpCode_t      commandOpCode;
} hciCommandStatusEvent_t;

/*! Hardware Error Event : 0x10 */
typedef struct
{
    bleHardwareErrorCode_t      status;
} hciHardwareErrorEvent_t;

typedef struct
{
    uint8_t                 numberOfHandles;
    uint16_t                connectionHandle[gcGapMaximumActiveConnections_c];
    uint16_t                hcNumCompletedPackets[gcGapMaximumActiveConnections_c];
} hciNumberOfCompletedPacketsEvent_t;

/*! Data Buffer Overflow Event : 0x1A */
typedef struct
{
    hciDataBufferOverflowLinkType_t         linkType;
} hciDataBufferOverflowEvent_t;

/*! Authenticated Payload Timeout Expired Event : 0x57 */
typedef struct
{
    uint16_t                connectionHandle;
} hciAuthenticatedPayloadTimeoutExpiredEvent_t;

/*! OCF 0x0001 */
/*! HCI_Set_Event_Mask */
typedef struct
{
    uint8_t             eventMask[8]; /* hciSetEventMaskEventShift_t */
} hciSetEventMaskCommand_t;

/*! OCF 0x0003 */
/*! HCI_Reset */
/*! No parameters */
/*! HCI_Reset - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciResetCommandComplete_t;

/*! OCF 0x002D */
/*! HCI_Read_Transmit_Power_Level */
typedef struct
{
    uint16_t                        connectionHandle;
    bleTransmitPowerLevelType_t     type;
} hciReadTransmitPowerLevelCommand_t;

/*! HCI_Read_Transmit_Power_Level - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t                  status;
    uint16_t                        connectionHandle;
    int8_t                          transmitPowerlevel;  /* This is a signed 8 bit integer - Range: -30..20 dBm*/
} hciReadTransmitPowerLevelCommandComplete_t;

/*! OCF 0x0031 */
/*! HCI_Set_Controller_To_Host_Flow_Control */
typedef struct
{
    hciControllerToHostFlowControlEnable_t      eventMask;
} hciSetControllerToHostFlowControlCommand_t;

/*! HCI_Set_Controller_To_Host_Flow_Control - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t                              status;
} hciSetControllerToHostFlowControlCommandComplete_t;

/*! OCF 0x0033 */
/*! HCI_Host_Buffer_Size */
typedef struct
{
    uint16_t            hostAclDataPacketlength;
    uint8_t             hostSynchronousDataPacketLength;
    uint16_t            hostTotalNumAclDataPackets;
    uint16_t            hostTotalNumSynchronousDataPackets;
} hciHostBufferSizeCommand_t;

/*! HCI_Host_Buffer_Size - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciHostBufferSizeCommandComplete_t;

/*! OCF 0x0035 */
/*! HCI_Host_Number_Of_Completed_Packets */
typedef struct
{
    uint16_t            connectionHandle;
    uint16_t            hostNrOfCompletedPackets;
} bleHostCompletedPacketsParams_t;

typedef struct
{
    uint8_t             numberOfHandles;
    uint16_t            connectionHandle[gcGapMaximumActiveConnections_c];
    uint16_t            hostNrOfCompletedPackets[gcGapMaximumActiveConnections_c];
} hciHostNumberOfCompletedPacketsCommand_t;

/*! HCI_Host_Number_Of_Completed_Packets - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t                      status;
} hciHostNumberOfCompletedPacketsCommandComplete_t;

/*! OCF 0x0063 */
/*! HCI_Set_Event_Mask_Page_2 */
typedef struct
{
    uint8_t             eventMaskPage2[8]; /* hciSetEventMaskPage2EventShift_t */
} hciSetEventMaskPage2Command_t;

/*! HCI_Set_Event_Mask_Page_2 - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciSetEventMaskPage2CommandComplete_t;

/*! OCF 0x007B */
/*! HCI_Read_Authenticated_Payload_Timeout */
typedef struct
{
    uint16_t            connectionHandle;
} hciReadAuthenticatedPayloadTimeoutCommand_t;

/*! HCI_Read_Authenticated_Payload_Timeout - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint16_t            authenticatedPayloadTimeout;
} hciReadAuthenticatedPayloadTimeoutCommandComplete_t;

/*! OCF 0x007C */
/*! HCI_Write_Authenticated_Payload_Timeout */
typedef struct
{
    uint16_t            connectionHandle;
    uint16_t            authenticatedPayloadTimeout;
} hciWriteAuthenticatedPayloadTimeoutCommand_t;

/*! HCI_Write_Authenticated_Payload_Timeout - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciWriteAuthenticatedPayloadTimeoutCommandComplete_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x04 : Informational Parameters
***************************************************************************** */

/*! OCF 0x0001 */
/*! HCI_LE_Read_Local_Version_Information */
/*! No parameters */
/*! HCI_LE_Read_Local_Version_Information - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             hciVersion;
    uint16_t            hciRevision;
    uint8_t             lmpPalVersion;
    uint16_t            manufacturerName;
    uint16_t            lmpPalSubversion;
} hciReadLocalVersionInfoCommandComplete_t;

/*! OCF 0x0002 */
/*! HCI_Read_Local_Supported_Commands */
/*! No parameters */
/*! HCI_Read_Local_Supported_Commands - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             supportedCommands[64]; /* hciSupportedCommandsShift_t */
} hciReadLocalSupportedCommandsCommandComplete_t;

/*! OCF 0x0003 */
/*! HCI_Read_Local_Supported_Features */
/*! No parameters */
/*! HCI_Read_Local_Supported_Features - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             lmpFeatures[8];
} hciReadLocalSupportedFeaturesCommandComplete_t;

/*! OCF 0x0009 */
/*! HCI_Read_BD_ADDR */
/*! No parameters */
/*! HCI_Read_BD_ADDR - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             bdAddr[gcBleDeviceAddressSize_c];
} hciReadBdAddrCommandComplete_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x05 : Status Parameters
***************************************************************************** */

/*! OCF 0x0005 */
/*! HCI_Read_RSSI */
typedef struct
{
    uint16_t            handle;
} hciReadRssiCommand_t;
/*! HCI_Read_RSSI - Command Complete Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            handle;
    int8_t              rssi; /* This is a signed 8 bit integer - Range: -127..20 dBm for a LE Controller*/
} hciReadRssiCommandComplete_t;


/*! HCI Commands and Events for ************************************************
*   OGF : 0x08 : LE Controller Commands
***************************************************************************** */

/*! OCF 0x0001 */
/*! HCI_LE_Set_Event_Mask */
typedef struct
{
    uint8_t             leEventMask[8]; /* hciLeSetEventMaskEventShift_t */
} hciLeSetEventMaskCommand_t;

/*! OCF 0x0002 */
/*! HCI_LE_Read_Buffer_Size */
/*! No parameters */

/*! OCF 0x0003 */
/*! HCI_LE_Read_Local_Supported_Features */
/*! No parameters */

/*! OCF 0x0005 */
/*! HCI_LE_Set_Random_Address */
typedef struct
{
    uint8_t             randomAddress[gcBleDeviceAddressSize_c];
} hciLeSetRandomAddressCommand_t;

/*! OCF 0x0006 */
/*! HCI_LE_Set_Advertising_Parameters */
typedef struct
{
    uint16_t                        advertisingIntervalMin;
    uint16_t                        advertisingIntervalMax;
    bleAdvertisingType_t            advertisingType;
    hciBleAddressType_t             ownAddressType;
    hciBleAddressType_t             directAddressType;
    uint8_t                         directAddress[gcBleDeviceAddressSize_c];
    bleAdvertisingChannelMap_t      advertisingChannelMap;
    bleAdvertisingFilterPolicy_t    advertisingFilterPolicy;
} hciLeSetAdvertisingParametersCommand_t;

/*! OCF 0x0007 */
/*! HCI_LE_Read_Advertising_Channel_Tx_Power */
/*! No parameters */

/*! OCF 0x0008 */
/*! HCI_LE_Set_Advertising_Data */
typedef struct
{
    uint8_t             advertisingDataLength;
    const uint8_t      *pAdvertisingData;
} hciLeSetAdvertisingDataCommand_t;

/*! OCF 0x0009 */
/*! HCI_LE_Set_Scan_Response_Data */
typedef struct
{
    uint8_t             scanResponseDataLength;
    const uint8_t      *pScanResponseData;
} hciLeSetScanResponseDataCommand_t;

/*! OCF 0x000B */
/*! HCI_LE_Set_Scan_Parameters */
typedef struct
{
    bleScanType_t                 scanType;
    uint16_t                      scanInterval;
    uint16_t                      scanWindow;
    hciBleAddressType_t           ownAddressType;
    hciBleScanningFilterPolicy_t  scanningFilterPolicy;
} hciLeSetScanParametersCommand_t;

/*! OCF 0x000C */
/*! HCI_LE_Set_Scan_Enable */
typedef struct
{
    hciLeScanEnable_t           scanEnable;
    hciLeFilterDuplicates_t     filterDuplicates;
} hciLeSetScanEnableCommand_t;

/*! LE Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x02 */
typedef struct
{
    bleAdvertisingReportEventType_t         eventType;
    bleAddressType_t                        addressType;
    uint8_t                                 address[gcBleDeviceAddressSize_c];
    uint8_t                                 dataLength;
    uint8_t                                 data[gHciLeAdvertisingDataLength_c];
    uint8_t                                 rssi;
} bleAdvertisingReportEventParams_t;

/*! LE Direct Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x0B */
typedef struct
{
    bleAdvertisingReportEventType_t         eventType;
    bleAddressType_t                        addressType;
    uint8_t                                 address[gcBleDeviceAddressSize_c];
    bleAddressType_t                        directAddressType;
    uint8_t                                 directAddress[gcBleDeviceAddressSize_c];
    uint8_t                                 rssi;
} bleDirectedAdvertisingReportEventParams_t;

typedef struct
{
    uint8_t                                 numReports;
    bleAdvertisingReportEventParams_t       *aAdvReports;
} hciLeAdvertisingReportEvent_t;

/*! OCF 0x000D */
/*! HCI_LE_Create_Connection */
typedef struct
{
    uint16_t                    scanInterval;
    uint16_t                    scanWindow;
    bleInitiatorFilterPolicy_t  initiatorFilterPolicy;
    hciBleAddressType_t         peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    hciBleAddressType_t         ownAddressType;
    uint16_t                    connIntervalMin;
    uint16_t                    connIntervalMax;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    uint16_t                    minimumCELength;
    uint16_t                    maximumCELength;
} hciLeCreateConnectionCommand_t;

/*! LE Connection Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x01 */
typedef struct
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    bleLlConnectionRole_t       role;
    bleAddressType_t            peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    uint16_t                    connInterval;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    bleMasterClockAccuracy_t    masterClockAccuracy;
} hciLeConnectionCompleteEvent_t;

/*! OCF 0x000E */
/*! HCI_LE_Create_Connection_Cancel */
/*! No parameters */

/*! OCF 0x000F */
/*! HCI_LE_Read_White_List_Size */
/*! No parameters */

/*! OCF 0x0010 */
/*! HCI_LE_Clear_White_List */
/*! No parameters */

/*! OCF 0x0011 */
/*! HCI_LE_Add_Device_To_White_List */
typedef struct
{
    bleAddressType_t    addressType;
    uint8_t             address[gcBleDeviceAddressSize_c];
} hciLeAddDeviceToWhiteListCommand_t;

/*! OCF 0x0012 */
/*! HCI_LE_Remove_Device_From_White_List */
typedef struct
{
    bleAddressType_t    addressType;
    uint8_t             address[gcBleDeviceAddressSize_c];
} hciLeRemoveDeviceFromWhiteListCommand_t;

/*! OCF 0x0013 */
/*! HCI_LE_Connection_Update */
typedef struct
{
    uint16_t            connectionHandle;
    uint16_t            connIntervalMin;
    uint16_t            connIntervalMax;
    uint16_t            connLatency;
    uint16_t            supervisionTimeout;
    uint16_t            minimumCeLength;
    uint16_t            maximumCeLength;
} hciLeConnectionUpdateCommand_t;

/*! LE Connection Update Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x03 */
/* Although not used, tag is needed in order to satisfy MISRA rule 10.3 */
typedef struct hciLeConnectionUpdateCompleteEvent_tag
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint16_t            connInterval;
    uint16_t            connLatency;
    uint16_t            supervisionTimeout;
} hciLeConnectionUpdateCompleteEvent_t;

/*! OCF 0x0014 */
/*! HCI_LE_Set_Host_Channel_Classification */
typedef struct
{
    uint8_t             channelMap[gcBleChannelMapSize_c];
} hciLeSetHostChannelClassificationCommand_t;

/*! OCF 0x0015 */
/*! HCI_LE_Read_Channel_Map */
typedef struct
{
    uint16_t            connectionHandle;
} hciLeReadChannelMapCommand_t;

/*! OCF 0x0016 */
/*! HCI_LE_Read_Remote_Features */
typedef struct
{
    uint16_t            connectionHandle;
} hciLeReadRemoteFeaturesCommand_t;

/*! LE Read Remote Features Complete Event : LE Meta Event : 0x3E : Subevent Code : 0x04 */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             leFeatures[8]; /* hciLeSupportedFeatures_tag */
} hciLeReadRemoteFeaturesCompleteEvent_t;

/*! LE Long Term Key Request Event : LE Meta Event : 0x3E - Subevent Code : 0x05 */
typedef struct
{
    uint16_t                connectionHandle;
    uint8_t                 randomNumber[8];
    uint16_t                encryptionDiversifier;
} hciLeLongTermKeyRequestEvent_t;

/*! LE Long Term Key Request Event : LE Meta Event : 0x3E - Subevent Code : 0x06 */
typedef struct
{
    uint16_t                connectionHandle;
    uint16_t                intervalMin;
    uint16_t                intervalMax;
    uint16_t                latency;
    uint16_t                timeout;
} hciLeRemoteConnectionParameterRequestEvent_t;

/*! LE Data Length Change Event : LE Meta Event : 0x3E - Subevent Code : 0x07 */
typedef struct
{
    uint16_t                connectionHandle;
    uint16_t                maxTxOctets;
    uint16_t                maxTxTime;
    uint16_t                maxRxOctets;
    uint16_t                maxRxTime;
}hciLeDataLengthChangeEvent_t;

/*! LE Read Local P-256 Public Key Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x08 */
typedef struct
{
    hciErrorCode_t          status;
    uint8_t                 localP256PublicKey[64];
}hciLeReadLocalP256PublicKeyCompleteEvent_t;

/*! LE Generate DHKey Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x09 */
typedef struct
{
    hciErrorCode_t          status;
    uint8_t                 dhKey[32];
}hciLeGenerateDhKeyCompleteEvent_t;

/*! LE Enhanced Connection Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x0A */
typedef struct
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    bleLlConnectionRole_t       role;
    bleAddressType_t            peerAddressType;
    uint8_t                     peerAddress[gcBleDeviceAddressSize_c];
    uint8_t                     localResolvablePrivateAddress[gcBleDeviceAddressSize_c];
    uint8_t                     peerResolvablePrivateAddress[gcBleDeviceAddressSize_c];
    uint16_t                    connInterval;
    uint16_t                    connLatency;
    uint16_t                    supervisionTimeout;
    bleMasterClockAccuracy_t    masterClockAccuracy;
}hciLeEnhancedConnectionCompleteEvent_t;

typedef struct
{
    uint8_t                                   numReports;
    bleDirectedAdvertisingReportEventParams_t *aAdvReports;
} hciLeDirectedAdvertisingReportEvent_t;

/*! LE PHY Update Complete Event : LE Meta Event : 0x3E - Subevent Code : 0x0C */
typedef struct
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    uint8_t                     txPhy;
    uint8_t                     rxPhy;
} hciLePhyUpdateCompleteEvent_t;

/*! Vendor Specific Enhanced Notification Event : LE Meta Event : 0x3E - Subevent Code : 0xFF */
typedef struct hciVendorEnhancedNotificationEvent_tag
{
    uint16_t                    eventType;
    uint16_t                    connectionHandle;
    int8_t                      rssi;
    uint8_t                     channel;
    uint16_t                    ev_counter;
    uint16_t                    timestamp;
    uint8_t                     adv_handle;
} hciVendorEnhancedNotificationEvent_t;

#if (gBLE50_d == TRUE)
/*! Extended/Periodic Advertising data block */
typedef struct hciLeExtAdvReportEventData_tag
{
    struct hciLeExtAdvReportEventData_tag *pNext;
    uint8_t                               dataLength;
    uint8_t                               aData[1];
}hciLeExtAdvReportEventData_t;

/*! Extended Advertising Report parameters */
typedef struct hciLeExtAdvReportEventParams_tag
{
    hciErrorCode_t                          status; /* Host internal use only. */
    hciBleExtAdvReportEventType_t           eventType;
    hciBleAddressType_t                     addrType;
    uint8_t                                 addr[gcBleDeviceAddressSize_c];
    uint8_t                                 primaryPHY;
    uint8_t                                 secondaryPHY;
    uint8_t                                 SID;
    uint8_t                                 txPower;
    uint8_t                                 rssi;
    uint16_t                                advInterval;
    hciBleAddressType_t                     directAddrType;
    uint8_t                                 directAddr[gcBleDeviceAddressSize_c];
    hciLeExtAdvReportEventData_t            *pData;
} hciLeExtAdvReportEventParams_t;

/*! LE Extended Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x0D */
typedef struct hciLeExtAdvReportEvent_tag
{
    uint8_t                                 numReports;
    hciLeExtAdvReportEventParams_t          *aAdvReports;
} hciLeExtAdvReportEvent_t;

/*! LE Periodic Advertising Sync Established Event : LE Meta Event : 0x3E - Subevent Code : 0x0E */
typedef struct hciLePeriodicAdvSyncEstbEvent_tag
{
    hciErrorCode_t                          status;
    uint16_t                                syncHandle;
    uint8_t                                 advertisingSID;
    bleAddressType_t                        advertiserAddrType;
    uint8_t                                 advertiserAddr[gcBleDeviceAddressSize_c];
    uint8_t                                 advertiserPHY;
    uint16_t                                periodicAdvertisingInterval;
    uint8_t                                 advertiserClockAccuracy;
} hciLePeriodicAdvSyncEstbEvent_t;

/*! LE Periodic Advertising Report Event : LE Meta Event : 0x3E - Subevent Code : 0x0F */
typedef struct hciLePeriodicAdvReportEvent_tag
{
    hciErrorCode_t                          status; /* Host internal use only. */
    uint16_t                                syncHandle;
    uint8_t                                 txPower;
    uint8_t                                 rssi;
    hciBleExtAdvReportStatus_t              dataStatus;
    hciLeExtAdvReportEventData_t            *pData;
} hciLePeriodicAdvReportEvent_t;

/*! LE Periodic Advertising Sync Lost Event : LE Meta Event : 0x3E - Subevent Code : 0x10 */
typedef struct hciLePeriodicAdvSyncLostEvent_tag
{
    uint16_t                                syncHandle;
} hciLePeriodicAdvSyncLostEvent_t;

/*! LE Scan Timeout Event : LE Meta Event : 0x3E - Subevent Code : 0x11 */
/* Event has no parameters. */

/*! LE Advertising Set Terminated Event : LE Meta Event : 0x3E - Subevent Code : 0x12 */
typedef struct hciLeAdvSetTerminatedEvent_tag
{
    hciErrorCode_t                          status;
    uint8_t                                 advHandle;
    uint16_t                                connHandle;
    uint8_t                                 numCompletedExtAdvEvents;
} hciLeAdvSetTerminatedEvent_t;

/*! LE Scan Request Received Event : LE Meta Event : 0x3E - Subevent Code : 0x13 */
typedef struct hciLeScanReqReceivedEvent_tag
{
    uint8_t                                 advHandle;
    bleAddressType_t                        scannerAddrType;
    uint8_t                                 scannerAddr[gcBleDeviceAddressSize_c];
} hciLeScanReqReceivedEvent_t;

/*! LE Channel Selection Algorithm Event : LE Meta Event : 0x3E - Subevent Code : 0x14 */
typedef struct hciLeChannelSelAlgorithmEvent_tag
{
    uint16_t                                connHandle;
    uint8_t                                 channelSelectionAlgorithm;
} hciLeChannelSelAlgorithmEvent_t;
#endif

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
/*! OCF 0x0017 */
/*! HCI_LE_Encrypt */
typedef struct
{
    uint8_t             key[16];
    uint8_t             plaintextData[16];
} hciLeEncryptCommand_t;
#endif

/*! OCF 0x0018 */
/*! HCI_LE_Rand */
/*! No parameters */

/*! OCF 0x0019 */
/*! HCI_LE_Start_Encryption */
typedef struct
{
    uint16_t            connectionHandle;
    uint8_t             randomNumber[8];
    uint16_t            encryptedDiversifier;
    uint8_t             longTermKey[16];
} hciLeStartEncryptionCommand_t;

/*! Encryption Change Event : 0x08 */
typedef struct
{
    hciErrorCode_t              status;
    uint16_t                    connectionHandle;
    hciLlEncryptionEnabled_t    encryptionEnabled;
} hciEncryptionChangeEvent_t;

/*! Encryption Key refresh Complete Event : 0x30 */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciEncryptionKeyRefreshCompleteEvent_t;

/*! OCF 0x001A */
/*! HCI_LE_Long_Term_Key_Request_Reply */
typedef struct
{
    uint16_t            connectionHandle;
    uint8_t             longTermKey[16];
} hciLeLongTermKeyRequestReplyCommand_t;

/*! OCF 0x001B */
/*! HCI_LE_Long_Term_Key_Request_Negative_Reply */
typedef struct
{
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestNegativeReplyCommand_t;

/*! OCF 0x001D */
/*! HCI_LE_Receiver_Test */
typedef struct
{
    bleChannelFrequency_t   rxChannel;
} hciLeReceiverTestCommand_t;

/*! OCF 0x001E */
/*! HCI_LE_Transmitter_Test */
typedef struct
{
    bleChannelFrequency_t       txChannel;
    uint8_t                     lengthOfTestData;
    uint8_t                     packetPayload;
} hciLeTransmitterTestCommand_t;

/*! OCF 0x0020 */
/*! LE_Remote_Connection_Parameter_Request_Reply */
typedef struct
{
    uint16_t            connectionHandle;
    uint16_t            intervalMin;
    uint16_t            intervalMax;
    uint16_t            latency;
    uint16_t            timeout;
    uint16_t            minimumCeLength;
    uint16_t            maximumCeLength;
} hciLeRemoteConnectionParameterRequestReplyCommand_t;

/*! OCF 0x0021 */
/*! LE_Remote_Connection_Parameter_Request_Negative_Reply */
typedef struct
{
    uint16_t            connectionHandle;
    hciErrorCode_t      reason;
} hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t;

/*! HCI_LE_Set_Data_Length */
typedef struct
{
    uint16_t            connectionHandle;
    uint16_t            txOctets;
    uint16_t            txTime;
} hciLeSetDataLengthCommand_t;

/*! HCI_LE_Write_Suggested_Default_Data_Length */
typedef struct
{
    uint16_t            suggestedMaxTxOctets;
    uint16_t            suggestedMaxTxTime;
} hciLeWriteSuggestedDefaultDataLengthCommand_t;

/*! HCI_LE_Generate_DHKey */
typedef struct
{
    uint8_t             remoteP256PublicKey[64];
} hciLeGenerateDhKeyCommand_t;

/*! HCI_LE_Add_Device_To_Resolving_List */
typedef struct
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
    uint8_t             peerIRK[gcSmpIrkSize_c];
    uint8_t             localIRK[gcSmpIrkSize_c];
} hciLeAddDeviceToResolvingListCommand_t;

/*! HCI_LE_Remove_Device_From_Resolving_List */
typedef struct
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeRemoveDeviceFromResolvingListCommand_t;

/*! HCI_LE_Read_Peer_Resolvable_Address */
typedef struct
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeReadPeerResolvableAddressCommand_t;

/*! HCI_LE_Read_Local_Resolvable_Address */
typedef struct
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
} hciLeReadLocalResolvableAddressCommand_t;

/*! HCI_LE_Set_Address_Resolution_Enable */
typedef struct
{
    bool_t              addressResolutionEnable;
} hciLeSetAddressResolutionEnableCommand_t;

/*! HCI_LE_Set_Resolvable_Private_Address_Timeout */
typedef struct
{
    uint16_t            rpaTimeout;
} hciLeSetResolvablePrivateAddressTimeoutCommand_t;

/*! OCF 0x004E */
/*! HCI_LE_Set_Privacy_Mode */
typedef struct
{
    bleAddressType_t    peerIdentityAddressType;
    uint8_t             peerIdentityAddress[gcBleDeviceAddressSize_c];
    blePrivacyMode_t    privacyMode;
} hciLeSetPrivacyModeCommand_t;


/*! OCF 0x0030 */
/*! HCI_LE_Read_Phy */
typedef struct
{
    uint16_t            connectionHandle;
} hciLeReadPhyCommand_t;

/*! OCF 0x0031 */
/*! HCI_LE_Set_Default_Phy */
typedef struct
{
    uint8_t             allPhys;
    uint8_t             txPhys;
    uint8_t             rxPhys;
} hciLeSetDefaultPhyCommand_t;

/*! OCF 0x0032 */
/*! HCI_LE_Set_Phy */
typedef struct
{
    uint16_t            connectionHandle;
    uint8_t             allPhys;
    uint8_t             txPhys;
    uint8_t             rxPhys;
    uint16_t            phyOptions;
} hciLeSetPhyCommand_t;

/*! OCF 0x0033 */
/*! HCI_LE_Enhanced_Receiver_Test */
typedef struct
{
    uint8_t             rxChannel;
    uint8_t             phy;
    uint8_t             modulationIndex;
} hciLeEnhancedReceiverTestCommand_t;

/*! OCF 0x0034 */
/*! HCI_LE_Enhanced_Transmitter_Test */
typedef struct
{
    uint8_t             txChannel;
    uint8_t             dataLen;
    uint8_t             payloadType;
    uint8_t             phy;
} hciLeEnhancedTransmitterTestCommand_t;

typedef struct
{
    uint16_t            cmdFlag;
    uint8_t*            pParams;
    uint8_t             paramsLength;
}hciVendorSpecificDebugCommand_t;

typedef struct
{
    uint8_t                       powerLevel;
    bleTransmitPowerChannelType_t channelType;
} hciSetTxPowerLevelCommand_t;

typedef struct
{
    hciErrorCode_t                status;
} hciSetTxPowerCommandComplete_t;

typedef struct
{
    uint16_t    connectionHandle;
    uint16_t    eventType;      /*! bleNotificationEventType_t */
} hciVendorEnhancedNotificationCommand_t;

typedef struct
{
    hciErrorCode_t                status;
} hciVendorEnhancedNotificationCommandComplete_t;

#if (gBLE50_d == TRUE)
/*! OCF 0x0035 */
/*! HCI_LE_Set_Advertising_Set_Random_Address */
typedef struct hciLeSetAdvSetRandomAddrCommand_tag
{
    uint8_t                      advertisingHandle;
    uint8_t                      randomAddress[gcBleDeviceAddressSize_c];
}hciLeSetAdvSetRandomAddrCommand_t;

/*! OCF 0x0036 */
/*! HCI_LE_Set_Ext_Advertising_Parameters */
typedef struct hciLeSetExtAdvParamsCommand_tag
{
    uint8_t                      advertisingHandle;
    uint16_t                     advertisingEventProperties;
    uint32_t                     primaryAdvertisingIntervalMin;
    uint32_t                     primaryAdvertisingIntervalMax;
    bleAdvertisingChannelMap_t   primaryAdvertisingChannelMap;
    hciBleAddressType_t          ownAddressType;
    hciBleAddressType_t          peerAddressType;
    uint8_t                      peerAddress[gcBleDeviceAddressSize_c];
    bleAdvertisingFilterPolicy_t advertisingFilterPolicy;
    int8_t                       advertisingTxPower;
    uint8_t                      primaryAdvertisingPHY;
    uint8_t                      secondaryAdvertisingMaxSkip;
    uint8_t                      secondaryAdvertisingPHY;
    uint8_t                      advertisingSID;
    uint8_t                      scanRequestNotificationEnable;
} hciLeSetExtAdvParamsCommand_t;

/*! OCF 0x0037 */
/*! HCI_LE_Set_Ext_Advertising_Data */
typedef struct hciLeSetExtAdvertisingDataCommand_tag
{
    uint8_t                      advertisingHandle;
    hciBleExtDataOperation_t     operation;
    hciBleFragmentPreference_t   fragmentPreference;
    uint8_t                      advertisingDataLength;
    const uint8_t               *pAdvertisingData;
} hciLeSetExtAdvertisingDataCommand_t;

/*! OCF 0x0038 */
/*! HCI_LE_Set_Ext_Scan_Response Data */
typedef struct hciLeSetExtScanRespDataCommand_tag
{
    uint8_t                      advertisingHandle;
    hciBleExtDataOperation_t     operation;
    hciBleFragmentPreference_t   fragmentPreference;
    uint8_t                      scanResponseDataLength;
    const uint8_t               *pScanResponseData;
} hciLeSetExtScanRespDataCommand_t;

/*! OCF 0x0039 */
/*! HCI_LE_Set_Extended_Advertising_Enable */
typedef struct hciLeSetExtAdvEnableCommand_tag
{
    uint8_t                      enable;
    uint8_t                      numberOfSets;
    uint8_t                      advertisingHandle[gHciMaxAdvertisingSets_c];
    uint16_t                     duration[gHciMaxAdvertisingSets_c];
    uint8_t                      maxExtAdvertisingEvents[gHciMaxAdvertisingSets_c];
} hciLeSetExtAdvEnableCommand_t;

/*! OCF 0x003A */
/*! HCI_LE_Read_Maximum_Advertising_Data_Length - No parameters */

/*! OCF 0x003B */
/*! HCI_LE_Read_Number_Of_Supported_Advertising_Sets - No parameters */

/*! OCF 0x003C */
/*! HCI_LE_Remove_Advertising_Set */
typedef struct hciLeRemoveAdvSetCommand_tag
{
    uint8_t                      advertisingHandle;
} hciLeRemoveAdvSetCommand_t;

/*! OCF 0x003D */
/*! HCI_LE_Clear_Advertising_Sets - No parameters */

/*! OCF 0x003E */
/*! HCI_LE_Set_Periodic_Advertising_Parameters */
typedef struct hciLeSetPeriodicAdvParamsCommand_tag
{
    uint8_t                      advertisingHandle;
    uint16_t                     periodicAdvertisingIntervalMin;
    uint16_t                     periodicAdvertisingIntervalMax;
    uint16_t                     periodicAdvertisingProperties;
} hciLeSetPeriodicAdvParamsCommand_t;

/*! OCF 0x003F */
/*! HCI_LE_Set_Periodic_Advertising_Data */
typedef struct hciLeSetPeriodicAdvDataCommand_tag
{
    uint8_t                     advertisingHandle;
    uint8_t                     operation;
    uint8_t                     advertisingDataLength;
    uint8_t                     *pAdvertisingData;
} hciLeSetPeriodicAdvDataCommand_t;

/*! OCF 0x0040 */
/*! HCI_LE_Set_Periodic_Advertising_Enable */
typedef struct hciLeSetPeriodicAdvEnableCommand_tag
{
    uint8_t enable;
    uint8_t advertisingHandle;
} hciLeSetPeriodicAdvEnableCommand_t;

/*! OCF 0x0041 */
/*! HCI_LE_Set_Ext_Scan_Parameters */
typedef struct hciLeSetExtScanParamsCommand_tag
{
    hciBleAddressType_t          ownAddressType;
    bleScanningFilterPolicy_t    scanningFilterPolicy;
    uint8_t                      scanningPHYs;
    bleScanType_t                scanType;
    uint16_t                     scanInterval;
    uint16_t                     scanWindow;
} hciLeSetExtScanParamsCommand_t;

/*! OCF 0x0042 */
/*! HCI_LE_Ext_Scan_Enable */
typedef struct hciLeExtScanEnableCommand_tag
{
    hciLeScanEnable_t            enable;
    hciLeFilterDuplicates_t      filterDuplicates;
    uint16_t                     duration;
    uint16_t                     period;
} hciLeExtScanEnableCommand_t;

/*! OCF 0x0043 */
/*! HCI_LE_Ext_Create_Connection */
typedef struct hciLeExtCreateConnectionCommand_tag
{
    bleInitiatorFilterPolicy_t   initiatorFilterPolicy;
    hciBleAddressType_t          ownAddressType;
    hciBleAddressType_t          peerAddressType;
    uint8_t                      peerAddress[gcBleDeviceAddressSize_c];
    uint8_t                      initiatingPHYs;
    uint16_t                     scanInterval[gHciMaxPHYs_c];
    uint16_t                     scanWindow[gHciMaxPHYs_c];
    uint16_t                     connIntervalMin[gHciMaxPHYs_c];
    uint16_t                     connIntervalMax[gHciMaxPHYs_c];
    uint16_t                     connLatency[gHciMaxPHYs_c];
    uint16_t                     supervisionTimeout[gHciMaxPHYs_c];
    uint16_t                     minimumCELength[gHciMaxPHYs_c];
    uint16_t                     maximumCELength[gHciMaxPHYs_c];
} hciLeExtCreateConnectionCommand_t;

/*! OCF 0x0044 */
/*! HCI_LE_Periodic_Advertising_Create_Sync */
typedef struct hciLePeriodicAdvCreateSyncCommand_tag
{
    bleInitiatorFilterPolicy_t   filterPolicy;
    uint8_t                      advertisingSID;
    hciBleAddressType_t          advertiserAddressType;
    uint8_t                      advertiserAddress[gcBleDeviceAddressSize_c];
    uint16_t                     skip;
    uint16_t                     syncTimeout;
    uint8_t                      unused;
} hciLePeriodicAdvCreateSyncCommand_t;

/*! OCF 0x0045 */
/*! HCI_LE_Periodic_Advertising_Create_Sync_Cancel - No parameters */

/*! OCF 0x0046 */
/*! HCI_LE_Periodic_Advertising_Terminate_Sync */
typedef struct hciLePeriodicAdvTerminateSyncCommand_tag
{
    uint16_t                     syncHandle;
} hciLePeriodicAdvTerminateSyncCommand_t;

/*! OCF 0x0047 */
/*! HCI_LE_Add_Device_To_Periodic Advertiser_List */
typedef struct hciLeAddDeviceToPeriodicAdvListCommand_tag
{
    hciBleAddressType_t          advertiserAddressType;
    uint8_t                      advertiserAddress[gcBleDeviceAddressSize_c];
    uint8_t                      advertisingSID;
} hciLeAddDeviceToPeriodicAdvListCommand_t;

/*! OCF 0x0048 */
/*! HCI_LE_Remove_Device_From_Periodic_Advertiser_List */
typedef struct hciLeRemoveDeviceFromPeriodicAdvListCommand_tag
{
    hciBleAddressType_t          advertiserAddressType;
    uint8_t                      advertiserAddress[gcBleDeviceAddressSize_c];
    uint8_t                      advertisingSID;
} hciLeRemoveDeviceFromPeriodicAdvListCommand_t;

/*! OCF 0x0049 */
/*! HCI_LE_Clear_Periodic_Advertiser_List - No parameters */

/*! OCF 0x004A */
/*! HCI_LE_Read_Periodic_Advertiser_List_Size - No parameters */

#endif /* (gBLE50_d == TRUE) */

/*
* Command Complete Parameters
*/
/*! HCI Command Complete Events ************************************************
*   OGF : 0x08 : LE Controller Commands
***************************************************************************** */
/*! HCI_LE_Set_Event_Mask - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetEventMaskCommandComplete_t;

/*! HCI_LE_Read_Buffer_Size - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            hcLeDataPacketLength;
    uint8_t             hcTotalNumLeDataPackets;
} hciLeReadBufferSizeCommandComplete_t;

/*! HCI_LE_Read_Local_Supported_Features - Return Parameters */
/* Only LMP Feature Page 0 is supported and required by BLE */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             leFeatures[8]; /* hciLeSupportedFeatures_tag */
} hciLeReadLocalSupportedFeaturesCommandComplete_t;

/*! HCI_LE_Set_Random_Address - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetRandomAddressCommandComplete_t;

/*! HCI_LE_Set_Advertising_Parameters - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetAdvertingParametersCommandComplete_t;

/*! HCI_LE_Read_Advertising_Channel_Tx_Power - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    int8_t              transmitPowerlevel; /* This is a signed 8 bit integer - Range: -20..10 dBm */
} hciLeReadAdvertisingChannelTxPowerCommandComplete_t;

/*! HCI_LE_Set_Advertising_Data - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetAdvertisingDataCommandComplete_t;

/*! HCI_LE_Set_Scan_Response_Data - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetScanResponseDataCommandComplete_t;

/*! HCI_LE_Set_Advertising_Enable - Return Parameters */
typedef struct
{
    hciErrorCode_t              status;
} hciLeSetAdvertisingEnableCommandComplete_t;

/*! HCI_LE_Set_Scan_Parameters - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetScanParametersCommandComplete_t;

/*! HCI_LE_Set_Scan_Enable - Return Parameters */
typedef struct
{
    hciErrorCode_t              status;
} hciLeSetScanEnableCommandComplete_t;

/*! HCI_LE_Create_Connection_Cancel - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeCreateConnectionCancelCommandComplete_t;

/*! HCI_LE_Read_White_List_Size - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             whiteListSize;
} hciLeReadWhiteListSizeCommandComplete_t;

/*! HCI_LE_Clear_White_List - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeClearWhiteListCommandComplete_t;

/*! HCI_LE_Add_Device_To_White_List - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeAddDeviceToWhiteListCommandComplete_t;

/*! HCI_LE_Remove_Device_From_White_List - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeRemoveDeviceFromWhiteListCommandComplete_t;

/*! HCI_LE_Set_Host_Channel_Classification - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetHostChannelClassificationCommandComplete_t;

/*! HCI_LE_Read_Channel_Map - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             channelMap[gcBleChannelMapSize_c];
} hciLeReadChannelMapCommandComplete_t;

#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
/*! HCI_LE_Encrypt - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             encryptedData[16];
} hciLeEncryptCommandComplete_t;
#endif

#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
/*! HCI_LE_Rand - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             randomNumber[8];
} hciLeRandCommandComplete_t;
#endif

/*! HCI_LE_Long_Term_Key_Request_Reply - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestReplyCommandComplete_t;

/*! HCI_LE_Long_Term_Key_Request_Negative_Reply - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeLongTermKeyRequestNegativeReplyCommandComplete_t;

/*! HCI_LE_Read_Supported_States - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             leStates[8]; /* hciLeLLSupportedStatesShift_t */
} hciLeReadSupportedStatesCommandComplete_t;

/*! HCI_LE_Receiver_Test - Return Parameters */
typedef struct
{
    hciErrorCode_t          status;
} hciLeReceiverTestCommandComplete_t;

/*! HCI_LE_Transmitter_Test - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeTransmitterTestCommandComplete_t;

/*! HCI_LE_Test_End - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            numberOfPackets;
} hciLeTestEndCommandComplete_t;

/*! LE_Remote_Connection_Parameter_Request_Reply - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeRemoteConnectionParameterRequestReplyCommandComplete_t;

/*! LE_Remote_Connection_Parameter_Request_Negative_Reply - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeRemoteConnectionParameterRequestNegativeReplyCommandComplete_t;

/*! HCI_LE_Set_Data_Length Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
} hciLeSetDataLengthCommandComplete_t;

/*! HCI_LE_Read_Suggested_Default_Data_Length Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            suggestedMaxTxOctets;
    uint16_t            suggestedMaxTxTime;
} hciLeReadSuggestedDefaultDataLengthCommandComplete_t;

/*! HCI_LE_Write_Suggested_Default_Data_Length Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeWriteSuggestedDefaultDataLengthCommandComplete_t;

/*! HCI_LE_Add_Device_To_Resolving_List Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeAddDeviceToResolvingListCommandComplete_t;

/*! HCI_LE_Clear_Resolving_List Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeClearResolvingListCommandComplete_t;

/*! HCI_LE_Read_Peer_Resolvable_Address Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             peerResolvableAddress[gcBleDeviceAddressSize_c];
} hciLeReadPeerResolvableAddressCommandComplete_t;

/*! HCI_LE_Read_Local_Resolvable_Address Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint8_t             localResolvableAddress[gcBleDeviceAddressSize_c];
} hciLeReadLocalResolvableAddressCommandComplete_t;

/*! HCI_LE_Set_Address_Resolution_Enable Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetAddressResolutionEnableCommandComplete_t;

/*! HCI_LE_Set_Resolvable_Private_Address_Timeout Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetResolvablePrivateAddressTimeoutCommandComplete_t;

/*! HCI_LE_Set_Privacy_Mode */
typedef struct hciLeSetPrivacyModeCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetPrivacyModeCommandComplete_t;


/*! HCI_LE_Read_Phy - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
    uint16_t            connectionHandle;
    uint8_t             txPhy;
    uint8_t             rxPhy;
} hciLeReadPhyCommandComplete_t;

/*! HCI_LE_Set_Default_Phy - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeSetDefaultPhyCommandComplete_t;

/*! HCI_LE_Enhanced_Receiver_Test - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeEnhancedReceieverTestCommandComplete_t;

/*! HCI_LE_Enhanced_Transmitter_Test - Return Parameters */
typedef struct
{
    hciErrorCode_t      status;
} hciLeEnhancedTransmitterTestCommandComplete_t;

#if (gBLE50_d == TRUE)
/*! HCI_LE_Set_Advertising_Set_Random_Address - Return Parameters */
typedef struct hciLeSetAdvSetRandomAddrCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetAdvSetRandomAddrCommandComplete_t;

/*! HCI_LE_Set_Ext_Advertising_Parameters - Return Parameters */
typedef struct hciLeSetExtAdvParamsCommandComplete_tag
{
    hciErrorCode_t      status;
    int8_t              transmitPowerlevel; /* This is a signed 8 bit integer - Range: -20..10 dBm */
} hciLeSetExtAdvertingParamsCommandComplete_t;

/*! HCI_LE_Set_Ext_Advertising_Data - Return Parameters */
typedef struct hciLeSetExtAdvertisingDataCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetExtAdvertingDataCommandComplete_t;

/*! HCI_LE_Set_Ext_Scan_Response_Data - Return Parameters */
typedef struct hciLeSetExtScanRespDataCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetExtScanRespDataCommandComplete_t;

/*! HCI_LE_Set_Extended_Advertising_Enable - Return Parameters */
typedef struct hciLeSetExtAdvEnableCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetExtAdvEnableCommandComplete_t;

/*! HCI_LE_Read_Maximum_Advertising_Data_Length - Return Parameters */
typedef struct hciLeReadMaxAdvDataLenCommandComplete_tag
{
    hciErrorCode_t      status;
    uint16_t            maxAdvDataLen;
} hciLeReadMaxAdvDataLenCommandComplete_t;

/*! HCI_LE_Read_Number_Of_Supported_Advertising_Sets - Return Parameters */
typedef struct hciLeReadNumOfSupportedAdvSetsCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             numOfAdvSets;
} hciLeReadNumOfSupportedAdvSetsCommandComplete_t;

/*! HCI_LE_Remove_Advertising_Set */
typedef struct hciLeRemoveAdvSetCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeRemoveAdvSetCommandComplete_t;

/*! HCI_LE_Clear_Advertising_Sets - Return Parameters */
typedef struct hciLeClearAdvSetsCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeClearAdvSetsCommandComplete_t;

/*! HCI_LE_Set_Periodic_Advertising_Parameters */
typedef struct hciLeSetPeriodicAdvParamsCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetPeriodicAdvParamsCommandComplete_t;

/*! HCI_LE_Set_Periodic_Advertising_Data - Return Parameters */
typedef struct hciLeSetPeriodicAdvDataCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetPeriodicAdvDataCommandComplete_t;

/*! HCI_LE_Set_Periodic_Advertising_Enable - Return Parameters */
typedef struct hciLeSetPeriodicAdvEnableCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetPeriodicAdvEnableCommandComplete_t;

/*! HCI_LE_Set_Ext_Scan_Parameters - Return Parameters */
typedef struct hciLeSetExtScanParamsCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetExtScanParamsCommandComplete_t;

/*! HCI_LE_Set_Ext_Scan_Enable - Return Parameters */
typedef struct hciLeSetExtScanEnableCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeSetExtScanEnableCommandComplete_t;

/*! HCI_LE_Periodic_Advertising_Create_Sync_Cancel - Return Parameters */
typedef struct hciLePeriodicAdvCreateSyncCancelCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLePeriodicAdvCreateSyncCancelCommandComplete_t;

/*! HCI_LE_Periodic_Advertising_Terminate_Sync */
typedef struct hciLePeriodicAdvTerminateSyncCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLePeriodicAdvTerminateSyncCommandComplete_t;

/*! HCI_LE_Clear_Periodic_Advertiser_List - Return Parameters */
typedef struct hciLeClearPeriodicAdvListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeClearPeriodicAdvListCommandComplete_t;

typedef struct hciLeAddDeviceToPeriodicAdvListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeAddDeviceToPeriodicAdvListCommandComplete_t;

/*! HCI_LE_Remove_Device_From_Periodic_Advertiser_List - Return Parameters */
typedef struct hciLeRemoveDeviceFromPeriodicAdvListCommandComplete_tag
{
    hciErrorCode_t      status;
} hciLeRemoveDeviceFromPeriodicAdvListCommandComplete_t;

/*! HCI_LE_Read_Periodic_Advertiser_List_Size */
typedef struct hciLeReadPeriodicAdvListSizeCommandComplete_tag
{
    hciErrorCode_t      status;
    uint8_t             periodicAdvListSize;
} hciLeReadPeriodicAdvListSizeCommandComplete_t;

#endif /* (gBLE50_d == TRUE) */

/*! LE Meta Event : 0x3E */
typedef struct
{
    hciLeMetaSubEventCode_t        subEventCode;
    PACKED_UNION
    {
        hciLeConnectionCompleteEvent_t                  hciLeConnCompleteEvent;
        hciLeAdvertisingReportEvent_t                   hciLeAdvReportEvent;
        hciLeConnectionUpdateCompleteEvent_t            hciLeConnUpdateCompleteEvent;
        hciLeReadRemoteFeaturesCompleteEvent_t          hciLeReadRemoteFeaturesCompleteEvent;
        hciLeLongTermKeyRequestEvent_t                  hciLeLongTermKeyReqEvent;
        hciLeRemoteConnectionParameterRequestEvent_t    hciLeRemoteConnectionParameterRequestEvent;
        hciLeDataLengthChangeEvent_t                    hciLeDataLengthChangeEvent;
        hciLeReadLocalP256PublicKeyCompleteEvent_t      hciLeReadLocalP256PublicKeyCompleteEvent;
        hciLeGenerateDhKeyCompleteEvent_t               hciLeGenerateDhKeyCompleteEvent;
        hciLeEnhancedConnectionCompleteEvent_t          hciLeEnhancedConnCompleteEvent;
        hciLeDirectedAdvertisingReportEvent_t           hciLeDirectedAdvReportEvent;
        hciLePhyUpdateCompleteEvent_t                   hciLePhyUpdateCompleteEvent;
#if (gBLE50_d == TRUE)
        hciLeExtAdvReportEvent_t                        hciLeExtAdvReportEvent;
        hciLePeriodicAdvReportEvent_t                   hciLePeriodicAdvReportEvent;
        hciLePeriodicAdvSyncEstbEvent_t                 hciLePeriodicAdvSyncEstbEvent;
        hciLePeriodicAdvSyncLostEvent_t                 hciLePeriodicAdvSyncLostEvent;
        hciLeAdvSetTerminatedEvent_t                    hciLeAdvSetTerminatedEvent;
        hciLeScanReqReceivedEvent_t                     hciLeScanReqReceivedEvent;
        hciLeChannelSelAlgorithmEvent_t                 hciLeChannelSelAlgorithm;
#endif
        hciVendorEnhancedNotificationEvent_t            hciEnhancedNotificationEvent;
    }eventData;
} hciLeMetaEvent_t;

typedef struct
{
    uint8_t                 numHciCommandPackets;
    hciCommandOpCode_t      commandOpCode;
    union
    {
        hciErrorCode_t                                          status;
        /*! HCI OGF : 0x03 : Controller & Baseband Commands */
        hciSetEventMaskCommandComplete_t                        hciSetEventMaskCommComplete;
        hciResetCommandComplete_t                               hciResetCommComplete;
        hciReadTransmitPowerLevelCommandComplete_t              hciReadTransmitPowerLevelCommComplete;
        hciSetControllerToHostFlowControlCommandComplete_t      hciSetControllerToHostFlowControlCommComplete;
        hciHostBufferSizeCommandComplete_t                      hciHostBufferSizeCommComplete;
        hciHostNumberOfCompletedPacketsCommandComplete_t        hciHostNumberOfCompletedPacketsCommComplete;
        hciSetEventMaskPage2CommandComplete_t                   hciSetEventMaskPage2CommComplete;
        hciReadAuthenticatedPayloadTimeoutCommandComplete_t     hciReadAuthenticatedPayloadTimeoutCommComplete;
        hciWriteAuthenticatedPayloadTimeoutCommandComplete_t    hciWriteAuthenticatedPayloadTimeoutCommComplete;
        /*! HCI OGF : 0x04 : Informational Parameters */
        hciReadLocalVersionInfoCommandComplete_t                hciReadLocalVersionInfoCommComplete;
        hciReadLocalSupportedCommandsCommandComplete_t          hciReadLocalSupportedCommandsCommComplete;
        hciReadLocalSupportedFeaturesCommandComplete_t          hciReadLocalSupportedFeaturesCommComplete;
        hciReadBdAddrCommandComplete_t                          hciReadBdAddrCommComplete;
        /*! HCI OGF : 0x05 : Status Parameters */
        hciReadRssiCommandComplete_t                            hciReadRssiCommComplete;
        /*! HCI OGF : 0x08 : LE Controller Commands */
        hciLeSetEventMaskCommandComplete_t                      hciLeSetEventMaskCommComplete;
        hciLeReadBufferSizeCommandComplete_t                    hciLeReadBufferSizeCommComplete;
        hciLeReadLocalSupportedFeaturesCommandComplete_t        hciLeReadLocalSupportedFeaturesCommComplete;
        hciLeSetRandomAddressCommandComplete_t                  hciLeSetRandomAddressCommComplete;
        hciLeSetAdvertingParametersCommandComplete_t            hciLeSetAdvertingParametersCommComplete;
        hciLeReadAdvertisingChannelTxPowerCommandComplete_t     hciLeReadAdvertisingChannelTxPowerCommComplete;
        hciLeSetAdvertisingDataCommandComplete_t                hciLeSetAdvertiseDataCommComplete;
        hciLeSetScanResponseDataCommandComplete_t               hciLeSetScanResponseDataCommComplete;
        hciLeSetAdvertisingEnableCommandComplete_t              hciLeSetAdvertisingEnableCommComplete;
        hciLeSetScanParametersCommandComplete_t                 hciLeSetScanParametersCommComplete;
        hciLeSetScanEnableCommandComplete_t                     hciLeSetScanEnableCommComplete;
        hciLeCreateConnectionCancelCommandComplete_t            hciLeCreateConnectionCancelCommComplete;
        hciLeReadWhiteListSizeCommandComplete_t                 hciLeReadWhiteListSizeCommComplete;
        hciLeClearWhiteListCommandComplete_t                    hciLeClearWhiteListCommComplete;
        hciLeAddDeviceToWhiteListCommandComplete_t              hciLeAddDeviceToWhiteListCommComplete;
        hciLeRemoveDeviceFromWhiteListCommandComplete_t         hciLeRemoveDeviceFromWhiteListCommComplete;
        hciLeSetHostChannelClassificationCommandComplete_t      hciLeSetHostChannelClassificationCommComplete;
        hciLeReadChannelMapCommandComplete_t                    hciLeReadChannelMapCommComplete;
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)
        hciLeEncryptCommandComplete_t                           hciLeEncryptCommComplete;
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)
        hciLeRandCommandComplete_t                              hciLeRandCommComplete;
#endif
        hciLeLongTermKeyRequestReplyCommandComplete_t           hciLeLongTermKeyRequestReplyCommComplete;
        hciLeLongTermKeyRequestNegativeReplyCommandComplete_t   hciLeLongTermKeyRequestNegativeReplyCommComplete;
        hciLeReadSupportedStatesCommandComplete_t               hciLeReadSupportedStatesCommComplete;
        hciLeReceiverTestCommandComplete_t                      hciLeReceiverTestCommComplete;
        hciLeTransmitterTestCommandComplete_t                   hciLeTransmitterTestCommComplete;
        hciLeTestEndCommandComplete_t                           hciLeTestEndCommComplete;
        hciLeRemoteConnectionParameterRequestReplyCommandComplete_t             hciLeRemoteConnectionParameterRequestReplyCommComplete;
        hciLeRemoteConnectionParameterRequestNegativeReplyCommandComplete_t     hciLeRemoteConnectionParameterRequestNegativeReplyCommComplete;
        hciLeWriteSuggestedDefaultDataLengthCommandComplete_t    hciLeWriteSuggestedDefaultDataLengthCommComplete;
        hciLeReadSuggestedDefaultDataLengthCommandComplete_t     hciLeReadSuggestedDefaultDataLengthCommComplete;
        hciLeSetDataLengthCommandComplete_t                      hciLeSetDataLengthCommComplete;
        hciLeSetResolvablePrivateAddressTimeoutCommandComplete_t hciLeSetResolvablePrivateAddressTimeoutCommComplete;
        hciLeSetAddressResolutionEnableCommandComplete_t         hciLeSetAddressResolutionEnableCommComplete;
        hciLeClearResolvingListCommandComplete_t                 hciLeClearResolvingListCommComplete;
        hciLeAddDeviceToResolvingListCommandComplete_t           hciLeAddDeviceToResolvingListCommComplete;
        hciLeReadPeerResolvableAddressCommandComplete_t          hciLeReadPeerResolvableAddressCommComplete;
        hciLeReadLocalResolvableAddressCommandComplete_t         hciLeReadLocalResolvableAddressCommComplete;
        hciLeSetPrivacyModeCommandComplete_t                     hciLeSetPrivacyModeCommComplete;
        /* v5.0 */
        hciLeReadPhyCommandComplete_t                            hciLeReadPhyCommandComplete;
        hciLeSetDefaultPhyCommandComplete_t                      hciLeSetDefaultPhyCommandComplete;
        hciLeEnhancedReceieverTestCommandComplete_t              hciLeEnhancedReceieverTestCommandComplete;
        hciLeEnhancedTransmitterTestCommandComplete_t            hciLeEnhancedTransmitterTestCommandComplete;
        hciSetTxPowerCommandComplete_t                           hciSetTxPowerCommComplete;
        hciVendorEnhancedNotificationCommandComplete_t           hciVendorEnhNotifCommComplete;
#if (gBLE50_d == TRUE)
        hciLeSetAdvSetRandomAddrCommandComplete_t                hciLeSetAdvSetRandomAddrCommComplete;
        hciLeSetExtAdvertingParamsCommandComplete_t              hciLeSetExtAdvertingParamsCommComplete;
        hciLeSetExtAdvertingDataCommandComplete_t                hciLeSetExtAdvertingDataCommComplete;
        hciLeSetExtScanRespDataCommandComplete_t                 hciLeSetExtScanRespDataCommComplete;
        hciLeSetExtAdvEnableCommandComplete_t                    hciLeSetExtAdvEnableCommComplete;
        hciLeReadMaxAdvDataLenCommandComplete_t                  hciLeReadMaxAdvDataLenCommComplete;
        hciLeReadNumOfSupportedAdvSetsCommandComplete_t          hciLeReadNumOfSupportedAdvSetsCommComplete;
        hciLeRemoveAdvSetCommandComplete_t                       hciLeRemoveAdvSetCommComplete;
        hciLeClearAdvSetsCommandComplete_t                       hciLeClearAdvSetsCommComplete;
        hciLeSetPeriodicAdvParamsCommandComplete_t               hciLeSetPeriodicAdvParamsCommComplete;
        hciLeSetPeriodicAdvDataCommandComplete_t                 hciLeSetPeriodicAdvDataCommComplete;
        hciLeSetPeriodicAdvEnableCommandComplete_t               hciLeSetPeriodicAdvEnableCommComplete;
        hciLeSetExtScanParamsCommandComplete_t                   hciLeSetExtScanParamsCommComplete;
        hciLeSetExtScanEnableCommandComplete_t                   hciLeSetExtScanEnableCommComplete;
        hciLePeriodicAdvCreateSyncCancelCommandComplete_t        hciLePeriodicAdvCreateSyncCancelCommComplete;
        hciLePeriodicAdvTerminateSyncCommandComplete_t           hciLePeriodicAdvTerminateSyncCommComplete;
        hciLeAddDeviceToPeriodicAdvListCommandComplete_t         hciLeAddDeviceToPeriodicAdvListCommComplete;
        hciLeRemoveDeviceFromPeriodicAdvListCommandComplete_t    hciLeRemoveDeviceFromPeriodicAdvListCommComplete;
        hciLeClearPeriodicAdvListCommandComplete_t               hciLeClearPeriodicAdvListCommComplete;
        hciLeReadPeriodicAdvListSizeCommandComplete_t            hciLeReadPeriodicAdvListSizeCommComplete;
#endif
    }commCompleteReturnParams;
} hciCommandCompleteEvent_t;

typedef struct
{
    hciEventCode_t      eventCode;
    uint8_t             parLength;
    union
    {
        hciDisconnectionCompleteEvent_t                 hciDisconnectionCompleteEvent;
        hciEncryptionChangeEvent_t                      hciEncryptionChangeEvent;
        hciReadRemoteVersionInformationCompleteEvent_t  hciReadRemoteVersionInformationCompleteEvent;
        hciCommandCompleteEvent_t                       hciCommandCompleteEvent;
        hciCommandStatusEvent_t                         hciCommandStatusEvent;
        hciHardwareErrorEvent_t                         hciHardwareErrorEvent;
        hciNumberOfCompletedPacketsEvent_t              hciNumberOfCompletedPacketsEvent;
        hciDataBufferOverflowEvent_t                    hciDataBufferOverflowEvent;
        hciEncryptionKeyRefreshCompleteEvent_t          hciEncryptionKeyRefreshCompleteEvent;
        hciLeMetaEvent_t                                hciLeMetaEvent;
        hciAuthenticatedPayloadTimeoutExpiredEvent_t    hciAuthenticatedPayloadTimeoutExpiredEvent;
    }eventData;
} hciEvent_t;

/*! ****************************************************************************
*   COMMANDS
***************************************************************************** */

/*! ****************************************************************************
*   DATA PACKETS
***************************************************************************** */

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

extern const uint8_t gMaxAdvReportQueueSize;

/************************************************************************************
*************************************************************************************
* Interface callback type definitions
*************************************************************************************
************************************************************************************/
typedef bleResult_t (*hciLeEventCallback_t) (hciLeMetaEvent_t* pEvent);

typedef bleResult_t (*hciCommandCompleteCallback_t) (hciCommandCompleteEvent_t* pEvent);

typedef bleResult_t (*hciCommandStatusCallback_t) (hciCommandStatusEvent_t* pEvent);

typedef bleResult_t (*hciEventCallback_t) (hciEvent_t* pEvent);

typedef bleResult_t (*hciAclDataCallback_t) (uint16_t connectionHandle, void* pPacket);

typedef struct
{
    /* LE Controller Uplink Interface function pointer */
    hciHostToControllerInterface_t   pHostToController;
}hciInterfaceStruct_t;

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#ifdef __cplusplus
    extern "C" {
#endif

/* Generic Interface */

/*! *********************************************************************************
* \fn           bleResult_t Hci_Init ( const hciInterfaceStruct_t* pConfigStruct )
*
* \brief        Clears HCI local data and registers the Controller interface send packet function.
*
* \param[in]    pConfigStruct pointer to the HCI configuration structure.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */
bleResult_t Hci_Init(
                const hciInterfaceStruct_t* pConfigStruct);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterLeEventCallback ( hciLeEventCallback_t pLeCallback )
*
* \brief        Function used by GAP to register LE Meta event callback in HCI.
*
* \param[in]    pLeCallback     LE Meta event callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */

bleResult_t Hci_RegisterLeEventCallback(
                hciLeEventCallback_t pLeCallback);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterCommandCompleteEventCallback ( hciCommandCompleteCallback_t pCcCallback )
*
* \brief        Function used by GAP to register command complete event callback in HCI.
*
* \param[in]    pCcCallback     command complete event callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */
bleResult_t Hci_RegisterCommandCompleteEventCallback(
                hciCommandCompleteCallback_t pCcCallback);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterCommandStatusEventCallback ( hciCommandStatusCallback_t pCsCallback )
*
* \brief        Function used by GAP to register command status event callback in HCI.
*
* \param[in]    pCsCallback     command status event callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */
bleResult_t Hci_RegisterCommandStatusEventCallback(
                hciCommandStatusCallback_t pCsCallback);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterGenericEventCallback ( hciEventCallback_t pCallback )
*
* \brief        Function used by GAP to register generic event callback in HCI.
*
* \param[in]    pCallback      generic event callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */

bleResult_t Hci_RegisterGenericEventCallback(
                hciEventCallback_t pCallback);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterL2caCallback ( hciEventCallback_t pCallback, hciAclDataCallback_t pAclCallback )
*
* \brief        Function used by L2CAP to register event callback and data receive callback in HCI.
*
* \param[in]    pCallback          event callback to register.
* \param[in]    pAclCallback       data receive callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */
bleResult_t Hci_RegisterL2caCallback(
                hciEventCallback_t      pCallback,
                hciAclDataCallback_t    pAclCallback);

/*! *********************************************************************************
* \fn           bleResult_t Hci_RegisterSmCallback ( hciEventCallback_t pSmCallback )
*
* \brief        Function used by SM to register event callback in HCI.
*
* \param[in]    pSmCallback        event callback to register.
* \param[out]   None
*
* \return       Status
*
* \remarks      Generic Interface
*
********************************************************************************** */
bleResult_t Hci_RegisterSmCallback(
                hciEventCallback_t pSmCallback);


/* Device Setup Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_Reset( void )
*
* \brief        The Reset command will reset the Controller and the Link Layer on the
*               LE Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Device Setup Group
*
********************************************************************************** */
bleResult_t Hci_Reset(void);                                                                    /* 3.2 */

/* Controller Flow Control Group */
#if (gHciBrEdrCommandSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadBufferSize( void )
*
* \brief        The function sends the HCI Read Buffer Size (OGF : 0x04; OCF : 0x0005) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Flow Control Group
*               On an Primary Controller that supports LE only, the Read_Buffer_Size
*               command shall not be supported (the LE_Read_Buffer_Size command is to be
*               used in this case).
*
********************************************************************************** */
bleResult_t Hci_ReadBufferSize(void);                                                           /* 4.5 */
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadBufferSize( void )
*
* \brief        The function sends the HCI LE Read Buffer Size (OGF : 0x08; OCF : 0x0002) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeReadBufferSize(void);                                                         /* 8.2 */

/* Controller Information Group */
#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadLocalVersionInformation( void )
*
* \brief        The function sends the HCI Read Local Version Information (OGF : 0x04; OCF : 0x0001) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadLocalVersionInformation(void);                                              /* 4.1 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadLocalSupportedFeatures( void )
*
* \brief        The function sends the HCI Read Local Supported Features (OGF : 0x04; OCF : 0x0003) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadLocalSupportedFeatures(void);                                               /* 4.3 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadSupportedStates( void )
*
* \brief        The function sends the HCI LE Read Supported States (OGF : 0x08; OCF : 0x001C) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_LeReadSupportedStates(void);                                                    /* 8.27 */

#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadLocalSupportedCommands( void )
*
* \brief        The function sends the HCI Read Local Supported Commands (OGF : 0x04; OCF : 0x0002) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadLocalSupportedCommands(void);                                      /* 4.2 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadBdAddr( void )
*
* \brief        The function sends the HCI Read BD_ADDR (OGF : 0x04; OCF : 0x0009) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadBdAddr(void);                                                              /* 4.6 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadLocalSupportedFeatures( void )
*
* \brief        The function sends the HCI LE Read Local Supported Features (OGF : 0x08; OCF : 0x0003) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Controller Information Group
*
********************************************************************************** */
bleResult_t Hci_LeReadLocalSupportedFeatures(void);                                   /* 8.3 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetRandomAddress(const hciLeSetRandomAddressCommand_t *pParam)
*
* \brief        The function sends the HCI LE Set Random Address (OGF : 0x08; OCF : 0x0005) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the random address.
* \param[out]
*
* \return       Status
*
* \remarks      Controller Configuration Group
*
********************************************************************************** */
bleResult_t Hci_LeSetRandomAddress(
                const hciLeSetRandomAddressCommand_t *pParam);                                        /* 8.4 */

#if gLeBroadcasterSupported_d
/* Controller Configuration Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetAdvertisingEnable(hciLeAdvertisingEnable_t advertisingEnable)
*
* \brief        The function sends the HCI LE Set Advertising Enable (OGF : 0x08; OCF : 0x000A) command to the Controller.
*
* \param[in]    hciLeAdvertisingEnable_t gHciLeAdvertisingEnable_c   enable advertising set.
*                                        gHciLeAdvertisingDisable_c  disable advertising set.
* \param[out]
*
* \return       Status
*
* \remarks      Controller Configuration Group
*
********************************************************************************** */
bleResult_t Hci_LeSetAdvertisingEnable(hciLeAdvertisingEnable_t advertisingEnable);      /* 8.9 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetAdvertisingData(const hciLeSetAdvertisingDataCommand_t* pParam)
*
* \brief        The function sends the HCI LE Set Advertising Data (OGF : 0x08; OCF : 0x0008) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing advertising data length and advertising data address.
* \param[out]
*
* \return       Status
*
* \remarks      Controller Configuration Group
*
********************************************************************************** */
bleResult_t Hci_LeSetAdvertisingData(
                const hciLeSetAdvertisingDataCommand_t* pParam);                                      /* 8.7 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetAdvertisingParameters(const hciLeSetAdvertisingParametersCommand_t* pParam)
*
* \brief        The function sends the HCI LE Set Advertising Parameters (OGF : 0x08; OCF : 0x0006) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing advertising parameters.
* \param[out]
*
* \return       Status
*
* \remarks      Controller Configuration Group
*
********************************************************************************** */
bleResult_t Hci_LeSetAdvertisingParameters(
                const hciLeSetAdvertisingParametersCommand_t *pParam);                                /* 8.5 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetScanResponseData(const hciLeSetScanResponseDataCommand_t *pParam)
*
* \brief        The function sends the HCI LE Set Scan Response Data (OGF : 0x08; OCF : 0x0009) command to the Controller.
*
* \param[in]    pParam pointer to a structure containing scan response data length and scan response data address.
* \param[out]
*
* \return       Status
*
* \remarks      Controller Configuration Group
*
********************************************************************************** */
bleResult_t Hci_LeSetScanResponseData(
                const hciLeSetScanResponseDataCommand_t *pParam);                                     /* 8.8 */
#endif /* gLeBroadcasterSupported_d */

#if gLeObserverSupported_d
/* Device Discovery Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetScanEnable(const hciLeSetScanEnableCommand_t *pParam)
*
* \brief        The function sends the HCI LE Set Scan Enable (OGF : 0x08; OCF : 0x000C) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing scan enable/disable information and filter duplicates configuration.
* \param[out]
*
* \return       Status
*
* \remarks      Device Discovery Group
*
********************************************************************************** */
bleResult_t Hci_LeSetScanEnable(const hciLeSetScanEnableCommand_t *pParam);                 /* 8.11 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetScanParameters(const hciLeSetScanParametersCommand_t *pParam)
*
* \brief        The function sends the HCI LE Set Scan Parameters (OGF : 0x08; OCF : 0x000B) command to the Controller.
*
* \param[in]    pParam pointer to a structure containing scan configuration parameters.
* \param[out]
*
* \return       Status
*
* \remarks      Device Discovery Group
*
********************************************************************************** */
bleResult_t Hci_LeSetScanParameters(const hciLeSetScanParametersCommand_t* pParam);       /* 8.10 */
#endif /* gLeObserverSupported_d */

/* Connection Setup Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_Disconnect( const hciDisconnectCommand_t *pParam )
*
* \brief        The function sends the HCI Disconnect (OGF : 0x01; OCF : 0x0006) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle and disconnect reason.
* \param[out]   None
*
* \return       Status
*
* \remarks      Connection Setup Group
*
********************************************************************************** */
bleResult_t Hci_Disconnect(const hciDisconnectCommand_t *pParam);                              /* 1.6 */

#if gConnMasterSupported_d

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeCreateConnection(const hciLeCreateConnectionCommand_t *pParam)
*
* \brief        The function sends the HCI LE Create Connection (OGF : 0x08; OCF : 0x000D) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing connection configuration parameters.
* \param[out]
*
* \return       Status
*
* \remarks      Connection Setup Group
*
********************************************************************************** */
bleResult_t Hci_LeCreateConnection(const hciLeCreateConnectionCommand_t *pParam);          /* 8.12 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeCreateConnectionCancel( void )
*
* \brief        The function sends the HCI LE Create Connection Cancel (OGF : 0x08; OCF : 0x000E) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Connection Setup Group
*
********************************************************************************** */
bleResult_t Hci_LeCreateConnectionCancel(void);                                         /* 8.13 */

/* Physical Links Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetHostChannelClassification(const hciLeSetHostChannelClassificationCommand_t *pParam)
*
* \brief        The function sends the HCI LE Set Host Channel Classification (OGF : 0x08; OCF : 0x0014) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the channel map.
* \param[out]
*
* \return       Status
*
* \remarks      Physical Links Group
*
********************************************************************************** */
bleResult_t Hci_LeSetHostChannelClassification(
                const hciLeSetHostChannelClassificationCommand_t *pParam);                            /* 8.19 */
#endif /* gConnMasterSupported_d */

#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)
/* Remote Information Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadRemoteVersionInformation( const hciReadRemoteVersionInformationCommand_t *pParam )
*
* \brief        The function sends the HCI Read Remote Version Information (OGF : 0x01; OCF : 0x001D) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Remote Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadRemoteVersionInformation(
                const hciReadRemoteVersionInformationCommand_t *pParam);                              /* 1.23 */
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadRemoteFeatures( const hciLeReadRemoteFeaturesCommand_t *pParam )
*
* \brief        The function sends the HCI LE Read Remote Features (OGF : 0x08; OCF : 0x0016) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Remote Information Group
*
********************************************************************************** */
bleResult_t Hci_LeReadRemoteFeatures(
                const hciLeReadRemoteFeaturesCommand_t *pParam);                                      /* 8.21 */

/* Connection State Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeConnectionUpdate( const hciLeConnectionUpdateCommand_t *pParam )
*
* \brief        The function sends the HCI LE Connection Update (OGF : 0x08; OCF : 0x0013) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection parameters.
* \param[out]   None
*
* \return       Status
*
* \remarks      Connection State Group
*
********************************************************************************** */
bleResult_t Hci_LeConnectionUpdate(const hciLeConnectionUpdateCommand_t* pParam);                     /* 8.18 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoteConnParamReqReply( const hciLeRemoteConnectionParameterRequestReplyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remote Connection Parameter Request Reply (OGF : 0x08; OCF : 0x0020) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection parameters.
* \param[out]   None
*
* \return       Status
*
* \remarks      Connection State Group
*
********************************************************************************** */
bleResult_t Hci_LeRemoteConnParamReqReply(
                const hciLeRemoteConnectionParameterRequestReplyCommand_t *pParam);                   /* 8.31 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoteConnectionParameterRequestNegativeReply( const hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remote Connection Parameter Request Negative Reply (OGF : 0x08; OCF : 0x0021) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle and the reason.
* \param[out]   None
*
* \return       Status
*
* \remarks      Connection State Group
*
********************************************************************************** */
bleResult_t Hci_LeRemoteConnectionParameterRequestNegativeReply(
                const hciLeRemoteConnectionParameterRequestNegativeReplyCommand_t *pParam);           /* 8.32 */

#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)
/* Host Flow Control Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_HostBufferSize( const hciHostBufferSizeCommand_t *pParam )
*
* \brief        The function sends the HCI Host Buffer Size (OGF : 0x03; OCF : 0x0033) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the Host buffer information.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_HostBufferSize(
                const hciHostBufferSizeCommand_t *pParam);                                            /* 3.39 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_SetControllerToHostFlowControl( const hciSetControllerToHostFlowControlCommand_t *pParam )
*
* \brief        The function sends the HCI Set Controller to Host Flow Control (OGF : 0x03; OCF : 0x0031) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the flow control type.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_SetControllerToHostFlowControl(
                const hciSetControllerToHostFlowControlCommand_t *pParam);                            /* 3.38 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_HostNumberOfCompletedPackets( const hciHostNumberOfCompletedPacketsCommand_t *pParam )
*
* \brief        The function sends the HCI Host Number of Completed Packets (OGF : 0x03; OCF : 0x0035) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the completed packets information.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_HostNumberOfCompletedPackets(
                const hciHostNumberOfCompletedPacketsCommand_t *pParam);                              /* 3.40 */
#endif

#if (gLePingIsSupported_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_SetEventMaskPage2( const hciSetEventMaskPage2Command_t *pParam )
*
* \brief        The function sends the HCI Set Event Mask Page 2 (OGF : 0x03; OCF : 0x0063) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the bitmap of the events to be generated by the HCI for the Host.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_SetEventMaskPage2(
                const hciSetEventMaskPage2Command_t *pParam);                                         /* 3.69 */
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_SetEventMask( const hciSetEventMaskCommand_t *pParam )
*
* \brief        The function sends the HCI Set Event Mask (OGF : 0x03; OCF : 0x0001) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the bitmap of the events to be generated by the HCI for the Host.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_SetEventMask(
                const hciSetEventMaskCommand_t *pParam);                                              /* 3.1 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeAddDeviceToWhiteList( const hciLeAddDeviceToWhiteListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Add Device To White List (OGF : 0x08; OCF : 0x0011) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the address type and the address of the device to be added to white list.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeAddDeviceToWhiteList(
                const hciLeAddDeviceToWhiteListCommand_t *pParam);                                    /* 8.16 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeClearWhiteList( void )
*
* \brief        The function sends the HCI LE Clear White List (OGF : 0x08; OCF : 0x0010) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeClearWhiteList(void);                                                         /* 8.15 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadWhiteListSize( void )
*
* \brief        The function sends the HCI LE Read White List Size (OGF : 0x08; OCF : 0x000F) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeReadWhiteListSize(void);                                                      /* 8.14 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoveDeviceFromWhiteList( const hciLeRemoveDeviceFromWhiteListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remove Device From White List (OGF : 0x08; OCF : 0x0012) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the address type and the address of the device to be removed from the white list.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeRemoveDeviceFromWhiteList(
                const hciLeRemoveDeviceFromWhiteListCommand_t *pParam);                               /* 8.17 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetEventMask( const hciLeSetEventMaskCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Event Mask (OGF : 0x08; OCF : 0x0001) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the bitmap of the events to be generated by the HCI for the Host.
* \param[out]   None
*
* \return       Status
*
* \remarks      Host Flow Control Group
*
********************************************************************************** */
bleResult_t Hci_LeSetEventMask(
                const hciLeSetEventMaskCommand_t *pParam);                                            /* 8.1 */

/* Link Information Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadTransmitPowerLevel( const hciReadTransmitPowerLevelCommand_t *pParam )
*
* \brief        The function sends the HCI LE Read Transmit Power (OGF : 0x08; OCF : 0x004B) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the conection handle and the type of the power level.
* \param[out]   None
*
* \return       Status
*
* \remarks      Link Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadTransmitPowerLevel(const hciReadTransmitPowerLevelCommand_t *pParam);             /* 3.35 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadRssi( const hciReadRssiCommand_t *pParam )
*
* \brief        The function sends the HCI Read RSSI (OGF : 0x05; OCF : 0x0005) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the conection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Link Information Group
*
********************************************************************************** */
bleResult_t Hci_ReadRssi(const hciReadRssiCommand_t *pParam);                                         /* 5.4 */
#if gLeBroadcasterSupported_d

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadAdvertisingChannelTxPower( void  )
*
* \brief        The function sends the HCI LE Read Advertising Channel Tx Power (OGF : 0x08; OCF : 0x0007) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Link Information Group
*
********************************************************************************** */
bleResult_t Hci_LeReadAdvertisingChannelTxPower(void);                                          /* 8.6 */
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadChannelMap( const hciLeReadChannelMapCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Read Channel Map (OGF : 0x08; OCF : 0x0015) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the conection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Link Information Group
*
********************************************************************************** */
bleResult_t Hci_LeReadChannelMap(const hciLeReadChannelMapCommand_t *pParam);                         /* 8.20 */

/* Data Transfer Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_SendAclPacket( uint8_t *pHciPacket )
*
* \brief        The function transmits a pre-formatted ACL data packet.
*
* \param[in]    pHciPacket pointer to the formatted packet.
* \param[out]   None
*
* \return       HCI status
*
* \remarks      Data Transfer Group
*
********************************************************************************** */
bleResult_t Hci_SendAclPacket ( uint8_t *pHciPacket );

/* Authentication and Encryption Group */
#if defined(gHciLeEncryptSupport_d) && (gHciLeEncryptSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeEncrypt( const hciLeEncryptCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Encrypt (OGF : 0x08; OCF : 0x0017) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the encrypt key and data to be encrypted.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_LeEncrypt(const hciLeEncryptCommand_t *pParam);                                       /* 8.22 */
#endif
#if defined(gHciLeRandomSupport_d) && (gHciLeRandomSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRand( void )
*
* \brief        The function sends the HCI LE Rand (OGF : 0x08; OCF : 0x0018) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_LeRand(void);                                                                   /* 8.23 */
#endif
#if (gSmpInitiatorSupported_d==1)

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeStartEncryption( const hciLeStartEncryptionCommand_t *pParam )
*
* \brief        The function sends the HCI LE Start Encryption (OGF : 0x08; OCF : 0x0019) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing encryption parameters.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_LeStartEncryption(const hciLeStartEncryptionCommand_t *pParam);                       /* 8.24 */
#endif

#if (gSmpResponderSupported_d == 1)

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeLongTermKeyRequestReply( const hciLeLongTermKeyRequestReplyCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Long Term Key Request Reply (OGF : 0x08; OCF : 0x001A) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the conection handle and the long term key.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_LeLongTermKeyRequestReply(
                const hciLeLongTermKeyRequestReplyCommand_t   *pParam);                               /* 8.25 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeLongTermKeyRequestNegativeReply( const hciLeLongTermKeyRequestNegativeReplyCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Long Term Key Request Negative Reply (OGF : 0x08; OCF : 0x001B) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the conection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_LeLongTermKeyRequestNegativeReply(
                const hciLeLongTermKeyRequestNegativeReplyCommand_t *pParam);                         /* 8.26 */
#endif

#if (gLePingIsSupported_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_ReadAuthenticatedPayloadTimeout( const hciReadAuthenticatedPayloadTimeoutCommand_t   *pParam  )
*
* \brief        The function sends the HCI Read Authenticated Payload Timeout (OGF : 0x03; OCF : 0x007B) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_ReadAuthenticatedPayloadTimeout(
                const hciReadAuthenticatedPayloadTimeoutCommand_t *pParam);                           /* 3.93 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_WriteAuthenticatedPayloadTimeout( const hciWriteAuthenticatedPayloadTimeoutCommand_t   *pParam  )
*
* \brief        The function sends the HCI Write Authenticated Payload Timeout (OGF : 0x03; OCF : 0x007C) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle and the authenticated payload timeout.
* \param[out]   None
*
* \return       Status
*
* \remarks      Authentication and Encryption Group
*
********************************************************************************** */
bleResult_t Hci_WriteAuthenticatedPayloadTimeout(
                const hciWriteAuthenticatedPayloadTimeoutCommand_t *pParam);                          /* 3.94 */
#endif

/* Testing Group */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReceiverTest( const hciLeReceiverTestCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Receiver Test (OGF : 0x08; OCF : 0x001D) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the rx channel.
* \param[out]   None
*
* \return       Status
*
* \remarks      Testing Group
*
********************************************************************************** */
bleResult_t Hci_LeReceiverTest(const hciLeReceiverTestCommand_t *pParam);                             /* 8.28 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeTransmitterTest( const hciLeTransmitterTestCommand_t   *pParam  )
*
* \brief        The function sends the HCI LE Transmitter Test (OGF : 0x08; OCF : 0x001E) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the tx channel, test data length and test data.
* \param[out]   None
*
* \return       Status
*
* \remarks      Testing Group
*
********************************************************************************** */
bleResult_t Hci_LeTransmitterTest(const hciLeTransmitterTestCommand_t *pParam);                       /* 8.29 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeTestEnd( void )
*
* \brief        The function sends the HCI LE Test End (OGF : 0x08; OCF : 0x001F) command to the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks      Testing Group
*
********************************************************************************** */
bleResult_t Hci_LeTestEnd(void);                                                                /* 8.30 */

/* HCI Vendor Specific Commands */
#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_VendorSpecificDebug( const hciVendorSpecificDebugCommand_t *pParam )
*
* \brief        The function sends a vendor specific debug (OGF : 0x3f; OCF : 0x00xx) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing OCF, a pointer to the command parameters and their length.
* \param[out]   None
*
* \return       Status
*
* \remarks      HCI Vendor Specific Command placeholder
*
********************************************************************************** */
bleResult_t Hci_VendorSpecificDebug(const hciVendorSpecificDebugCommand_t *pParam);
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_VendorSpecificSetTxPowerLevel( const hciSetTxPowerLevelCommand_t *pParam )
*
* \brief        The function sends the vendor specific debug Set Tx Power Level(OGF : 0x3f; OCF : 0x012D) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the power level and the channel type(adv/conn).
* \param[out]   None
*
* \return       Status
*
* \remarks      HCI Vendor Specific Command
*
********************************************************************************** */
bleResult_t Hci_VendorSpecificSetTxPowerLevel(const hciSetTxPowerLevelCommand_t *pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_VendorSpecificEnhancedNotification( const hciVendorEnhancedNotificationCommand_t *pParam )
*
* \brief        The function sends the vendor specific debug Enhanced Notification(OGF : 0x3f; OCF : 0x01F0) command to the Controller.
*
* \param[in]    pParam  pointer to a structure containing the connection handle and event type bitmap(bleNotificationEventType_t).
* \param[out]   None
*
* \return       Status
*
* \remarks      HCI Vendor Specific Command
*
********************************************************************************** */
bleResult_t Hci_VendorSpecificEnhancedNotification(const hciVendorEnhancedNotificationCommand_t *pParam);

/* v4.2 specific interface */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetDataLength( const hciLeSetDataLengthCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Data Length (OGF : 0x08; OCF : 0x0022) command to the Controller.
*               Allows the Host to suggest maximum transmission packet size and maximum
*               packet transmission time to be used for a given connection.
*
* \param[in]    pParam  pointer to a structure containing the connection handle, max tx payload and max tx time.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetDataLength(
                const hciLeSetDataLengthCommand_t *pParam);                                           /* 8.33 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadSuggestedDefaultDataLength( void )
*
* \brief        The function sends the HCI LE Read Suggested Default Data Length (OGF : 0x08; OCF : 0x0023) command to the Controller.
*               Allows the Host to read the Host's preferred values for the Controller's
*               maximum transmitted number of payload octets and maximum packet transmission
*               time to be used for new connections.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadSuggestedDefaultDataLength(void);                                         /* 8.34 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeWriteSuggestedDefaultDataLength( const hciLeWriteSuggestedDefaultDataLengthCommand_t *pParam )
*
* \brief        The function sends the HCI LE Write Suggested Default Data Length (OGF : 0x08; OCF : 0x0024) command to the Controller.
*               Allows the Host to specify its preferred values for the Controller's
*               maximum transmission number of payload octets and maximum packet transmission
*               time to be used for new connections.
*
* \param[in]    pParam  pointer to a structure containing the maximum transmission number of payload octets and maximum packet transmission time.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeWriteSuggestedDefaultDataLength(
                const hciLeWriteSuggestedDefaultDataLengthCommand_t *pParam);                         /* 8.35 */
#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)
/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadLocalP256PublicKey( void )
*
* \brief        The function sends the HCI LE Read Local P-256 Public Key (OGF : 0x08; OCF : 0x0025) command to the Controller.
*               Used to return the local P-256 public key from the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadLocalP256PublicKey(void);                                                 /* 8.36 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeGenerateDhKey( const hciLeGenerateDhKeyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Generate DHKey (OGF : 0x08; OCF : 0x0026) command to the Controller.
*               Initiate generation of a Diffie-Hellman key in the Controller for use
*               over the LE transport.
*
* \param[in]    pParam  pointer to a structure containing the remote P-256 Public Key.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeGenerateDhKey(
                const hciLeGenerateDhKeyCommand_t *pParam);                                           /* 8.37 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoveDeviceFromResolvingList( const hciLeRemoveDeviceFromResolvingListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remove Device From Resolving List (OGF : 0x08; OCF : 0x0028) command to the Controller.
*               Allows the Host to remove one device from the resolving list used to resolve Resolvable Private Addresses in the Controller.
*
* \param[in]    pParam  pointer to a structure containing peer Identity Address Type and peer Identity Address.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeRemoveDeviceFromResolvingList(
                const hciLeRemoveDeviceFromResolvingListCommand_t *pParam);                           /* 8.39 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadResolvingListSize( void )
*
* \brief        The function sends the HCI LE Read Resolving List Size(OGF : 0x08; OCF : 0x002A) command to the Controller.
*               Allows the Host to read the total number of entries in the resolving list that can be stored in the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadResolvingListSize(void);                                                  /* 8.41 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadLocalResolvableAddress( const hciLeReadLocalResolvableAddressCommand_t *pParam )
*
* \brief        The function sends the HCI LE Read Local Resolvable Address(OGF : 0x08; OCF : 0x002C) command to the Controller.
*               Allows the Host to get the current local Resolvable Private Address
*               being used for the corresponding peer Identity Address.
*
* \param[in]    pParam  pointer to a structure containing peer Identity Address Type and peer Identity Address.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadLocalResolvableAddress(
                const hciLeReadLocalResolvableAddressCommand_t *pParam);                              /* 8.43 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadMaximumDataLength( void )
*
* \brief        The function sends the HCI LE Read Maximum Data Length(OGF : 0x08; OCF : 0x002F) command to the Controller.
*               Allows the Host to read the Controller's maximum supported payload octets
*               and packet duration times for transmission and reception.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadMaximumDataLength(void);                                                        /* 8.46 */
#endif

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeAddDeviceToResolvingList( const hciLeAddDeviceToResolvingListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Add Device To Resolving List (OGF : 0x08; OCF : 0x0027) command to the Controller.
*               Allows the Host to add one device to the resolving list used to generate
*               and resolve Resolvable Private Addresses in the Controller.
*
* \param[in]    pParam  pointer to a structure containing peer Identity Address Type, peer Identity Address, peer IRK, local IRK.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeAddDeviceToResolvingList(
                const hciLeAddDeviceToResolvingListCommand_t *pParam);                                /* 8.38 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeClearResolvingList( void )
*
* \brief        The function sends the HCI LE Clear Resolving List (OGF : 0x08; OCF : 0x0029) command to the Controller.
*               Allows the Host to remove all devices from the resolving list used to resolve Resolvable Private Addresses in the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeClearResolvingList(void);                                                     /* 8.40 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadPeerResolvableAddress( const hciLeReadPeerResolvableAddressCommand_t *pParam )
*
* \brief        The function sends the HCI LE Read Peer Resolvable Address(OGF : 0x08; OCF : 0x002B) command to the Controller.
*               Allows the Host to get the current peer Resolvable Private Address being used
*               for the corresponding peer Public and Random (static) Identity Address.
*
* \param[in]    pParam  pointer to a structure containing peer Identity Address Type and peer Identity Address.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadPeerResolvableAddress(
                const hciLeReadPeerResolvableAddressCommand_t *pParam);                               /* 8.42 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetAddressResolutionEnable( const hciLeSetAddressResolutionEnableCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Address Resolution Enable(OGF : 0x08; OCF : 0x002D) command to the Controller.
*               Allows the Host to enable resolution of Resolvable Private Addresses in the Controller.
*
* \param[in]    pParam  pointer to a structure containing address Resolution Enable boolean value(0-disabled / 1-enabled).
* \param[out]   None
*
* \return       Status
*
* \remarks      This command can be used at any time except when:
*                    Advertising is enabled
*                    Scanning is enabled
*                    Create connection command is outstanding
*
********************************************************************************** */
bleResult_t Hci_LeSetAddressResolutionEnable(
                const hciLeSetAddressResolutionEnableCommand_t *pParam);                              /* 8.44 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetResolvablePrivateAddressTimeout( const hciLeSetResolvablePrivateAddressTimeoutCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Resolvable Private Address Timeout(OGF : 0x08; OCF : 0x002E) command to the Controller.
*               Allows the Host to set the length of time the Controller uses a
*               Resolvable Private Address before a new resolvable private address is
*               generated and starts being used.
*
* \param[in]    pParam  pointer to a structure containing RPA Timeout value in seconds.
* \param[out]   None
*
* \return       Status
*
* \remarks      Timeout range is 1 s to 1 hour
*               Default value is 15 minutes
*
********************************************************************************** */
bleResult_t Hci_LeSetResolvablePrivateAddressTimeout(
                const hciLeSetResolvablePrivateAddressTimeoutCommand_t *pParam);                      /* 8.45 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetPrivacyMode( hciLeSetPrivacyModeCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Privacy Mode(OGF : 0x08; OCF : 0x004E) command to the Controller.
*               This command is used to allow the Host to specify the privacy mode to be used for a given entry on
*               the resolving list.
*
* \param[in]    pParam  pointer to a structure containing peer identity address type, peer identity address and privacy mode.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetPrivacyMode(const hciLeSetPrivacyModeCommand_t *pParam);                         /* 8.77 */

/* v5.0 specific interface */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadPhy( const hciLeReadPhyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Read Phy(OGF : 0x08; OCF : 0x0030) command to the Controller.
*               Allows the Host to read the current transmitter PHY
*               and receiver PHY on the connection identified by the Connection_Handle.
*
* \param[in]    pParam  pointer to a structure containing the Connection Handle.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadPhy(const hciLeReadPhyCommand_t *pParam);                                       /* 8.47 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetDefaultPhy( const hciLeSetDefaultPhyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Default Phy(OGF : 0x08; OCF : 0x0031) command to the Controller.
*               Allows the Host to specify its preferred values for the transmitter PHY
*               and receiver PHY to be used for all subsequent connections over the LE transport.
*
* \param[in]    pParam  pointer to a structure containing the phy affected by the command(TxPhy, RxPhy, both) and the phy selected for each direction.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetDefaultPhy(const hciLeSetDefaultPhyCommand_t *pParam);                           /* 8.48 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetPhy( const hciLeSetPhyCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Phy(OGF : 0x08; OCF : 0x0032) command to the Controller.
*               Allows the Host to set the PHY preferences for the connection identified
*               by the connection handle.
*
* \param[in]    pParam  pointer to a structure containing the connection handle,
*               the phy affected by the command(TxPhy, RxPhy, both), the phy selected for each direction
*               and the coded phy option(s2/s8).
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetPhy(const hciLeSetPhyCommand_t *pParam);                                         /* 8.49 */

#if defined(gHciCompleteHciCmdSupport_d) && (gHciCompleteHciCmdSupport_d == TRUE)

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeEnhancedReceiverTest( const hciLeEnhancedReceiverTestCommand_t *pParam )
*
* \brief        The function sends the HCI LE Receiver Test[v2](OGF : 0x08; OCF : 0x0033) command to the Controller.
*               This command is used to start a test where the DUT receives test reference
*               packets at a fixed interval. The tester generates the test reference packets.
*
* \param[in]    pParam  pointer to a structure containing the Rx channel, the phy and the modulation index used by the transmitter.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeEnhancedReceiverTest(const hciLeEnhancedReceiverTestCommand_t *pParam);             /* 8.50 */

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeEnhancedTransmitterTest( const hciLeEnhancedTransmitterTestCommand_t *pParam )
*
* \brief        The function sends the HCI LE Transmitter Test[v2](OGF : 0x08; OCF : 0x0034) command to the Controller.
*               This command is used to start a test where the DUT generates test reference packets at a fixed interval.
*
* \param[in]    pParam  pointer to a structure containing the Tx channel, the phy, the payload and the length of test data.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeEnhancedTransmitterTest(const hciLeEnhancedTransmitterTestCommand_t *pParam);       /* 8.51 */
#endif

#if (gBLE50_d == TRUE)
/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetAdvSetRandomAddr( hciLeSetAdvSetRandomAddrCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Advertising Set Random Address(OGF : 0x08; OCF : 0x0035) command to the Controller.
*               This command is used to set the random device address for the advertiser's address contained in the advertising PDUs for an advertising set.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle and the random address.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetAdvSetRandomAddr(hciLeSetAdvSetRandomAddrCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtAdvParams( hciLeSetExtAdvParamsCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Advertising Parameters(OGF : 0x08; OCF : 0x0036) command to the Controller.
*               This command is used to set the parameters for extended advertising.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle and advertising parameters.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetExtAdvParams(hciLeSetExtAdvParamsCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtAdvertisingData( hciLeSetExtAdvertisingDataCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Advertising Data(OGF : 0x08; OCF : 0x0037) command to the Controller.
*               This command is used to set the data used in advertising PDUs that have a data field.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle, operation, fragment preference,
*                        advertising data length and advertising data.
* \param[out]   None
*
* \return       Status
*
* \remarks      This command may be issued at any time after an advertising set identified by the advertising handle
*               parameter has been created using the HCI LE Set Extended Advertising Parameters command.
*
********************************************************************************** */
bleResult_t Hci_LeSetExtAdvertisingData(hciLeSetExtAdvertisingDataCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtScanRespData( hciLeSetExtScanRespDataCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Scan Response Data(OGF : 0x08; OCF : 0x0038) command to the Controller.
*               This command is used to provide scan response data used in scanning response PDUs.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle, operation, fragment preference,
*                        scan response data length and scan response data.
* \param[out]   None
*
* \return       Status
*
* \remarks      This command may be issued at any time after an advertising set identified by the advertising handle
*               parameter has been created using the HCI LE Set Extended Advertising Parameters command.
*
********************************************************************************** */
bleResult_t Hci_LeSetExtScanRespData(hciLeSetExtScanRespDataCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtAdvEnable( hciLeSetExtAdvEnableCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Advertising Enable(OGF : 0x08; OCF : 0x0039) command to the Controller.
*               This command is used to request the Controller to enable or disable one or more advertising sets.
*
* \param[in]    pParam  pointer to a structure containing the operation(enable/disable), the number of advertising sets and three arrays
*                        of number of advertising sets elements containing advertising handles, advertising durations and maximum advertising events.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetExtAdvEnable(hciLeSetExtAdvEnableCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadMaxAdvDataLen( void )
*
* \brief        The function sends the HCI LE Read Maximum Advertising Data Length(OGF : 0x08; OCF : 0x003A) command to the Controller.
*               This command is used to read the maximum length of data supported by the Controller for use as
*               advertisement data or scan response data in an advertising event or as periodic advertisement data.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadMaxAdvDataLen(void);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadNumOfSupportedAdvSets( void )
*
* \brief        The function sends the HCI LE Read Number of Supported Advertising Sets(OGF : 0x08; OCF : 0x003B) command to the Controller.
*               This command is used to read the maximum number of advertising sets supported by the advertising Controller at the same time.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadNumOfSupportedAdvSets(void);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoveAdvSet( hciLeRemoveAdvSetCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remove Advertising Set(OGF : 0x08; OCF : 0x003C) command to the Controller.
*               This command is used to remove an advertising set from the Controller.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeRemoveAdvSet(hciLeRemoveAdvSetCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetPeriodicAdvParams( hciLeSetPeriodicAdvParamsCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Periodic Advertising Parameters(OGF : 0x08; OCF : 0x003E) command to the Controller.
*               This command is used to set the parameters for periodic advertising.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle, minimum advertising interval(N*1.25 ms),
*                       maximum advertising interval(N*1.25 ms) and the advertising properties bitmap.
* \param[out]   None
*
* \return       Status
*
* \remarks      advertising intervals range is 0x0006 to 0xffff (7.5 ms to 81.91875 s)
*
********************************************************************************** */
bleResult_t Hci_LeSetPeriodicAdvParams(hciLeSetPeriodicAdvParamsCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeClearAdvSets( void )
*
* \brief        The function sends the HCI LE Clear Advertising Sets(OGF : 0x08; OCF : 0x003D) command to the Controller.
*               This command is used to remove all existing advertising sets from the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeClearAdvSets(void);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetPeriodicAdvData( hciLeSetPeriodicAdvDataCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Periodic Advertising Data(OGF : 0x08; OCF : 0x003F) command to the Controller.
*               This command is used to set the data used in periodic advertising PDUs.
*
* \param[in]    pParam  pointer to a structure containing the advertising handle, operation,
*                       advertising data length and advertising data address.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetPeriodicAdvData(hciLeSetPeriodicAdvDataCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetPeriodicAdvEnable( hciLeSetPeriodicAdvEnableCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Periodic Advertising Enable(OGF : 0x08; OCF : 0x0040) command to the Controller.
*               This command is used to request the Controller to enable or disable the periodic advertising for the advertising
*               set specified by the advertising handle parameter (ordinary advertising is not affected).
*
* \param[in]    pParam  pointer to a structure containing the operation(enable/disable) and the advertising handle.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeSetPeriodicAdvEnable(hciLeSetPeriodicAdvEnableCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtScanParams( hciLeSetExtScanParamsCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Scan Parameters(OGF : 0x08; OCF : 0x0041) command to the Controller.
*               This command is used to set the extended scan parameters to be used on the advertising physical channels.
*
* \param[in]    pParam   pointer to a structure containing own address type, scanning filter policy, scanning phys,
*                        as well as scan type, scan interval and scan window for each phy.
* \param[out]   None
*
* \return       Status
*
* \remarks      scan interval and scan window are given in 0.625 ms slots(Time = N * 0.625 ms)
*               and their range is from 0x0004 to 0xffff( 2.5 ms to 40.959375 s)
*
********************************************************************************** */
bleResult_t Hci_LeSetExtScanParams(hciLeSetExtScanParamsCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeSetExtScanEnable( hciLeExtScanEnableCommand_t *pParam )
*
* \brief        The function sends the HCI LE Set Extended Scan Enable(OGF : 0x08; OCF : 0x0042) command to the Controller.
*               This command is used to enable or disable scanning.
*
* \param[in]    pParam   pointer to a structure containing operation(enable/disable), filter duplicate policy,
*                        scan duration and scan period.
* \param[out]   None
*
* \return       Status
*
* \remarks      scan duration is given in 10 ms slots(Time = N * 10 ms). N = 0x0000 means scan continuously until explicitly disabled.
*               scan period is given in 1.28 s slots(Time = N * 1.28 s). N = 0x0000 means scan continuously.
*
********************************************************************************** */
bleResult_t Hci_LeSetExtScanEnable(hciLeExtScanEnableCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeExtCreateConnection( hciLeExtCreateConnectionCommand_t *pParam )
*
* \brief        The function sends the HCI LE Extended Create Connection(OGF : 0x08; OCF : 0x0043) command to the Controller.
*               This command is used to create an ACL connection to a connectable advertiser.
*
* \param[in]    pParam   pointer to a structure containing own and peer address type, peer address, initiator
*                        scan parameters and connection parameters.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeExtCreateConnection(hciLeExtCreateConnectionCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LePeriodicAdvCreateSync( hciLePeriodicAdvCreateSyncCommand_t *pParam )
*
* \brief        The function sends the HCI LE Periodic Advertising Create Sync(OGF : 0x08; OCF : 0x0044) command to the Controller.
*               This command is used to synchronize with a periodic advertising train from an advertiser and begin receiving periodic
*               advertising packets.
*
* \param[in]    pParam   pointer to a structure containing sync options, advertising SID,  advertiser address type,
*                        advertiser address, maximum number of consecutive periodic advertising events that the receiver may skip
*                        and maximum permitted time between successful receives.
* \param[out]   None
*
* \return       Status
*
* \remarks      This command may be issued whether or not scanning is enabled and scanning may be enabled and disabled
*               while this command is pending. However, synchronization can only occur when scanning is enabled.
*               While scanning is disabled, no attempt to synchronize will take place.
*
********************************************************************************** */
bleResult_t Hci_LePeriodicAdvCreateSync(hciLePeriodicAdvCreateSyncCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LePeriodicAdvCreateSyncCancel( void )
*
* \brief        The function sends the HCI LE Periodic Advertising Create Sync Cancel(OGF : 0x08; OCF : 0x0045) command to the Controller.
*               This command is used to cancel the HCI LE Periodic Advertising Create Sync command while it is pending.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LePeriodicAdvCreateSyncCancel(void);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LePeriodicAdvTerminateSync( hciLePeriodicAdvTerminateSyncCommand_t *pParam )
*
* \brief        The function sends the HCI LE Periodic Advertising Terminate Sync(OGF : 0x08; OCF : 0x0046) command to the Controller.
*               This command is used to stop reception of the periodic advertising train identified by the sync handle parameter.
*
* \param[in]    pParam   pointer to a structure containing the sync handle.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LePeriodicAdvTerminateSync(hciLePeriodicAdvTerminateSyncCommand_t* pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeAddDeviceToPeriodicAdvList( hciLeAddDeviceToPeriodicAdvListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Add Device To Periodic Advertiser List(OGF : 0x08; OCF : 0x0047) command to the Controller.
*               This command is used to add an entry, consisting of a single device address and SID, to the Periodic
*               Advertiser list stored in the Controller.
*
* \param[in]    pParam  pointer to a structure containing advertiser address type, advertiser address and advertising SID.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeAddDeviceToPeriodicAdvList(hciLeAddDeviceToPeriodicAdvListCommand_t *pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeRemoveDeviceFromPeriodicAdvList( hciLeRemoveDeviceFromPeriodicAdvListCommand_t *pParam )
*
* \brief        The function sends the HCI LE Remove Device From Periodic Advertiser List(OGF : 0x08; OCF : 0x0048) command to the Controller.
*               This command is used to remove one entry from the list of Periodic Advertisers stored in the Controller.
*
* \param[in]    pParam  pointer to a structure containing advertiser address type, advertiser address and advertising SID.
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeRemoveDeviceFromPeriodicAdvList(hciLeRemoveDeviceFromPeriodicAdvListCommand_t *pParam);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeClearPeriodicAdvList( void )
*
* \brief        The function sends the HCI LE Clear Periodic Advertiser List(OGF : 0x08; OCF : 0x0049) command to the Controller.
*               This command is used to remove all entries from the list of Periodic Advertisers in the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeClearPeriodicAdvList(void);

/*! *********************************************************************************
* \fn           bleResult_t Hci_LeReadPeriodicAdvListSize( void )
*
* \brief        The function sends the HCI LE Read Periodic Advertiser List Size(OGF : 0x08; OCF : 0x004A) command to the Controller.
*               This command is used to read the total number of Periodic Advertiser list entries that can be stored in the Controller.
*
* \param[in]    None
* \param[out]   None
*
* \return       Status
*
* \remarks
*
********************************************************************************** */
bleResult_t Hci_LeReadPeriodicAdvListSize(void);
#endif

#ifdef __cplusplus
    }
#endif

#endif /* HCI_INTERFACE_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
