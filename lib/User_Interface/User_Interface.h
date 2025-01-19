#ifndef _User_Interface_H_
#define _User_Interface_H_

/// Includes Base
#include <Wire.h>
/// Includes External
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>

/// Defines
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

/**
 * @brief Class that stores the state of and controls for the display
 */
class User_Interface
{
  public:
    User_Interface(void);
    ~User_Interface(void);

    bool initialize(void);

  private:
    Adafruit_SSD1306 display;

    uint8_t currLayer;

    void displayLayerMenu(uint8_t layer = 0u);
    void displayStartupScreen(void);
};

#endif