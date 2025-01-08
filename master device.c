#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>
#endif
 
RH_ASK driver;
 
const int buttonPin = 2; // Define pin for the button
char letter = 'F'; // Initial letter mode
unsigned long previousMillis = 0;
const long interval = 5000; // Interval at which to send data (milliseconds)
const int redLedPin = 7;
const int blueLedPin = 8; 
void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);   
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
      ;
#endif
    pinMode(redLedPin, OUTPUT); // Set red LED pin as output
    pinMode(blueLedPin, OUTPUT); // Set blue LED pin as output
    pinMode(buttonPin, INPUT_PULLUP);
}
void loop()
{
    // Check the button state frequently
    if (digitalRead(buttonPin) == LOW) {
        delay(50); // Debounce delay
        if (digitalRead(buttonPin) == LOW) {
            // Toggle the letter
            letter = (letter == 'F') ? 'A' : 'F';
            while (digitalRead(buttonPin) == LOW); 
        }
      checkState(letter);
    }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        int sensorValue = analogRead(A0);
        float masterTemp = map(sensorValue, 0, 1023, 0, 100);
        Serial.print("Sent Master Temperature: ");
        Serial.print(masterTemp);
        Serial.println(" C");
        char msg[15]
        // Convert float to string and add letter
        dtostrf(masterTemp, 4, 2, msg); 
        strncat(msg, &letter, 1); 
        // Send the message
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
    }
}
void checkState(char letter){
  switch (letter){
    case 'F':
      digitalWrite(redLedPin, HIGH); // Turn on red LED
      digitalWrite(blueLedPin, LOW); // Turn off blue LED
      break;
    case 'A':
      digitalWrite(redLedPin, LOW); // Turn off red LED
      digitalWrite(blueLedPin, HIGH); // Turn on blue LED
      break;
  }
}
 
 
