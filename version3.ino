#include <LiquidCrystal_I2C.h>     // include library for the LCD
#include "DHT.h"  // include library for the temperature and humidity sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and size

//Pin definitions
const int motionSensorPin = 2; //Diigtal pin connected to the motionsensor
const int UP = A1;              //analog pin connected to the button 1
const int DOWN = 4;             //Diigtal pin connected to the button 2
const int OK = 5;               //Diigtal pin connected to the button 3
const int PWSD = 6;             //Diigtal pin connected to the button 4
const int alarmPin = 7; //Diigtal pin connected to the buzzer
//const int led1Pin = 8; //Diigtal pin connected to the LED 1 for Motion dection indicator
const int led2Pin = 9; //Digital pin connected to the LED 2 for DHT11 indicator 
const int flamesensorPin = 10;  // Digital pin connected to Flame sensor
const int DHT11PIN = 11;          // DHT11 data pin connected to digital pin 2
//const int led3Pin = A3; //Digital pin connected to LED 3 for alarm
const int reedswitch1=3; //Digital pin for doorcontact1
const int reedswitch2=8; //Digital pin for doorcontact1
const int led4Pin=A0; //analog pin conncted to LED 5 for Presistor yellow
const int Presistor=A2; //ANALOG pin connected to photoresistor
const int led5Pin=A3; //analog pin for alarm red
//Threshold values for temperature and humdity, light
const float temperatureThreshold = 35.0;
const float humidityThreshold = 60.0;
int lightthreshold = 300;
#define DHTTYPE DHT11             // DHT type is DHT11
DHT dht(DHT11PIN, DHTTYPE);

//Variables to store the motion sensor state
boolean securityState = false;
byte password[4] = { 2, 3, 4, 1 };
byte counter_pos;
byte digitValue;
byte pswd[4];
boolean password_flag = false;

void setup() {
  Serial.begin(9600); //Initialize the SI
  lcd.init(); 
  lcd.begin(16, 2);           // Initialize the LCD
  lcd.backlight();            // Turn on the LCD backlight
  lcd.clear();
  dht.begin();
  pinMode(motionSensorPin, INPUT);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(PWSD, INPUT_PULLUP);
  pinMode(alarmPin, OUTPUT);
  //pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  //pinMode(led3Pin, OUTPUT);
  pinMode (led4Pin, OUTPUT);
  pinMode(flamesensorPin, INPUT);
  pinMode(reedswitch1, INPUT);
  pinMode(reedswitch2, INPUT);
  pinMode(Presistor, INPUT);
  pinMode(led5Pin, OUTPUT);

  //Initialize the alarm and LED
  digitalWrite(alarmPin, LOW);
  //digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  //digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);
  digitalWrite(led5Pin, LOW);
}

void loop() {
if (digitalRead(PWSD) == LOW) {
    password_flag = true;
    Serial.println("Enter 4-digit");
    counter_pos = 0;
    while (password_flag) {
      if (!digitalRead(UP)) {
        delay(25);
    if(!digitalRead(UP)){
          while (!digitalRead(UP)) {}
          digitValue++;
          if(digitValue>9) digitValue=0;
          Serial.println(digitValue);
    }
      }
      if (!digitalRead(DOWN)) {
        delay(25);
        if (!digitalRead(DOWN)) {
          while (!digitalRead(DOWN)) {}
          digitValue--;
          if(digitValue>9) digitValue=9;
          Serial.println(digitValue);
        }
      }
      if (!digitalRead(OK)) {
                delay(25);
        if (!digitalRead(OK)) {
          while (!digitalRead(OK)) {}
                pswd[counter_pos] = digitValue;
        counter_pos++;
        digitValue=0;
        Serial.println("counter="+String(counter_pos));
      }
      }
      if (counter_pos == 4) {
        Serial.println("Check Password");
        for(int i=0;i<4;i++){
          Serial.print(pswd[i]);
          Serial.print(" ");
        }
        Serial.println(" ");
        password_flag = false;
        Serial.println(memcmp(pswd,password,4));
        if (memcmp(pswd,password,4)==0) {
          securityState=!securityState;
          Serial.println(securityState);
          digitalWrite(9, securityState);
          Serial.println("Correct");
        }
          if (memcmp(pswd,password,4)!=0) {
          Serial.println("Incorrect");
        }
      }
    }
  }

  //If motion is detected and securityState is high, turn on the LED1
  if (digitalRead(motionSensorPin) == HIGH && securityState == true) {
    //digitalWrite(led1Pin, HIGH);
  } else {
    //digitalWrite(led1Pin, LOW);
  }

  // Read photoresistor value
int lightValue = analogRead(Presistor);
if (lightValue < lightthreshold)  {
  digitalWrite(led4Pin, HIGH);
  Serial.println("LIGHT IS ON");
  Serial.println(analogRead(Presistor));
  }else{
    digitalWrite(led4Pin, LOW);
     Serial.println("LIGHT IS OFF!");
     Serial.println(analogRead(Presistor));
      }
  // Read flame sensor value
  if (digitalRead(flamesensorPin) == HIGH)  {
  Serial.println("Fire!");
  }else{
  Serial.println("No Fire!");
      }
// Read  REEDSWITCH1 value
  if (digitalRead(reedswitch1) == LOW)  {
  Serial.println("DOOR1 CLOSED!");
  //digitalWrite(led5Pin, LOW);
  }else{
  Serial.println("DOOR1 OPEN!");
  //digitalWrite(led5Pin, HIGH);
      }
// Read  REEDSWITCH2 value
  if (digitalRead(reedswitch2) == HIGH)  {
  Serial.println("DOOR2 CLOSED!");
  }else{
  Serial.println("DOOR2 OPEN!");
      }

  // Read and display temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature();
  delay(1000);
  float humidity = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  if (temperature > temperatureThreshold or humidity > humidityThreshold && securityState == true) {
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
      }
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C "); 

   //If the any of the security system is violated, activate the alarm 
  if ((securityState == true) and ((digitalRead(motionSensorPin) == HIGH) or (temperature > temperatureThreshold) 
  or (humidity > humidityThreshold) or (digitalRead(flamesensorPin) == HIGH) or (digitalRead(reedswitch1) == HIGH) or (digitalRead(reedswitch2) == LOW)  )) {
    tone(alarmPin, 1000);
    digitalWrite(led5Pin, HIGH);
  } else {
    noTone(alarmPin);
    digitalWrite(led5Pin, LOW);
  }
  }
