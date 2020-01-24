
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"


// Pin Definitions
#define DHT_PIN_DATA	2
#define OLED128X32_PIN_RST	3



// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);
#define SSD1306_LCDHEIGHT 32
Adafruit_SSD1306 oLed128x32(OLED128X32_PIN_RST);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    oLed128x32.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    oLed128x32.clearDisplay(); // Clear the buffer.
    oLed128x32.display();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2') {
    // Monochrome 128x32 I2C OLED graphic display - Test Code
    oLed128x32.setTextSize(1);
    oLed128x32.setTextColor(WHITE);
    oLed128x32.setCursor(0, 10);
    oLed128x32.clearDisplay();
    oLed128x32.println("Circuito.io Rocks!");
    oLed128x32.display();
    delay(1);
    oLed128x32.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x32.stopscroll();
    delay(1000);
    oLed128x32.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x32.stopscroll();
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) Monochrome 128x32 I2C OLED graphic display"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Monochrome 128x32 I2C OLED graphic display"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
