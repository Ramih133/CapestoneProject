{\rtf1\ansi\ansicpg1252\cocoartf2818
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\froman\fcharset0 Times-Bold;\f1\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue0;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c0;}
\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\sl285\sa213\partightenfactor0

\f0\b\fs26\fsmilli13333 \cf2 \expnd0\expndtw0\kerning0
#include <RH_ASK.h>
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #ifdef RH_HAVE_HARDWARE_SPI
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #include <SPI.h> // Not actually used but needed to compile
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #endif
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 RH_ASK driver;
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 const int redLedPin = 7; // Define pin for red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 const int greenLedPin = 8; // Define pin for blue LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 void setup()
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #ifdef RH_HAVE_SERIAL
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 Serial.begin(9600); 
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #endif
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 if (!driver.init())
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #ifdef RH_HAVE_SERIAL
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.println("init failed");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #else
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 ;
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 #endif
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 pinMode(redLedPin, OUTPUT); // Set red LED pin as output
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 pinMode(greenLedPin, OUTPUT); // Set green LED pin as output
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 void loop()
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 int sensorValue = analogRead(A0);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 float remoteTemp = map(sensorValue, 0, 1023, 0, 100);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 uint8_t buflen = sizeof(buf);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 if (driver.recv(buf, &buflen)) // Non-blocking
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 // Message with a good checksum received
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 // Convert buf to a string
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 buf[buflen] = '\\0'; // Null-terminate the string
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 // Separate the letter from the float value
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 char receivedMsg[15];
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 strncpy(receivedMsg, (char *)buf, buflen - 1); // Copy the float part
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 receivedMsg[buflen - 1] = '\\0'; // Null-terminate the float part
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 char receivedLetter = buf[buflen - 1]; // Extract the letter
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 // If you need to convert the received string back to a number (e.g., float)
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 float receivedTemp = atof(receivedMsg);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.print("Received Master Temperature: ");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.print(receivedTemp);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.println(" C");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.print("Received Mode: ");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.println(receivedLetter);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.print("Internal Temperature: ");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.print(remoteTemp);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 Serial.println(" C");
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 checkTemp(remoteTemp, receivedTemp, receivedLetter);
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 void checkTemp(float remoteTemp, float receivedTemp, char receivedLetter)
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 if (remoteTemp > receivedTemp && receivedLetter=='A')
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(redLedPin, LOW); // Turn on red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(greenLedPin, HIGH); // Turn off green LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 else if (remoteTemp < receivedTemp && receivedLetter=='A')
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(redLedPin, HIGH); // Turn off red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(greenLedPin, LOW); // Turn on green LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}else if (remoteTemp > receivedTemp && receivedLetter=='F')
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(redLedPin, HIGH); // Turn off red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(greenLedPin, LOW); // Turn on green LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}else if (remoteTemp < receivedTemp && receivedLetter=='F')
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(redLedPin, LOW); // Turn off red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(greenLedPin, HIGH); // Turn on green LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 else
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \{
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(redLedPin, LOW); // Turn off red LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0\'a0\'a0\'a0\'a0 digitalWrite(greenLedPin, LOW); // Turn off blue LED
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0\'a0\'a0 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \}
\f1\b0\fs29\fsmilli14667 \

\f0\b\fs26\fsmilli13333 \'a0
\f1\b0\fs29\fsmilli14667 \
}