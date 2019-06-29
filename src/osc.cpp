#include "osc.h"

SLIPEncodedSerial SLIPSerial(Serial1);

//Takes a value, but uses osc_message_address, defined in main, as the address
//osc_message_address needs to be set to the correct address before calling OSCMsgSend
void OSCMsgSend(float value)
{
  Serial.println(osc_message_address);
  OSCMessage msgOUT(osc_message_address);
  msgOUT.add(value);
  //Check that it is a valid OSC message
  if(!msgOUT.hasError())
  {
    SLIPSerial.beginPacket();
    msgOUT.send(SLIPSerial);
    SLIPSerial.endPacket();
    if (debug) {
      Serial.println("Message sent to ESP!");
    }
  }
  if (debug) {
    Serial.println("Error in OSC message!");
  }
  msgOUT.empty();
}

//Takes both address, and value as arguments
void OSCMsgSend(char * address, float value)
{
  Serial.println(address);
  OSCMessage msgOUT(address);
  msgOUT.add(value);
  //Check that it is a valid OSC message
  if(!msgOUT.hasError())
  {
    SLIPSerial.beginPacket();
    msgOUT.send(SLIPSerial);
    SLIPSerial.endPacket();
    if (debug) {
      Serial.println("Message sent to ESP!");
    }
  }
  else {
    if (debug) {
      Serial.println("Error in OSC message!");
    }
  }
  msgOUT.empty();
}

void OSCMsgReceive()
{

  OSCMessage msgIN;
  int size;

  static unsigned long microsTime = 0;
  while (!SLIPSerial.endofPacket())
  {
    if ((size = SLIPSerial.available()) > 0)
    {
      microsTime = micros();
      while (size--)  //this needs a byte limit
      {
        msgIN.fill(SLIPSerial.read());
      }
    }
    if ((micros() - microsTime) > 10000) break; //Timeout for no eoP()
  }


  if(!msgIN.hasError())
  {
    if (debug) {
      Serial.println("Routing OSC message");
    }
    msgIN.route("/Program",changeLEDProgram);
    msgIN.route("/Variable",changeValue);
    msgIN.route("/Colorpreset",changeColorPreset);
    msgIN.route("/react", changeAudioReactSettings);
  }

}
