#include "program_blink.h"




CRGBPalette16 * blink_palette_array[] = { &blink_palette_purple, &blink_palette_orange, &blink_palette_bluetones};
CRGBPalette16 * active_palette;



uint8_t index_LEDi[NUM_LEDS_PER_STRIP * NUM_STRIPS];
uint32_t next_blink_LEDi[NUM_LEDS_PER_STRIP * NUM_STRIPS];
uint32_t blink_random_time;


void blink()
{
  active_program = BLINK;
  blink_random_time = 10000;
  for (int i = 0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; i++) {
    index_LEDi[i] = 0;
    next_blink_LEDi[i] = millis()+(random16()%blink_random_time);
    leds[i] = 0;
  }
  FastLED.show();
  total_steps1 = 255;
  interval = 10;
  active_palette = &blink_palette_bluetones;
  update = true;
  Serial.println("Program BLINK activated!");
  react_to_audio = false;
}

// Update the Blink pattern
void blinkUpdate()
{
  //Runs through each LED
  for (int i = 0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; i++)
  {
    //Checks if time now is greater or eaqual to next blink time
    if (millis() >= next_blink_LEDi[i])
    {

      leds[i] = ColorFromPalette( *active_palette, index_LEDi[i]);     //Sets the color of the LED to a value in a previously generated palette
      index_LEDi[i]++;                                                //Increases index so that the next color in the palette will be selected on the next round

      //Checks if we have run through the entire color palette
      if (index_LEDi[i] >= total_steps1)
      {
        index_LEDi[i] = 0;                                            //Resets the index to 0
        next_blink_LEDi[i] = (millis()+(random16()%blink_random_time));  //Generates a new time for the next blink
      }
    }
  }
  FastLED.show();
}
