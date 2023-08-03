
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
#define LEDPIN5 12            // LED 5 digital pin connected to digital pin 12
#define REEDSWITCHPIN 10      // Mini reed switch digital pin connected to digital pin 9
#define REEDSWITCHPIN2 A2        // Button 2 digital pin connected to digital pin 11
#define BUTTONPIN1 9        // Button 1 digital pin connected to digital pin 10
#define BUTTONPIN2 11        // Button 2 digital pin connected to digital pin 11


//#define BUTTONPIN3 12        // Button 3 digital pin connected to digital pin 12
//#define BUTTONPIN4 13        // Button 4 digital pin connected to digital pin 13

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and size

int threshold = 100; // analog input trigger level from photoresistor
char buttonstatus = "0000" ;


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
pinMode(LEDPIN5, OUTPUT); //Set LED 5 pin as output
pinMode(BUZZERPIN, OUTPUT); // Set buzzer pin as output
pinMode(REEDSWITCHPIN, INPUT); // Set mini reed switch pin as input with internal pull-up resistor
pinMode(REEDSWITCHPIN2, INPUT); // Set mini reed switch pin as input with internal pull-up resistor
pinMode(PIRPIN, INPUT);     // Set PIR sensor pin as input
pinMode(BUTTONPIN1, INPUT_PULLUP); // Set button 1 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN2, INPUT_PULLUP); // Set button 2 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN3, INPUT_PULLUP); // Set button 3 pin as input with internal pull-up resistor
//pinMode(BUTTONPIN4, INPUT_PULLUP); // Set button 4 pin as input with internal pull-up resistor
pinMode(FLAME, INPUT);
}

void loop() 
  
  {
// Read temperature and humidity from DHT11 sensor
float temperature = dht.readTemperature();
float humidity = dht.readHumidity();
lcd.setCursor(0, 0);
lcd.print("Temp: ");
lcd.print(temperature);
lcd.print("C");
lcd.setCursor(0, 1);
lcd.print("Humidity: ");
lcd.print(humidity);
lcd.print("%");

if (temperature > 30 or humidity > 70) {
    digitalWrite(LEDPIN1, HIGH);
  } else {
    digitalWrite(LEDPIN1, LOW);
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
  Serial.println("Fire!");
  }else{
    digitalWrite(LEDPIN2, LOW);
     Serial.println("No Fire!");
      }
    
// Read PIR sensor value
if (digitalRead(PIRPIN) == HIGH)  {
  digitalWrite(LEDPIN3, HIGH);
  Serial.println("Motion Detected!");
  }else{
    digitalWrite(LEDPIN3, LOW);
     Serial.println("NO Motion!");
      }
// Read DOOR STATUS 1
if (digitalRead(REEDSWITCHPIN)   == 1 )  {
  digitalWrite(LEDPIN4, HIGH);
  Serial.println("Door 1 Open!");
  }else{
    digitalWrite(LEDPIN4, LOW);
     Serial.println("Door 1 CLOSED!");
      }

// Read DOOR STATUS 2
if (digitalRead(REEDSWITCHPIN2)   == 0 )  {
  digitalWrite(LEDPIN4, HIGH);
  Serial.println("Door 2 OPEN!");
  }else{
    digitalWrite(LEDPIN4, LOW);
     Serial.println("Door 2 CLOSED!");
      }

// Read photoresistor value
int lightValue = analogRead(PHOTOPIN);
if (lightValue > threshold)  {
  digitalWrite(LEDPIN5, LOW);
  Serial.println("LIGHT IS OFF");
  Serial.println(analogRead(PHOTOPIN));
  }else{
    digitalWrite(LEDPIN5, HIGH);
     Serial.println("LIGHT IS ON!");
     Serial.println(analogRead(PHOTOPIN));
      }
//Security password implementation


 {
   int buttonStatus = digitalRead(BUTTONPIN1);
   Serial.println(buttonStatus);
   delay(50);

if ((temperature > 30 or humidity > 70)  or (digitalRead(FLAME) == HIGH) or (digitalRead(PIRPIN) == HIGH) or digitalRead(REEDSWITCHPIN) == 1 or digitalRead(REEDSWITCHPIN2) == 0   ) {
  tone(BUZZERPIN, 100);
  Serial.println("Alarm triggered!");
}else{
  noTone(BUZZERPIN);
}}}


//if (BUTTONPIN1 or BUTTONPIN2 = HIGH )  {
  //digitalWrite(LEDPIN5, HIGH);
