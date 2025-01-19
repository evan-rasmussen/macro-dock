#include <Arduino.h>
#include <User_Interface.h>

User_Interface ui;

// put function declarations here:
int myFunction(int, int);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate ui voltage from 3.3V internally
    if (!ui.initialize())
    {
        Serial.println(F("UI initialization failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    else
    {
        Serial.println(F("UI Initialized!"));
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(1000);
    int result = myFunction(2, 3);
    Serial.println(result);
}

// put function definitions here:
int myFunction(int x, int y)
{
    return x + y;
}