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

#if gFsciIncluded_c

#include "fsci_ble.h"

#if gFsciBleHciLayerEnabled_d
    #include "fsci_ble_hci.h"
#endif 

#if gFsciBleL2capLayerEnabled_d
    #include "fsci_ble_l2cap.h"
#endif 

#if gFsciBleSmLayerEnabled_d
    #include "fsci_ble_sm.h"
#endif 


#if gFsciBleAttLayerEnabled_d
    #include "fsci_ble_att.h"
#endif 

#if gFsciBleGattDbAttLayerEnabled_d
    #include "fsci_ble_gatt_db_att.h"
#endif 

#include "Panic.h"

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

extern uint32_t fsciBleInterfaceId;

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

void fsciBleRegisterPrivate
(
    uint32_t fsciInterfaceId
)
{
#if gFsciBleHciLayerEnabled_d
    /* Register HCI command handler */
    if(fsciBleRegisterOpGroup(gFsciBleHciOpcodeGroup_c, 
                              fsciBleHciHandler, 
                              fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)fsciBleRegister, 0, 0);
    }
#endif /* gFsciBleHciLayerEnabled_d */
    
#if gFsciBleL2capLayerEnabled_d
    /* Register L2CAP command handler */
    if(fsciBleRegisterOpGroup(gFsciBleL2capOpcodeGroup_c, 
                              fsciBleL2capHandler, 
                              fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)fsciBleRegister, 0, 0);
    }
#endif /* gFsciBleL2capLayerEnabled_d */

#if gFsciBleSmLayerEnabled_d
    /* Register SM command handler */
    if(fsciBleRegisterOpGroup(gFsciBleSmOpcodeGroup_c, 
                              fsciBleSmHandler, 
                              fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)fsciBleRegister, 0, 0);
    }
#endif /* gFsciBleSmLayerEnabled_d */

    #if gFsciBleGattDbAttLayerEnabled_d
    /* Register GATT Database (ATT) command handler */
    if(fsciBleRegisterOpGroup(gFsciBleGattDbAttOpcodeGroup_c, 
                              fsciBleGattDbAttHandler, 
                              fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)fsciBleRegister, 0, 0);
    }
#endif /* gFsciBleGattDbAttLayerEnabled_d */
    
#if gFsciBleAttLayerEnabled_d
    /* Register ATT command handler */
    if(fsciBleRegisterOpGroup(gFsciBleAttOpcodeGroup_c, 
                              fsciBleAttHandler, 
                              fsciInterfaceId) != gFsciSuccess_c)
    {
        panic(0, (uint32_t)fsciBleRegister, 0, 0);
    }
#endif /* gFsciBleAttLayerEnabled_d */
    
    /* Save FSCI interface to be used for monitoring */
    fsciBleInterfaceId = fsciInterfaceId;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

#endif /* gFsciIncluded_c */

/*! *********************************************************************************
* @}
********************************************************************************** */
