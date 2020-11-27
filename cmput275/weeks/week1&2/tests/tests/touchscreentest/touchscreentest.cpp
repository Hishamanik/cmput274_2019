#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

// Pin Definitions
#define YP A3
#define XM A2
#define YM 9
#define XP 8
#define SD_CS 10

// Pressure of zero means no pressing
#define MINPRESSURE 400   // min pressure value considered valid
#define MAXPRESSURE 800  // max pressure value considered valid

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

int PEN_SIZE = 4;
const int BOX_SIZE = 40;

uint16_t colors[] = {
    TFT_BLUE,
    TFT_CYAN,
    TFT_GREEN,
    TFT_RED,
    TFT_YELLOW,
    TFT_BLACK
};

int current_color;


MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


void loop() {
    // query touchscreen and then reset pin states
    TSPoint touch = ts.getPoint(); // (x, y, pressure)
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);

    Serial.print(touch.x);
    Serial.print(' ');
    Serial.print(touch.y);
    Serial.print(' ');
    Serial.println(touch.z);

    // Challenge: have the pen radius change with pressure
    if (touch.z >= MINPRESSURE && touch.z <= MAXPRESSURE) {
        int ptx = map(touch.y, TS_MINX, TS_MAXX, 0,tft.width());
        int pty = map(touch.x, TS_MINY, TS_MAXY,0, tft.height());
        tft.fillCircle(ptx, pty, PEN_SIZE, colors[current_color]);
         

        if (ptx < BOX_SIZE) {
            int old_color = current_color;
            current_color = pty/BOX_SIZE;
            Serial.print("Color: ");
            Serial.println(colors[current_color]);

            if(current_color<5) {
                tft.fillRect(0, BOX_SIZE*old_color, BOX_SIZE, BOX_SIZE, colors[old_color]);
                tft.drawRect(0, BOX_SIZE*current_color, BOX_SIZE, BOX_SIZE, TFT_WHITE);
            }
        }
    }

    
}


/**
 * Init display, etc.
 */
void setup() {
    // Begin Serial Communication
    init();
    Serial.begin(9600);
    Serial.flush();

    // Initiailize tft Display
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    // Draw the color selection boxes
    for (int i=0;i<5;i++)
        tft.fillRect(0, BOX_SIZE*i, BOX_SIZE, BOX_SIZE, colors[i]);
    tft.setCursor(10,10+BOX_SIZE*5);
    tft.setTextSize(4);
    tft.print("E");

    // Highlight the current selection
    tft.drawRect(0, 0, BOX_SIZE, BOX_SIZE, TFT_WHITE);
    current_color = 0;
}

int main() {
    setup();
    while (true) {
        loop();
        delay(5); // lower delay makes it more interactive
    }
}