#ifndef __MAIN_H_INCLUDED_
#define __MAIN_H_INCLUDED_

#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>
#include "program_custom_lamp.h"
#include "utility_functions.h"
#include "program_blink.h"
#include "program_cycle.h"
#include "osc.h"
#include "theater_chase.h"
#include "scanner.h"

extern CRGBPalette16 blink_palette_purple;
extern CRGBPalette16 blink_palette_orange;
extern CRGBPalette16 blink_palette_bluetones;
extern CRGBPalette16 heatcolorPalette;

#define NUM_LEDS_PER_STRIP 150
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
enum program { NONE, CUSTOM_LAMP, BLINK, CYCLE, THEATER_CHASE, SCANNER};
enum direction { FORWARD, REVERSE};
enum display_mode { CONTINOUS_STRIP, SAME_ON_ALL_STRIPS };
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
extern float delta;
extern float slope;

#endif
