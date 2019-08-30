#include "program_fireworks.h"

DEFINE_GRADIENT_PALETTE(explosion_gp){
255, 255, 255, 255, //full white
224, 255, 255, 0,  //bright yellow
128, 255, 0, 0};     //red

DEFINE_GRADIENT_PALETTE(sparks_gp){
0, 255, 0, 0,      //red
224, 255, 255, 0,    //bright yellow
255, 255, 255, 255}; //full white

CRGBPalette16 explosion_palette = explosion_gp;
CRGBPalette16 spark_palette = sparks_gp;

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

Firework *firework_array[NUM_STRIPS*STRIP_SPLIT] = {&firework0, &firework1, &firework2, &firework3, &firework4, &firework5, &firework6, &firework7, &firework8, &firework9, &firework10, &firework11, &firework12, &firework13, &firework14, &firework15};

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
    active_spark_palette = &spark_palette;
    get_random_palette = true;
    next_launch_max_wait = 30000;
    next_launch_min_wait = 10000;
    flare_hue = 10;
    flare_sat = 255;
    flare_val = 255;
    flare_tail_length = 100;
}

void Firework::prepare_for_launch()
{
    random16_add_entropy(random());
    current_stage = LAUNCH;
    flare_position = 0.0;
    int random_add = random16(next_launch_min_wait, next_launch_max_wait);
    next_launch_time = millis() + random_add;
    flare_velocity = float(random16(50,100))/100;
    launched = false;
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
        spark_velocity[x] *= gravity;
        
    }

    // Check how fast the fastest spark is. When the velocity of the fastest spark passes a threshold we move to the next stage
    float fastest_spark = 0.0;
    for (uint8_t x = 0; x < number_of_sparks; x++)
    {
        if (spark_velocity[x] > fastest_spark) {
            fastest_spark = spark_velocity[x];
        }
    }
    if (fastest_spark < 0.3) {
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
        prepare_for_launch();
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