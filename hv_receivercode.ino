/*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// Must match the transmitter's struct exactly
struct SensorData {
    int x4;
    int x5;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  Serial.println("Receiver ready. Waiting for data...");
}

void loop() {
  if (radio.available()) {
    SensorData receivedData;
    radio.read(&receivedData, sizeof(receivedData));
    
    Serial.print("Received - A4: ");
    Serial.print(receivedData.x4);
    Serial.print(", A5: ");
    Serial.println(receivedData.x5);
  }
}