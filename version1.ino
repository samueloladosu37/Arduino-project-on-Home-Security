
#include <LiquidCrystal_I2C.h>     // include library for the LCD
#include "DHT.h"  // include library for the temperature and humidity sensor


#define DHTPIN 2             // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11   
#define FLAME 13          // Flame sensor analog pin connected to analog pin A0
#define PIRPIN 3             // PIR sensor digital pin connected to digital pin 3
#define PHOTOPIN A1          // Photoresistor analog pin connected to analog pin A1
#define BUZZERPIN 4          // Buzzer digital pin connected to digital pin 4
#define LEDPIN1 5            // LED 1 digital pin connected to digital pin 5
#define LEDPIN2 6            // LED 2 digital pin connected to digital pin 6
#define LEDPIN3 7            // LED 3 digital pin connected to digital pin 7
#define LEDPIN4 8            // LED 4 digital pin connected to digital pin 8
#define REEDSWITCHPIN 9      // Mini reed switch digital pin connected to digital pin 9
#define BUTTONPIN1 10        // Button 1 digital pin connected to digital pin 10
#define BUTTONPIN2 11        // Button 2 digital pin connected to digital pin 11
//#define BUTTONPIN3 12        // Button 3 digital pin connected to digital pin 12
//#define BUTTONPIN4 13        // Button 4 digital pin connected to digital pin 13

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and size
//const int flamesensorMin = 0; // sensor minimum
//const int flamesensorMax = 0; // sensor maximum

void setup() {
Serial.begin(9600);
lcd.init(); 
lcd.begin(16, 2);           // Initialize the LCD
lcd.backlight();            // Turn on the LCD backlight
lcd.clear();
pinMode(LEDPIN1, OUTPUT);   // Set LED 1 pin as output
pinMode(LEDPIN2, OUTPUT);   // Set LED 2 pin as output
pinMode(LEDPIN3, OUTPUT);   // Set LED 3 pin as output
pinMode(LEDPIN4, OUTPUT);   // Set LED 4 pin as output
pinMode(BUZZERPIN, OUTPUT); // Set buzzer pin as output
pinMode(REEDSWITCHPIN, INPUT_PULLUP); // Set mini reed switch pin as input with internal pull-up resistor
pinMode(PIRPIN, INPUT);     // Set PIR sensor pin as input
pinMode(BUTTONPIN1, INPUT_PULLUP); // Set button 1 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN2, INPUT_PULLUP); // Set button 2 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN3, INPUT_PULLUP); // Set button 3 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN4, INPUT_PULLUP); // Set button 4 pin as input with internal pull-up resistor
pinMode(FLAME, INPUT);
}

void loop() {
// Read temperature and humidity from DHT11 sensor
int temperature = dht.readTemperature();
int humidity = dht.readHumidity();
lcd.setCursor(0, 0);
lcd.print("Temp: ");
lcd.print(temperature);
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("Humidity: ");
lcd.print(humidity);
lcd.print("%");

if (temperature > 24 or humidity > 60) {
    digitalWrite(LEDPIN1, HIGH);
    //tone(BUZZERPIN,1000);
  } else {
    digitalWrite(LEDPIN1, LOW);
    //noTone(BUZZERPIN);
      }
Serial.print("Humidity: ");
Serial.print(humidity);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.println(" *C ");

// Read flame sensor value
if (digitalRead(FLAME) == HIGH)  {
  digitalWrite(LEDPIN2, HIGH);
  //noTone(BUZZERPIN);
  Serial.println("Fire!");
  }else{
    digitalWrite(LEDPIN2, LOW);
    //tone(BUZZERPIN, 1000);
     Serial.println("NO Fire!");
      }
    
//Activate alarm
if ((temperature > 24 or humidity > 60) or (digitalRead(FLAME) == HIGH) or (digitalRead(PIRPIN) == HIGH) or (digitalRead(REEDSWITCHPIN) == LOW) ) {
  tone(BUZZERPIN, 1000);
}else{
  noTone(BUZZERPIN);
      }


// Read PIR sensor value
if (digitalRead(PIRPIN) == HIGH)  {
  digitalWrite(LEDPIN3, HIGH);
  //noTone(BUZZERPIN);
  Serial.println("Motion Detected!");
  }else{
    digitalWrite(LEDPIN3, LOW);
    //tone(BUZZERPIN, 1000);
     Serial.println("NO Motion!");
      }

// Read mini reed switch state
if (digitalRead(REEDSWITCHPIN) == LOW)  {
  digitalWrite(LEDPIN4, LOW);
  //noTone(BUZZERPIN);
  Serial.println("Door Closed!");
  }else{
    digitalWrite(LEDPIN4, HIGH);
    //tone(BUZZERPIN, 1000);
     Serial.println("Door Open!");
      }}

// Read photoresistor value
//int lightValue = analogRead(PHOTOPIN);


