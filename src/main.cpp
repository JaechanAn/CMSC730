#include <Arduino.h>

/**
 * Constant definition
 */
const int ledPin = 2; // Default LED is connected to GPIO 2, check out the def of LED_BUILTIN
const int scale = 1;  // For debugging, increase to 10 gets you 10 times slow execution.

const int morseCode[10][5] = {
    {1, 1, 1, 1, 1}, // 0
    {0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 1, 1}, // 2
    {0, 0, 0, 1, 1}, // 3
    {0, 0, 0, 0, 1}, // 4
    {0, 0, 0, 0, 0}, // 5
    {1, 0, 0, 0, 0}, // 6
    {1, 1, 0, 0, 0}, // 7
    {1, 1, 1, 0, 0}, // 8
    {1, 1, 1, 1, 0}, // 9
};

/**
 * Function pre-definition
 */
void sendMorseCode(int);

void blinkLed(int);

// The setup() method runs once, when the sketch starts
void setup()
{
    // put your setup code here, to run once:
    pinMode(ledPin, OUTPUT); // initialize the digital pin as an output

    Serial.begin(9600);
}

// The loop() method runs over and over again, as long as the Arduino has power
void loop()
{
    if (Serial.available() > 0)
    {
        // Read the incoming byte
        char incomingByte = Serial.read();

        // Echo the incoming byte back to the serial monitor
        Serial.print("You entered: ");
        Serial.println(incomingByte);

        int idx = (int)(incomingByte) - (int)('0'); // this trick only works if the ascii code for numerics is continuous
        sendMorseCode(idx);
        delay(300 * scale);
    }
}

void sendMorseCode(int x)
{
    if (x < 0 || x > 9)
    {
        // Shouldn't happen
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        blinkLed(morseCode[x][i]);
        if (i != 4) // last one doesn't need to be delayed, it is delayed in the outer loop for between letters
        {
            delay(100 * scale); // space between parts of the same letter
        }
    }
}

void blinkLed(int x)
{
    digitalWrite(ledPin, HIGH);
    if (x == 0)
    {
        delay(100 * scale); // dot
    }
    else if (x == 1)
    {
        delay(300 * scale); // dash
    }
    digitalWrite(ledPin, LOW);
}