#include "utility_functions.h"
bool debug_utility = false;
void updateLEDs()
{
  // Serial.println("Entered updateLEDs()");
  if(update)
  {
    if ((millis() - last_update) > interval) // time to update
    {
      last_update = millis();
      switch (active_program)
      {
        case NONE:
          break;
        case BLINK:
          blinkUpdate();
          break;
        case THEATER_CHASE:
          theaterChaseUpdate();
          break;
        case SCANNER:
          scannerUpdate();
          break;
        case PREPROGRAM:
          preprogramUpdate();
          break;
        case VUMETER:
          vumeterUpdate();
          break;
        case PULSE:
          pulseUpdate();
          break;
        case FIREWORKS:
          //Serial.println("updateLEDs() running fireworksUpdate()");
          fireworksUpdate();
          //Serial.println("updateLEDs() finished running fireworksUpdate()");
          break;
        default:
          break;
      }
    }
  }
  // Serial.println("Exited updateLEDs()");
}

// Increment the Index and reset at the end
void incrementIndex(int *program_index, uint16_t *total_steps, int *increment_by)
{
  if (dir == FORWARD)
  {
    *program_index = *program_index + *increment_by;
    if (*program_index >= *total_steps)
    {
      *program_index = 0;
    }
  }
  if (dir == REVERSE)
  {
    *program_index = *program_index - *increment_by;
    if (*program_index <= 0)
    {
      *program_index = *total_steps;
    }
  }
}

void setHue1(uint8_t hue) {
  hue1 = hue;
}
void setValue1(uint8_t value) {
  value1 = value;
}
void setSaturation1(uint8_t saturation) {
  saturation1 = saturation;
}

void setInterval(uint8_t i) {
  interval = i;
}

void setBlinkRandomTime(uint32_t x)
{
  blink_random_time = x;
}

void setActivePalette(OSCMessage &msg, int addrOffset) {

  if(msg.fullMatch("/palette/classic")) {
    active_palette = &spectrum_classic;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/warm")) {
    active_palette = &spectrum_warm;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/pastel")) {
    active_palette = &spectrum_pastel;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/candy")) {
    active_palette = &spectrum_candy;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/rainbow")) {
    spec_mode = RAINBOW;
  }
  if(msg.fullMatch("/palette/blue")) {
    active_palette = &blink_palette_bluetones;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/orange")) {
    active_palette = &blink_palette_orange;
    spec_mode = GRADIENT;
  }
  if(msg.fullMatch("/palette/purple")) {
    active_palette = &blink_palette_purple;
    spec_mode = GRADIENT;
  }
  if (msg.fullMatch("/palette/vintage"))
  {
    active_palette = &blink_palette_es_vintage;
    spec_mode = GRADIENT;
  }
  if (msg.fullMatch("/palette/purplefly"))
  {
    active_palette = &blink_palette_purplefly;
    spec_mode = GRADIENT;
  }
  if (msg.fullMatch("/palette/greeny"))
  {
    active_palette = &blink_palette_greeny;
    spec_mode = GRADIENT;
  }
  if (msg.fullMatch("/palette/bhw1_14"))
  {
    active_palette = &blink_palette_bhw1_14;
    spec_mode = GRADIENT;
  }
  if (msg.fullMatch("/palette/bhw2_22"))
  {
    active_palette = &blink_palette_bhw2_22;
    spec_mode = GRADIENT;
  }
}

void changeLEDProgram(OSCMessage &msg, int addrOffset )
{
  update = true;

  if(msg.fullMatch("/program/preprogram"))
  {
    preprogram();
    if (debug_utility) {
      Serial.println("Activated the program Preprogram");
    }
  }

  if(msg.fullMatch("/program/blink"))
  {
    blink();
    if (debug_utility) {
      Serial.println("Activated the program Blink");
    }
  }

  if(msg.fullMatch("/program/theaterchase"))
  {
    theaterChase();
    if (debug_utility) {
      Serial.println("Activated the program Theater Chase");
    }
  }

  if(msg.fullMatch("/program/scanner"))
  {
    scanner();
    if (debug_utility) {
      Serial.println("Activated the program Scanner");
    }
  }

  if(msg.fullMatch("/program/vumeter"))
  {
    vumeter();
    if (debug_utility) {
      Serial.println("Activated the program VU-meter");
    }
  }

  if (msg.fullMatch("/program/pulse"))
  {
    pulse();
    if (debug_utility) {
      Serial.println("Activated the program pulse");
    }
  }

  if (msg.fullMatch("/program/fireworks"))
  {
    fireworks();
    if (debug_utility) {
      Serial.println("Activated the program fireworks");
    }
  }
}

void changeValue(OSCMessage &msg, int addrOffset )
{
  if (msg.fullMatch("/variable/interval"))
  {
    float value = msg.getFloat(0);
    setInterval((int)value);
    update = true;
  }

  if (msg.fullMatch("/variable/value1"))
  {
    uint8_t value = (uint8_t)msg.getFloat(0);
    value1 = value;
    update = true;
  }
  if (msg.fullMatch("/variable/value2"))
  {
    uint8_t value = (uint8_t)msg.getFloat(0);
    value2 = value;
    update = true;
  }
  if (msg.fullMatch("/variable/saturation1"))
  {
    uint8_t saturation = (uint8_t)msg.getFloat(0);
    saturation1 = saturation;
    update = true;
  }
  if (msg.fullMatch("/variable/saturation2"))
  {
    uint8_t saturation = (uint8_t)msg.getFloat(0);
    saturation2 = saturation;
    update = true;
  }
  if (msg.fullMatch("/variable/hue1"))
  {
    uint8_t hue = (uint8_t)msg.getFloat(0);
    hue1 = hue;
    update = true;
  }
  if (msg.fullMatch("/variable/hue2"))
  {
    uint8_t hue = (uint8_t)msg.getFloat(0);
    hue2 = hue;
    update = true;
  }

  if (msg.fullMatch("/variable/color1"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    uint8_t y = (uint8_t)msg.getFloat(1);

    setSaturation1(x);
    setHue1(y);

    update = true;
  }

  if (msg.fullMatch("/variable/color2"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    uint8_t y = (uint8_t)msg.getFloat(1);

    saturation2 = x;
    hue2 = y;

    update = true;
  }

  //Random interval for blink
  if (msg.fullMatch("/variable/blinkrandomtime"))
  {
    float value = msg.getFloat(0);
    setBlinkRandomTime((int)value);
    update = true;
  }

  if (msg.fullMatch("/variable/chase_mode"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    if (x > -1)
    {
      if (x == 1) {
        c_mode = REGULAR;
      }
      else if (x == 2) {
        c_mode = RAINBOW_CHASE;
      }
    }
    update = true;
  }

  if (msg.fullMatch("/variable/pixel_distance"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    pixel_distance = x;
    update = true;
  }

  if (msg.fullMatch("/variable/pixel_width"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    pixel_width = x;
    update = true;
  }

  if (msg.fullMatch("/variable/direction"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    Serial.print("Direction: ");
    Serial.println(x);
    if (x == 1) {
      dir = FORWARD;
    }
    if (x == 2) {
      dir = REVERSE;
    }
    update = true;
  }

  if (msg.fullMatch("/variable/stopstart"))
  {
    update = 1-update;
    FastLED.delay(10);
  }

  if (msg.fullMatch("/variable/tail_length"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    tail_length = x;
    update = true;
  }

  if (msg.fullMatch("/variable/globalbrightness"))
  {
    uint8_t brightness = (uint8_t)msg.getFloat(0);
    FastLED.setBrightness(brightness);
    OSCMsgSend("/variable/globalbrightness/value", brightness);
  }

}

void allLedsOff()
{
  for(int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS;x++)
  {
    leds[x] = CRGB::Black;
  }
}

void allLedsOn()
{
  for(int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS;x++)
  {
    leds[x] = CRGB::White;
  }
}

void generate_led_order_array(led_order order)
{
  int ledindex = 0;

  // "Normal" order. The pixels are ordered the way the strips are connected
  if (order == NORMAL)
  {
    Serial.println("LED order = NORMAL");
    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++) {
      led_order_array[i] = i;
    }
  }

  // Strip order is untouched, but every strip (or virtual strip if STRIP_SPLIT > 1) is backwards
  else if (order == EVERY_STRIP_REVERSED)
  {
    Serial.println("LED order = EVERY_STRIP_REVERSED");
    for (int i = 0; i < NUM_STRIPS * STRIP_SPLIT; i++)
    {
      for (int x = NUM_LEDS_PER_STRIP / STRIP_SPLIT; x > 0; x--)
      {
        led_order_array[ledindex] = (i*(NUM_LEDS_PER_STRIP / STRIP_SPLIT))+(x-1);
        ledindex ++;
      }
    }
  }

  // The order of the strips are reversed, but each individual strip (or virtual strip if STRIP_SPLIT > 1) is forwards
  else if (order == STRIPS_IN_REVERSE_ORDER)
  {
    Serial.println("LED order = STRIPS_IN_REVERSE_ORDER");
    for (int i = NUM_STRIPS*STRIP_SPLIT; i > 0; i--)
    {
      for (int x = 0; x < NUM_LEDS_PER_STRIP/STRIP_SPLIT; x++)
      {
        led_order_array[ledindex] = ((i-1)*NUM_LEDS_PER_STRIP/STRIP_SPLIT)+x;
        ledindex ++;
      }
    }
  }

  else if (order == EVERY_SECOND_STRIP_REVERSED)
  {
    Serial.println("LED order = EVERY_SECOND_STRIP_REVERSED");
    for (int i = 0; i < NUM_STRIPS * STRIP_SPLIT; i++)
    {
      if (i % 2 == 0)
      {
        for (int x = 0; x < NUM_LEDS_PER_STRIP/STRIP_SPLIT; x++)
        {
          led_order_array[ledindex] = (i * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + x;
          ledindex ++;
        }
      }
      else
      {
        for (int x = NUM_LEDS_PER_STRIP / STRIP_SPLIT; x > 0; x--)
        {
          led_order_array[ledindex] = (i*(NUM_LEDS_PER_STRIP / STRIP_SPLIT))+(x-1);
          ledindex ++;
        }
      }
    }
  }

  // ----- Uncomment to print the generated LED order to terminal -----
  //
  // delay(5000);
  // for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
  // {
  //   if ((i + 1) % (NUM_LEDS_PER_STRIP/STRIP_SPLIT) == 0)
  //   {
  //     Serial.println(led_order_array[i]);
  //     Serial.println("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  //   }
  //   else
  //   {
  //     Serial.print(led_order_array[i]);
  //     Serial.print(", ");
  //   }
  // }

}
