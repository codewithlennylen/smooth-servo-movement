#include <Arduino.h>
#include <Servo.h>

// Servo connected to pin 8 on the MEGA 2560 [PWM]
int signalPin = 8;

// Potentiometer to control the Servo
int potentiometer = A0;

// Create a Servo instance
Servo myServo;

int value;
int potValue;
float valueSmoothed;
float valuePrevious;

void setup()
{
  // set up Servo instance
  myServo.attach(signalPin);
  Serial.begin(9600);
}

void loop()
{

  // Reading ranges from 0 to 1023
  potValue = analogRead(potentiometer);

  // Map the reading to the Servo's range
  value = map(potValue, 0, 1023, 0, 180);

  //* SMOOTHING

  valueSmoothed = (value * 0.05) + (valuePrevious * 0.95);
  valuePrevious = valueSmoothed;

  //* END OF SMOOTHING

  // you can use Arduino's Serial Plotter to view the data.
  Serial.print(potValue);
  Serial.print(" --- ");
  Serial.print(value);
  Serial.print(" --- ");
  Serial.println(valueSmoothed);

  // Write the smoothed value to the Servo instance.
  myServo.write(valueSmoothed);

  delay(10);
}