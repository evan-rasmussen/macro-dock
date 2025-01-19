#include <User_Interface.h>

/*!
    @brief  Constructor for UI for I2C-interfaced SSD1306 displays.
    @param  w
            Display width in pixels
    @param  h
            Display height in pixels
    @param  twi
            Pointer to an existing TwoWire instance (e.g. &Wire, the
            microcontroller's primary I2C bus).
    @param  rst_pin
            Reset pin (using Arduino pin numbering), or -1 if not used
            (some displays might be wired to share the microcontroller's
            reset pin).
    @param  clkDuring
            Speed (in Hz) for Wire transmissions in SSD1306 library calls.
            Defaults to 400000 (400 KHz), a known 'safe' value for most
            microcontrollers, and meets the SSD1306 datasheet spec.
            Some systems can operate I2C faster (800 KHz for ESP32, 1 MHz
            for many other 32-bit MCUs), and some (perhaps not all)
            SSD1306's can work with this -- so it's optionally be specified
            here and is not a default behavior. (Ignored if using pre-1.5.7
            Arduino software, which operates I2C at a fixed 100 KHz.)
    @param  clkAfter
            Speed (in Hz) for Wire transmissions following SSD1306 library
            calls. Defaults to 100000 (100 KHz), the default Arduino Wire
            speed. This is done rather than leaving it at the 'during' speed
            because other devices on the I2C bus might not be compatible
            with the faster rate. (Ignored if using pre-1.5.7 Arduino
            software, which operates I2C at a fixed 100 KHz.)
    @return User_Interface object.
    @note   Call the object's begin() function before use -- buffer
            allocation is performed there!
*/
User_Interface::User_Interface() :
    display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

/*!
    @brief  Destructor for User_Interface object.
*/
User_Interface::~User_Interface(void)
{
}

bool User_Interface::initialize(void)
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }

    // clear any current buffer
    display.clearDisplay();

    // display startup screen
    displayStartupScreen();
    delay(2000);

    // load layer 1

    displayLayerMenu();
    return true;
}

// private

/**
 * @brief Displays the Layer Selection Menu, highlighting one of them
 * @param layer the layer number to highlight
 */
void User_Interface::displayLayerMenu(uint8_t layer)
{
    display.clearDisplay();

    uint8_t j = 1;
    for (uint8_t i = 0; i < 128; i += 32)
    {
        display.drawRoundRect(i, 1, 30, 30, 4, SSD1306_WHITE);
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(i + 10, 9);
        display.printf("%d", j);
        j++;
        if (layer == j - 1)
        {
            display.fillRoundRect(i, 1, 30, 30, 4, SSD1306_INVERSE);
        }
    }
    display.display();
}

/**
 * @brief Displays the startup screen
 */
void User_Interface::displayStartupScreen()
{
    display.clearDisplay();
    // 3 top lines
    display.drawLine(20, 4, 108, 4, SSD1306_WHITE);
    display.drawLine(10, 6, 118, 6, SSD1306_WHITE);
    display.drawLine(0, 8, 128, 8, SSD1306_WHITE);
    // Text
    display.setFont(&FreeMonoBoldOblique12pt7b);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 25);
    display.print(F("MacroDock"));
    // 3 bottom lines
    display.drawLine(0, 27, 128, 27, SSD1306_WHITE);
    display.drawLine(10, 29, 118, 29, SSD1306_WHITE);
    display.drawLine(20, 31, 108, 31, SSD1306_WHITE);

    display.display();

    // Set font back to default
    display.setFont();
}