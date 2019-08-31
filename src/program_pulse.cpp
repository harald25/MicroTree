#include "program_pulse.h"

int index_pulse_strip_i[NUM_STRIPS * STRIP_SPLIT];
uint32_t next_pulse_strip_i[NUM_STRIPS * STRIP_SPLIT];
uint8_t pulse_hue_strip_i[NUM_STRIPS * STRIP_SPLIT];
uint8_t pulse_sat_strip_i[NUM_STRIPS * STRIP_SPLIT];
uint16_t pulse_minimum_random_time;
bool pulse_random_color;
uint8_t pulse_lookuptable[] = {
    10,
    25,
    35,
    35,
    35,
    35,
    35,
    35,
    35,
    36,
    36,
    36,
    36,
    37,
    37,
    38,
    38,
    39,
    39,
    40,
    40,
    41,
    42,
    43,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    52,
    53,
    54,
    56,
    57,
    59,
    60,
    62,
    64,
    65,
    67,
    69,
    71,
    73,
    75,
    78,
    80,
    82,
    85,
    87,
    90,
    93,
    96,
    99,
    102,
    105,
    108,
    111,
    114,
    118,
    121,
    125,
    128,
    132,
    136,
    140,
    144,
    147,
    151,
    155,
    159,
    164,
    168,
    172,
    176,
    180,
    184,
    188,
    192,
    196,
    200,
    204,
    208,
    211,
    215,
    219,
    222,
    225,
    229,
    232,
    235,
    237,
    240,
    242,
    244,
    246,
    248,
    250,
    251,
    252,
    255,
    255,
    255,
    255,
    255,
    254,
    254,
    254,
    253,
    253,
    253,
    252,
    251,
    251,
    250,
    249,
    249,
    248,
    247,
    246,
    245,
    244,
    243,
    242,
    241,
    240,
    238,
    237,
    236,
    235,
    233,
    232,
    230,
    229,
    227,
    226,
    224,
    222,
    221,
    219,
    217,
    215,
    213,
    212,
    210,
    208,
    206,
    204,
    202,
    200,
    197,
    195,
    193,
    191,
    189,
    187,
    184,
    182,
    180,
    177,
    175,
    173,
    170,
    168,
    166,
    163,
    161,
    158,
    156,
    153,
    151,
    148,
    146,
    143,
    141,
    138,
    136,
    133,
    131,
    128,
    126,
    123,
    121,
    118,
    116,
    113,
    111,
    108,
    106,
    103,
    101,
    98,
    96,
    93,
    91,
    89,
    86,
    84,
    81,
    79,
    77,
    74,
    72,
    70,
    68,
    65,
    63,
    61,
    59,
    57,
    55,
    53,
    51,
    49,
    47,
    45,
    43,
    41,
    39,
    37,
    36,
    34,
    32,
    30,
    29,
    27,
    26,
    24,
    23,
    21,
    20,
    19,
    17,
    16,
    15,
    14,
    13,
    12,
    11,
    10,
    9,
    8,
    7,
    6,
    5,
    5,
    4,
    3,
    3,
    2,
    2,
    1,
    0
};

void pulse()
{
    active_program = PULSE;
    interval = 2;
    hue1 = 200;
    saturation1 = 200;
    value1 = 0;
    update = true;
    pulse_minimum_random_time = 1000;
    increment_by1 = 1;
    total_steps1 = 255;
    pulse_random_color = true;

    for (uint8_t i = 0; i < NUM_STRIPS * STRIP_SPLIT; i++) {
        preparePulse(i); 
    }
}

void pulseUpdate()
{
    // Looping through all the elements of next_pulse_strip_i[] array
    // It has as many elements as there are "virtual strips". Number of virtual strips = NUM_STRIPS * STRIP_SPLIT
    for (uint8_t i = 0; i < NUM_STRIPS * STRIP_SPLIT; i++)
    {
        // Checks if time now is equal to, or larger than the time for the next pulse for strip number i
        if (millis() >= next_pulse_strip_i[i])
        {
            // Loops through all elements (LEDs) in the current virtual strip
            for (uint8_t x = 0; x < NUM_LEDS_PER_STRIP / STRIP_SPLIT; x++)
            {
                if (pulse_random_color) {
                    leds[led_order_array[(i * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + x]] = CHSV(pulse_hue_strip_i[i], pulse_sat_strip_i[i], pulse_lookuptable[index_pulse_strip_i[i]]);
                }
                else {
                    leds[led_order_array[(i * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + x]] = CHSV(hue1,saturation1,pulse_lookuptable[index_pulse_strip_i[i]]);
                }
            }
            index_pulse_strip_i[i] ++;
            // Check if we reached the end of total_steps1. If we did a new time for the next pulse should be generated
            if (index_pulse_strip_i[i] >= total_steps1)
            {
                preparePulse(i);
            }
        }
    }
    FastLED.show();
}

void preparePulse(uint8_t strip_n)
{
    random16_add_entropy(analogRead(A13));
    next_pulse_strip_i[strip_n] = millis() + random16(10000) + pulse_minimum_random_time;
    index_pulse_strip_i[strip_n] = 0;
    pulse_hue_strip_i[strip_n] = random8();
    pulse_sat_strip_i[strip_n] = random8();
}

void pulseSettings(OSCMessage &msg, int addrOffset)
{
    if (msg.fullMatch("/pulse/page"))
    {
        sendPulseValuesToTouchosc();
    }
    else if (msg.fullMatch("/pulse/randomcolor"))
    {
        float value = msg.getFloat(0);
        pulse_random_color = (bool)value;
        OSCMsgSend("/pulse/randomcolor", (float)pulse_random_color);
        Serial.print("Random colors: ");
        Serial.println(value);
    }
    else if (msg.fullMatch("/pulse/minimumrandomtime"))
    {
        float value = msg.getFloat(0);
        pulse_minimum_random_time = (uint16_t)value;
    }
    else {
        Serial.println("Invalid OSC address");
    }
}

void sendPulseValuesToTouchosc()
{
    OSCMsgSend("/variable/interval", (float)interval);
    OSCMsgSend("/pulse/randomcolor", (float)pulse_random_color);
    OSCMsgSend("/pulse/minimumrandomtime", (float)pulse_minimum_random_time);
}