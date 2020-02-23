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

#include "button_io.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/**
 * \file       button_io.c
 * \defgroup   button-io-implementation Driver implementation
 * \ingroup    button-io
 * \copyright  Copyright &copy; 2020, Tuomas Terho. All rights reserved.
 * @{
 */

/// Port clock for buttons 1 and 2
#define PORT_CLOCK_FOR_BUTTONS_1_2 kCLOCK_PortC
/// Port clock for buttons 3, 4, 5 and 6
#define PORT_CLOCK_FOR_BUTTONS_3_4_5_6 kCLOCK_PortB
/// Port clock for buttons 7 and 8
#define PORT_CLOCK_FOR_BUTTONS_7_8 kCLOCK_PortA

/// Port for buttons 1 and 2
#define PORT_FOR_BUTTONS_1_2 PORTC
/// Port for buttons 3, 4, 5 and 6
#define PORT_FOR_BUTTONS_3_4_5_6 PORTB
/// Port for buttons 7 and 8
#define PORT_FOR_BUTTONS_7_8 PORTA

/// GPIO for buttons 1 and 2
#define GPIO_FOR_BUTTONS_1_2 GPIOC
/// GPIO for buttons 3, 4, 5 and 6
#define GPIO_FOR_BUTTONS_3_4_5_6 GPIOB
/// GPIO for buttons 7 and 8
#define GPIO_FOR_BUTTONS_7_8 GPIOA

/// Pin for button 1 input (port C)
#define BUTTON_1_INPUT_PIN 3u
/// Pin for button 2 input (port C)
#define BUTTON_2_INPUT_PIN 1u
/// Pin for button 3 input (port B)
#define BUTTON_3_INPUT_PIN 19u
/// Pin for button 4 input (port B)
#define BUTTON_4_INPUT_PIN 17u
/// Pin for button 5 input (port B)
#define BUTTON_5_INPUT_PIN 3u
/// Pin for button 6 input (port B)
#define BUTTON_6_INPUT_PIN 1u
/// Pin for button 7 input (port A)
#define BUTTON_7_INPUT_PIN 19u
/// Pin for button 8 input (port A)
#define BUTTON_8_INPUT_PIN 13u

/// Pin for button 1 backlight output (port C)
#define BUTTON_1_OUTPUT_PIN 2u
/// Pin for button 2 backlight output (port C)
#define BUTTON_2_OUTPUT_PIN 0u
/// Pin for button 3 backlight output (port B)
#define BUTTON_3_OUTPUT_PIN 18u
/// Pin for button 4 backlight output (port B)
#define BUTTON_4_OUTPUT_PIN 16u
/// Pin for button 5 backlight output (port B)
#define BUTTON_5_OUTPUT_PIN 2u
/// Pin for button 6 backlight output (port B)
#define BUTTON_6_OUTPUT_PIN 0u
/// Pin for button 7 backlight output (port A)
#define BUTTON_7_OUTPUT_PIN 18u
/// Pin for button 8 backlight output (port A)
#define BUTTON_8_OUTPUT_PIN 12u

/// Port pin pull-up configuration
#define PIN_PULL_UP_DISABLED 0
/// Port pin slew rate select
#define PIN_SLEW_RATE_FAST 0
/// Port pin passive filter configuration
#define PIN_PASSIVE_FILTER_DISABLED 0
/// Port pin drive strength selection
#define PIN_DRIVE_STRENGT_FAST 0
/// Default pin output status
#define PIN_OUTPUT_LOW_BY_DEFAULT 0

/// Common port pin configuration for all button inputs and outputs
static const port_pin_config_t pin_config = {
        .pullSelect = PIN_PULL_UP_DISABLED,
        .slewRate = PIN_SLEW_RATE_FAST,
        .passiveFilterEnable = PIN_PASSIVE_FILTER_DISABLED,
        .driveStrength = PIN_DRIVE_STRENGT_FAST,
        .mux = kPORT_MuxAsGpio
};

/// Common GPIO configuration for all button input pins
static const gpio_pin_config_t gpio_input_config = {
        .pinDirection = kGPIO_DigitalInput
};

/// Common GPIO confguration for all button backlight output pins
static gpio_pin_config_t gpio_output_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = PIN_OUTPUT_LOW_BY_DEFAULT
};

/**
 * \brief Initialize button 1 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_1_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_1_2, BUTTON_1_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_1_2, BUTTON_1_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 1 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_1_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 1 input status
 *
 * \return Result of the operation
 */
static uint32_t button_1_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_1_2, BUTTON_1_INPUT_PIN);
}

/**
 * \brief Initialize button 2 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_2_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_1_2, BUTTON_2_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_1_2, BUTTON_2_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 2 input

 * \return Result of the operation
 */
static mdv_result_t button_2_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 2 input status
 *
 * \return Result of the operation
 */
static uint32_t button_2_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_1_2, BUTTON_2_INPUT_PIN);
}

/**
 * \brief Initialize button 3 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_3_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_3_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_3_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 3 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_3_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 3 input status
 *
 * \return Result of the operation
 */
static uint32_t button_3_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_3_INPUT_PIN);
}

/**
 * \brief Initialize button 4 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_4_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_4_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_4_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 4 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_4_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 4 input status
 *
 * \return Result of the operation
 */
static uint32_t button_4_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_4_INPUT_PIN);
}

/**
 * \brief Initialize button 5 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_5_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_5_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_5_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 5 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_5_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 5 input status
 *
 * \return Result of the operation
 */
static uint32_t button_5_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_5_INPUT_PIN);
}

/**
 * \brief Initialize button 6 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_6_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_6_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_6_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 6 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_6_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 6 input status
 *
 * \return Result of the operation
 */
static uint32_t button_6_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_6_INPUT_PIN);
}

/**
 * \brief Initialize button 7 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_7_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_7_8, BUTTON_7_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_7_8, BUTTON_7_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 7 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_7_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 7 input status
 *
 * \return Result of the operation
 */
static uint32_t button_7_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_7_8, BUTTON_7_INPUT_PIN);
}

/**
 * \brief Initialize button 8 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_8_input_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_7_8, BUTTON_8_INPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_7_8, BUTTON_8_INPUT_PIN,
                &gpio_input_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 8 input
 *
 * \return Result of the operation
 */
static mdv_result_t button_8_input_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Get button 8 input status
 *
 * \return Result of the operation
 */
static uint32_t button_8_input_get(void)
{
        return GPIO_PinRead(GPIO_FOR_BUTTONS_7_8, BUTTON_8_INPUT_PIN);
}

/**
 * \brief Initialize button 1 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_1_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_1_2, BUTTON_1_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_1_2, BUTTON_1_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 1 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_1_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 1 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_1_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_1_2, BUTTON_1_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 2 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_2_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_1_2, BUTTON_2_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_1_2, BUTTON_2_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 2 output

 * \return Result of the operation
 */
static mdv_result_t button_2_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 2 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_2_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_1_2, BUTTON_2_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 3 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_3_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_3_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_3_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 3 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_3_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 3 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_3_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_3_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 4 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_4_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_4_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_4_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 4 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_4_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 4 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_4_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_4_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 5 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_5_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_5_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_5_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 5 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_5_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 5 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_5_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_5_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 6 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_6_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_3_4_5_6, BUTTON_6_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_6_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 6 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_6_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 6 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_6_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_3_4_5_6, BUTTON_6_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 7 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_7_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_7_8, BUTTON_7_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_7_8, BUTTON_7_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 7 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_7_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 7 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_7_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_7_8, BUTTON_7_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

/**
 * \brief Initialize button 8 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_8_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_BUTTONS_7_8, BUTTON_8_OUTPUT_PIN,
                &pin_config);
        GPIO_PinInit(GPIO_FOR_BUTTONS_7_8, BUTTON_8_OUTPUT_PIN,
                &gpio_output_config);

        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize button 8 output
 *
 * \return Result of the operation
 */
static mdv_result_t button_8_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set button 8 output status
 *
 * \return Result of the operation
 */
static mdv_result_t button_8_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_BUTTONS_7_8, BUTTON_8_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

mdv_digital_input_t button_input[BA8_MAXIMUM_LOOPS] = {
        {button_1_input_init, button_1_input_uninit, button_1_input_get},
        {button_2_input_init, button_2_input_uninit, button_2_input_get},
        {button_3_input_init, button_3_input_uninit, button_3_input_get},
        {button_4_input_init, button_4_input_uninit, button_4_input_get},
        {button_5_input_init, button_5_input_uninit, button_5_input_get},
        {button_6_input_init, button_6_input_uninit, button_6_input_get},
        {button_7_input_init, button_7_input_uninit, button_7_input_get},
        {button_8_input_init, button_8_input_uninit, button_8_input_get},
};

mdv_digital_output_t button_backlight[BA8_MAXIMUM_LOOPS] = {
        {button_1_output_init, button_1_output_uninit, button_1_output_set},
        {button_2_output_init, button_2_output_uninit, button_2_output_set},
        {button_3_output_init, button_3_output_uninit, button_3_output_set},
        {button_4_output_init, button_4_output_uninit, button_4_output_set},
        {button_5_output_init, button_5_output_uninit, button_5_output_set},
        {button_6_output_init, button_6_output_uninit, button_6_output_set},
        {button_7_output_init, button_7_output_uninit, button_7_output_set},
        {button_8_output_init, button_8_output_uninit, button_8_output_set},
};

mdv_result_t button_io_init(void)
{
        // Enable port clock for the ports where the buttons are connected to.
        CLOCK_EnableClock(PORT_CLOCK_FOR_BUTTONS_1_2);
        CLOCK_EnableClock(PORT_CLOCK_FOR_BUTTONS_3_4_5_6);
        CLOCK_EnableClock(PORT_CLOCK_FOR_BUTTONS_7_8);
}

/** @} */

/* EOF */