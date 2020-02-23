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

#ifndef ALARM_LOOP_IO_H
#define ALARM_LOOP_IO_H

#include "ba8_common.h"
#include "mdv_digital_input.h"

/**
 * \file       alarm_loop_io.h
 * \defgroup   alarm-loop-io Alarm loop input drivers
 * \ingroup    ba8
 * \copyright  Copyright &copy; 2020, Tuomas Terho. All rights reserved.
 *
 * Input drivers for alarm loop alert signals.
 *
 * @{
 */

/**
 * \brief Alarm inputs
 */
extern mdv_digital_input_t alarm_input[BA8_MAXIMUM_LOOPS];

/**
 * \brief Shield alarm inputs
 */
extern mdv_digital_input_t shield_alarm_input[BA8_MAXIMUM_LOOPS];

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

/**
 * \brief Initializes the alarm input interface
 */
mdv_result_t alarm_loop_io_init(void);

#ifdef __cplusplus
extern }
#endif // ifdef __cplusplus

/** @} */

#endif // ifndef ALARM_LOOP_IO_H

/* EOF */