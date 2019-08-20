#include "program_fireworks.h"

DEFINE_GRADIENT_PALETTE(explosion_gp){
255, 255, 255, 255, //full white
224, 255, 255, 0,  //bright yellow
128, 255, 0, 0};     //red

DEFINE_GRADIENT_PALETTE(sparks_gp){
255, 255, 255, 255, //full white
224, 255, 255, 0,   //bright yellow
128, 255, 0, 0};    //red

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
    interval = 1;
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
    Serial.println("Hit da?");
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
    gravity = 0.95;
    active_spark_palette = &spark_palette;
    get_random_palette = true;
    next_launch_max_wait = 30000;
    next_launch_min_wait = 1000;
    flare_hue = 10;
    flare_sat = 255;
    flare_val = 255;
    flare_tail_length = 10;
}

void Firework::prepare_for_launch()
{
    Serial.println("Preparing for launch!");
    random16_add_entropy(random());
    current_stage = LAUNCH;
    flare_position = 0.0;
    next_launch_time = millis() + random16(next_launch_min_wait,next_launch_max_wait);
    flare_velocity = float(random16(50,90))/100;
    launched = false;
    // Reset all LEDs of the strip
    for (uint16_t i; i < NUM_LEDS_PER_STRIP/STRIP_SPLIT; i++)
    {
        leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + i]] = CRGB::Black;
    }

}

void Firework::launch()
{
    Serial.println("Her");
    if (launched & flare_velocity < 0.1) {
        Serial.println("Time to explode");
        current_stage = EXPLOSION;
    }
    else
    {   
        if (!launched)
        {
            Serial.println("We are launching!");
            leds[led_order_array[(strip_number*(NUM_LEDS_PER_STRIP/STRIP_SPLIT))+(int)flare_position]] = CHSV(flare_hue,flare_sat,flare_val);
            launched = true;
        }
        else
        {
            Serial.println("We are in the air and rising");
            // Fading the tail/trail of the flare
            for (uint16_t i = 0; i < (int)flare_position; i++)
            {
                leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + i]].fadeToBlackBy(flare_tail_length);
            }
            // Dunno if this works! o.O
            // The idea is to get the fraction from flare position (pixel_spill), and use this fraction to dim "current position" and start lighting up the next LED
            // The result should then be that the pixel glides along the strip instead of jumping from pixel to pixel
            float pixel_spill = flare_position - (int)flare_position; 
            leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + (int)flare_position]] = CHSV(flare_hue, flare_sat, (flare_val*pixel_spill));
            leds[led_order_array[(strip_number * (NUM_LEDS_PER_STRIP / STRIP_SPLIT)) + (int)flare_position]+1] = CHSV(flare_hue, flare_sat, (flare_val * pixel_spill));
        }
        flare_position += flare_velocity;       // New position = current + velocity
        Serial.print("Flare position: ");
        Serial.println(flare_position);
        flare_velocity *= gravity; // New velocity = current * gravity (gravity is between 0 and 1, so velocity will decrease)
        Serial.print("Flare velocity: ");
        Serial.println(flare_velocity);
    }
}

void Firework::explosion()
{
    Serial.println("EXPLOSION!!!");
    // Code here
    current_stage = WAITING;
}

void Firework::fading()
{
    // Code here
}

void Firework::set_palette(CRGBPalette16 *palette)
{
    // Code here
}

void Firework::update_firework()
{
    if (current_stage == WAITING) {
        Serial.println("Kommer hit");
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