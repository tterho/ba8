/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2020, Tuomas Terho
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "alarm_loop_io.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/**
 * \file       alarm_loop_io.c
 * \defgroup   alarm-loop-io-implementation Driver implementation
 * \ingroup    alarm-loop-io
 * \copyright  Copyright &copy; 2020, Tuomas Terho. All rights reserved.
 * @{
 */

/// Port clock for loops 1, 2, 3 and 4
#define PORT_CLOCK_FOR_LOOPS_1_2_3_4 kCLOCK_PortC
/// Port clock for loops 5, 6, 7 and 8
#define PORT_CLOCK_FOR_LOOPS_5_6_7_8 kCLOCK_PortD

/// Port for loops 1, 2, 3 and 4
#define PORT_FOR_LOOPS_1_2_3_4 PORTC
/// Port for loops 5, 6, 7 and 8
#define PORT_FOR_LOOPS_5_6_7_8 PORTD

/// GPIO for loops 1, 2, 3 and 4
#define GPIO_FOR_LOOPS_1_2_3_4 GPIOC
/// GPIO for loops 5, 6, 7 and 8
#define GPIO_FOR_LOOPS_5_6_7_8 GPIOD

/// Pin for loop 1 alarm input (port C)
#define LOOP_1_ALARM_INPUT_PIN 5u
/// Pin for loop 2 alarm input (port C)
#define LOOP_2_ALARM_INPUT_PIN 7u
/// Pin for loop 3 alarm input (port C)
#define LOOP_3_ALARM_INPUT_PIN 9u
/// Pin for loop 4 alarm input (port C)
#define LOOP_4_ALARM_INPUT_PIN 11u
/// Pin for loop 5 alarm input (port D)
#define LOOP_5_ALARM_INPUT_PIN 1u
/// Pin for loop 6 alarm input (port D)
#define LOOP_6_ALARM_INPUT_PIN 3u
/// Pin for loop 7 alarm input (port D)
#define LOOP_7_ALARM_INPUT_PIN 5u
/// Pin for loop 8 alarm input (port D)
#define LOOP_8_ALARM_INPUT_PIN 7u

/// Pin for loop 1  shield alarm input (port C)
#define LOOP_1_SHIELD_ALARM_INPUT_PIN 4u
/// Pin for loop 2  shield alarm input (port C)
#define LOOP_2_SHIELD_ALARM_INPUT_PIN 6u
/// Pin for loop 3  shield alarm input (port C)
#define LOOP_3_SHIELD_ALARM_INPUT_PIN 8u
/// Pin for loop 4  shield alarm input (port C)
#define LOOP_4_SHIELD_ALARM_INPUT_PIN 10u
/// Pin for loop 5  shield alarm input (port D)
#define LOOP_5_SHIELD_ALARM_INPUT_PIN 0u
/// Pin for loop 6  shield alarm input (port D)
#define LOOP_6_SHIELD_ALARM_INPUT_PIN 2u
/// Pin for loop 7  shield alarm input (port D)
#define LOOP_7_SHIELD_ALARM_INPUT_PIN 4u
/// Pin for loop 8  shield alarm input (port D)
#define LOOP_8_SHIELD_ALARM_INPUT_PIN 6u

/// Port pin pull-up configuration
#define PIN_PULL_UP_ENABLED 0
/// Port pin slew rate select
#define PIN_SLEW_RATE_FAST 0
/// Port pin passive filter configuration
#define PIN_PASSIVE_FILTER_DISABLED 0
/// Port pin drive strength selection
#define PIN_DRIVE_STRENGTH_FAST 0

/// Common port pin configuration for all loop inputs and outputs
static const port_pin_config_t pin_config = {
        .pullSelect = PIN_PULL_UP_ENABLED,
        .slewRate = PIN_SLEW_RATE_FAST,
        .passiveFilterEnable = PIN_PASSIVE_FILTER_DISABLED,
        .driveStrength = PIN_DRIVE_STRENGTH_FAST,
        .mux = kPORT_MuxAsGpio
};

/// Common GPIO configuration for all loop input pins
static const gpio_pin_config_t gpio_input_config = {
        .pinDirection = kGPIO_DigitalInput
};

/**
 * \brief Initialize loop 1 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_1_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_1_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_1_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 1 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_1_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 1 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_1_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4, LOOP_1_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 2 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_2_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_2_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_2_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 2 alarm input

 * \return Result of the operation
 */
static mdv_result_t loop_2_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 2 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_2_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4, LOOP_2_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 3 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_3_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_3_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_3_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 3 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_3_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 3 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_3_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4, LOOP_3_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 4 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_4_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_4_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_4_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 4 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_4_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 4 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_4_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4, LOOP_4_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 5 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_5_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_5_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_5_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 5 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_5_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 5 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_5_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8, LOOP_5_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 6 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_6_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_6_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_6_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 6 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_6_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 6 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_6_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8, LOOP_6_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 7 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_7_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_7_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_7_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 7 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_7_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 7 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_7_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8, LOOP_7_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 8 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_8_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_8_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_8_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 8 alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_8_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get loop 8 alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_8_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8, LOOP_8_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 1 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_1_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_1_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_1_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 1 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_1_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 1 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_1_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4,
                LOOP_1_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 2 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_2_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_1_2_3_4, LOOP_2_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_1_2_3_4, LOOP_2_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 2 shield alarm input

 * \return Result of the operation
 */
static mdv_result_t loop_2_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 2 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_2_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_1_2_3_4,
                LOOP_2_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 3 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_3_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_3_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_3_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 3 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_3_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 3 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_3_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_3_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 4 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_4_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_4_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_4_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 4 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_4_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 4 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_4_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_4_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 5 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_5_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_5_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_5_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 5 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_5_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 5 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_5_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_5_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 6 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_6_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_6_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_6_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 6 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_6_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 6 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_6_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_6_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 7 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_7_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_7_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_7_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 7 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_7_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 7 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_7_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_7_SHIELD_ALARM_INPUT_PIN);
}

/**
 * \brief Initialize loop 8 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_8_shield_alarm_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_LOOPS_5_6_7_8, LOOP_8_SHIELD_ALARM_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_LOOPS_5_6_7_8, LOOP_8_SHIELD_ALARM_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize loop 8 shield alarm input
 *
 * \return Result of the operation
 */
static mdv_result_t loop_8_shield_alarm_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set loop 8 shield alarm input status
 *
 * \return Result of the operation
 */
static uint32_t loop_8_shield_alarm_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_LOOPS_5_6_7_8,
                LOOP_8_SHIELD_ALARM_INPUT_PIN);
}

mdv_digital_input_t alarm_input[BA8_MAXIMUM_LOOPS] = {
        {loop_1_alarm_input_init, loop_1_alarm_input_uninit,
                loop_1_alarm_input_get},
        {loop_2_alarm_input_init, loop_2_alarm_input_uninit,
                loop_2_alarm_input_get},
        {loop_3_alarm_input_init, loop_3_alarm_input_uninit,
                loop_3_alarm_input_get},
        {loop_4_alarm_input_init, loop_4_alarm_input_uninit,
                loop_4_alarm_input_get},
        {loop_5_alarm_input_init, loop_5_alarm_input_uninit,
                loop_5_alarm_input_get},
        {loop_6_alarm_input_init, loop_6_alarm_input_uninit,
                loop_6_alarm_input_get},
        {loop_7_alarm_input_init, loop_7_alarm_input_uninit,
                loop_7_alarm_input_get},
        {loop_8_alarm_input_init, loop_8_alarm_input_uninit,
                loop_8_alarm_input_get},
};

mdv_digital_input_t shield_alarm_input[BA8_MAXIMUM_LOOPS] = {
        {loop_1_shield_alarm_input_init, loop_1_shield_alarm_input_uninit,
                loop_1_shield_alarm_input_get},
        {loop_2_shield_alarm_input_init, loop_2_shield_alarm_input_uninit,
                loop_2_shield_alarm_input_get},
        {loop_3_shield_alarm_input_init, loop_3_shield_alarm_input_uninit,
                loop_3_shield_alarm_input_get},
        {loop_4_shield_alarm_input_init, loop_4_shield_alarm_input_uninit,
                loop_4_shield_alarm_input_get},
        {loop_5_shield_alarm_input_init, loop_5_shield_alarm_input_uninit,
                loop_5_shield_alarm_input_get},
        {loop_6_shield_alarm_input_init, loop_6_shield_alarm_input_uninit,
                loop_6_shield_alarm_input_get},
        {loop_7_shield_alarm_input_init, loop_7_shield_alarm_input_uninit,
                loop_7_shield_alarm_input_get},
        {loop_8_shield_alarm_input_init, loop_8_shield_alarm_input_uninit,
                loop_8_shield_alarm_input_get},
};

mdv_result_t alarm_loop_io_init(void)
{
        // Enable port clock for the ports where the loops are connected to.
        CLOCK_EnableClock(PORT_CLOCK_FOR_LOOPS_1_2_3_4);
        CLOCK_EnableClock(PORT_CLOCK_FOR_LOOPS_5_6_7_8);

        return MDV_RESULT_OK;
}

/** @} */

/* EOF */