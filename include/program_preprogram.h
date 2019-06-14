#ifndef __PREPROGRAM_H_INCLUDED_
#define __PREPROGRAM_H_INCLUDED_

#include "main.h"

void preprogram();
void preprogramUpdate();
extern program active_preprogram;

class SettingsObject
{
  public:
    int16_t setting_interval;
    int16_t setting_increment_by1;
    int16_t setting_increment_by2;
    int16_t setting_saturation1;
    int16_t setting_value1;
    int16_t setting_hue1;
    int16_t setting_saturation2;
    int16_t setting_value2;
    int16_t setting_hue2;
    int16_t setting_preprogram_length;
    program setting_active_preprogram;



    SettingsObject(int16_t s_interval, int16_t s_inc_by1, int16_t s_inc_by2, int16_t s_sat1, int16_t s_sat2, int16_t s_val1, int16_t s_val2, int16_t s_hue1, int16_t s_hue2, int16_t s_prep_length, program s_active_preprog);    //Update all the class variables with the corresponding global variables
    void getGlobalSettings();
    //Update all the global variables with the ones given to the settings object
    void setGlobalSettings();
    int16_t getPreprogramLength();
    program getActivePreprogram();
};

extern SettingsObject settings_program1;
extern SettingsObject settings_program2;
extern SettingsObject settings_program3;
extern SettingsObject settings_program4;
extern SettingsObject settings_program5;
extern SettingsObject settings_program6;
extern SettingsObject settings_program7;
extern SettingsObject settings_program8;


#endif
