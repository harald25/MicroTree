#include "utility_functions.h"
bool debug_utility = false;
void updateLEDs()
{
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
          Serial.println("Case VUMETER");
          vumeterUpdate();
        default:
          break;
      }
    }
  }
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

}

void changeLEDProgram(OSCMessage &msg, int addrOffset )
{
  update = true;

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

}

void allLedsOff()
{
  for(int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS;x++)
  {
    leds[led_array[x]] = CRGB::Black;
  }
}

void allLedsOn()
{
  for(int x = 0; x < NUM_LEDS_PER_STRIP*NUM_STRIPS;x++)
  {
    leds[led_array[x]] = CRGB::White;
  }
}
