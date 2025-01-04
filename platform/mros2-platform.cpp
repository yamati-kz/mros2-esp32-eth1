/* target dependent procedure for mros2-mbed
 * Copyright (c) 2023 mROS-base
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* NOTE: 
 *   this file has not been implemented and used yet
 */

#include "mros2.h"
#include "mros2-platform.h"

#include "cmsis_os.h"
#ifdef CONFIG_MROS2_ESP32_NETIF_WIFI
#include "wifi.h"
#elif CONFIG_MROS2_ESP32_NETIF_ETHERNET
#include "example_ethernet.h"
#else /* Not use Kconfig.projbuild */
#include "wifi.h"
#endif

/*
 *  Setup network I/F
 */
extern "C" esp_err_t mros2_platform_network_connect(void)
{
#ifdef CONFIG_MROS2_ESP32_NETIF_WIFI
  init_wifi();
#elif CONFIG_MROS2_ESP32_NETIF_ETHERNET
  init_ethernet();
#else /* Not use Kconfig.projbuild */
  init_wifi();
#endif
  osKernelStart();

  /* get mros2 IP address and set it to RTPS */
#ifdef CONFIG_MROS2_ESP32_NETIF_WIFI
  uint32_t ipaddr = get_mros2_ip_addr();
#elif CONFIG_MROS2_ESP32_NETIF_ETHERNET
  uint32_t ipaddr = get_mros2_ip_addr_eth();
#else /* Not use Kconfig.projbuild */
  uint32_t ipaddr = get_mros2_ip_addr();
#endif
  return mros2_setIPAddrRTPS(ipaddr);
}
