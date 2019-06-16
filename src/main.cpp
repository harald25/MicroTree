#include "main.h"

// DEGUGGING
// If set to true, debug messages will be output to serial device
bool debug = false;

int led_array [NUM_LEDS_PER_STRIP*NUM_STRIPS];
CRGB leds [NUM_LEDS_PER_STRIP*NUM_STRIPS];
display_mode displaymode;
direction dir;
program active_program;
int interval;
int last_update;
int program_index1;
int program_index2;
int increment_by1;
int increment_by2;
uint16_t total_steps1;
uint16_t total_steps2;
uint8_t saturation1;
uint8_t value1;
uint8_t hue1;
uint8_t saturation2;
uint8_t value2;
uint8_t hue2;
bool update;
char osc_message_address[18];
float delta;
float slope;

// Put in a separate file because it's long as fuck
#include "led_coordinate_array.txt"

// GRADIENT PALLETTES
DEFINE_GRADIENT_PALETTE( blink_purple_gp ) {
  0,     0,  0,  0,     //black
100,   255,  0,  255,   //Purple
255,     0,  0,  0};   //Black

DEFINE_GRADIENT_PALETTE( blink_orange_gp ) {
  0,     0,  0,  0,     //black
100,   255,  100,  0,   //orange
255,     0,  0,  0};   //black

DEFINE_GRADIENT_PALETTE( blink_bluetones_gp ) {
  0,     0,  0,  0,     //black
64,   33,  180,  226,   //Dark blue
128,   109,  197,  224, //Light blue
192,   33,  180,  226,  //Dark blue
255,     0,  0,  0};   //black

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     100,  255,  0,   //green-ish
128,   255,  0,  0,   //red
224,   255,255,  0,   //bright yellow
255,   255,255,255 }; //full white

CRGBPalette16 blink_palette_purple = blink_purple_gp;
CRGBPalette16 blink_palette_orange = blink_orange_gp;
CRGBPalette16 blink_palette_bluetones = blink_bluetones_gp;

CRGBPalette16 heatcolorPalette = heatmap_gp;



void ledArrayMaker()
{
  int x = 0;
  for (int i = NUM_STRIPS-1; i>-1; i--)
  {
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
      led_array[x] = (i*NUM_LEDS_PER_STRIP)+j;
      x++;
    }
  }
}

void setup() {
  Serial.begin(9600);         //Teensy <=> Computer
  SLIPSerial.begin(115200);   //Teensy <=> ESP
  Serial.println("Started");

  FastLED.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  FastLED.setCorrection(COLOR_CORRECTION);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);


  ledArrayMaker();
  preprogram();
}

void loop() {
    OSCMsgReceive();
    updateLEDs();
}
