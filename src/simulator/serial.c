// Example code for interacting with serial_irq.c
//
// Copyright (C) 2018  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#include <fcntl.h> // fcntl
#include <unistd.h> // STDIN_FILENO
#include "board/serial_irq.h" // serial_get_tx_byte
#include "board/gpio.h" // uart_setup
#include "sched.h" // sched_shutdown

static void
do_uart(void)
{
    for (;;) {
        uint8_t data;
        int ret = serial_get_tx_byte(0, &data);
        if (ret)
            break;
        else
            write(STDOUT_FILENO, &data, sizeof(data));

        // XXX - Normally the code would check if input data is
        // available and call serial_rx_byte()
    }
}

struct uart_config
uart_setup(uint8_t bus, uint32_t baud, uint8_t *id, uint32_t priority)
{
    // Make stdin/stdout non-blocking
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fcntl(STDOUT_FILENO, F_SETFL
          , fcntl(STDOUT_FILENO, F_GETFL, 0) | O_NONBLOCK);

    *id = 0;

    return (struct uart_config){  };
}

void
uart_enable_tx_irq(struct uart_config config)
{
    // Normally this would enable the hardware irq, but we just call
    // do_uart() directly in this demo code.
    do_uart();
}
