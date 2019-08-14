#ifndef __MAIN_H_INCLUDED_
#define __MAIN_H_INCLUDED_

// ----- ENUMERATIONS ----- //
enum direction { FORWARD, REVERSE};
enum display_mode { CONTINOUS_STRIP, SAME_ON_ALL_STRIPS };
enum program { NONE, CUSTOM_LAMP, BLINK, THEATER_CHASE, SCANNER, PREPROGRAM, VUMETER,PULSE};

#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3003000)
#error "Requires FastLED 3.3 or later; check github for latest code."
#endif
#include <Audio.h>

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

extern AudioInputAnalog         adc1;
extern AudioAnalyzeFFT1024      fft;
extern AudioConnection          patchCord;

extern CRGBPalette16 blink_palette_purple;
extern CRGBPalette16 blink_palette_orange;
extern CRGBPalette16 blink_palette_bluetones;
extern CRGBPalette16 heatcolorPalette;
extern CRGBPalette16 spectrum_candy;
extern CRGBPalette16 spectrum_pastel;
extern CRGBPalette16 spectrum_warm;
extern CRGBPalette16 spectrum_classic;
extern CRGBPalette16 * active_palette;

#define STRIP_SPLIT 2   //Define how many "virtual strips" each of the outputs should be split into
                        //NUM_LEDS_PER_STRIP must be dividable by this number
#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 8
#define COLOR_CORRECTION TypicalSMD5050
#define GLOBAL_BRIGHTNESS 255
extern CRGB leds [NUM_LEDS_PER_STRIP*NUM_STRIPS];

// ----- Array to hold x and y coordinates for all the LEDs
extern int led_coordinates [NUM_LEDS_PER_STRIP*NUM_STRIPS][2];

// ----- An array that holds the correct order of the LEDs ----- //
// ----- Because I put each individual LED strip in reverse in my roof T_T ----- //
extern int led_array [NUM_LEDS_PER_STRIP*NUM_STRIPS];


// ----- DECLEARING VARIABLES ----- //
extern bool debug;
extern display_mode displaymode;
extern direction dir;
extern program active_program;
extern int interval;
extern int last_update;
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
extern char osc_message_address[18];

#endif
