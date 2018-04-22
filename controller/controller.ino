//https://www.arduino.cc/en/Reference/SPI
//https://www.arduino.cc/en/Tutorial/SPITransaction 
//http://arduino-er.blogspot.com/2014/09/communication-betweeen-arduinos-using.html
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*
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
int currentResolution = 0;
int numPixels;
char* pixels;


int getNumPixels() { 
  return resolutions[currentResolution][0] * 
         resolutions[currentResolution][1];
}
void setPixels(){
  numPixels = getNumPixels();
  if(pixels){
    free(pixels);
  }
  pixels = (char*)malloc(numPixels*3*sizeof(char));
}


void updateLCDScreen(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.write("Resolution:");
  lcd.setCursor(0,2);
  lcd.write(resolutions[currentResolution][0]);
  lcd.write("x");
  lcd.write(resolutions[currentResolution][1]);
}

void updateResolution(){
    currentResolution = (currentResolution + 1) % numResolutions;
    updateLCDScreen();
    setPixels();
    Serial.write(currentResolution);
}

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
    Serial.flush();
    int i = 0;
    while(Serial.available()){ //Read in pictures
      pixels[i++] = Serial.read();
    }
  }
}


void changeResolutionButton(){
  if(digitalRead(upResolutionButton)){
    while(!digitalRead(upResolutionButton)){} //Wait for release
    updateResolution();
  }
}


void setup(){
  Serial.begin(921600);  //link to PC

  pinMode(INPUT, captureButton);
  pinMode(INPUT, upResolutionButton);
  lcd.begin(16, 2);
  updateLCDScreen();
  Serial.write(currentResolution);
  Serial.flush();
  //Serial.println("Setup");
}


void loop(){
  //Check camera capture button
  cameraCaptureButton();


  //Check resolution change button
  changeResolutionButton();

}

