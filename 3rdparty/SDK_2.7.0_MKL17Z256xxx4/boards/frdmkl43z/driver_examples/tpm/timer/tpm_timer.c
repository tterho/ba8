/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* define instance */
#define BOARD_TPM TPM0
/* Interrupt number and interrupt handler for the TPM instance used */
#define BOARD_TPM_IRQ_NUM TPM0_IRQn
#define BOARD_TPM_HANDLER TPM0_IRQHandler
/* Get source clock for TPM driver */
#define TPM_SOURCE_CLOCK (CLOCK_GetFreq(kCLOCK_McgIrc48MClk) / 4)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool tpmIsrFlag           = false;
volatile uint32_t milisecondCounts = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t cnt;
    uint32_t loop       = 2;
    uint32_t secondLoop = 1000U;
    const char *signals = "-|";
    tpm_config_t tpmInfo;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Select the clock source for the TPM counter as kCLOCK_McgIrc48MClk */
    CLOCK_SetTpmClock(1U);

    /* Print a note to terminal */
    PRINTF("\r\nTPM example to simulate a timer\r\n");
    PRINTF("\r\nYou will see a \"-\" or \"|\" in terminal every 1 second:\r\n");

    TPM_GetDefaultConfig(&tpmInfo);

#ifndef TPM_PRESCALER
#define TPM_PRESCALER kTPM_Prescale_Divide_4
#endif

    /* TPM clock divide by TPM_PRESCALER */
    tpmInfo.prescale = TPM_PRESCALER;

    /* Initialize TPM module */
    TPM_Init(BOARD_TPM, &tpmInfo);

    /*
     * Set timer period.
     */
    TPM_SetTimerPeriod(BOARD_TPM, USEC_TO_COUNT(1000U, TPM_SOURCE_CLOCK));

    TPM_EnableInterrupts(BOARD_TPM, kTPM_TimeOverflowInterruptEnable);

    EnableIRQ(BOARD_TPM_IRQ_NUM);

    TPM_StartTimer(BOARD_TPM, kTPM_SystemClock);

    cnt = 0;
    while (true)
    {
        if (tpmIsrFlag)
        {
            milisecondCounts++;
            tpmIsrFlag = false;
            if (milisecondCounts >= secondLoop)
            {
                PRINTF("%c", signals[cnt & 1]);
                cnt++;
                if (cnt >= loop)
                {
                    cnt = 0;
                }
                milisecondCounts = 0U;
            }
        }
        __WFI();
    }
}

void BOARD_TPM_HANDLER(void)
{
    /* Clear interrupt flag.*/
    TPM_ClearStatusFlags(BOARD_TPM, kTPM_TimeOverflowFlag);
    tpmIsrFlag = true;
    __DSB();
}
