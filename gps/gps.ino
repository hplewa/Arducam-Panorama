#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
float lat = 28.5458, lon = 77.1703; // create variable for latitude and longitude object
SoftwareSerial gpsSerial(3, 4); //rx,tx


//LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
//initialize LCD board and constants
const int rs = 12, en = 11, d4 = 5, d5 = 6, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ledPin = 8;
int x = 0;

TinyGPS gps; // create gps object
void setup() {
  Serial.begin(921600); // connect serial
  //Serial.println("The GPS Received Signal:");
  gpsSerial.begin(9600); // connect gps sensor
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
}
void loop() {

//while (Serial.read() != 0x11) {}
  while (Serial.read() != 0x11) {
    
//    if (x==0) {
//    digitalWrite(ledPin, HIGH);
//  }
//
//  if (x==1) {
//    digitalWrite(ledPin, LOW);
//  }
  
    }

  if (x==0) {
    x=1;
    //digitalWrite(ledPin, HIGH);
  }

  if (x==1) {
    x=0;
    //digitalWrite(ledPin, LOW);
  }

  //while ((!Serial.available()) || (Serial.read() != 0x11)){}

  while (gpsSerial.available()) { // check for gps data
    if (gps.encode(gpsSerial.read())) // encode gps data
    {
      gps.f_get_position(&lat, &lon); // get latitude and longitude
      // display position
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("GPS Signal");
      //Serial.print("Position: ");
      //Serial.print("Latitude:");
      //Serial.print(lat,6);
      //Serial.print(";");
      //Serial.print("Longitude:");
      //Serial.println(lon,6);
      lcd.setCursor(1, 0);
      lcd.print("LAT:");
      lcd.setCursor(5, 0);
      lcd.print(lat);
      //Serial.print(lat);
      //Serial.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(",LON:");
      lcd.setCursor(5, 1);
      lcd.print(lon);
    }
  }
  String latitude = String(lat, 6);
  String longitude = String(lon, 6);
  //Serial.println(latitude+";"+longitude);


  Serial.println(latitude);
  Serial.println(longitude);
digitalWrite(ledPin, HIGH);
delay(1000);
digitalWrite(ledPin, LOW);
  lcd.setCursor(0, 0);
  //lcd.print(latitude+";"+longitude);
  lcd.print(latitude);
  lcd.setCursor(0, 1);
  lcd.print(longitude);
  //delay(1000);
}
