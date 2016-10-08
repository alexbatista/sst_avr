/*****************************************************************************
* Product: SST example, 80x86, Turbo C++ 1.01
*
* Copyright (C) 2006 Miro Samek and Robert Ward. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Contact information:
* Email:    miro@quantum-leaps.com
* Internet: www.quantum-leaps.com
*****************************************************************************/
#include "sst_port.h"
#include "sst_exa.h"
#include <util/delay.h>

#define BLINK_DELAY_MS 2000
#define BLINK_FAST_DELAY_MS 300
/*..........................................................................*/
void tickTaskA(SSTEvent e) {
    static uint8_t counter = 0;
    if(counter == 0)
        PORTB ^= (1 << PORTB5);
    counter++;
}

void tickTaskB(SSTEvent e) {

    _delay_ms(BLINK_FAST_DELAY_MS);
    PORTB |= _BV(PORTB5);
    _delay_ms(BLINK_FAST_DELAY_MS);
    PORTB &= ~_BV(PORTB5);
}