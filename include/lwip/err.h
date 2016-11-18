/**
 * @file
 * lwIP Error codes
 */
/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef LWIP_HDR_ERR_H
#define LWIP_HDR_ERR_H

#include "lwip/opt.h"
#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup infrastructure_errors Error codes
 * @ingroup infrastructure
 * @{
 */

/** Define LWIP_ERR_T in cc.h if you want to use
 *  a different type for your platform (must be signed). */
#ifdef LWIP_ERR_T
typedef LWIP_ERR_T err_t;
#else /* LWIP_ERR_T */
typedef s8_t err_t;
#endif /* LWIP_ERR_T*/

/* Definitions for error constants. */

/** No error, everything OK. */
#define ERR_OK          0 
/** Out of memory error.     */
#define ERR_MEM        -1
/** Buffer error.            */
#define ERR_BUF        -2
/** Timeout.                 */
#define ERR_TIMEOUT    -3
/** Routing problem.         */
#define ERR_RTE        -4
/** Operation in progress    */
#define ERR_INPROGRESS -5
/** Illegal value.           */
#define ERR_VAL        -6
/** Operation would block.   */
#define ERR_WOULDBLOCK -7
/** Address in use.          */
#define ERR_USE        -8
/** Already connecting.      */
#define ERR_ALREADY    -9
/** Conn already established.*/
#define ERR_ISCONN     -10
/** Not connected.           */
#define ERR_CONN       -11
/** Low-level netif error    */
#define ERR_IF         -12

#define ERR_IS_FATAL(e) ((e) <= ERR_ABRT)
/** Connection aborted.      */
#define ERR_ABRT       -13
/** Connection reset.        */
#define ERR_RST        -14
/** Connection closed.       */
#define ERR_CLSD       -15
/** Illegal argument.        */
#define ERR_ARG        -16

/**
 * @}
 */

#ifdef LWIP_DEBUG
extern const char *lwip_strerr(err_t err);
#else
#define lwip_strerr(x) ""
#endif /* LWIP_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_ERR_H */
