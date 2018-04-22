//https://www.arduino.cc/en/Reference/SPI
//https://www.arduino.cc/en/Tutorial/SPITransaction
//http://arduino-er.blogspot.com/2014/09/communication-betweeen-arduinos-using.html
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


/*
<<<<<<< HEAD
 * Buttons
 */
const int captureButton = 6;
const int upResolutionButton = 7;

/*
 * GPS Interface
 */
byte gpsSignal = 0x11;
 
/*
 * Camera Interface
*/
byte captureSignal = 0x10;
const int numResolutions = 9;
int resolutions[numResolutions][2] = { {160, 120}, {176,144}, {320, 240},
                                    {352, 288}, {640, 480}, {800, 600},
                                    {1024, 768}, {1280, 1024}, {1600, 1200}};
=======
   GPS data
*/
const int gpsSignal = 0x11;

/*
   Buttons
*/
const int captureButton = 7;
const int upResolutionButton = 8;

/*
   Camera Interface
*/
const int captureCode = 0x10;
const int numResolutions = 9;
int resolutions[numResolutions][2] = { {160, 120}, {176, 144}, {320, 240},
  {352, 288}, {640, 480}, {800, 600},
  {1024, 768}, {1280, 1024}, {1600, 1200}
};
>>>>>>> master
int currentResolution = 0;
int numPixels;
char* pixels;
int numBytes;


int getNumPixels() {
  return resolutions[currentResolution][0] *
         resolutions[currentResolution][1];
}
void setPixels() {
  numPixels = getNumPixels();
  if (pixels) {
    free(pixels);
  }
  numBytes = numPixels * 3;
  pixels = (char*)malloc(numBytes * sizeof(char));
}


void updateLCDScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Resolution:");
  lcd.setCursor(0, 1);

  lcd.print(resolutions[currentResolution][0]);
  lcd.print("x");
  lcd.print(resolutions[currentResolution][1]);
}

void updateResolution() {
  currentResolution = (currentResolution + 1) % numResolutions;
  updateLCDScreen();
  setPixels();
  Serial.write(currentResolution);
}

<<<<<<< HEAD
void cameraCaptureButton(){
  if(digitalRead(captureButton)){
    while(!digitalRead(cameraCaptureButton)){} //Wait for release

    //Get GPS data
    Serial.write(gpsSignal);

    while(!Serial.available()){} //Wait for signal
    double latitude = Serial.read();
    double longitude = Serial.read();



    //Get pictures
    Serial.write(captureSignal);
=======
void cameraCaptureButton() {
  //lcd.setCursor(14,0);
  int state = digitalRead(captureButton);
  //Serial.println(state);
  if (state) {
    while (digitalRead(captureButton)) {} //Wait for release
    //delay(10000);
    //Send GPS signal
    lcd.setCursor(14,0);
    
    Serial.write(gpsSignal);
    
    
    while (!Serial.available()) { Serial.println("Waiting for pauls code.."); }
    
    
    float lat = Serial.parseFloat();
    Serial.flush();
    
    while (!Serial.available()) {}
    float lon = Serial.parseFloat();
>>>>>>> master
    Serial.flush();

    lcd.setCursor(0, 0);
    lcd.print(lat);
    lcd.print(lon);


    //Send Camera Signal
    Serial.write(captureCode);
    //Serial.flush();
    int i = 0;
    //while(!Serial.available()){}
    //while (for ) { //Read in pictures
    for(i = 0; i < numBytes; i++){
      if(Serial.available()){
        pixels[i++] = Serial.read();
      }
    }
    Serial.flush();

  }
}


<<<<<<< HEAD
void changeResolutionButton(){
  if(digitalRead(upResolutionButton)){
    while(!digitalRead(upResolutionButton)){} //Wait for release
=======

void changeResolutionButton() {
  if (digitalRead(upResolutionButton)) {
    while (!digitalRead(upResolutionButton)) {} //Wait for release
>>>>>>> master
    updateResolution();
  }
}


void setup() {
  Serial.begin(921600);  //link to PC

  pinMode(INPUT, captureButton);
  pinMode(INPUT, upResolutionButton);
  lcd.begin(16, 2);
  updateLCDScreen();
  setPixels();

  Serial.write(currentResolution);
  //Serial.flush();
  //Serial.println("Setup");
}


void loop() {

  //Check camera capture button
  cameraCaptureButton();


  //Check resolution change button
  //changeResolutionButton();

}

