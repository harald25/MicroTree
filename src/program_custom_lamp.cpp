#include "program_custom_lamp.h"


uint16_t lamps [][3] =
{
  {0,1177,1199},
  {1,1155,1176},
  {1,1133,1154},
  {0,1111,1132},
  {0,1094,1110},   //Side1
  {0,1073,1093},
  {1,1051,1072},
  {1,1029,1050},
  {0,1007,1028},
  {0,990,1006},   //Side2
  {0,969,989},
  {1,947,968},
  {1,923,946},
  {0,900,922},
  {0,883,899},    //Side3
  {0,861,882},
  {1,839,860},
  {1,817,838},
  {0,794,816},
  {0,776,793},    //Side4
  {0,753,775},
  {1,733,752},
  {1,712,732},
  {0,691,711},
  {0,673,690},    //Side5
  {0,651,672},
  {1,629,650},
  {1,607,628},
  {0,585,606},
  {0,567,584},    //Side6
  {0,544,566},
  {1,521,543},
  {1,499,520},
  {0,476,498},
  {0,458,475},    //Side7
  {0,436,457},
  {1,414,435},
  {1,391,413},
  {0,368,390},
  {0,349,367},    //Side8
  {0,327,348},
  {1,305,326},
  {1,283,304},
  {0,260,282},
  {0,243,259},    //Side9
  {0,220,242},
  {1,198,219},
  {1,175,197},
  {0,152,174},
};

void customLamp()
{
  allLedsOff();   //Turn all LEDS off first
  //This loop sets the lamps back to their "start state" as defined in the original 'lamps'-array
  //It is necessary in order for the lamp states to reset when the program is reactivated from touchOSC
  //The state defined when the array is initialized doesn't actually matter since this overwrites everything
  for (int x = 0; x < 49; x++)
  {
    lamps[x][0] = 0;
    if(((x % 5) == 1) || ((x % 5) == 2)) {
      lamps[x][0] = 1;
    }
  }

  updateCustomLampState();

  hue1 = 25;
  saturation1 = 255;
  value1 = 255;
  active_program = CUSTOM_LAMP;
  update = true;
}

//Updates touchOSC with the current on/off state of all lamps
void updateCustomLampState()
{
  //This loop sends the state of all lamps to touchOSC via OSC-messages. This updates the push buttons in the app
  for (int x = 0; x < 49; x++)
  {
    float osc_message_value = 0.0;
    if (lamps[x][0] == 1) {
      osc_message_value = 50.0;     //Because of how touch OSC works, value needs to be at least = number of lamps +1
                                    //This is because the buttons have value range from and to equal to their lamp number which the program uses to recognize which lamp should be activated.
                                    //This value range is also used to determine what value you need to return to the app in order to activate a buttons.
    }
    setLampAddress(x+1);
    OSCMsgSend(osc_message_value);
    FastLED.delay(1); //Might not be necessary, but I thought a delay might be smart so the ESP is not hammered with too many messages at a time
  }
}

void customLampUpdate()
{
  for (int i = 0; i < 49; i++)
  {
    if (lamps[i][0])
    {
      for (int j = lamps[i][1]; j < (lamps[i][2]+1); j++)
      {
        leds[led_array[j]] = CHSV(hue1,saturation1,value1);
      }
    }
    else
    {
      for (int j = lamps[i][1]; j < (lamps[i][2]+1); j++)
      {
        leds[led_array[j]] = CRGB::Black;
      }
    }
  }
  update = false; //No need to keep updating a static program
  FastLED.show();
}

void activateDeactivateLamp(int lamp_number)
{
  if (lamp_number > 0)
  {
    lamp_number = lamp_number - 1;                    //Touch OSC is configured to start at 1 instead of 0 like the array of lamps does
    lamps[lamp_number][0] = 1-lamps[lamp_number][0];  //Flips from 1 to 0, or 0 to 1
    Serial.printf("Lamp number %d turned to %d \n", lamp_number, lamps[lamp_number][0]);
    update = true;  //Something has changed so we should update

    //Send a message to TouchOSC so the correct button activates
    float osc_message_value = 0.0;
    if (lamps[lamp_number][0]) {
      osc_message_value = 50.0;
    }
    setLampAddress(lamp_number+1);
    OSCMsgSend(osc_message_value);
  }
}

void setLampAddress(int lamp)
{
  char address[18] = "/Variable/lamp/";
  for (int x = 0; x < 18; x++) {
    osc_message_address[x] = address[x];
  }
  char lamp_number[3];
  itoa(lamp,lamp_number,10);
  strcat(osc_message_address,lamp_number);
}

void setCustomlampPreset(uint8_t preset_number)
{
  //Skinkelys
  if (preset_number == 1)
  {
    Serial.println("CustomlampPreset 1");
    allLampsOff();
    activateDeactivateLamp(21);
    activateDeactivateLamp(22);
    activateDeactivateLamp(23);
    activateDeactivateLamp(24);

    setValue1(100);
    setHue1(30);
    setSaturation1(200);
    updateCustomLampState();
  }
  //Gaming
  if (preset_number == 2)
  {
    Serial.println("CustomlampPreset 2");
    allLampsOff();
    activateDeactivateLamp(2);
    activateDeactivateLamp(3);
    activateDeactivateLamp(4);
    activateDeactivateLamp(5);
    activateDeactivateLamp(6);
    updateCustomLampState();

    //Orange
    setColorPreset(2);
  }
  //Arbeidslys
  if (preset_number == 3)
  {
    Serial.println("CustomlampPreset 3");
    allLampsOn();
    setValue1(255);
    setHue1(255);
    setSaturation1(0);
    updateCustomLampState();
  }
  //Bordlys (lys over kontorpulter, sofa, og bord)
  if (preset_number == 4)
  {
    Serial.println("CustomlampPreset 4");
    allLampsOff();
    //Over Harald PC
    activateDeactivateLamp(2);
    activateDeactivateLamp(3);
    activateDeactivateLamp(4);
    //Over Jon PC
    activateDeactivateLamp(12);
    activateDeactivateLamp(11);
    //Over sofa
    activateDeactivateLamp(21);
    activateDeactivateLamp(22);
    activateDeactivateLamp(23);
    activateDeactivateLamp(24);
    activateDeactivateLamp(30);
    activateDeactivateLamp(40);
    //Over stuebord
    activateDeactivateLamp(33);
    activateDeactivateLamp(32);
    activateDeactivateLamp(27);
    activateDeactivateLamp(28);
    updateCustomLampState();

    //Warm White
    setColorPreset(1);
  }
}

void allLampsOn()
{
  for(int x = 0; x < 49; x++)
  {
    lamps[x][0] = 1;
  }
  setValue1(255);
}
void allLampsOff()
{
  for(int x = 0; x < 49; x++)
  {
    lamps[x][0] = 0;
  }

}
