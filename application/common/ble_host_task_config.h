/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2020 NXP
* All rights reserved.
*
* \file
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef BLE_HOST_TASK_CONFIG_H
#define BLE_HOST_TASK_CONFIG_H

#include "fsl_device_registers.h"

#include "fsl_os_abstraction.h"

/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/

/*
 * These values should be modified by the application as necessary.
 * They are used by the task initialization code from ble_host_tasks.c.
 */
#ifndef gHost_TaskStackSize_c
    #ifndef EC_P256_DSPEXT
    #define EC_P256_DSPEXT 1
    #endif
    #define gHost_TaskStackMinSize_c 0x600
    #define gHostTask_XtraStackSzForEcP256 0x280
    /* The use of the DSP extension optimized EC P256 library requires more stack */
    #if (defined(EC_P256_DSPEXT) && (EC_P256_DSPEXT == 1)) && (defined gAppUsePairing_d && (gAppUsePairing_d != 0))
        #define gHost_TaskStackSize_c ((gHost_TaskStackMinSize_c) + (gHostTask_XtraStackSzForEcP256))
    #else
        #define gHost_TaskStackSize_c (gHost_TaskStackMinSize_c)
    #endif
#endif


#ifndef gHost_TaskPriority_c
#define gHost_TaskPriority_c 6
#endif

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
* \brief  Initializes the two tasks of the BLE Host Stack.
*
* \return  osaStatus_t.
*
********************************************************************************** */
osaStatus_t Ble_HostTaskInit(void);

#ifdef __cplusplus
}
#endif

#endif /* BLE_HOST_TASK_CONFIG_H */

/*! *********************************************************************************
* @}
********************************************************************************** */
