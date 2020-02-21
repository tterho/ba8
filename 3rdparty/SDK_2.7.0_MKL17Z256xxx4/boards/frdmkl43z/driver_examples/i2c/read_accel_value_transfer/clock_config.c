/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. CLOCK_SetSimSafeDivs, to make sure core clock, bus clock, flexbus clock
 *    and flash clock are in allowed range during clock mode switch.
 *
 * 2. Call CLOCK_Osc0Init to setup OSC clock, if it is used in target mode.
 *
 * 3. Call CLOCK_SetMcgliteConfig to set MCG_Lite configuration.
 *
 * 4. Call CLOCK_SetSimConfig to set the clock configuration in SIM.
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v7.0
processor: MKL43Z256xxx4
package_id: MKL43Z256VLH4
mcu_data: ksdk2_0
processor_version: 0.7.1
board: FRDM-KL43Z
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_smc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OSC_CAP0P 0U                   /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U          /*!< Disable external reference clock */
#define SIM_OSC32KSEL_OSC32KCLK_CLK 0U /*!< OSC32KSEL select: OSC32KCLK clock */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: Bus_clock.outFreq, value: 24 MHz}
- {id: Core_clock.outFreq, value: 48 MHz}
- {id: Flash_clock.outFreq, value: 24 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGIRCLK.outFreq, value: 8 MHz}
- {id: MCGPCLK.outFreq, value: 48 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
settings:
- {id: MCGMode, value: HIRC}
- {id: MCG.CLKS.sel, value: MCG.HIRC}
- {id: MCG_C2_OSC_MODE_CFG, value: ModeOscLowPower}
- {id: MCG_C2_RANGE0_CFG, value: Very_high}
- {id: MCG_MC_HIRCEN_CFG, value: Enabled}
- {id: OSC0_CR_ERCLKEN_CFG, value: Enabled}
- {id: OSC_CR_ERCLKEN_CFG, value: Enabled}
- {id: SIM.CLKOUTSEL.sel, value: MCG.MCGPCLK}
- {id: SIM.COPCLKSEL.sel, value: OSC.OSCERCLK}
- {id: SIM.FLEXIOSRCSEL.sel, value: MCG.MCGPCLK}
- {id: SIM.LPUART0SRCSEL.sel, value: MCG.MCGPCLK}
- {id: SIM.LPUART1SRCSEL.sel, value: MCG.MCGPCLK}
- {id: SIM.RTCCLKOUTSEL.sel, value: OSC.OSCERCLK}
- {id: SIM.TPMSRCSEL.sel, value: MCG.MCGPCLK}
- {id: SIM.USBSRCSEL.sel, value: MCG.MCGPCLK}
sources:
- {id: MCG.HIRC.outFreq, value: 48 MHz}
- {id: OSC.OSC.outFreq, value: 32 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
const mcglite_config_t mcgliteConfig_BOARD_BootClockRUN = {
    .outSrc          = kMCGLITE_ClkSrcHirc,  /* MCGOUTCLK source is HIRC */
    .irclkEnableMode = kMCGLITE_IrclkEnable, /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
    .ircs            = kMCGLITE_Lirc8M,      /* Slow internal reference (LIRC) 8 MHz clock selected */
    .fcrdiv          = kMCGLITE_LircDivBy1,  /* Low-frequency Internal Reference Clock Divider: divided by 1 */
    .lircDiv2        = kMCGLITE_LircDivBy1,  /* Second Low-frequency Internal Reference Clock Divider: divided by 1 */
    .hircEnableInNotHircMode = true,         /* HIRC source is enabled */
};
const sim_clock_config_t simConfig_BOARD_BootClockRUN = {
    .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK, /* OSC32KSEL select: OSC32KCLK clock */
    .clkdiv1  = 0x10000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV4: /2 */
};
const osc_config_t oscConfig_BOARD_BootClockRUN = {
    .freq        = 0U,                   /* Oscillator frequency: 0Hz */
    .capLoad     = (OSC_CAP0P),          /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeOscLowPower, /* Oscillator low power */
    .oscerConfig = {
        .enableMode =
            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
    }};

/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Set MCG to HIRC mode. */
    CLOCK_SetMcgliteConfig(&mcgliteConfig_BOARD_BootClockRUN);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

/*******************************************************************************
 ********************* Configuration BOARD_BootClockVLPR ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockVLPR
outputs:
- {id: Bus_clock.outFreq, value: 1 MHz}
- {id: Core_clock.outFreq, value: 2 MHz}
- {id: Flash_clock.outFreq, value: 1 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGIRCLK.outFreq, value: 2 MHz}
- {id: System_clock.outFreq, value: 2 MHz}
settings:
- {id: MCGMode, value: LIRC2M}
- {id: powerMode, value: VLPR}
- {id: MCG_C2_OSC_MODE_CFG, value: ModeOscLowPower}
- {id: RTCCLKOUTConfig, value: 'yes'}
- {id: SIM.OUTDIV4.scale, value: '2', locked: true}
- {id: SIM.RTCCLKOUTSEL.sel, value: OSC.OSCERCLK}
sources:
- {id: MCG.LIRC.outFreq, value: 2 MHz}
- {id: OSC.OSC.outFreq, value: 32.768 kHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockVLPR configuration
 ******************************************************************************/
const mcglite_config_t mcgliteConfig_BOARD_BootClockVLPR = {
    .outSrc          = kMCGLITE_ClkSrcLirc,  /* MCGOUTCLK source is LIRC */
    .irclkEnableMode = kMCGLITE_IrclkEnable, /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
    .ircs            = kMCGLITE_Lirc2M,      /* Slow internal reference (LIRC) 2 MHz clock selected */
    .fcrdiv          = kMCGLITE_LircDivBy1,  /* Low-frequency Internal Reference Clock Divider: divided by 1 */
    .lircDiv2        = kMCGLITE_LircDivBy1,  /* Second Low-frequency Internal Reference Clock Divider: divided by 1 */
    .hircEnableInNotHircMode = false,        /* HIRC source is not enabled */
};
const sim_clock_config_t simConfig_BOARD_BootClockVLPR = {
    .er32kSrc = SIM_OSC32KSEL_OSC32KCLK_CLK, /* OSC32KSEL select: OSC32KCLK clock */
    .clkdiv1  = 0x10000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV4: /2 */
};
const osc_config_t oscConfig_BOARD_BootClockVLPR = {
    .freq        = 0U,                   /* Oscillator frequency: 0Hz */
    .capLoad     = (OSC_CAP0P),          /* Oscillator capacity load: 0pF */
    .workMode    = kOSC_ModeOscLowPower, /* Oscillator low power */
    .oscerConfig = {
        .enableMode = OSC_ER_CLK_DISABLE, /* Disable external reference clock */
    }};

/*******************************************************************************
 * Code for BOARD_BootClockVLPR configuration
 ******************************************************************************/
void BOARD_BootClockVLPR(void)
{
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_SetSimSafeDivs();
    /* Set MCG to LIRC2M mode. */
    CLOCK_SetMcgliteConfig(&mcgliteConfig_BOARD_BootClockVLPR);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_BOARD_BootClockVLPR);
    /* Set VLPR power mode. */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
#if (defined(FSL_FEATURE_SMC_HAS_LPWUI) && FSL_FEATURE_SMC_HAS_LPWUI)
    SMC_SetPowerModeVlpr(SMC, false);
#else
    SMC_SetPowerModeVlpr(SMC);
#endif
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateVlpr)
    {
    }
    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKVLPR_CORE_CLOCK;
}
