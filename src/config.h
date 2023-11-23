/**
 * SPDX-FileCopyrightText: 2023 Stephen Merrony
 * SPDX-License-Identifier: BSD-4-Clause-Shortened
 */

#ifndef CONFIG_H
#define CONFIG_H

#define APP_NAME "gpio_checker"

#define MAX_GPIOS 30
//                         10987654321098765432109876543210
//                          3          2         1
#define ALL_RP2040_GPIOS 0b00111111111111111111111111111111
#define ALL_PICO_GPIOS   0b00011100011111111111111111111111

#define GPIOS_TO_TEST ALL_PICO_GPIOS

#endif // CONFIG_H