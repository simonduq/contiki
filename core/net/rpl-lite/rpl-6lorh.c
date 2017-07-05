/*
 * Copyright (c) 2009, Swedish Institute of Computer Science.
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
 *         Compressed RPL headers for 6LoRH.
 *
 * \author Simon Duquennoy <simon.duquennoy@inria.fr>
 */

/**
 * \addtogroup uip6
 * @{
 */

#include "net/rpl-lite/rpl.h"
#include "net/ipv6/sicslowpan.h"
#include "net/packetbuf.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL RPL_LOG_LEVEL

#define UIP_IP_BUF          ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

/*--------------------------------------------------------------------*/
static void
add_hdr_srh(void)
{

}
/*--------------------------------------------------------------------*/
static void
add_hdr_rpi(void)
{
  /* Always include RPI */
  // TODO
}
/*--------------------------------------------------------------------*/
static void
add_hdr_ipinip(void)
{
  if(uip_ds6_is_my_addr(&UIP_IP_BUF->srcipaddr)) {
    /* 6lorh adds ext headers. If we are not the source of the packet, we
    must encapsulate it in IP-in-IP. */
    // TODO
  }
}
/*---------------------------------------------------------------------------*/
void
rpl_6lorh_add_headers(uint8_t *buf)
{
  add_hdr_srh();
  add_hdr_rpi();
  add_hdr_ipinip();
}
/*---------------------------------------------------------------------------*/
int
rpl_6lorh_digest_headers(uint8_t *buf, int *do_forward, linkaddr_t *next_hop)
{
  uint8_t len;
  uint8_t type;

  if(do_forward == NULL || next_hop == NULL) {
    return 0;
  }

  switch((buf[0] & SIXLORH_DISPATCH_MASK)) {
    case SIXLORH_DISPATCH_ELECTIVE:
      len = buf[0] & SIXLORH_LEN_MASK;
      type = buf[1];
      if(type == SIXLORH_TYPE_IPINIP) {
        digest_ipinip();
        buf += len;
      } else {
        LOG_WARN("skipping unspported elective 6LoRH type: 0x%02x\n", buf[1]);
        buf += len;
      }
      break;
    case SIXLORH_DISPATCH_CRITICAL:
      len = buf[0] & SIXLORH_LEN_MASK;
      type = buf[1];
      if(type == SIXLORH_TYPE_RPI) {
        digest_rpi();
        buf += len;
      } else if(type >= SIXLORH_TYPE_SRH_1 && type <= SIXLORH_TYPE_SRH_16) {
        digest_srh();
        buf += len;
      } else {
        LOG_ERR("unspported critical 6LoRH type: 0x%02x\n", buf[1]);
        return 0;
      }
      break
    default:
      LOG_ERR("not a 6LoRH dispatch: 0x%02x\n", buf[0]);
      break;
  }
}

/** @}*/
