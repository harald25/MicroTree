#include "program_preprogram.h"
#include "program_blink.h"
#include "program_scanner.h"
#include "program_theater_chase.h"

bool debug_preprogram = false;

char preprogram_led_address[40];
program active_preprogram;
int last_preprogram_change;
int preprogram_last_update = 0;
uint8_t preprogram_index = 0;
bool preprogram_just_changed;
bool preprogram_first_run;
//Parameter order:                interval, sat1, sat2, val1, val2, hue1, hue2, pixel dist, pixel width,  tail length,  preprogram length,  active progrma
SettingsObject settings_program1( 1,        255,   255,   175,  50,   1,   1,    25,        15,          10,           60,                 BLINK);
SettingsObject settings_program2( 50,       255,   255,   175,  50,   1,   1,    5,         7,           50,           60,                 SCANNER);
SettingsObject settings_program3( 25,       255,   255,   175,  50,   1,   200,  25,        5,           10,           60,                 THEATER_CHASE);
SettingsObject settings_program4( 25,       255,   255,   175,  50,   1,   1,    15,        10,          20,           60,                 VUMETER);
SettingsObject settings_program5( 25,       255,   255,   175,  50,   1,   1,    15,        5,           50,           60,                 SCANNER);
SettingsObject settings_program6( 25,       255,   255,   175,  50,   1,   200,  15,        5,           30,           60,                 THEATER_CHASE);
SettingsObject settings_program7( 25,       255,   255,   175,  50,   1,   1,    5,         5,           60,           60,                 BLINK);
SettingsObject settings_program8( 25,       255,   255,   175,  50,   1,   1,    5,         5,           50,           60,                 SCANNER);
SettingsObject * settings_array[8] = {&settings_program1,&settings_program2,&settings_program3,&settings_program4,&settings_program5,&settings_program6,&settings_program7,&settings_program8};
const uint8_t number_of_preprograms = 8; //This number must equal the length of $settings_array


void preprogram()
{
  last_preprogram_change = 0;
  preprogram_index = 0;
  preprogram_just_changed = 1;
  preprogram_first_run = 1;
  update = 1;
  active_program = PREPROGRAM;
  last_preprogram_change = millis();
  sendAllPreprogramValuesToTouchosc();
}

void preprogramUpdate()
{
  if ((millis() - last_preprogram_change) > (settings_array[preprogram_index]->getPreprogramLength()*1000))
  {
    if (1) {
      Serial.println("Time since last update is larger than preprogram_length");
      Serial.println(millis() - last_preprogram_change);
      Serial.println(settings_array[preprogram_index]->getPreprogramLength());
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
    settings_array[preprogram_index]->setGlobalSettings();
    sendSinglePreprogramValuesToTouchosc(preprogram_index);
    toggleActivePreprogramButton(preprogram_index);

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
      case VUMETER:
        vumeter();
        break;
      default:
        break;
      }
      active_program = PREPROGRAM; //Need to set this because the initializing function of the different programs sets it "wrong"
      preprogram_just_changed = 0;
      settings_array[preprogram_index]->setGlobalSettings();
  }

  //Check to see if it is time to update current preprogram
  if ((millis() - preprogram_last_update) > interval) // time to update
  {
    if(debug_preprogram) {
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
        break;
      case THEATER_CHASE:
        theaterChaseUpdate();
        break;
      case SCANNER:
        scannerUpdate();
        break;
      case VUMETER:
        vumeterUpdate();
        break;
      default:
        break;
    }
  }
}

//Constructor for the SettingsObject
SettingsObject::SettingsObject(int16_t s_interval, int16_t s_sat1, int16_t s_sat2, int16_t s_val1, int16_t s_val2, int16_t s_hue1, int16_t s_hue2,
                              int16_t s_pd, int16_t s_pw, int16_t s_tl, int16_t s_prep_length, program s_active_preprog)
{
  setting_interval = s_interval;
  setting_saturation1 = s_sat1;
  setting_value1 = s_val1;
  setting_hue1 = s_hue1;
  setting_saturation2 = s_sat2;
  setting_value2 = s_val2;
  setting_hue2 = s_hue2;
  setting_preprogram_length = s_prep_length;
  setting_active_preprogram = s_active_preprog;
  setting_pixel_distance = s_pd;
  setting_pixel_width = s_pw;
  setting_tail_length = s_tl;
}


//Update all the class variables with the corresponding global variables
void SettingsObject::setObjectSettings()
{
  setting_interval = interval;
  setting_saturation1 = saturation1;
  setting_saturation2 = saturation2;
  setting_value1 = value1;
  setting_value2 = value2;
  setting_hue1 = hue1;
  setting_hue2 = hue2;
  setting_active_preprogram = active_preprogram;
  setting_pixel_distance = pixel_distance;
  setting_pixel_width = pixel_width;
  setting_tail_length = tail_length;
}

//Update all the global variables with the ones from the SettingsObject
void SettingsObject::setGlobalSettings()
{
  if(setting_interval > -1) {
    interval = (int)setting_interval;
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
  if(setting_pixel_distance > -1) {
    pixel_distance = setting_pixel_distance;
  }
  if(setting_pixel_width > -1) {
    pixel_width = setting_pixel_width;
  }
  if(setting_tail_length > -1) {
    tail_length = setting_tail_length;
  }
  if(setting_preprogram_length == -1) {
    setting_preprogram_length = 10;
  }
  active_preprogram = settings_array[preprogram_index]->getActivePreprogram();
  if(debug_preprogram) {
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

void SettingsObject::setPreprogramLength(int length) {
  setting_preprogram_length = length;
}

uint16_t SettingsObject::getInterval() {
  return setting_interval;
}
uint16_t SettingsObject::getSaturaion1() {
  return setting_saturation1;
}
uint16_t SettingsObject::getSaturaion2() {
  return setting_saturation2;
}
uint16_t SettingsObject::getHue1() {
  return setting_hue1;
}
uint16_t SettingsObject::getHue2() {
  return setting_hue2;
}
uint16_t SettingsObject::getValue1() {
  return setting_value1;
}
uint16_t SettingsObject::getValue2() {
  return setting_value2;
}
uint16_t SettingsObject::getPixelWidth() {
  return setting_pixel_width;
}
uint16_t SettingsObject::getPixelDistance() {
  return setting_pixel_distance;
}
uint16_t SettingsObject::getTailLength() {
  return setting_tail_length;
}

void SettingsObject::setActiveProgram(program prog)
{
  setting_active_preprogram = prog;
}

void sendSinglePreprogramValuesToTouchosc(uint8_t prog_index)
{
  OSCMsgSend("/variable/interval", (float)settings_array[prog_index]->getInterval());
  OSCMsgSend("/variable/value1", (float)settings_array[prog_index]->getValue1());
  OSCMsgSend("/variable/value2", (float)settings_array[prog_index]->getValue2());
  OSCMsgSend("/variable/pixel_width", (float)settings_array[prog_index]->getPixelWidth());
  OSCMsgSend("/variable/pixel_distance", (float)settings_array[prog_index]->getPixelDistance());
  OSCMsgSend("/variable/tail_length", (float)settings_array[prog_index]->getTailLength());
  setPreprogramLed(preprogram_index,settings_array[prog_index]->getActivePreprogram());

  char index_as_char[3];
  char address[27] = "/preprogram/length/value/";
  itoa (prog_index,index_as_char,10);
  strcat(address,index_as_char);
  sendSinglePreprogramLengthToTouchosc(prog_index, settings_array[prog_index]->getPreprogramLength());
}

void sendAllPreprogramValuesToTouchosc()
{
  for (uint8_t x = 0; x < 8; x++) {
    setPreprogramLed(x,settings_array[x]->getActivePreprogram());
    sendSinglePreprogramLengthToTouchosc(x,settings_array[x]->getPreprogramLength());
  }
}

void setPreprogramLedAddress(uint8_t index, program prog)
{
  char index_as_char[3];
  const char base_address[28] = "/preprogram/active_program/";
  for (int x = 0; x < 28; x++) {
    preprogram_led_address[x] = base_address[x];
  }
  itoa (index,index_as_char,10);
  strcat(preprogram_led_address,index_as_char);

  if(prog == THEATER_CHASE) {
    strcat(preprogram_led_address,"/theater");
  }
  if(prog == BLINK) {
    strcat(preprogram_led_address,"/blink");
  }
  if(prog == SCANNER) {
    strcat(preprogram_led_address,"/scanner");
  }
  if(prog == VUMETER) {
    strcat(preprogram_led_address,"/vumeter");
  }
}
void setPreprogramLed(uint8_t index, program prog)
{
  if (prog == THEATER_CHASE) {
    setPreprogramLedAddress(index,THEATER_CHASE);
    OSCMsgSend(preprogram_led_address,1);
    setPreprogramLedAddress(index,BLINK);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,SCANNER);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,VUMETER);
    OSCMsgSend(preprogram_led_address,0);
  }
  if (prog == BLINK) {
    setPreprogramLedAddress(index,THEATER_CHASE);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,BLINK);
    OSCMsgSend(preprogram_led_address,1);
    setPreprogramLedAddress(index,SCANNER);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,VUMETER);
    OSCMsgSend(preprogram_led_address,0);
  }
  if (prog == SCANNER) {
    setPreprogramLedAddress(index,THEATER_CHASE);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,BLINK);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,SCANNER);
    OSCMsgSend(preprogram_led_address,1);
    setPreprogramLedAddress(index,VUMETER);
    OSCMsgSend(preprogram_led_address,0);
  }
  if (prog == VUMETER) {
    setPreprogramLedAddress(index,THEATER_CHASE);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,BLINK);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,SCANNER);
    OSCMsgSend(preprogram_led_address,0);
    setPreprogramLedAddress(index,VUMETER);
    OSCMsgSend(preprogram_led_address,1);
  }
}

void sendSinglePreprogramLengthToTouchosc(uint8_t index, int16_t length)
{
  char address[27] = "/preprogram/length/value/";
  char int_as_char[2];
  itoa(index,int_as_char,10);
  strcat(address,int_as_char);
  OSCMsgSend(address,length);
}
void preprogramSettings(OSCMessage &msg, int addrOffset)
{
  if (msg.fullMatch("/preprogram/page"))
  {
    sendAllPreprogramValuesToTouchosc();
  }
  if (msg.fullMatch("/preprogram/save_settings"))
  {
    settings_array[preprogram_index]->setObjectSettings();
  }

  if(msg.match("/preprogram/length"))
  {
    int16_t length = msg.getFloat(0);
    char int_as_char[2];
    msg.getAddress(int_as_char,19); //The index part of the address will be the 19th character in the string
    uint8_t i = (uint8_t)int_as_char[0] - 48; //Convert from ASCII (in ascii '0' = 48, '1' = 49,... etc)
    settings_array[i]->setPreprogramLength(length);
    sendSinglePreprogramLengthToTouchosc(i, length);
  }

  if (msg.match("/preprogram/toggle"))
  {
    char buffer[2];
    msg.getAddress(buffer,19); //The index part of the address will be the 19th character in the string
    uint8_t i = (uint8_t)buffer[0] - 48; //Convert from ASCII (in ascii '0' = 48, '1' = 49,... etc)

    if(debug_preprogram) {
      Serial.print("Toggeling preprogram number: ");
      Serial.println(i);
    }
    toggleActivePreprogram(i);
  }
  if (msg.match("/preprogram/activeprogram"))
  {
    uint8_t activeprogram = (uint8_t)msg.getFloat(0);
    switch (activeprogram)
    {
      case 0:
        settings_array[preprogram_index]->setActiveProgram(THEATER_CHASE);
        theaterChase();
        active_program = PREPROGRAM;
        active_preprogram = settings_array[preprogram_index]->getActivePreprogram();
        break;
      case 1:
        settings_array[preprogram_index]->setActiveProgram(VUMETER);
        vumeter();
        active_program = PREPROGRAM;
        active_preprogram = settings_array[preprogram_index]->getActivePreprogram();
        break;
      case 2:
        settings_array[preprogram_index]->setActiveProgram(BLINK);
        blink();
        active_program = PREPROGRAM;
        active_preprogram = settings_array[preprogram_index]->getActivePreprogram();
        break;
      case 3:
        settings_array[preprogram_index]->setActiveProgram(SCANNER);
        scanner();
        active_program = PREPROGRAM;
        active_preprogram = settings_array[preprogram_index]->getActivePreprogram();
        break;
      default:
        break;
    }
    sendSinglePreprogramValuesToTouchosc(preprogram_index);

  }
}

void toggleActivePreprogram(uint8_t index)
{
  preprogram_index = index;
  preprogram_just_changed = 1;
  last_preprogram_change = millis();
  toggleActivePreprogramButton(index);
}

void toggleActivePreprogramButton(uint8_t index)
{
  const char base_address[20] = "/preprogram/toggle/";
  for (uint8_t x = 0; x < 8; x++)
  {
    char full_address[21];
    for (uint8_t q = 0; q < 20; q++) {
      full_address[q] = base_address[q];
    }
    char index_as_char[3] = "";
    itoa(x,index_as_char,10);
    strcat(full_address,index_as_char);

    if(debug_preprogram) {
      Serial.println("OSC address");
      for(int y = 0; y < 20; y++) {
        Serial.print(full_address[y]);
      }
      Serial.println(" ");
      Serial.print("X is: ");
      Serial.println(x);
      Serial.println("--------------------- ");
    }

    if (x == index) {
      OSCMsgSend(full_address,1);
    }
    else {
      OSCMsgSend(full_address,0);
    }
  }
}
