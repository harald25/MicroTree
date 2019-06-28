#include "utility_functions.h"

// Audio library objects
AudioInputAnalog         adc1(A3);
AudioAnalyzeFFT1024      fft;
AudioConnection          patchCord1(adc1, fft);

const unsigned int audio_rective_setting_max_value = 255;
// These parameters adjust the vertical thresholds
const float maxLevel = 0.5;      // 1.0 = max, lower is more "sensitive"
const float dynamicRange = 20.0; // total range to display, in decibels
const float linearBlend = 0.3;   // useful range is 0 to 0.7
// This array holds the volume level (0 to 1.0) for each
// vertical pixel to turn on.  Computed in setup() using
// the 3 parameters above.
float thresholdVertical[audio_rective_setting_max_value];
float level_old;
float smoothing_coeff_positive = 1.0; // experiment with different coefficients; --> 0.0 < smoothing_coeff < 1.0
float smoothing_coeff_negative = 1.0;
bool react_to_audio = 0;

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
        case CUSTOM_LAMP:
          customLampUpdate();
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
        default:
          break;
      }
    }
  }
}

void audioReact(audio_reactive_setting setting)
{
  if(react_to_audio)
  {
    float level;
    if (fft.available())
    {
      level = fft.read(1, 10);

      if((level-level_old) > 0.0)
      {
        level = smoothing_coeff_positive * level + (1.0 - smoothing_coeff_positive) * level_old;
      }
      else
      {
        level = smoothing_coeff_negative * level + (1.0 - smoothing_coeff_negative) * level_old;
      }
      level_old = level;

      for(unsigned int x = 0; x < audio_rective_setting_max_value; x++)
      {
        if (level >= thresholdVertical[x])
        {
          value2 = x;
          break;
        }
      }
    }
  }
}

void computeVerticalLevels() {
  unsigned int y;
  float n, logLevel, linearLevel;

  for (y=0; y < audio_rective_setting_max_value; y++) {
    n = (float)y / (float)(audio_rective_setting_max_value - 1);
    logLevel = pow10f(n * -1.0 * (dynamicRange / 20.0));
    linearLevel = 1.0 - n;
    linearLevel = linearLevel * linearBlend;
    logLevel = logLevel * (1.0 - linearBlend);
    thresholdVertical[y] = (logLevel + linearLevel) * maxLevel;
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

void setActivePalette(int x) {
  active_palette = blink_palette_array[x];
}

void changePreset(OSCMessage &msg, int addrOffset )
{
  if (debug) {
    Serial.println("Changing preset");
  }

  update = true;  //Times are a changin', we need to update

  if(msg.fullMatch("/Preset/custom_lamp") && (active_program == CUSTOM_LAMP))
  {
    if (debug) {
      Serial.println("CustomlampPreset");
    }
    uint8_t preset_number = (uint8_t)msg.getFloat(0);
    setCustomlampPreset(preset_number);
  }

}

void changeColorPreset(OSCMessage &msg, int addrOffset )
{
  if (debug) {
    Serial.println("Changing color preset");
  }

  update = true;  //Times are a changin', we need to update

  if(msg.fullMatch("/Colorpreset"))
  {

    if (debug) {
      Serial.println("ColorPreset");
    }
    uint8_t color_preset_number = (uint8_t)msg.getFloat(0);
    setColorPreset(color_preset_number);
  }
}

void changeLEDProgram(OSCMessage &msg, int addrOffset )
{
  update = true;

  if(msg.fullMatch("/Program/custom_lamp"))
  {
    customLamp();
    if (debug) {
      Serial.println("Activated the program Custom Lamp");
    }

  }

  if(msg.fullMatch("/Program/blink"))
  {
    blink();

    if (debug) {
      Serial.println("Activated the program Blink");
    }
  }

  if(msg.fullMatch("/Program/theaterchase"))
  {
    theaterChase();
    if (debug) {
      Serial.println("Activated the program Theater Chase");
    }
  }

  if(msg.fullMatch("/Program/scanner"))
  {
    scanner();

    if (debug) {
      Serial.println("Activated the program Scanner");
    }
  }
}

void changeValue(OSCMessage &msg, int addrOffset )
{
  if (msg.fullMatch("/Variable/interval"))
  {
    float value = msg.getFloat(0);
    setInterval((int)value);
    update = true;
  }

  if (msg.fullMatch("/Variable/value1"))
  {
    uint8_t value = (uint8_t)msg.getFloat(0);
    value1 = value;
    update = true;
  }
  if (msg.fullMatch("/Variable/value2"))
  {
    uint8_t value = (uint8_t)msg.getFloat(0);
    value2 = value;
    update = true;
  }
  if (msg.fullMatch("/Variable/saturation1"))
  {
    uint8_t saturation = (uint8_t)msg.getFloat(0);
    saturation1 = saturation;
    update = true;
  }
  if (msg.fullMatch("/Variable/saturation2"))
  {
    uint8_t saturation = (uint8_t)msg.getFloat(0);
    saturation2 = saturation;
    update = true;
  }
  if (msg.fullMatch("/Variable/hue1"))
  {
    uint8_t hue = (uint8_t)msg.getFloat(0);
    hue1 = hue;
    update = true;
  }
  if (msg.fullMatch("/Variable/hue2"))
  {
    uint8_t hue = (uint8_t)msg.getFloat(0);
    hue2 = hue;
    update = true;
  }

  if (msg.match("/Variable/lamp"))
  {
    float lamp = msg.getFloat(0);
    activateDeactivateLamp(uint8_t(lamp));
    update = true;
  }

  if (msg.fullMatch("/Variable/color1"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    uint8_t y = (uint8_t)msg.getFloat(1);

    setSaturation1(x);
    setHue1(y);

    update = true;
  }

  if (msg.fullMatch("/Variable/color2"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    uint8_t y = (uint8_t)msg.getFloat(1);

    saturation2 = x;
    hue2 = y;

    update = true;
  }

  //Random interval for blink
  if (msg.fullMatch("/Variable/blinkrandomtime"))
  {
    float value = msg.getFloat(0);
    setBlinkRandomTime((int)value);
    update = true;
  }

  if (msg.fullMatch("/Variable/palette"))
  {
    int x = (int)msg.getFloat(0);
    if (x > -1) {
      setActivePalette(x);
    }
    else {
      setActivePalette(0);
    }
    update = true;
  }

  if (msg.fullMatch("/Variable/chase_mode"))
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

  if (msg.fullMatch("/Variable/pixel_distance"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    pixel_distance = x;
    update = true;
  }

  if (msg.fullMatch("/Variable/pixel_width"))
  {
    uint8_t x = (uint8_t)msg.getFloat(0);
    pixel_width = x;
    update = true;
  }

  if (msg.fullMatch("/Variable/direction"))
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

  if (msg.fullMatch("/Variable/stopstart"))
  {
    update = 1-update;
    FastLED.delay(10);
    Serial.print("Update: ");
    Serial.println(update);
  }

  if (msg.fullMatch("/Variable/tail_length"))
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

void setColorPreset(uint8_t color_preset)
{
  //Warm white
  if(color_preset == 1)
  {

    setHue1(25);
    setSaturation1(180);
    setValue1(255);
    if (debug) {
      Serial.println("Activated the color preset warm white");
    }
  }

  //Orange
  if(color_preset == 2)
  {
    setHue1(20);
    setSaturation1(255);
    setValue1(255);
    if (debug) {
      Serial.println("Activated the color preset orange");
    }
  }

  //Bluegreen
  if(color_preset == 3)
  {
    setHue1(128);
    setSaturation1(200);
    setValue1(255);
    if (debug) {
      Serial.println("Activated the color preset bluegreen");
    }
  }
  //Purple
  if(color_preset == 4)
  {
    setHue1(230);
    setSaturation1(255);
    setValue1(255);
    if (debug) {
      Serial.println("Activated the color preset purple");
    }
  }
}
