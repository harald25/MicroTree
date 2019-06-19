#include "program_preprogram.h"
#include "program_blink.h"
#include "program_custom_lamp.h"
#include "program_scanner.h"
#include "program_theater_chase.h"

program active_preprogram;
int last_preprogram_change;
int preprogram_last_update = 0;
int16_t preprogram_length; //The default value if nothing else is passed to SettingsObject
uint8_t preprogram_index;
bool preprogram_just_changed;
bool preprogram_first_run;
SettingsObject settings_program1(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,BLINK);
SettingsObject settings_program2(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,SCANNER);
SettingsObject settings_program3(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,THEATER_CHASE);
SettingsObject settings_program4(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,BLINK);
SettingsObject settings_program5(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,SCANNER);
SettingsObject settings_program6(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,THEATER_CHASE);
SettingsObject settings_program7(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,BLINK);
SettingsObject settings_program8(-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,SCANNER);
SettingsObject settings_array[8] = {settings_program1,settings_program2,settings_program3,settings_program4,settings_program5,settings_program6,settings_program7,settings_program8};
const uint8_t number_of_preprograms = 8; //This number must equal the length of $settings_array


void preprogram()
{
  last_preprogram_change = 0;
  preprogram_length = 10 * 1000; //10 seconds
  preprogram_index = 0;
  preprogram_just_changed = 1;
  preprogram_first_run = 1;
  update = 1;
  active_program = PREPROGRAM;
}

void preprogramUpdate()
{
  //Check to see if it is time to change to the next preprogram
  if ((millis() - last_preprogram_change) > preprogram_length)
  {
    if (debug) {
      Serial.println("Time since last update is larger than preprogram_length");
      Serial.println(millis() - last_preprogram_change);
      Serial.println(preprogram_length);
    }
    preprogram_index ++;
    if (preprogram_index >= number_of_preprograms) {
      preprogram_index = 0;
    }
    preprogram_just_changed = 1;
    last_preprogram_change = millis();
  }

  if((preprogram_just_changed) || (preprogram_first_run))
  {
    preprogram_first_run = 0;
    settings_array[preprogram_index].setGlobalSettings();
    //Run the functions to initialize current preprogram
    switch (active_preprogram)
    {
      Serial.println("Switch active_program.");
      case NONE:
        break;
      case BLINK:
        blink();
        Serial.println("Blink preprogram activated");
        break;
      case THEATER_CHASE:
        theaterChase();
        Serial.println("Theater chase preprogram activated");
        break;
      case SCANNER:
        scanner();
        Serial.println("Scanner preprogram activated");
        break;
      default:
        break;
      }
      active_program = PREPROGRAM; //Need to set this because the initializing function of the different programs sets it "wrong"
      preprogram_just_changed = 0;
  }

  //Check to see if it is time to update current preprogram
  if ((millis() - preprogram_last_update) > interval) // time to update
  {
    if(debug) {
      Serial.println("Time to update");
      Serial.println(millis() - preprogram_last_update);
    }
    preprogram_last_update = millis();
    switch (active_preprogram)
    {
      case NONE:
        break;
      case BLINK:
        blinkUpdate();
        Serial.println("Blink update");
        break;
      case THEATER_CHASE:
        theaterChaseUpdate();
        Serial.println("Theater Chase update");
        break;
      case SCANNER:
        scannerUpdate();
        Serial.println("Scanner update");
        break;
      default:
        break;
    }
  }
}

//Constructor for the SettingsObject
SettingsObject::SettingsObject(int16_t s_interval, int16_t s_inc_by1, int16_t s_inc_by2, int16_t s_sat1, int16_t s_sat2, int16_t s_val1, int16_t s_val2, int16_t s_hue1, int16_t s_hue2, int16_t s_prep_length, program s_active_preprog)
{
  setting_interval = s_interval;
  setting_increment_by1 = s_inc_by1;
  setting_increment_by2 = s_inc_by2;
  setting_saturation1 = s_sat1;
  setting_value1 = s_val1;
  setting_hue1 = s_hue1;
  setting_saturation2 = s_sat2;
  setting_value2 = s_val2;
  setting_hue2 = s_hue2;
  setting_preprogram_length = s_prep_length;
  setting_active_preprogram = s_active_preprog;
}


//Update all the class variables with the corresponding global variables
void SettingsObject::getGlobalSettings()
{
  setting_interval = interval;
  setting_increment_by1 = increment_by1;
  setting_increment_by2 = increment_by2;
  setting_saturation1 = saturation1;
  setting_saturation2 = saturation2;
  setting_value1 = value1;
  setting_value2 = value2;
  setting_hue1 = hue1;
  setting_hue2 = hue2;
  setting_preprogram_length = preprogram_length;
  setting_active_preprogram = active_preprogram;
}

//Update all the global variables with the ones from the SettingsObject
void SettingsObject::setGlobalSettings()
{
  if(setting_interval > -1) {
    interval = (int)setting_interval;
  }
  if(increment_by1 > -1) {
    increment_by1 = setting_increment_by1;
  }
  if(increment_by2 > -1) {
    increment_by2 = setting_increment_by2;
  }
  if(setting_saturation1 > -1) {
    saturation1 = setting_saturation1;
  }
  if(setting_saturation2 > -1) {
    saturation2 = setting_saturation2;
  }
  if(setting_value1 > -1) {
    value1 = setting_value1;
  }
  if(setting_value2 > -1) {
    value2 = setting_value2;
  }
  if(setting_hue1 > -1) {
    hue1 = setting_hue1;
  }
  if(setting_hue2 > -1) {
    hue2 = setting_hue2;
  }
  if (settings_array[preprogram_index].getPreprogramLength() > -1) {
    preprogram_length = settings_array[preprogram_index].getPreprogramLength();
  }
  active_preprogram = settings_array[preprogram_index].getActivePreprogram();
  if(debug) {
    Serial.print("Active preprogram is now: ");
    Serial.println(active_preprogram);
  }
}

int16_t SettingsObject::getPreprogramLength() {
  return setting_preprogram_length;
}

program SettingsObject::getActivePreprogram() {
  return setting_active_preprogram;
}
