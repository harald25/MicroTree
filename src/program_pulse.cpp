#include "program_pulse.h"

enum pulse_stage {INCREASE, DECREASE};

float acceleration = 1.5;
float deceleration = 0.5;
pulse_stage stage;
int next_pulse;
bool pulse_active;

void pulse()
{
    active_program = PULSE;
    stage = INCREASE;
    interval = 100;
    hue1 = 200;
    saturation1 = 200;
    value1 = 0;
    update = true;
    next_pulse = millis();
    pulse_active = false;
    
}

void pulseUpdate()
{
    if ((millis() > next_pulse) && (!pulse_active)) {
        pulse_active = true;
        Serial.println("Activating pulse");
    }
    
    if (pulse_active) 
    {
        uint8_t value1_old = value1;
        if (stage == INCREASE)
        {
          
            if (value1 == 0) {
                value1 = 1;
                Serial.println(value1);
            }
            else if (value1 > 0) {
                Serial.println("Kommer vi hit?");
                value1 = (value1 * acceleration) + 1;
                if (value1 < value1_old) {      //If value1 is bigger that value1_old, it is because value1 overflowed (passed over 255).
                    value1 = 255;
                    stage = DECREASE;
                }
            }
        }
        else if (stage == DECREASE)
        {
            Serial.println("Stage = DECREASE");
           value1 = value1 * deceleration;
           if (value1 > value1_old) {       //If value1 is bigger that value1_old, it is because value1 underflowed (passed under 0)
                value1 = 0;
                stage = INCREASE;
                pulse_active = false;
                next_pulse = millis() + 5000;
           }
        }
        else {
            Serial.println("You should never have ended up here!");
        }
        for(int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
        {
            leds[i] = CHSV(hue1, saturation1, value1);
        }
        FastLED.show();
    }
}