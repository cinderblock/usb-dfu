/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
 */

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
 */

/** \file
 *  \brief LUFA Custom Board LED Hardware Driver (Template)
 *
 *  This is a stub driver header file, for implementing custom board
 *  layout hardware with compatible LUFA board specific drivers. If
 *  the library is configured to use the BOARD_USER board mode, this
 *  driver file should be completed and copied into the "/Board/" folder
 *  inside the application's folder.
 *
 *  This stub is for the board-specific component of the LUFA LEDs driver,
 *  for the LEDs (up to four) mounted on most development boards.
 */

#ifndef __LEDS_USER_H__
#define __LEDS_USER_H__

#include <stdint.h>

/* Includes: */
// TODO: Add any required includes here

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

/* Preprocessor Checks: */
#if !defined(__INCLUDE_FROM_LEDS_H)
#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
#endif

/* Public Interface - May be used in end-application: */
/* Macros: */
/** LED mask for the first LED on the board. */
#define LEDS_LED1 _BV(0)

/** LED mask for the second LED on the board. */
#define LEDS_LED2 _BV(1)

/** LED mask for the third LED on the board. */
#define LEDS_LED3 _BV(2)

/** LED mask for the fourth LED on the board. */
#define LEDS_LED4 _BV(3)

/** LED mask for all the LEDs on the board. */
#define LEDS_ALL_LEDS (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)

/** LED mask for none of the board LEDs. */
#define LEDS_NO_LEDS 0

/* Inline Functions: */
#if !defined(__DOXYGEN__)

struct GRB {
  // Matches datasheet
  uint8_t g;
  uint8_t r;
  uint8_t b;
};

extern struct GRB buffer[6];

void update_leds();

static inline void LEDs_Init(void) {}

static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask) {
  if (LEDMask & LEDS_LED1) {
    // buffer[0].r = 255;
    // buffer[0].g = 255; // Disable?
    buffer[0].b = 64; // Disable?
  }
  if (LEDMask & LEDS_LED2) {
    // buffer[1].r = 255;
    // buffer[1].g = 255; // Disable?
    buffer[1].b = 64; // Disable?
  }
  if (LEDMask & LEDS_LED3) {
    // buffer[2].r = 255; // Disable?
    buffer[2].g = 255;
    // buffer[2].b = 255; // Disable?
  }
  if (LEDMask & LEDS_LED4) {
    // buffer[3].r = 255; // Disable?
    buffer[3].g = 255;
    // buffer[3].b = 255; // Disable?
  }
  update_leds();
}

static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask) {
  if (LEDMask & LEDS_LED1) {
    // buffer[0].r = 0;
    // buffer[0].g = 0; // Disable?
    buffer[0].b = 0; // Disable?
  }
  if (LEDMask & LEDS_LED2) {
    // buffer[1].r = 0;
    // buffer[1].g = 0; // Disable?
    buffer[1].b = 0; // Disable?
  }
  if (LEDMask & LEDS_LED3) {
    // buffer[2].r = 0; // Disable?
    buffer[2].g = 0;
    // buffer[2].b = 0; // Disable?
  }
  if (LEDMask & LEDS_LED4) {
    // buffer[3].r = 0; // Disable?
    buffer[3].g = 0;
    // buffer[3].b = 0; // Disable?
  }
  update_leds();
}

static inline void LEDs_Disable(void) { LEDs_TurnOffLEDs(LEDS_ALL_LEDS); }

//			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
//			{
//				// Add code to set the Leds in the given LEDMask to the status given in ActiveMask here
//             PORTC |= LEDMask & ActiveMask & LEDS_LED1;
//             PORTC &= ~(LEDMask & ~ActiveMask & LEDS_LED1);
//			}

static inline void LEDs_SetAllLEDs(const uint8_t LEDMask) { LEDs_TurnOnLEDs(LEDMask); }

static inline void LEDs_ToggleLEDs(const uint8_t LEDMask) {
  if (LEDMask & LEDS_LED1) {
    // buffer[0].r ^= 255;
    // buffer[0].g ^= 255; // Disable?
    buffer[0].b ^= 64; // Disable?
  }
  if (LEDMask & LEDS_LED2) {
    // buffer[1].r ^= 255;
    // buffer[1].g ^= 255; // Disable?
    buffer[1].b ^= 64; // Disable?
  }
  if (LEDMask & LEDS_LED3) {
    // buffer[2].r ^= 255; // Disable?
    buffer[2].g ^= 255;
    // buffer[2].b ^= 255; // Disable?
  }
  if (LEDMask & LEDS_LED4) {
    // buffer[3].r ^= 255; // Disable?
    buffer[3].g ^= 255;
    // buffer[3].b ^= 255; // Disable?
  }
  update_leds();
}

// 			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
// 			static inline uint8_t LEDs_GetLEDs(void)
// 			{
// //             return PINC & LEDS_ALL_LEDS;
// 			}
#endif

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

#endif
