#include "scanner.h"

uint8_t tail_length;

void scanner()
{
  displaymode = SAME_ON_ALL_STRIPS;
  dir = FORWARD;
  active_program = SCANNER;
  interval = 20;
  hue1 = 10;
  value1 = 255;
  saturation1 = 255;
  tail_length = 10;
  if (displaymode == CONTINOUS_STRIP) {
  total_steps1 = (NUM_LEDS_PER_STRIP*NUM_STRIPS-1)*2;
  }
  if (displaymode == SAME_ON_ALL_STRIPS) {
    total_steps1 = (NUM_LEDS_PER_STRIP-1)*2;
  }
  program_index1 = 0;
  increment_by1 = 1;
  dir = FORWARD;
  update = true;
}

void scannerUpdate()
{
  if(displaymode == CONTINOUS_STRIP )
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP*NUM_STRIPS; i++)
    {
      if (i == program_index1) // first half of the scan
      {
         leds[led_array[i]] = CHSV(hue1, saturation1, value1);
      }
      else if (i == total_steps1 - program_index1) // The return trip.
      {
        leds[led_array[i]] = CHSV(hue1, saturation1, value1);
      }
      else  // fade to black
      {
        leds[led_array[i]].fadeToBlackBy( tail_length );
      }
    }
  }
  if(displaymode == SAME_ON_ALL_STRIPS)
  {
    for (int i = 0; i < NUM_STRIPS; i++)
    {
      for (int y = 0; y < NUM_LEDS_PER_STRIP; y++)
      {
        if (y == program_index1) // first half of the scan
        {
           leds[led_array[y+(i*NUM_LEDS_PER_STRIP)]] = CHSV(hue1, saturation1, value1);
        }
        else if (y == total_steps1 - program_index1) // The return trip.
        {
          leds[led_array[y+(i*NUM_LEDS_PER_STRIP)]] = CHSV(hue1, saturation1, value1);
        }
        else  // fade to black
        {
          leds[led_array[y+(i*NUM_LEDS_PER_STRIP)]].fadeToBlackBy( tail_length );
        }
      }
    }
  }
  FastLED.show();
  incrementIndex(&program_index1, &total_steps1, &increment_by1);
}
