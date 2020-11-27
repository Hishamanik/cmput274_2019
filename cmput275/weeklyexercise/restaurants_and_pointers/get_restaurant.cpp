// Name: Al Hisham Anik
// ID: 1585385
// CMPUT275, Winter 2020
//
//Exercise 2: Restaurants and Pointers

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <TouchScreen.h>
#include <Fonts/FreeSansBold9pt7b.h>
using namespace std;

#define SD_CS 10

// physical dimensions of the tft display (# of pixels)
#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320

// touch screen pins, obtained from the documentaion
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// dimensions of the part allocated to the map display
#define MAP_DISP_WIDTH (DISPLAY_WIDTH - 60)
#define MAP_DISP_HEIGHT DISPLAY_HEIGHT

#define REST_START_BLOCK 4000000
#define NUM_RESTAURANTS 1066

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 940
#define TS_MAXY 920

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

MCUFRIEND_kbv tft;

// a multimeter reading says there are 300 ohms of resistance across the plate,
// so initialize with this to get more accurate readings
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// different than SD
Sd2Card card;

//This structure stores the name of resturants with their, latitude, longitude and ratings
struct restaurant {
  int32_t lat;
  int32_t lon;
  uint8_t rating; // from 0 to 10
  char name[55];
};



int BOX_SIZE = 160; //The buttons BoxHeight is initialized here
int global; //intializing a global variable to store valu in getrestaurant process

//Setup function is implemeted to set the SD card, Display Run values in the tft display and provide the button opstion for user interface
void setup() {
  init();
  Serial.begin(9600);

  // tft display initialization
  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);

  // SD card initialization for raw reads
  Serial.print("Initializing SPI communication for raw reads...");
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("failed! Is the card inserted properly?");
    while (true) {}
  }
  else {
    Serial.println("OK!");

    tft.setFont(&FreeSansBold9pt7b);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    

    //Cursor is started from y-coordinate=20 so that the font size doesnot make the alphabets go above the screen
    tft.setCursor(0,20);
    // print text without moving the cursor to the next line
    tft.println("RECENT SLOW RUN:");
    tft.println("Not yet run");
    tft.println(" ");
    tft.println("SLOW RUN AVG:");
    tft.println("Not yet run");
    tft.println(" ");
    tft.println("RECENT FAST RUN:");
    tft.println("Not yet run");
    tft.println(" ");
    tft.println("FAST RUN AVG:");
    tft.println("Not yet run");

  Serial.println("Done!");

  //Alphabets for button names are initialzed in an array
  char slow[] = { 'S', 'L', 'O', 'W', '\0' }; 
  char fast[] = { 'F', 'A', 'S', 'T', '\0' };


    //This block of code, draws position to store slow button and name it
    tft.drawRect(MAP_DISP_WIDTH, 0, 60, DISPLAY_HEIGHT/2 , TFT_RED);  //Width of the button's block is given 60 and height is given 160 = Display_Height/2
    tft.setTextSize(1);
    int a = 0 ;
    for (int i=0;i<4;i++) {
      tft.setCursor(DISPLAY_WIDTH-35,55+a); // Cursor is set at a magic number position to make the text appears at the middle of the 1st button
      tft.println(slow[i]);
      a +=15; //This magic number gives the chance for each alphabet of slow to be printed one below another without getting mix up
    }
      
    //This block of code, draws position to store fast button and name it
    tft.drawRect(MAP_DISP_WIDTH, DISPLAY_HEIGHT/2, 60, DISPLAY_HEIGHT/2, TFT_RED);
    tft.setTextSize(1);
    int k =0;
    for (int i=0;i<4;i++) {
      tft.setCursor(DISPLAY_WIDTH-35, (BOX_SIZE+55)+k); // Cursor is set at a magic number position to make the text appears at the middle of the 2nd button
      tft.println(fast[i]);
      k +=15; //This magic number gives the chance for each alphabet of fast to be printed one below another without getting mix up
    } 
  }
}



//This function calls resturant names from each block of SD card repeatedly which makes it a slow process
//by going over each block 8 times to fetch 8 restaurants name
void getRestaurant(int restIndex, restaurant* restPtr) {
  uint32_t blockNum = REST_START_BLOCK + restIndex/8;
  restaurant restBlock[8];

  while (!card.readBlock(blockNum, (uint8_t*) restBlock)) {
    Serial.println("Read block failed, trying again.");
  }

  *restPtr = restBlock[restIndex % 8];
}

//This function calls resturant names from each block of SD card once which makes it a fast process
void getRestaurantFastImplementation(int restIndex, restaurant* restPtr) {
  uint32_t blockNum = REST_START_BLOCK + restIndex/8;

  if (blockNum != global) {
    global = blockNum;
    restaurant restBlock[8];
    global = REST_START_BLOCK + restIndex/8;
    while (!card.readBlock(blockNum, (uint8_t*) restBlock)) {
      Serial.println("Read block failed, trying again.");
    }
  }
  restaurant restBlock[8];

  *restPtr = restBlock[restIndex % 8];
}

//This is a slow function of calling resturants names
void getRestaurantSlow() {
  // now start reading restaurant data, let's do the first block now
  restaurant restBlock[8]; // 512 bytes in total: a block

  Serial.println("Now reading restaurants");


  Serial.println();
  Serial.println("Fetching all restaurants");
  restaurant rest;
  Serial.println(NUM_RESTAURANTS);
  //Fetching and printing all the 1066 names of resturants
  for (int i = 0; i < NUM_RESTAURANTS; ++i) {
    getRestaurant(i, &rest);
    Serial.println(rest.name);
  }

}

//This is a fast function for calling names of resturants
void getRestaurantFast() {
  restaurant rest;
  for (int i = 0; i < NUM_RESTAURANTS; ++i) {
    getRestaurantFastImplementation(i, &rest);
    Serial.println(rest.name);
  } 
} 


void loop() {
  // query touchscreen and then reset pin states
  TSPoint touch = ts.getPoint(); // (x, y, pressure)
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
    
  if (touch.z >= MINPRESSURE && touch.z <= MAXPRESSURE) {
    int ptx = map(touch.y, TS_MINX, TS_MAXX, 0, DISPLAY_WIDTH);
    int pty = map(touch.x, TS_MINY, TS_MAXY, 0, DISPLAY_HEIGHT);

    //This function gets implemented only when slow button is pushed in tft Display
    //ptx<60 and pty>160 is the position where the button slow is reserved 
    if (ptx < 60 && pty > 160) {
      unsigned int timeSlow1 = millis();
      getRestaurantSlow();
      unsigned int timeSlow2 = millis();
      unsigned int timeSlow = timeSlow2 -timeSlow1 ; //measures the running time of the slow function call

      static uint16_t callSlow =0;
      callSlow++;
      static unsigned int sumSlow =0;
      tft.fillRect(0, 22, 200, 40 , TFT_BLACK); //updates new value of run under recent run with magic number to cover up the previous position
      tft.setCursor(0,35);
      tft.print(timeSlow);
      tft.println(" ms");
          
      //This block sums all the previous slow resturant call run and prints the average
      sumSlow += timeSlow;
      unsigned int average = sumSlow/callSlow ; //makes an average of all the run took place for slow 
      tft.setCursor(0,100);
      tft.fillRect(0, 87, 200, 40, TFT_BLACK); //updates new value of average run under average run with magic number to cover up the previous position
      tft.print(average);
      tft.println(" ms");
    }

    //This function gets implemented when fast button is pushed in tft Display
    //ptx<60 and pty<160 is the position where the button slow is reserved 
    if (ptx < 60 && pty < 160) {
      unsigned int timeFast1 = millis();
      getRestaurantFast();
      unsigned int timeFast2 = millis();
      unsigned int timeFast = timeFast2 -timeFast1 ; //measures the time taken to run the fast getrestaurant function
      
      static uint16_t callFast =0;
      callFast++;
      static unsigned int sumFast =0;
          
      //This block updates the new Fast run
      tft.setCursor(0,175);
      tft.fillRect(0, 155, 200, 30 , TFT_BLACK); 
      tft.setCursor(0,170);
      tft.print(timeFast);
      tft.println(" ms");

      //This block sums all the previous fast resturant call run and prints the average of fast run
      sumFast += timeFast;
      unsigned int average = sumFast/callFast ; //makes an average of all preious Fast run call
      tft.setCursor(0,235);
      tft.fillRect(0, 220, 200, 40 , TFT_BLACK);
      tft.print(average);
      tft.println(" ms");
    } 
  }
}

int main() {
  setup();
  
  //This loop gets implemented only when the tft diplay is touch at button positions
  while (true) {
    loop();
    delay(5);
  }

  Serial.end();

  return 0;
}