/*
 * Copyright (c) 2017, Inria.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 */

/**
 * \file
 *         Header file for 6LoRH
 *
 * \author Simon Duquennoy <simon.duquennoy@inria.fr>
 */

 #ifndef RPL_6LORH_H_
 #define RPL_6LORH_H_

/**
 * \addtogroup uip6
 * @{
 */

/********** Constants **********/
#define SIXLORH_DISPATCH_ELECTIVE      0xa0 /* 101xxxxx */
#define SIXLORH_DISPATCH_CRITICAL      0x80 /* 100xxxxx */
#define SIXLORH_DISPATCH_MASK          0xe0 /* ^^^xxxxx */
#define SIXLORH_LEN_MASK               0x1f /* xxx^^^^^ */

#define SIXLORH_TYPE_SRH_1                0
#define SIXLORH_TYPE_SRH_2                1
#define SIXLORH_TYPE_SRH_4                2
#define SIXLORH_TYPE_SRH_8                3
#define SIXLORH_TYPE_SRH_16               4
#define SIXLORH_TYPE_RPI                  5
#define SIXLORH_TYPE_IPINIP               6

/********** Public functions **********/

int rpl_6lorh_add_headers(uint8_t *buf);
int rpl_6lorh_digest_headers(uint8_t *buf, int *do_forward, linkaddr_t *next_hop);

 /** @} */

#endif /* RPL_6LORH_H_ */
