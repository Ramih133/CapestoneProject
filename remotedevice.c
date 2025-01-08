#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
 
RH_ASK driver;
 
const int redLedPin = 7; // Define pin for red LED
const int greenLedPin = 8; // Define pin for blue LED
 
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
    pinMode(greenLedPin, OUTPUT); // Set green LED pin as output
}
void loop()
{
    int sensorValue = analogRead(A0);
    float remoteTemp = map(sensorValue, 0, 1023, 0, 100);
 
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        // Message with a good checksum received
        // Convert buf to a string
        buf[buflen] = '\0'; // Null-terminate the string
 
        // Separate the letter from the float value
        char receivedMsg[15];
        strncpy(receivedMsg, (char *)buf, buflen - 1); // Copy the float part
        receivedMsg[buflen - 1] = '\0'; // Null-terminate the float part
 
        char receivedLetter = buf[buflen - 1]; // Extract the letter
 
        // If you need to convert the received string back to a number (e.g., float)
        float receivedTemp = atof(receivedMsg);
 
        Serial.print("Received Master Temperature: ");
        Serial.print(receivedTemp);
        Serial.println(" C");
 
        Serial.print("Received Mode: ");
        Serial.println(receivedLetter);
 
        Serial.print("Internal Temperature: ");
        Serial.print(remoteTemp);
        Serial.println(" C");
 
        checkTemp(remoteTemp, receivedTemp, receivedLetter);
    }
}
void checkTemp(float remoteTemp, float receivedTemp, char receivedLetter)
{
    if (remoteTemp > receivedTemp && receivedLetter=='A')
    {
        digitalWrite(redLedPin, LOW); // Turn on red LED
        digitalWrite(greenLedPin, HIGH); // Turn off green LED
    }
    else if (remoteTemp < receivedTemp && receivedLetter=='A')
    {
        digitalWrite(redLedPin, HIGH); // Turn off red LED
        digitalWrite(greenLedPin, LOW); // Turn on green LED
    }else if (remoteTemp > receivedTemp && receivedLetter=='F')
    {
        digitalWrite(redLedPin, HIGH); // Turn off red LED
        digitalWrite(greenLedPin, LOW); // Turn on green LED
    }else if (remoteTemp < receivedTemp && receivedLetter=='F')
    {
        digitalWrite(redLedPin, LOW); // Turn off red LED
        digitalWrite(greenLedPin, HIGH); // Turn on green LED
    }
    else
    {
        digitalWrite(redLedPin, LOW); // Turn off red LED
        digitalWrite(greenLedPin, LOW); // Turn off blue LED
    }
}
 
