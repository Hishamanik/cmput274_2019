/*
  Showcasing how to pull in restaurant data from 
  the SD card by reading one block at a time.
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <math.h>

#define SD_CS 10

#define REST_START_BLOCK 4000000
#define NUM_RESTAURANTS 1066

MCUFRIEND_kbv tft;

// different than SD
Sd2Card card;

struct restaurant {
  int32_t lat;
  int32_t lon;
  uint8_t rating; // from 0 to 10
  char name[55];
};

void setup() {
  init();
  Serial.begin(9600);

  // including this seems to fix some SD card readblock errors
  // (at least on the old display)
  uint16_t ID = tft.readID();
  tft.begin(ID);

  tft.fillScreen(TFT_BLACK);

  tft.setRotation(1);

  // The following initialization (commented out) is
  // not needed for just raw reads from the SD card, but you should add it later
  // when you bring the map picture back into your assignment
  // (both initializations are required for the assignment)

  // initialize the SD card
  /*
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed! Is the card inserted properly?");
    while (true) {}
  }
  else {
    Serial.println("OK!");
  }
  */

  // initialize SPI (serial peripheral interface)
  // communication between the Arduino and the SD controller

  Serial.print("Initializing SPI communication for raw reads...");
  // SPI Speed can be SPI_FULL_SPEED, SPI_HALF_SPEED or SPI_QUARTER_SPEED.
  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
    Serial.println("failed! Is the card inserted properly?");
    while (true) {}
  }
  else {
    Serial.println("OK!");
  }
}

// read the restaurant at position "restIndex" from the card
// and store at the location pointed to by restPtr
void getRestaurant(int restIndex, restaurant* restPtr) {
  // calculate the block containing this restaurant
  uint32_t blockNum = REST_START_BLOCK + restIndex/8;
  restaurant restBlock[8];

  // Serial.println(blockNum);

  // fetch the block of restaurants containing the restaurant
  // with index "restIndex"
  while (!card.readBlock(blockNum, (uint8_t*) restBlock)) {
    Serial.println("Read block failed, trying again.");
  }
  // Serial.print("Loaded: ");
  // Serial.println(restBlock[0].name);

  *restPtr = restBlock[restIndex % 8];
}

int main() {
  setup();
  
  // now start reading restaurant data, let's do the first block now
  restaurant restBlock[8]; // 512 bytes in total: a block

  Serial.println("Now reading restaurants");


  Serial.println();
  Serial.println("Fetching all restaurants");
  restaurant rest;
  // Part 1
  for (int i = 0; i < NUM_RESTAURANTS; ++i) {
    getRestaurant(i, &rest);
    if (rest.rating == 10){
      int new_rating = max(ceil((rest.rating + 1)/2),1);
      Serial.print(i);
      Serial.print(" ");
      Serial.print(rest.name);
      Serial.print(" ");
      Serial.println(new_rating);
    }
  }
  // Part 2
  for (int i = 0; i < NUM_RESTAURANTS; ++i) {
    getRestaurant(i, &rest);
    if (strstr(rest.name, "Subway")){
        Serial.print(i);
        Serial.print(" ");
        Serial.print("Latitude: ");
        Serial.print(rest.lat);
        Serial.print(", Longitude: ");
        Serial.print(rest.lon);
        Serial.print(", Rating: ");
        Serial.print(rest.rating);
        Serial.println();
      }
  }

  Serial.end();

  return 0;
}