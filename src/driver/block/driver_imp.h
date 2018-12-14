/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __DRIVER_IMP_H
#define __DRIVER_IMP_H

#include "util.h"

#include "device.h"
#include "kernel.h"

#include "driver.h"

#define DRIVER_VERSION_MAJOR 0
#define DRIVER_VERSION_MINOR 1
#define DRIVER_VERSION_PATCH 0

#define DRIVER_VERSION       STR(DRIVER_VERSION_MAJOR) "." STR(DRIVER_VERSION_MINOR) "." STR(DRIVER_VERSION_PATCH)
#define DRIVER_TYPE          "block"

#endif
