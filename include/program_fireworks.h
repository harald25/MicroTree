#ifndef __FIREWORKS_H_INCLUDED_
#define __FIREWORKS_H_INCLUDED_
#include "main.h"

#define MAX_NUMBER_OF_SPARKS = 60       // The maximum number of sparks from a firework explosion

CRGBPalette16 explosion_palette;
CRGBPalette16 spark_palette;

void fireworks();
void fireworksUpdate();

class Firework
{
    private:
        enum stage
        {
            FLARE,
            EXPLOSION,
            FADING,
            WAITING
        };
        stage current_stage;                                // What stage of the firework are we currently at
        int next_launch_time;                               // Time for next flare launch
        uint8_t flare_velocity;                             // Speed of the flare when it is launched
        uint16_t flare_position;                            // Current position of the flare
        uint8_t strip_number;                               // What strip this firework object is displayed on
        float gravity;                                      // Gravity makes things accelerate back down
        uint8_t number_of_sparks;                           // Number of sparks from explosion
        uint16_t spark_position[MAX_NUMBER_OF_SPARKS];      // Position of all the sparks
        uint8_t spark_velocity[MAX_NUMBER_OF_SPARKS];       // The current velocity of all the sparks
        uint8_t spark_gradient_index[MAX_NUMBER_OF_SPARKS]; // The index of the active_spark_palette this spark gets its color from
        CRGBPalette16 *active_spark_palette;                // The palette this firework object will get colors from
        bool get_random_palette;                            // True = random palette will be picked when new flare is generated. False = will get palette from the global active_palette 

        
        Firework(uint8_t strip_n);                          // The firework class constructor
        void prepare_for_launch();                          // This function resets all positions, and generates new random values
        
    
}

#endif
