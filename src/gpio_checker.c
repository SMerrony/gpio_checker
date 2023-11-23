/**
 * SPDX-FileCopyrightText: 2023 Stephen Merrony
 * SPDX-License-Identifier: BSD-4-Clause-Shortened
 */

#include <stdio.h>

#include <pico/stdlib.h>

#include "config.h"

void pull_all_down(uint32_t mask) {
    for (uint b = 0; b < MAX_GPIOS; b++) {
        if (((mask >> b) & 1) == 1) {
            gpio_pull_down(b);
        }
    }
}

void pull_all_up(uint32_t mask) {
    for (uint b = 0; b < MAX_GPIOS; b++) {
        if (((mask >> b) & 1) == 1) {
            gpio_pull_up(b);
        }
    }
}

int main() {
    stdio_init_all();
    busy_wait_ms(3000);
    printf("Welcome to %s\n", APP_NAME);

    uint testing_mask = GPIOS_TO_TEST;
    int errors = 0;

    gpio_init_mask(testing_mask);

    while (true) {

        printf("Starting test run\n");
        errors = 0;

        printf("1. Testing all pull-downs...\n");
        pull_all_down(testing_mask);
        busy_wait_ms(1);
        for (uint b = 0; b < MAX_GPIOS; b++) {
            if (((testing_mask >> b) & 1) == 1) {
                if (gpio_get(b)) {
                    errors++;
                    printf("ERROR: GPIO%d should be low, but appears to be high\n", b);
                }
            }
        }

        printf("2. Testing all pull-ups...\n");
        pull_all_up(testing_mask);
        busy_wait_ms(1);
        for (uint b = 0; b < MAX_GPIOS; b++) {
            if (((testing_mask >> b) & 1) == 1) {
                if (!gpio_get(b)) {
                    errors++;
                    printf("ERROR: GPIO%d should be high, but appears to be low\n", b);
                }
            }
        }

        printf("3. Pulling up each single pin and checking others remain low...\n");
        for (uint single = 0; single < MAX_GPIOS; single++) {
            pull_all_down(testing_mask);
            gpio_pull_up(single);
            busy_wait_ms(1);
            for (uint b = 0; b < MAX_GPIOS; b++) {
                if (((testing_mask >> b) & 1) == 1) {
                    if (gpio_get(b) && (b != single)) {
                        errors++;
                        printf("ERROR: Pulled up GPIO%d only, GPIO%d should be low, but appears to be high\n", single, b);
                    }
                }
            }

        }

        printf("4. Pulling down each single pin and checking others remain high...\n");
        for (uint single = 0; single < MAX_GPIOS; single++) {
            pull_all_up(testing_mask);
            gpio_pull_down(single);
            busy_wait_ms(1);
            for (uint b = 0; b < MAX_GPIOS; b++) {
                if (((testing_mask >> b) & 1) == 1) {
                    if (!gpio_get(b) && (b != single)) {
                        errors++;
                        printf("ERROR: Pulled down GPIO%d only, GPIO%d should be high, but appears to be low\n", single, b);
                    }
                }
            }

        }

        printf("\nEnd of run, %d error(s) detected\n", errors);

        busy_wait_ms(1000);

    }
}