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

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor to open

  // Initialize OLED

  Wire.begin();
  Wire.setClock(400000L);
  
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
   oled.println("Lora RX Test Ready !");
   delay(2000);
}

void loop() {
  // Check for incoming LoRa packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read the packet
    String incomingData = "";
    while (LoRa.available()) {
      incomingData += (char)LoRa.read();
    }

    // Get RSSI
    int rssi = LoRa.packetRssi();

    // oled data on serial monitor
    Serial.print("Received counter: ");
    Serial.println(incomingData);
    Serial.print("RSSI: ");
    Serial.println(rssi);

    // Update OLED oled
    oled.clear();
    oled.println("Received Data:");
    oled.print("Counter: ");
    oled.println(incomingData);
    oled.print("RSSI: ");
    oled.print(rssi);
    oled.println(" dBm");
  }
}
