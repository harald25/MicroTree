#ifndef __PREPROGRAM_H_INCLUDED_
#define __PREPROGRAM_H_INCLUDED_

#include "main.h"

void preprogram();
void preprogramUpdate();

class SettingsObject
{
  public:
    int16_t setting_interval;
    int16_t setting_saturation1;
    int16_t setting_value1;
    int16_t setting_hue1;
    int16_t setting_saturation2;
    int16_t setting_value2;
    int16_t setting_hue2;
    int16_t setting_preprogram_length;
    program setting_active_preprogram;
    int16_t setting_pixel_distance;
    int16_t setting_pixel_width;
    int16_t setting_tail_length;


    SettingsObject(int16_t s_interval, int16_t s_sat1, int16_t s_sat2, int16_t s_val1, int16_t s_val2, int16_t s_hue1,
                    int16_t s_hue2, int16_t s_prep_length, int16_t s_pd, int16_t s_pw, int16_t s_tl, program s_active_preprog);    //Update all the class variables with the corresponding global variables
    void setObjectSettings();
    //Update all the global variables with the ones given to the settings object
    void setGlobalSettings();
    int16_t getPreprogramLength();
    program getActivePreprogram();
    void setPreprogramLength(int length);

    uint16_t getInterval();
    uint16_t getSaturaion1();
    uint16_t getSaturaion2();
    uint16_t getHue1();
    uint16_t getHue2();
    uint16_t getValue1();
    uint16_t getValue2();
    uint16_t getPixelWidth();
    uint16_t getPixelDistance();
    uint16_t getTailLength();
    void setActiveProgram(program prog);
};

extern SettingsObject settings_program1;
extern SettingsObject settings_program2;
extern SettingsObject settings_program3;
extern SettingsObject settings_program4;
extern SettingsObject settings_program5;
extern SettingsObject settings_program6;
extern SettingsObject settings_program7;
extern SettingsObject settings_program8;
void preprogramSettings(OSCMessage &msg, int addrOffset);
void sendSinglePreprogramValuesToTouchosc(uint8_t prog_index);
void setPreprogramLed(uint8_t index, program prog);
void sendAllPreprogramValuesToTouchosc();
void toggleActivePreprogramButton(uint8_t index);
void toggleActivePreprogram(uint8_t index);
void sendSinglePreprogramLengthToTouchosc(uint8_t index, int16_t length);
extern program active_preprogram;


#endif
