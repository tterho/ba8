/**
 * \defgroup  ba8 Burglar Alarm with eight individually controlled loops
 * \copyright Copyright &copy; 2020, Tuomas Terho. All rights reserved.
 *
 * The BA8 Burglar Alarm is a general purpose burglar alarm system with eight
 * individually controlled loops. It has a touch button user interface with back
 * light indicators for switching the alarm loops on and off, and smart loops
 * with vandal resistant design. The alarm output is propagated by the means of
 * a magnetic relay with both active-open and active-close contactors. The
 * device has got a serial port connection for configuration and monitoring.
 *
 * # Licensing
 *
 * BSD 3-Clause License
 *
 * Copyright &copy; 2020, Tuomas Terho
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

#ifndef BA8_COMMON_H
#define BA8_COMMON_H

#include "mdv_common.h"

/**
 * \file      ba8_common.h
 * \defgroup  ba8-common Common types, macros and constant defines
 * \ingroup   ba8
 * @{
 */

/// Maximum loops in BA8 device
#define BA8_MAXIMUM_LOOPS 8u

/** @} */

#endif // ifndef BA8_COMMON_H

/* EOF */
