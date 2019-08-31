#include "main.h"

// DEGUGGING
// If set to true, debug messages will be output to serial device
bool debug = false;

AudioInputAnalog          adc1(A3); //Defined here and used in vumeter and audioreact
AudioAnalyzeFFT1024       fft;
AudioConnection           patchCord(adc1, fft);

CRGB leds [NUM_LEDS_PER_STRIP * NUM_STRIPS];
int led_order_array[NUM_LEDS_PER_STRIP * NUM_STRIPS];

display_mode displaymode;
direction dir;
program active_program;
int interval;
uint32_t last_update = 0;
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
bool update = true;
char osc_message_address[25];
float delta;
float slope;


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


DEFINE_GRADIENT_PALETTE( spectrum_classic_gp ) {
0,   0,  255,  0,    //Green
75, 255,  200,  0,  //Yellow
115,   255,  0,  0,   //Red
255,   255,  0,  0};    //Red

DEFINE_GRADIENT_PALETTE( spectrum_warm_gp ) {
0,      0,  0,  244,    //Blue
109,    0,  0,  244,    //Blue
110,   255,    0,  175,   //Lilla
190,   255,    0,  175,   //Lilla
191,   255,    0,  0,    //Red
255,   255,    0,  0};    //Red

DEFINE_GRADIENT_PALETTE( spectrum_pastel_gp ) {
0,      0,  200,  245,    //Bright blue
//25,      0,  200,  245,    //Bright blue
25,    0,  255,  0,    //Pastel green
150,    0,  255,  0,    //Pastel green
200,   239, 255,  10,   //Yellow
255,   255,   0,  0};    //Red

DEFINE_GRADIENT_PALETTE( spectrum_candy_gp ) {
0,   245,    50,  207,    //Pastel pink
100,   245,    50,  207,    //Pastel pink
125,   32,    255,  125,    //Pastel green
175,   32,    255,  125,    //Pastel green
200,   0,    162,  255,    //Pastel Blue
255,   0,    162,  255};    //Pastel Blue

// Gradient palette "es_vintage_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE(es_vintage_01_gp){
0, 0, 0, 0,
5, 4, 1, 1,
51, 16, 0, 1,
76, 97, 104, 3,
101, 255, 131, 19,
127, 67, 9, 4,
153, 16, 0, 1,
229, 4, 1, 1,
250, 4, 1, 1,
255, 0, 0, 0};

// Gradient palette "purplefly_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/purplefly.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(purplefly_gp){
0, 0, 0, 0,
63, 239, 0, 122,
191, 252, 255, 78,
255, 0, 0, 0};

// Gradient palette "bhw1_greeny_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_greeny.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_greeny_gp){
0, 0, 0, 0,
39, 7, 55, 8,
99, 42, 255, 45,
153, 7, 55, 8,
255, 0, 0, 0};

// Gradient palette "bhw1_14_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_14.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_14_gp){
0, 0, 0, 0,
12, 1, 1, 3,
53, 8, 1, 22,
80, 4, 6, 89,
119, 2, 25, 216,
145, 7, 10, 99,
186, 15, 2, 31,
233, 2, 1, 5,
255, 0, 0, 0};


// Gradient palette "bhw2_22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw2_22_gp){
0, 0, 0, 0,
99, 227, 1, 1,
130, 249, 199, 95,
155, 227, 1, 1,
255, 0, 0, 0};

CRGBPalette16 spectrum_candy = spectrum_candy_gp;
CRGBPalette16 spectrum_pastel = spectrum_pastel_gp;
CRGBPalette16 spectrum_warm = spectrum_warm_gp;
CRGBPalette16 spectrum_classic = spectrum_classic_gp;

CRGBPalette16 blink_palette_purple = blink_purple_gp;
CRGBPalette16 blink_palette_orange = blink_orange_gp;
CRGBPalette16 blink_palette_bluetones = blink_bluetones_gp;

CRGBPalette16 blink_palette_es_vintage = es_vintage_01_gp;
CRGBPalette16 blink_palette_purplefly = purplefly_gp;
CRGBPalette16 blink_palette_greeny = bhw1_greeny_gp;
CRGBPalette16 blink_palette_bhw1_14 = bhw1_14_gp;
CRGBPalette16 blink_palette_bhw2_22 = bhw2_22_gp;

CRGBPalette16 heatcolorPalette = heatmap_gp;

CRGBPalette16 * active_palette;




void setup() {
  delay(5000);
  Serial.begin(9600);         //Teensy <=> Computer
  SLIPSerial.begin(115200);   //Teensy <=> ESP
  Serial.println("Started");
  if(debug) {
    Serial.println("Debugging is activated");
  }

  //For sound reactivity
  AudioMemory(16);

  FastLED.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  FastLED.setCorrection(COLOR_CORRECTION);
  FastLED.setBrightness(GLOBAL_BRIGHTNESS);
  generate_led_order_array(EVERY_SECOND_STRIP_REVERSED);
  preprogram();
}

void loop() {
  OSCMsgReceive();
  audioReact((audio_reactive_setting)reactive_setting);
  updateLEDs();
}