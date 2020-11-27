/*
Name: Nibras Alam and Al Hisham Anik
ID #: 1617818 and 1585385
CMPUT 275, Winter 2019

Assignment 1: Restaurant Finder Part 2
***Consulted C++, Arduino, Adafruit GFX Documentation***
***Use of Lecture Code specified in function headers***
***QuickSort Algorithm Pseudocode from Wikipedia***

Included Files:
    -a1part2.cpp
    -lcd_image.cpp
    -lcd_image.h
    -Makefile
    -README

Running Instructions:
    1. Connect the Arduino Mega 2560 (with Display and Joystick Wired) through an A-B style USB cable to the computer
    2. Ensure the Arduino is using the proper port: /dev/ttyACM0 or - ACM1 ("arduino-port-select" in CML, hit "1" twice)
    3. Within the program directory including the Makefile, open a terminal window and enter "make && make upload && serial-mon"
    4. Ensure "avrdude done. Thank you." is visible at some point
    5. Program Functions:
        Mode 0: Use Arduino joystick to navigate the YEG Map (which will shift when hitting border). Tap the map area of screen to view all restaurants within current map patch. Click joystick to switch to Mode 1.
        
        Mode 1: When Mode 1 has been selected, the closest 21 restaurants will be listed based on Manhattan Distance from cursor. Sorting algorithm timing displayed in Serial Monitor.

        Scroll through the list and click joystick to switch back to Mode 0 with cursor centered over selected restaurant (or as centered as possible near the edges). Scrolling can span across pages to view entire list of restaurants - including past top of list which goes to the bottom of the list.

        Button Functions: Press the rating buttons or the sort buttons to change the type. Tap the screen in Mode 0 to view restaurants >= selected rating. Press the Joystick in Mode 0 to switch to Mode 1 with selected sorting(s) of restaurants >= selected rating.

Accesories:
    -Arduino MEGA 2560
    -TFT Display
    -1 Joystick
    -5 Breakout Wires (Male to Female)

Wiring Instructions:
    -Arduino GND <M---F> Joystick Pin GND
    -Arduino 5V <M---F> Joystick Pin 5V
    -Arduino Pin A8 <M---F> Joystick Pin VRy
    -Arduino Pin A9 <M---F> Joystick Pin VRx
    -Arduino Pin 53 <M---F> Joystick Pin SW
    ***Attach TFT Display (by lining up the matching pins) AFTER connecting wires***

Notes and Assumptions:
    -Follows all assumptions from the assignment
    -Modified xCursor and yCursor to be the top left corner of cursor rather than middle for personal ease in determining logic of code. mapX and mapY follow similar logic. 

Other Information:
    -Passes style checker
*/
/*
# Name: Nibras Alam and Al Hisham Anik
# ID: 1617818 and 1585385
# CMPUT 275, Winter 2020
#
# Assignment 1: Restaurant Finder Part 2
#
# Consulted C++, Arduino, and Adafruit GFX Documentation; Used Lecture 
# Slides; Use of Lecture Code mentioned in function headers
*/
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SD.h>
#include <TouchScreen.h>

#include <SPI.h>
#include <SD.h>
#include "lcd_image.h"

// physical component initialization
MCUFRIEND_kbv tft;
#define JOY_VERT A9  // should connect A9 to pin VRx
#define JOY_HORIZ A8  // should connect A8 to pin VRy
#define JOY_SEL 53

// joystick and cursor initialization
#define JOY_CENTER 512
#define JOY_DEADZONE 64
#define CURSOR_SIZE 9
int16_t cursorX, cursorY;  // based on top left corner of cursor


// display dimensions and image/map initialization
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320
#define MAP_DISP_WIDTH (DISPLAY_WIDTH - 60)
#define MAP_DISP_HEIGHT DISPLAY_HEIGHT
#define BUTTON_HEIGHT DISPLAY_HEIGHT/2

#define YEG_SIZE 2048
#define LAT_NORTH 5361858
#define LAT_SOUTH 5340953
#define LON_WEST -11368652
#define LON_EAST -11333496
lcd_image_t yegImage = {"yeg-big.lcd", YEG_SIZE, YEG_SIZE};

// top left corner coords of current map patch, default = YEG center
int16_t mapX = YEG_SIZE/2 - (MAP_DISP_WIDTH)/2;
int16_t mapY = YEG_SIZE/2 - MAP_DISP_HEIGHT/2;

// touch screen pins, obtained from the documentaion
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 940
#define TS_MAXY 920

// thresholds to determine if there was a touch
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// a multimeter reading says there are 300 ohms of resistance across the plate,
// so initialize with this to get more accurate readings
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define SD_CS 10

// different than SD
Sd2Card card;

// restuarant data and struct initialization
#define REST_START_BLOCK 4000000
#define NUM_RESTAURANTS 1066

struct restaurant {
    int32_t lat;
    int32_t lon;
    uint8_t rating;
    char name[55];
};

// global vars for getRestaurantFast()
// -1 ensures logic for same block comparison works initially
int32_t previousBlockNum = -1;
restaurant fastBlock[8];

// global vars to track current rating and sort type
uint8_t rating = 1, callSort = 1;

struct RestDist {
    uint16_t index;
    uint16_t dist;
};
RestDist rest_dist[NUM_RESTAURANTS];

// forward declarations
void redrawCursor(uint16_t colour);
void updateRatingButton();
void updateSortingButton();

void setup() {
    /*
        Initializes physical components and serial communication
        Initializes display with black screen to "clear"
        Followed by YEG map and initial cursor displayed
    */
    init();
    Serial.begin(9600);

    pinMode(JOY_SEL, INPUT_PULLUP);

    // TFT Display initialization
    uint16_t ID = tft.readID();  // read ID from display
    if (ID == 0xD3D3) ID = 0x9481;  // write-only shield
    tft.begin(ID);  // LCD gets ready to work

    // SD Card initialization
    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed! Is it inserted properly?");
        while (true) {}
    }
    Serial.println("OK!");

    // SD card initialization for raw reads
    Serial.print("Initializing SPI communication for raw reads...");
    if (!card.init(SPI_HALF_SPEED, SD_CS)) {
        Serial.println("failed! Is the card inserted properly?");
        while (true) {}
    } else {
        Serial.println("OK!");
    }

    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // draws initial buttons for rating/sort selectors
    updateRatingButton();
    updateSortingButton();

    // draws initial map patch (center of YEG)
    lcd_image_draw(&yegImage, &tft, mapX, mapY,
            0, 0, MAP_DISP_WIDTH, MAP_DISP_HEIGHT);

    // initial cursor position = center screen
    cursorX = (MAP_DISP_WIDTH)/2 - CURSOR_SIZE/2;
    cursorY = MAP_DISP_HEIGHT/2 - CURSOR_SIZE/2;

    redrawCursor(TFT_RED);
}


int32_t xToLon(int16_t x) {
    /*
        Converts x coord to longitutude; from assignment descrip.

        Arguments:
            x (int16_t): x coord

        Returns:
            longitutde (int32_t): longitude
    */
    return map(x, 0, YEG_SIZE, LON_WEST, LON_EAST);
}

int32_t yToLat(int16_t y) {
    /*
        Converts y coord to latitude; from assignment descrip.

        Arguments:
            y (int16_t): y coord

        Returns:
            latitude (int32_t): latitude
    */
    return map(y, 0, YEG_SIZE, LAT_NORTH, LAT_SOUTH);
}

int16_t lonToX(int32_t lon) {
        /*
        Converts longitutude to x coord; from assignment descrip.

        Arguments:
            longitutde (int32_t): longitude

        Returns:
            x (int16_t): x coord
    */
    return map(lon, LON_WEST, LON_EAST, 0, YEG_SIZE);
}

int16_t latToY(int32_t lat) {
    /*
        Converts latitude to y coord; from assignment descrip.

        Arguments:
            latitude (int32_t): latitude

        Returns:
            y (int16_t): y coord
    */
    return map(lat, LAT_NORTH, LAT_SOUTH, 0, YEG_SIZE);
}


void redrawMap(int16_t mapShiftX, int16_t mapShiftY, int16_t x, int16_t y) {
    /*
        Draws a new map patch whenever cursor is shifted into new area or
        when button is pressed for selected restaurant. x,y coords are for
        edge cases, a value of 300 is used otherwise to control the logic.

        Arguments:
            mapShiftX (int16_t): magnitude to shift map x-coord
            mapShiftY (int16_t): magnitude to shift map y-coord
            x (int16_t): x-coord of restaurant for edge cases
            y (int16_t): y-coord of restaurant for edge cases
        
        Returns:
            void

    */
    int16_t mapXPrevious = mapX;
    int16_t mapYPrevious = mapY;

    // constrain() ensures outside of map boundary is not drawn
    mapX = constrain((mapX+mapShiftX), 0, (YEG_SIZE-MAP_DISP_WIDTH));
    mapY = constrain((mapY+mapShiftY), 0, (YEG_SIZE-MAP_DISP_HEIGHT));

    // only draws if new patch or mode1->mode0
    if ((mapX != mapXPrevious) || (mapY != mapYPrevious) || (x != 300)) {
        lcd_image_draw(&yegImage, &tft, mapX, mapY,
                0, 0, MAP_DISP_WIDTH, MAP_DISP_HEIGHT);

        cursorX = (MAP_DISP_WIDTH)/2 - CURSOR_SIZE/2;
        cursorY = MAP_DISP_HEIGHT/2 - CURSOR_SIZE/2;

        // boundary cases
        if (x > YEG_SIZE-(MAP_DISP_WIDTH/2) || x < (MAP_DISP_WIDTH/2)) {
            cursorX = x - mapX - CURSOR_SIZE/2;
        }

        if (y > YEG_SIZE-(MAP_DISP_HEIGHT/2) || y < (MAP_DISP_HEIGHT/2)) {
            cursorY = y - mapY - CURSOR_SIZE/2;
        }

        // draws cursor at default center or based on edge cases
        cursorX = constrain((cursorX), 0, (MAP_DISP_WIDTH-(CURSOR_SIZE)));
        cursorY = constrain((cursorY), 0, (MAP_DISP_HEIGHT-(CURSOR_SIZE)));
        redrawCursor(TFT_RED);
    }
}

void redrawCursor(uint16_t colour) {
    /*
        Draws cursor based on new position

        Arguments:
            colour (uint16_t): desired cursor colour

        Returns:
            void
    */
    tft.fillRect(cursorX, cursorY, CURSOR_SIZE, CURSOR_SIZE, colour);
}

void drawCursorPath(int16_t xPrevious, int16_t yPrevious) {
    /*
        Fills in portion of map based on cursor's previous position

        Arguments:
            xPrevious (uint16_t): previous x position
            yPrevious (uint16_t): previous y position

        Returns:
            void
    */
    lcd_image_draw(&yegImage, &tft, mapX+xPrevious, mapY+yPrevious,
                xPrevious, yPrevious, CURSOR_SIZE, CURSOR_SIZE);
}

void cursorMovement(int16_t xVal, int16_t yVal) {
    /*
        Determines cursor movement based on joystick and shifts patch
        if required.

        Arguments:
            xVal (int16_t): xVal from joystick
            yVal (int16_t): yVal from joystick

        Returns:
            void
    */
    int8_t xChange = 0, yChange = 0;
    if (xVal > (JOY_CENTER + JOY_DEADZONE)) {
        xChange = -7;

    } else if (xVal < (JOY_CENTER - JOY_DEADZONE)) {
        xChange = 7;
    }

    if (yVal < (JOY_CENTER - JOY_DEADZONE)) {
        yChange = -7;

    } else if (yVal > (JOY_CENTER + JOY_DEADZONE)) {
        yChange = 7;
    }

    // stores previous coordinates before they are updated
    int16_t xPrevious = cursorX;
    int16_t yPrevious = cursorY;

    // constrain() ensures cursor is not drawn outside the screen's border
    cursorX = constrain((cursorX+xChange), 0, (MAP_DISP_WIDTH-(CURSOR_SIZE)));
    cursorY = constrain((cursorY+yChange), 0, (MAP_DISP_HEIGHT-(CURSOR_SIZE)));

    // only draws new cursor and fills in path if joystick moved
    if (abs(xChange) + abs(yChange) != 0) {
        drawCursorPath(xPrevious, yPrevious);
        redrawCursor(TFT_RED);

        // shifts patch only if cursor hits border; value of 300 for logic
        // purposes since redrawMap is also used for selecting a restaurant
        if ((MAP_DISP_WIDTH - CURSOR_SIZE - cursorX) == 0) {
            redrawMap(MAP_DISP_WIDTH, 0, 300, 300);

        } else if (cursorX == 0) {
            redrawMap(-(MAP_DISP_WIDTH), 0, 300, 300);
        }

        if ((MAP_DISP_HEIGHT - CURSOR_SIZE - cursorY) == 0) {
            redrawMap(0, MAP_DISP_HEIGHT, 300, 300);

        } else if (cursorY == 0) {
            redrawMap(0, -MAP_DISP_HEIGHT, 300, 300);
        }
    }
}


void getRestaurantFast(uint16_t restIndex, restaurant* restPtr) {
        /*
        Retrieves block *only if previous iteration had different block*
        based on index of restaurant and dereferences pointer to 
        restaurant object

        Arguments:
            restIndex (uint16_t):
            restPtr (restaurant*):
            
        Returns:
            None, but modifies restaurant object from pointer
    */
    uint32_t blockNum = REST_START_BLOCK + restIndex/8;
    if (blockNum != previousBlockNum) {
        while (!card.readBlock(blockNum,
                reinterpret_cast<uint8_t*>(fastBlock))) {
            Serial.println("Read block failed, trying again.");
        }
        previousBlockNum = blockNum;
    }
    *restPtr = fastBlock[restIndex % 8];
}


void swap(RestDist* arr, uint16_t i, uint16_t j) {
    /*
        Swaps values of 2 RestDist arr elements

        Arguments:
            arr (RestDist*): Pointer to array storing RestDist structs
            i (uint16_t): first index to swap
            j (uint16_t): second index to swap

        Returns:
            void
    */
    RestDist temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

uint16_t partition(RestDist* arr, int16_t low, int16_t high) {
     /*
        Used in quicksort algorithm to portion the sorting

        Arguments:
            arr (RestDist*): Pointer to array storing RestDist structs
            low (int16_t): start element of portion
            high (int16_t): end element of portion

        Returns:
            void
    */
    uint16_t pivot = arr[high].dist;
    int16_t i = (low - 1);

    for (int16_t j = low; j <= high - 1; j++) {
        if (arr[j].dist <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

void qSort(RestDist* arr, int16_t low, int16_t high) {
    /*
        Uses quick sort algorithm based on pseudocode from Wikipedia
        to sort RestDist by Manhattan distance from cursor

        Arguments:
            arr (RestDist*): Pointer to array storing RestDist structs
            low (int16_t): start element of array portion for sorting
            high (int16_t): end element of array portion for sorting

        Returns:
            void
    */
    if (low < high) {
        int16_t pi = partition(arr, low, high);
        qSort(arr, low, pi - 1);
        qSort(arr, pi + 1, high);
    }
}

void iSort(RestDist* arr, uint16_t length) {
    /*
        Uses insertion sort algorithm based on pseudocode to sort 
        RestDist by Manhattan distance from cursor

        Arguments:
            length (uint16_t): the length of the array
            arr (RestDist*): Pointer to array storing RestDist structs

        Returns:
            void
    */
    uint16_t i = 1;
    while (i < length) {
        uint16_t j = i;
        while (j > 0 && arr[j-1].dist > arr[j].dist) {
            swap(arr, j, j-1);
            j--;
        }
        i++;
    }
}


void centerRestaurant(int16_t x, int16_t y) {
    /*
        Shifts map and centers cursor based on selected restaurant; edge
        cases handled within redrawMap function based on restaurant coords

        Arguments:
            x (int16_t): x-coord of selected restaurant
            y (int16_t): y-coord of selected restaurant

        Returns:
            void
    */
    int16_t mapShiftX = (x - MAP_DISP_WIDTH/2) - mapX;
    int16_t mapShiftY = (y - MAP_DISP_HEIGHT/2) - mapY;

    redrawMap(mapShiftX, mapShiftY, x, y);
}

void newList(restaurant tempRest, uint16_t selectedRest,
                int8_t selectedListRest, uint8_t upper) {
    /*
        Updates screen when mode0 -> mode1 and when scrolling past
        the top or bottom

        Arguments:
            tempRest (restaurant): Pointer for storing temp restaurant object
            selectedRest (uint16_t): First restaurant on page (0-1065 index)
            selectedListRest (uint16_t): Selected restaurant to highlight
            upper (uint8_t): how many restaurants to display on page

        Returns:
            void
    */
    tft.fillScreen(0);
    for (uint16_t i = selectedRest; i < selectedRest + upper; i++) {
        getRestaurantFast(rest_dist[i].index, &tempRest);
        if (i % 21 != selectedListRest) {
            tft.setTextColor(TFT_WHITE, TFT_BLACK);

        } else {
            tft.setTextColor(TFT_BLACK, TFT_WHITE);
        }
        tft.setCursor(0, 15*(i % 21));
        tft.print(tempRest.name);
    }
}

void closestList(uint16_t restaurantCounter) {
    /*
        Switches to mode 1 and displays the 21 closest restaurants as a 
        scrollable list. If joystick pushed, then selects restaurant and
        switches back to mode 0. Part of code from assignment description.

        Arguments:
            restaurantCounter (uint16_t): Number of rest_dist elements to be 
                accessed and sorted

        Returns:
            void
    */
    tft.fillScreen(0);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextWrap(false);

    uint16_t selectedRest = 0;
    int8_t selectedListRest = 0;
    uint8_t upper = 21;
    restaurant tempRest;
    newList(tempRest, selectedRest, selectedListRest, upper);

    // loops while waiting for joystick scrolling or button push for mode 0
    // reprints selected restaurant to look like it's highlighted
    bool pushed = false;
    while (!pushed) {
        int16_t buttonVal = digitalRead(JOY_SEL);
        if (buttonVal == LOW) {
            pushed = true;
            updateSortingButton();
            updateRatingButton();
            centerRestaurant(lonToX(tempRest.lon), latToY(tempRest.lat));
        }

        int16_t yVal = analogRead(JOY_VERT);
        getRestaurantFast(rest_dist[selectedRest].index, &tempRest);
        // 15 == height of text (Font Pt. 2 - 1 space)
        if (yVal < (JOY_CENTER - JOY_DEADZONE)) {
            tft.setCursor(0, 15*selectedListRest);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.print(tempRest.name);

            selectedListRest--;
            if (selectedListRest < 0) {
                // case for scrolling up past top of list (goes to bottom)
                if (selectedRest == 0) {
                    selectedRest = restaurantCounter-(restaurantCounter%21);
                    selectedListRest = restaurantCounter%21 - 1;
                    upper = restaurantCounter % 21;
                    newList(tempRest, selectedRest, selectedListRest, upper);
                    selectedRest += selectedListRest;

                // case for scrolling up one page in general
                } else {
                    selectedRest -= 21;
                    selectedListRest = 20;
                    upper = 21;
                    newList(tempRest, selectedRest, selectedListRest, upper);
                    selectedRest += selectedListRest;
                }

            } else {
                // main case for scrolling up on page
                selectedRest--;
                getRestaurantFast(rest_dist[selectedRest].index, &tempRest);
                tft.setCursor(0, 15*selectedListRest);
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.print(tempRest.name);
            }

        } else if (yVal > (JOY_CENTER + JOY_DEADZONE)) {
            tft.setCursor(0, 15*selectedListRest);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.print(tempRest.name);

            selectedListRest++;
            // case for scrolling past bottom of list (goes to top of list)
            if ((selectedListRest > selectedRest%21) &&
                    (selectedRest == restaurantCounter-1)) {
                selectedRest = 0;
                selectedListRest = 0;
                upper = 21;
                newList(tempRest, selectedRest, selectedListRest, upper);

            // case for scrolling to last page
            } else if (selectedListRest > 20 &&
                            ((selectedRest + 1 + 21) > restaurantCounter-1)) {
                selectedRest += 1;
                selectedListRest = 0;
                upper = restaurantCounter % 21;
                newList(tempRest, selectedRest, selectedListRest, upper);

            // case for scrolling past bottom of page
            } else if (selectedListRest > 20) {
                selectedRest += 1;
                selectedListRest = 0;
                upper = 21;
                newList(tempRest, selectedRest, selectedListRest, upper);

            // main case for scrolling down on page
            } else {
                selectedRest++;
                getRestaurantFast(rest_dist[selectedRest].index, &tempRest);
                tft.setCursor(0, 15*selectedListRest);
                tft.setTextColor(TFT_BLACK, TFT_WHITE);
                tft.print(tempRest.name);
            }
        }
        delay(100);
    }
}

bool ratingChecker(uint8_t restaurantRating10) {
    /*
        Converts 10-star restaurant rating to 5-star and returns true
        if higher than current selected rating. Uses conversion from eClass

        Arguments:
            restaurantRating10 (uint8_t): 10-star rating

        Returns:
            true (bool): restaurant rating > selected rating
            false (bool): restaurant rating < selected rating 
    */
    uint8_t convertedRating = max((restaurantRating10 + 1)/2, 1);
    if (rating == 0) {
        rating = 5;
    }

    if (convertedRating >= rating) {
        return true;

    } else {
        return false;
    }
}

void closestFinder() {
    /*
        Uses the long/lat as x/y coords to find and order the closest
        restaurants to cursor based on Manhattan distance and selected
        rating

        Arguments:
            None

        Returns:
            void
    */
    int16_t restaurantCounter;
    if (callSort == 1 || callSort == 0) {
        restaurantCounter = 0;
        restaurant tempRest1;
        for (uint16_t i = 0; i < NUM_RESTAURANTS; i++) {
            getRestaurantFast(i, &tempRest1);
            if (ratingChecker(tempRest1.rating)) {
                int16_t x1 = lonToX(tempRest1.lon);
                int16_t x2 = mapX+cursorX+(CURSOR_SIZE/2);
                int16_t y1 = latToY(tempRest1.lat);
                int16_t y2 = mapY+cursorY+(CURSOR_SIZE/2);

                uint16_t manhattan = abs((x1-x2)) + abs((y1 - y2));
                rest_dist[restaurantCounter].index = i;
                rest_dist[restaurantCounter].dist = manhattan;
                restaurantCounter++;
            }
        }
        Serial.print("qSort Time for ");
        uint16_t initial = millis();
        qSort(rest_dist, 0, (restaurantCounter-1));
        uint16_t totalTime = millis() - initial;

        Serial.print(restaurantCounter);
        Serial.print(" restaurants: ");
        Serial.print(totalTime);
        Serial.println(" ms");
    }

    if (callSort == 2 || callSort == 0) {
        restaurantCounter = 0;
        restaurant tempRest2;
        for (uint16_t i = 0; i < NUM_RESTAURANTS; i++) {
            getRestaurantFast(i, &tempRest2);
            if (ratingChecker(tempRest2.rating)) {
                int16_t x1 = lonToX(tempRest2.lon);
                int16_t x2 = mapX+cursorX+(CURSOR_SIZE/2);
                int16_t y1 = latToY(tempRest2.lat);
                int16_t y2 = mapY+cursorY+(CURSOR_SIZE/2);

                int32_t manhattan = abs((x1-x2)) + abs((y1 - y2));
                rest_dist[restaurantCounter].index = i;
                rest_dist[restaurantCounter].dist = manhattan;
                restaurantCounter++;
            }
        }
        Serial.print("iSort Time for ");;
        uint16_t initial = millis();
        iSort(rest_dist, restaurantCounter);
        uint16_t totalTime = millis() - initial;

        Serial.print(restaurantCounter);
        Serial.print(" restaurants: ");
        Serial.print(totalTime);
        Serial.println(" ms");
    }

    Serial.println();
    closestList(restaurantCounter);
}


void drawRestaurantPoint(int16_t x, int16_t y) {
    /*
        Draws blue circle at restaurant point

        Arguments:
            x (int16_t): x position
            y (int16_t): y position

        Returns:
            void
    */
    tft.fillCircle(x, y, 3, TFT_BLUE);
}

void displayRestaurantPoints() {
    /*
        Checks all restaurants to see if they are within the current map 
        patch (map coords converted to lon/lat) + >= selected rating
        and then displays points

        Arguments:
            None

        Returns:
            void
    */
    restaurant tempRest;
    int32_t mapLonWest = xToLon(mapX);
    int32_t mapLonEast = xToLon(mapX+MAP_DISP_WIDTH);
    int32_t mapLatNorth = yToLat(mapY);
    int32_t mapLatSouth = yToLat(mapY+MAP_DISP_HEIGHT);

    for (uint16_t i = 0; i < NUM_RESTAURANTS; i++) {
        getRestaurantFast(i, &tempRest);
        if ((tempRest.lon > mapLonWest && tempRest.lon < mapLonEast) &&
                (tempRest.lat > mapLatSouth && tempRest.lat < mapLatNorth) &&
                    (ratingChecker(tempRest.rating))) {
            int16_t restaurantX = lonToX(tempRest.lon) - mapX;
            int16_t restaurantY = latToY(tempRest.lat) - mapY;
            drawRestaurantPoint(restaurantX, restaurantY);
        }
    }
}


void updateRatingButton() {
    /*
        Draws new rating button based on selected or changed rating

        Arguments:
            None

        Returns:
            void
    */
    tft.fillRect(MAP_DISP_WIDTH, 0, 60, BUTTON_HEIGHT, TFT_WHITE);
    tft.drawRect(MAP_DISP_WIDTH, 0, 60, BUTTON_HEIGHT, TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(MAP_DISP_WIDTH+21, (DISPLAY_HEIGHT/4)-12);

    char ratingChars[] = {'5', '1', '2', '3', '4', '5'};
    tft.print(ratingChars[rating]);
}

void updateSortingButton() {
    /*
        Draws new sorting button based on selected or changed rating

        Arguments:
            None

        Returns:
            void
    */
    char qSortChars[] = {'Q', 'S', 'O', 'R', 'T', '\0'};
    char iSortChars[] = {'I', 'S', 'O', 'R', 'T', '\0'};
    char bothChars[] = {'B', 'O', 'T', 'H', '\0'};
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.fillRect(MAP_DISP_WIDTH, BUTTON_HEIGHT, 60, BUTTON_HEIGHT, TFT_WHITE);
    tft.drawRect(MAP_DISP_WIDTH, BUTTON_HEIGHT, 60, BUTTON_HEIGHT, TFT_GREEN);

    if (callSort == 1) {
        for (uint8_t i = 0; i < 5; i++) {
            tft.setCursor(MAP_DISP_WIDTH+21, (DISPLAY_HEIGHT*3/4)-(60)+(i*23));
            tft.print(qSortChars[i]);
        }

    } else if (callSort == 2) {
        for (uint8_t i = 0; i < 5; i++) {
            tft.setCursor(MAP_DISP_WIDTH+21, (DISPLAY_HEIGHT*3/4)-(60)+(i*23));
            tft.print(iSortChars[i]);
        }

    } else if (callSort == 0) {
        for (uint8_t i = 0; i < 4; i++) {
            tft.setCursor(MAP_DISP_WIDTH+21, (DISPLAY_HEIGHT*3/4)-(60)+(i*23));
            tft.print(bothChars[i]);
        }
    }
}


void processInput() {
    /*
        Checks joystick input to shift cursor and/or map patch, to show
        closest 21 restaurants, or to display all restaurants in patch

        Arguments:
            None

        Returns:
            void
    */

    // joystick input for cursor movement or switch to mode 1
    int16_t xVal = analogRead(JOY_HORIZ);
    int16_t yVal = analogRead(JOY_VERT);
    int16_t buttonVal = digitalRead(JOY_SEL);

    // calls 1 = qSort; calls 2 == iSort; calls 3 = both
    if (buttonVal == LOW) {
        tft.fillScreen(0);
        callSort %= 3;
        closestFinder();
        delay(300);
    }

    cursorMovement(xVal, yVal);

    // read touchscreen input for displaying restaurants on maps
    TSPoint touch = ts.getPoint();
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);

    if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {
        return;
    }

    int16_t screen_x = map(touch.y, TS_MINX, TS_MAXX, DISPLAY_WIDTH-1, 0);
    int16_t screen_y = map(touch.x, TS_MINY, TS_MAXY, MAP_DISP_HEIGHT-1, 0);

    // checks if map area or button is pressed
    if ((screen_x >= 0 && screen_x <= MAP_DISP_WIDTH)
            && (screen_y >= 0 && screen_y <= MAP_DISP_HEIGHT)) {
        displayRestaurantPoints();
        delay(100);

    } else if (screen_x > MAP_DISP_WIDTH && screen_x < DISPLAY_WIDTH) {
        if (screen_y >= 0 && screen_y < BUTTON_HEIGHT) {
            rating = (rating + 1) % 5;
            updateRatingButton();

        } else if (screen_y >= BUTTON_HEIGHT && screen_y < DISPLAY_HEIGHT) {
            callSort = (callSort + 1) % 3;
            updateSortingButton();
        }
        delay(300);
    }

    delay(20);
}

int main() {
    setup();
    while (true) {
        processInput();
    }

    Serial.flush();
    Serial.end();
    return 0;
}