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

#include "relay_io.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/**
 * \file       relay_io.c
 * \defgroup   relay-io-implementation Driver implementation
 * \ingroup    relay-io
 * \copyright  Copyright &copy; 2020, Tuomas Terho. All rights reserved.
 * @{
 */

/// Port clock for the relay
#define PORT_CLOCK_FOR_RELAY kCLOCK_PortE

/// Port for the relay
#define PORT_FOR_RELAY PORTE

/// GPIO for the relay
#define GPIO_FOR_RELAY GPIOE

/// Pin for the relay output (port E)
#define RELAY_OUTPUT_PIN 29u

/// Port pin pull-up configuration
#define PIN_PULL_UP_DISABLED 0
/// Port pin slew rate select
#define PIN_SLEW_RATE_FAST 0
/// Port pin passive filter configuration
#define PIN_PASSIVE_FILTER_DISABLED 0
/// Port pin drive strength selection
#define PIN_DRIVE_STRENGTH_FAST 0
/// Default pin output status
#define PIN_OUTPUT_LOW_BY_DEFAULT 0

/// Port pin configuration for the relay output
static const port_pin_config_t pin_config = {
        .pullSelect = PIN_PULL_UP_DISABLED,
        .slewRate = PIN_SLEW_RATE_FAST,
        .passiveFilterEnable = PIN_PASSIVE_FILTER_DISABLED,
        .driveStrength = PIN_DRIVE_STRENGTH_FAST,
        .mux = kPORT_MuxAsGpio
};

/// GPIO confguration for the relay output
static gpio_pin_config_t gpio_output_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = PIN_OUTPUT_LOW_BY_DEFAULT
};

/**
 * \brief Initialize relay output
 *
 * \return Result of the operation
 */
static mdv_result_t relay_output_init(void)
{
        PORT_SetPinConfig(PORT_FOR_RELAY, RELAY_OUTPUT_PIN, &pin_config);
        GPIO_PinInit(GPIO_FOR_RELAY, RELAY_OUTPUT_PIN, &gpio_output_config);
        return MDV_RESULT_OK;
}

/**
 * \brief Uninitialize relay output
 *
 * \return Result of the operation
 */
static mdv_result_t relay_output_uninit(void)
{
        // Do nothing
        return MDV_RESULT_OK;
}

/**
 * \brief Set relay output status
 *
 * \return Result of the operation
 */
static mdv_result_t relay_output_set(uint32_t output)
{
        GPIO_PinWrite(GPIO_FOR_RELAY, RELAY_OUTPUT_PIN, output);
        return MDV_RESULT_OK;
}

mdv_digital_output_t relay_output = {
        relay_output_init, relay_output_uninit, relay_output_set
};

mdv_result_t relay_io_init(void)
{
        // Enable port clock for the port where the relay is connected to.
        CLOCK_EnableClock(PORT_CLOCK_FOR_RELAY);
        return MDV_RESULT_OK;
}

/** @} */

/* EOF */