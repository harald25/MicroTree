#include "program_preprogram.h"
#include "program_blink.h"
#include "program_custom_lamp.h"
#include "program_scanner.h"
#include "program_theater_chase.h"

int last_preprogram_change;
int preprogram_length;
uint8_t preprogram_index;
uint8_t number_of_preprograms;
bool preprogram_just_changed;

void preprogram()
{
  active_program = PREPROGRAM;
  last_preprogram_change = 0;
  preprogram_length = 10 * 1000; //10 seconds
  preprogram_index = 0;
  number_of_preprograms = 8;
  preprogram_just_changed = 1;
}

void preprogramUpdate()
{
  if ( (millis() - last_preprogram_change) > preprogram_length)
  {
    preprogram_index ++;
    if (preprogram_index >= number_of_preprograms) {
      preprogram_index = 0;
    }
  }

  if (preprogram_just_changed)
  {
    //Run the function to initialize current preprogram
  }
  // Run funtion to start updating the LEDs with currently active preprogram

}

class SettingsObject
{
  int setting_interval;
  int setting_increment_by1;
  int setting_increment_by2;
  int16_t setting_saturation1;
  int16_t setting_value1;
  int16_t setting_hue1;
  int16_t setting_saturation2;
  int16_t setting_value2;
  int16_t setting_hue2;


  public:
    SettingsObject(int si, int sib1, int sib2, int16_t ss1, int16_t ss2, int16_t sv1, int16_t sv2, int16_t sh1, int16_t sh2)
    {
      setting_interval = si;
      setting_increment_by1 = sib1;
      setting_increment_by2 = sib2;
      setting_saturation1 = ss1;
      setting_saturation2 = ss2;
      setting_value1 = sv1;
      setting_value2 = sv2;
      setting_hue1 = sh1;
      setting_hue2 = sh2;
    }

    //Need to make functions to change all class variables

    //Need to make function to update all global variables with 

};
