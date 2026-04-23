//by : Nyoman Yudi Kurniawan
//for : TRSE - Undiksha - 2025
//www.aisi555.com

#include <SPI.h>
#include <LoRa.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"


// Define LoRa pins
#define LORA_CS_PIN 10
#define LORA_RST_PIN 9
#define LORA_DIO0_PIN 2

// OLED settings
#define I2C_ADDRESS 0x3C
#define RST_PIN -1

SSD1306AsciiWire oled;


unsigned long lastSendTime = 0; // Timer for sending data
int counter = 0;                // Counter value

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Callibri14);
  oled.clear();
  oled.println("Initializing...");
  
  // Initialize LoRa
  Serial.println("Initializing LoRa...");
  SPI.begin();
  LoRa.setPins(LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);

  if (!LoRa.begin(433E6)) { // Set frequency to 433 MHz
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully.");

  // Clear OLED oled
   oled.println("Lora TX Test Ready !");
}

void loop() {
  unsigned long currentTime = millis();

  // Send data every 10 seconds
  if (currentTime - lastSendTime >= 10000) {
    lastSendTime = currentTime;

    // Increment counter and send
    counter++;
    Serial.print("Sending counter: ");
    Serial.println(counter);

        // Update OLED oled
    oled.clear();
    oled.println("Transmiting Data:");
    oled.print("Counter: ");
    oled.println(counter);

    
    LoRa.beginPacket();
    LoRa.print(counter);
    LoRa.endPacket();
  }
}
