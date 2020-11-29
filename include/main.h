#ifndef __MAIN_H_INCLUDED_
#define __MAIN_H_INCLUDED_

// ----- ENUMERATIONS ----- //
enum direction { FORWARD, REVERSE};
enum display_mode { CONTINOUS_STRIP, SAME_ON_ALL_STRIPS };
enum program { NONE, CUSTOM_LAMP, BLINK, THEATER_CHASE, SCANNER, PREPROGRAM, VUMETER,PULSE, FIREWORKS};
enum led_order { NORMAL, EVERY_STRIP_REVERSED, EVERY_SECOND_STRIP_REVERSED, STRIPS_IN_REVERSE_ORDER };

#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include <Audio.h>

#include<FastLED.h>
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3003000)
#error "Requires FastLED 3.3 or later; check github for latest code."
#endif

#include "utility_functions.h"
#include "program_blink.h"
#include "osc.h"
#include "program_theater_chase.h"
#include "program_scanner.h"
#include "program_preprogram.h"
#include "audio_react.h"
#include "program_vumeter.h"
#include "audio_react.h"
#include "program_pulse.h"
#include "program_fireworks.h"

extern AudioInputAnalog         adc1;
extern AudioAnalyzeFFT1024      fft;
extern AudioConnection          patchCord;

extern CRGBPalette16 blink_palette_purple;
extern CRGBPalette16 blink_palette_orange;
extern CRGBPalette16 blink_palette_bluetones;
extern CRGBPalette16 blink_palette_es_vintage;
extern CRGBPalette16 blink_palette_purplefly;
extern CRGBPalette16 blink_palette_greeny;
extern CRGBPalette16 blink_palette_bhw1_14;
extern CRGBPalette16 blink_palette_bhw2_22;
extern CRGBPalette16 heatcolorPalette;
extern CRGBPalette16 spectrum_candy;
extern CRGBPalette16 spectrum_pastel;
extern CRGBPalette16 spectrum_warm;
extern CRGBPalette16 spectrum_classic;
extern CRGBPalette16 * active_palette;

// Teensy Versions
// ==================================================================

#if defined(__arm__) && defined(CORE_TEENSY)
  #define PROCESSOR_TEENSY_3_X	1		// run on Paul Stoffregen's ARM Cortex M4 based teensy 3.0/teensy 3.1

  #if defined(__MK20DX128__)
    #define PROCESSOR_TEENSY_3_0	1

  #elif defined(__MK20DX256__)
    #define PROCESSOR_TEENSY_3_1	1
    #define PROCESSOR_TEENSY_3_2	1

  #elif defined(__MKL26Z64__)
    #define PROCESSOR_TEENSY_LC	1

  #elif defined(__MK64FX512__)
    #define PROCESSOR_TEENSY_3_5	1

  #elif defined(__MK66FX1M0__)
    #define PROCESSOR_TEENSY_3_6	1

  #else
    #error "Unknown Teensy, fix Meissner_Config.h"
  #endif
#endif


// User Configurable Values
// ==================================================================

#define STRIP_SPLIT 2   //Define how many "virtual strips" each of the outputs should be split into
                        //NUM_LEDS_PER_STRIP must be dividable by this number
#ifdef PROCESSOR_TEENSY_3_1
  #define NUM_LEDS_PER_STRIP 150
#else
  #define NUM_LEDS_PER_STRIP 300
#endif

#define NUM_STRIPS 8
#define COLOR_CORRECTION TypicalSMD5050
#define GLOBAL_BRIGHTNESS 150


// ----- An array that holds the correct order of the LEDs ----- //
extern int led_order_array[NUM_LEDS_PER_STRIP * NUM_STRIPS];
// ----- The FastLED CRGB array(s)  ----- //
extern CRGB leds[NUM_LEDS_PER_STRIP * NUM_STRIPS];

// ----- DECLEARING GLOBAL PROGRAM VARIABLES ----- //
extern bool debug;
extern display_mode displaymode;
extern direction dir;
extern program active_program;
extern int interval;
extern uint32_t last_update;
extern int program_index1;
extern int program_index2;
extern int increment_by1;
extern int increment_by2;
extern uint16_t total_steps1;
extern uint16_t total_steps2;
extern uint8_t saturation1;
extern uint8_t value1;
extern uint8_t hue1;
extern uint8_t saturation2;
extern uint8_t value2;
extern uint8_t hue2;
extern bool update;
extern char osc_message_address[25];

#endif
