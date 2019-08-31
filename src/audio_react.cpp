#include "audio_react.h"

// If set to true, messages will be output to serial console
const bool debug_audioreact = 0;

// AUDIO OBJECTS
// Audio objects are defined in main.h because they are shared between multiple programs

audio_reactive_setting reactive_setting = VAL1;
const unsigned int audio_rective_setting_max_value = 255;
// This array holds the volume level (0 to 1.0) for each
// vertical pixel to turn on.  Computed in setup() using
// the 3 parameters above.
float level_old;
float smoothing_coeff_positive = 1.0; // experiment with different coefficients; --> 0.0 < smoothing_coeff < 1.0
float smoothing_coeff_negative = 0.5;

//Setting some start values for the sound reactivity. These are later supposed
//to be manipulated with TouchOSC
bool react_to_audio = false;
uint16_t fft_start = 1;
uint16_t fft_stop = 3;
uint8_t amplification = 5;



void audioReact(audio_reactive_setting setting)
{
  if((active_preprogram != VUMETER) && (active_program != VUMETER) )
  {
    if(react_to_audio)
    {
      float level;
      if (fft.available())
      {
        //In casee the user sets stop higher than start via TouchOSC
        if(fft_stop < fft_start) {
          fft_stop = fft_start;
        }
        level = fft.read(fft_start,fft_stop);

        if((level-level_old) > 0.0)
        {
          level = smoothing_coeff_positive * level + (1.0 - smoothing_coeff_positive) * level_old;
        }
        else
        {
          level = smoothing_coeff_negative * level + (1.0 - smoothing_coeff_negative) * level_old;
        }
        level_old = level;
        level = (level * audio_rective_setting_max_value) * amplification;

        switch (setting)
        {
          case HUE1:
            hue1 = level;
            break;
          case HUE2:
            hue2 = level;
            break;
          case SAT1:
            saturation1 = level;
            break;
          case SAT2:
            saturation2 = level;
            break;
          case VAL1:
            value1 = level;
            break;
          case VAL2:
            value2 = level;
            break;
          case GLOB_BRIGHTNESS:
            FastLED.setBrightness(level);
            break;
          default:
            break;
        }
      }
    }
  }
}

void sendReactValuesToTouchosc()
{
  OSCMsgSend("/react/toggle", (float)react_to_audio);

  OSCMsgSend("/fft/start/value", (float)fft_start);
  OSCMsgSend("/react/fft/start", (float)fft_start);

  OSCMsgSend("/fft/stop/value", (float)fft_stop);
  OSCMsgSend("/react/fft/stop", (float)fft_stop);

  OSCMsgSend("/react/smooth_pos/value", (float)smoothing_coeff_positive);
  OSCMsgSend("/react/smooth_pos", (float)smoothing_coeff_positive);

  OSCMsgSend("/react/smooth_neg/value", (float)smoothing_coeff_negative);
  OSCMsgSend("/react/smooth_neg", (float)smoothing_coeff_negative);

  OSCMsgSend("/react/amplification", (float)amplification);
}

void setAudioReact(bool react) {
  react_to_audio = react;
  OSCMsgSend("/react/toggle", (float)react_to_audio);
  sendReactValuesToTouchosc();

  if(debug_audioreact) {
    Serial.print("Toggeling audio react: ");
    Serial.println(react_to_audio);
  }
}

void setFftStart(uint16_t fft) {
  fft_start = fft;
  OSCMsgSend("/fft/start/value", (float)fft_start);

  if(debug_audioreact) {
    Serial.print("FFT start: ");
    Serial.println(fft_start);
  }
}

void setFftStop(uint16_t fft) {
  fft_stop = fft;
  OSCMsgSend("/fft/stop/value", (float)fft_stop);

  if(debug_audioreact) {
    Serial.print("FFT stop: ");
    Serial.println(fft_stop);
  }
}

void setSmoothPos(float smooth_pos) {
  smoothing_coeff_positive = smooth_pos;
  OSCMsgSend("/react/smooth_pos/value", (float)smoothing_coeff_positive);

  if(debug_audioreact) {
    Serial.print("Smoothing coefficient positive: ");
    Serial.println(smoothing_coeff_positive);
  }
}

void setSmoothNeg(float smooth_neg) {
  smoothing_coeff_negative = smooth_neg;
  OSCMsgSend("/react/smooth_neg/value", (float)smoothing_coeff_negative);

  if(debug_audioreact) {
    Serial.print("Smoothing coefficient negative: ");
    Serial.println(smoothing_coeff_negative);
  }
}

void setAudioReactiveSetting(uint8_t setting) {
  reactive_setting = (audio_reactive_setting)setting;
}

void setAudioAmplification(uint8_t setting) {
  amplification = setting;
}

void audioReactSettings(OSCMessage &msg, int addrOffset)
{
  if (msg.fullMatch("/react/toggle"))
  {
    float value = msg.getFloat(0);
    setAudioReact((bool)value);
  }
  if (msg.fullMatch("/react/fft/start"))
  {
    float value = msg.getFloat(0);
    setFftStart((uint16_t)value);
  }
  if (msg.fullMatch("/react/fft/stop"))
  {
    float value = msg.getFloat(0);
    setFftStop((uint16_t)value);
  }
  if (msg.fullMatch("/react/smooth_pos"))
  {
    float value = msg.getFloat(0);
    setSmoothPos(value);
  }
  if (msg.fullMatch("/react/smooth_neg"))
  {
    float value = msg.getFloat(0);
    setSmoothNeg(value);
  }
  if (msg.fullMatch("/react/page"))
  {
    sendReactValuesToTouchosc();
  }
  if (msg.fullMatch("/react/reactive_setting"))
  {
    float value = msg.getFloat(0);
    setAudioReactiveSetting((uint8_t)value);
  }
  if (msg.fullMatch("/react/amplification"))
  {
    float value = msg.getFloat(0);
    setAudioAmplification(value);
  }
}
