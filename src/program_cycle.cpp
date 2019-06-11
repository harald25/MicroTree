#include "program_cycle.h"
cycle_order order;
cycle_mode mode;

CRGBPalette16 * cycle_palette_array[] = { &heatcolorPalette};
CRGBPalette16 * active_cycle_palette;

void cycle(cycle_mode c_mode, cycle_order c_order)
{
  order = WAVE;
  mode = GRADIENT;
  saturation1 = 255;
  value1 = 255;
  active_program = CYCLE;
  update = true;
  program_index1 = 0;
  program_index2 = 0;
  delta = 20;
  total_steps1 = 350;
  total_steps2 = 255;
  increment_by1 = 1;
  interval = 35;
  active_cycle_palette = &heatcolorPalette;
  slope = -2.0;

}

void cycleUpdate()
{
  if (order == START_TO_END)
  {
    for (int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS; x++)
    {
      if(mode == RAINBOW) {
        leds[led_array[x]] = CHSV(((x+program_index1)%255), saturation1, value1);
      }
      if(mode == GRADIENT) {
        leds[led_array[x]] = ColorFromPalette(*active_cycle_palette,((x+program_index1)%255));
      }

    }
  }

  if (order == WAVE)
  {
    // Note to self: don't confuse the x of the loop with the x-coordinate of the pixels. x in the loop represents a pixel in the LED strip
    // 'led_coordinates[x][0]' is the x-coordinate of the x'th pixel, 'led_coordinates[x][1]' is the y-coordinate of the x'th pixel
    for (int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS; x++)
    {

      int16_t y = program_index1 + (slope*led_coordinates[x][0]);
      // Calculate the distance between the y coordinate of the current pixel the y to be lit, calculated above
      int16_t dist = abs(y - (led_coordinates[x][1]+delta));

      // If distance is less than delta, the pixel should be lit
      if (dist < delta) {
        // Calculate brightness of the current pixel based on distance
        uint16_t brightness = (delta-dist)*(value1/delta);

        if (mode == RAINBOW) {
          leds[led_array[x]] = CHSV(((led_coordinates[x][1]+program_index1+program_index2)%255), saturation1, brightness);
        }
        if(mode == GRADIENT) {
          leds[led_array[x]] = ColorFromPalette(*active_cycle_palette,((led_coordinates[x][1]+program_index1+program_index2)%255));
          leds[led_array[x]].nscale8_video(brightness);
        }
      }
      else {
        leds[led_array[x]] = CRGB::Black;
      }

    }
    incrementIndex(&program_index2, &total_steps2, &increment_by2);
  }

  incrementIndex(&program_index1, &total_steps1, &increment_by1);

  FastLED.show();
}
