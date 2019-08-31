#include "program_fireworks.h"

// Gradient palette "Blues_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/Blues_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(Blues_09_gp){
    0, 234, 246, 255,
    28, 234, 246, 255,
    28, 177, 213, 235,
    56, 177, 213, 235,
    56, 132, 182, 216,
    84, 132, 182, 216,
    84, 73, 152, 186,
    113, 73, 152, 186,
    113, 26, 109, 164,
    141, 26, 109, 164,
    141, 7, 74, 135,
    170, 7, 74, 135,
    170, 1, 42, 108,
    198, 1, 42, 108,
    198, 1, 20, 74,
    226, 1, 20, 74,
    226, 1, 6, 29,
    255, 1, 6, 29};

// Gradient palette "BuGn_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/BuGn_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(BuGn_09_gp){
    0, 234, 248, 250,
    28, 234, 248, 250,
    28, 192, 233, 240,
    56, 192, 233, 240,
    56, 142, 215, 197,
    84, 142, 215, 197,
    84, 67, 176, 140,
    113, 67, 176, 140,
    113, 23, 139, 84,
    141, 23, 139, 84,
    141, 7, 109, 37,
    170, 7, 109, 37,
    170, 1, 67, 9,
    198, 1, 67, 9,
    198, 0, 39, 3,
    226, 0, 39, 3,
    226, 0, 13, 1,
    255, 0, 13, 1};

// Gradient palette "GnBu_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/GnBu_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(GnBu_09_gp){
    0, 234, 248, 219,
    28, 234, 248, 219,
    28, 182, 229, 174,
    56, 182, 229, 174,
    56, 142, 213, 133,
    84, 142, 213, 133,
    84, 86, 186, 108,
    113, 86, 186, 108,
    113, 38, 156, 132,
    141, 38, 156, 132,
    141, 11, 117, 158,
    170, 11, 117, 158,
    170, 2, 68, 122,
    198, 2, 68, 122,
    198, 1, 35, 95,
    226, 1, 35, 95,
    226, 1, 12, 46,
    255, 1, 12, 46};

// Gradient palette "Oranges_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/Oranges_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(Oranges_09_gp){
    0, 255, 233, 207,
    28, 255, 233, 207,
    28, 252, 203, 149,
    56, 252, 203, 149,
    56, 249, 162, 82,
    84, 249, 162, 82,
    84, 249, 109, 29,
    113, 249, 109, 29,
    113, 249, 69, 6,
    141, 249, 69, 6,
    141, 220, 36, 1,
    170, 220, 36, 1,
    170, 167, 15, 1,
    198, 167, 15, 1,
    198, 83, 8, 1,
    226, 83, 8, 1,
    226, 41, 4, 1,
    255, 41, 4, 1};

// Gradient palette "PuBu_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/PuBu_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(PuBu_09_gp){
    0, 255, 237, 245,
    28, 255, 237, 245,
    28, 208, 205, 223,
    56, 208, 205, 223,
    56, 150, 164, 197,
    84, 150, 164, 197,
    84, 83, 131, 174,
    113, 83, 131, 174,
    113, 32, 103, 151,
    141, 32, 103, 151,
    141, 4, 72, 125,
    170, 4, 72, 125,
    170, 1, 41, 100,
    198, 1, 41, 100,
    198, 1, 25, 57,
    226, 1, 25, 57,
    226, 1, 9, 17,
    255, 1, 9, 17};

// Gradient palette "PuRd_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/PuRd_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(PuRd_09_gp){
    0, 234, 231, 240,
    28, 234, 231, 240,
    28, 197, 193, 216,
    56, 197, 193, 216,
    56, 157, 125, 172,
    84, 157, 125, 172,
    84, 137, 77, 137,
    113, 137, 77, 137,
    113, 179, 33, 100,
    141, 179, 33, 100,
    141, 197, 4, 54,
    170, 197, 4, 54,
    170, 146, 1, 16,
    198, 146, 1, 16,
    198, 66, 0, 9,
    226, 66, 0, 9,
    226, 24, 0, 1,
    255, 24, 0, 1};

// Gradient palette "Emo_Barbie_Playmate_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/colo/rphnick/tn/Emo_Barbie_Playmate.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(Emo_Barbie_Playmate_gp){
    0, 64, 1, 1,
    51, 64, 1, 1,
    51, 152, 6, 4,
    102, 152, 6, 4,
    102, 206, 36, 29,
    153, 206, 36, 29,
    153, 247, 100, 77,
    204, 247, 100, 77,
    204, 234, 176, 123,
    255, 234, 176, 123};

// Gradient palette "YlOrRd_09_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/cb/seq/tn/YlOrRd_09.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 72 bytes of program space.

DEFINE_GRADIENT_PALETTE(YlOrRd_09_gp){
    0, 255, 255, 145,
    28, 255, 255, 145,
    28, 255, 217, 79,
    56, 255, 217, 79,
    56, 252, 178, 37,
    84, 252, 178, 37,
    84, 252, 115, 12,
    113, 252, 115, 12,
    113, 249, 69, 6,
    141, 249, 69, 6,
    141, 247, 18, 2,
    170, 247, 18, 2,
    170, 188, 1, 1,
    198, 188, 1, 1,
    198, 117, 0, 2,
    226, 117, 0, 2,
    226, 42, 0, 2,
    255, 42, 0, 2};

CRGBPalette16 spark_palette0 = Blues_09_gp;
CRGBPalette16 spark_palette1 = BuGn_09_gp;
CRGBPalette16 spark_palette2 = GnBu_09_gp;
CRGBPalette16 spark_palette3 = Oranges_09_gp;
CRGBPalette16 spark_palette4 = PuBu_09_gp;
CRGBPalette16 spark_palette5 = PuRd_09_gp;
CRGBPalette16 spark_palette6 = Emo_Barbie_Playmate_gp;
CRGBPalette16 spark_palette7 = YlOrRd_09_gp;

#define NUM_SPARK_PALETTES 8
CRGBPalette16 *spark_palette_array[NUM_SPARK_PALETTES] = {
    &spark_palette0,
    &spark_palette1,
    &spark_palette2,
    &spark_palette3,
    &spark_palette4,
    &spark_palette5,
    &spark_palette6,
    &spark_palette7};

Firework firework0(0);
Firework firework1(1);
Firework firework2(2);
Firework firework3(3);
Firework firework4(4);
Firework firework5(5);
Firework firework6(6);
Firework firework7(7);
Firework firework8(8);
Firework firework9(9);
Firework firework10(10);
Firework firework11(11);
Firework firework12(12);
Firework firework13(13);
Firework firework14(14);
Firework firework15(15);

Firework *firework_array[NUM_STRIPS*STRIP_SPLIT] = {
    &firework0,
    &firework1,
    &firework2,
    &firework3,
    &firework4,
    &firework5,
    &firework6,
    &firework7,
    &firework8,
    &firework9,
    &firework10,
    &firework11,
    &firework12,
    &firework13,
    &firework14,
    &firework15
};

void fireworks()
{
    interval = 30;
    active_program = FIREWORKS;
    FastLED.clear();
    FastLED.show();
    for (uint8_t i = 0; i < NUM_STRIPS * STRIP_SPLIT; i++)
    {
        firework_array[i]->prepare_for_launch();
    }
    update = true;
}

void fireworksUpdate()
{
    for (uint8_t i = 0; i < NUM_STRIPS*STRIP_SPLIT; i++)
    {
        firework_array[i]->update_firework();
    }
    FastLED.show();
}

// Constructor
Firework::Firework(uint8_t strip_n)
{
    strip_number = strip_n;
    current_stage = WAITING;
    gravity = 0.99;
    //spark_deceleration = 0.97;
    get_random_palette = true;
    next_launch_max_wait = 10000;
    next_launch_min_wait = 5000;
    flare_hue = 10;
    flare_sat = 255;
    flare_val = 255;
    flare_tail_length = 100;
}

void Firework::prepare_for_launch()
{
    random16_add_entropy(analogRead(A13));
    active_spark_palette = spark_palette_array[random8(0, NUM_SPARK_PALETTES + 1)];
    current_stage = LAUNCH;
    flare_position = 0.0;
    uint16_t random_add = random16(next_launch_min_wait, next_launch_max_wait);
    next_launch_time = millis() + random_add;
    flare_velocity = float(random16(50,100))/100;
    launched = false;   // Launch is prepared, but we have not launched yet
    // Reset all LEDs of the strip
    for (uint16_t i = 0; i < NUM_LEDS_PER_STRIP/STRIP_SPLIT; i++)
    {
        leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + i]] = CRGB::Black;
    }
}

void Firework::launch()
{
    // If the flare has slowed down to this value, we will go to the next stage: EXPLOSION!
    if (launched & (flare_velocity < 0.1))
    {
        // Prepare spark variables for explosion
        current_stage = EXPLOSION;
        number_of_sparks = random8(MIN_NUMBER_OF_SPARKS, MAX_NUMBER_OF_SPARKS);
        for (uint8_t x = 0; x < number_of_sparks; x++)
        {
            spark_gradient_index[x] = random8();
            spark_position[x] = flare_position;
            spark_position[x] = flare_position;
            spark_velocity[x] = float(random16(10, 125)) / 100;
            spark_velocity_direction[x] = random8(0,2);
        }
    }
    else
    {   
        if (!launched)
        {
            leds[led_order_array[(strip_number*(NUM_LEDS_PER_STRIP/STRIP_SPLIT))+(int)flare_position]] = CHSV(flare_hue,flare_sat,flare_val);
            launched = true;
        }
        else
        {
            // Fading the tail/trail of the flare. Only applying fadeToBlackBy() to the pixels with an index lower than (int)flare_position.
            // NB: Casting flare_position (which is a float) to int, will floor the value
            for (uint16_t i = 0; i < (int)flare_position; i++)
            {
                leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + i]].fadeToBlackBy(flare_tail_length);
            }
            // The idea is to get the fraction from flare position (pixel_spill), and use this fraction to start lighting up the next LED
            // The result should then be that the pixel glides along the strip instead of jumping from pixel to pixel
            float pixel_spill = ((int)flare_position + 1) - flare_position;
            leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + (int)flare_position]+1] = CHSV(flare_hue, flare_sat, (flare_val * (1 - pixel_spill)));
        }
        flare_position += flare_velocity;       // New position = current + velocity
        flare_velocity *= gravity; // New velocity = current * gravity (gravity is between 0 and 1, so velocity will decrease)
    }
}

void Firework::explosion()
{
    for (uint16_t x = 0; x < NUM_LEDS_PER_STRIP / STRIP_SPLIT; x++)
    {
        leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + x]].fadeToBlackBy(128);
    }

    for (uint8_t x = 0; x < number_of_sparks; x++)
    {
        // Set pixel values
        uint16_t pixel = led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + (int)spark_position[x]];
        CRGB pixel_color = ColorFromPalette(*active_spark_palette, spark_gradient_index[x]);
        leds[pixel] += pixel_color;

        // Update spark parameters
        if (spark_velocity_direction[x]) {
            spark_position[x] += spark_velocity[x];
        }
        else {
            spark_position[x] -= spark_velocity[x];
        }
        // Constrain position to be within the current LED strip
        spark_position[x] = constrain(spark_position[x],0.0,(float)(NUM_LEDS_PER_STRIP/STRIP_SPLIT));
        spark_velocity[x] *= 0.98;
        //spark_velocity[x] *= spark_deceleration;
        }

    // Check how fast the fastest spark is. When the velocity of the fastest spark passes a threshold we move to the next stage
    float fastest_spark = 0.0;
    for (uint8_t x = 0; x < number_of_sparks; x++)
    {
        if (spark_velocity[x] > fastest_spark) {
            fastest_spark = spark_velocity[x];
        }
    }
    if (fastest_spark < 0.05) {
        current_stage = FADING;
        spark_fade_end = millis() + SPARK_FADE_TIME;
    }
}

void Firework::fading()
{
    for (uint16_t x = 0; x < NUM_LEDS_PER_STRIP / STRIP_SPLIT; x++)
    {
        leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + x]].fadeToBlackBy(8);
    }

    if (millis() > spark_fade_end) {
        current_stage = WAITING;
    }
}

void Firework::set_palette(CRGBPalette16 *palette)
{
    // Code here
}

void Firework::update_firework()
{
    if (current_stage == WAITING) {
        if (millis() >= next_launch_time) {
            prepare_for_launch();
        }
    }
    else if (current_stage == LAUNCH) {
        launch();
    }
    else if (current_stage == EXPLOSION) {
        explosion();
    }
    else if (current_stage == FADING) {
        fading();
    }
    else {
        Serial.println("You should not have ended up here!!");
    }
}