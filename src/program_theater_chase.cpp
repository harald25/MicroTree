#include "program_theater_chase.h"

chase_mode c_mode;
uint8_t pixel_width;
uint8_t pixel_distance;

void theaterChase()
{
  c_mode = REGULAR;
  active_program = THEATER_CHASE;
  total_steps1 = NUM_STRIPS*NUM_LEDS_PER_STRIP;
  interval = 100;
  hue1 = 15;
  hue2 = 200;
  saturation1 = 255;
  saturation2 = 255;
  value1 = 255;
  value2 = 0;
  program_index1 = 0;
  dir = FORWARD;
  pixel_distance = 25;
  pixel_width = 10;
  update = true;
  increment_by1 = 1;
  allLedsOff();
}


void theaterChaseUpdate()
{
  audioReact((audio_reactive_setting)reactive_setting);
  if (c_mode == RAINBOW_CHASE)
  {
    uint8_t tail = 0;
    int last_middle = 0;

    for(int i=0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; i++)
    {
      if ((i + program_index1) % pixel_distance == 0)
      {
        leds[led_order_array[i]] = CHSV((i*10)%255, saturation1, value1);
        tail = pixel_width;
        last_middle = i;
      }
      else if (tail != 0)
      {
       leds[led_order_array[i]] = CHSV((((i*10)-(pixel_width-(tail*3)+1)))%255, saturation1, value1);
       tail--;
      }
      else
      {
        leds[led_order_array[i]] = CHSV(hue2, saturation2, value2);
      }
    }
  }

  if (c_mode == REGULAR)
  {
    for(int i=0; i< NUM_STRIPS*NUM_LEDS_PER_STRIP; i++)
    {
      if (((i + program_index1) % pixel_distance >= 0) && ((i + program_index1) % pixel_distance < pixel_width))
      {
        leds[led_order_array[i]] = CHSV(hue1, saturation1, value1);
      }
      else
      {
        leds[led_order_array[i]] = CHSV(hue2, saturation2, value2);
      }
    }
  }

  FastLED.show();
  incrementIndex(&program_index1, &total_steps1, &increment_by1);
}

void sendTheaterValuesToTouchosc()
{
  OSCMsgSend("/variable/interval", (float)interval);
  OSCMsgSend("/variable/value1", (float)value1);
  OSCMsgSend("/variable/value2", (float)value2);
  OSCMsgSend("/variable/pixel_width", (float)pixel_width);
  OSCMsgSend("/variable/pixel_distance", (float)pixel_distance);

}

void theaterSettings(OSCMessage &msg, int addrOffset)
{
    if (msg.fullMatch("/theater/page"))
    {
      sendTheaterValuesToTouchosc();
    }
}
