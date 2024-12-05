/*
Reinaldo Sabbagh and Nick Dorogy
*/
 
// libraries for SD card
#include <SD.h>
// libraries for Sensirion SDP810-25
#include <SensirionI2CSdp.h>
#include <Arduino.h>
#include <Wire.h>
 
// -------------------------------//
//              global            //
// -------------------------------//
const int samplerate = 1;            // [ms] define the sampling period
 
// -------------------------------//
//           init modules         //
// -------------------------------//
SensirionI2CSdp sdp;
 
// -------------------------------//
//          init SD card          //
// -------------------------------//
File dataFile;
 
// -------------------------------//
//       init sdp variables       //
// -------------------------------//
float sdpdfp = -999.0;
float sdptmp = -999.0;
 
// -------------------------------//
//       constant variables       //
// -------------------------------//
const float err = -999.0;
uint16_t error;
char errorMessage[256];
 
//----------------------------------------------------------------------------------//
//                                   MAINS FUNCS                                    //
//----------------------------------------------------------------------------------//
void setup(){
  Serial.begin(115200);
  while (!Serial){  delay(100); }
  // -------------------------------//
  //           init SD card         //
  // -------------------------------//
  // pinMode(10, OUTPUT);
  // if (!SD.begin(10)) {
  //   Serial.println("SD card initialization failed!");
  //   delay(100);
  //   return;
  // }
  // Serial.println("SD card initialized succesfully!");
 
  // dataFile = SD.open("data.txt", FILE_WRITE);
  // if (dataFile) {
  //   dataFile.print("sdpDiffP,");
  //   dataFile.println("sdpTemp,");
  //   // dataFile.flush();
  // } else {
  //   Serial.println("Couldn't open data file to print headers.");
  // }
  // -------------------------------//
  //            init SDP810         //
  // -------------------------------//
  Wire.begin();    
  sdp.begin(Wire, SDP8XX_I2C_ADDRESS_0);
  sdp.startContinuousMeasurementWithDiffPressureTCompAndAveraging();
  Serial.println("SDP810-25 configured.");
}
 
void loop() {
  collectData();
  delay(samplerate);
}
 
//----------------------------------------------------------------------------------//
//                                 CONTROL FUNCS                                    //
//----------------------------------------------------------------------------------//
void collectData() {
  diffP();
  // write();
  Serial.print(sdpdfp);
  Serial.print(",");
  Serial.println(sdptmp);
  Serial.flush();
}
 
//----------------------------------------------------------------------------------//
//                                 SUPPORT FUNCS                                    //
//----------------------------------------------------------------------------------//
void write() {
  dataFile.print('stupid');
  if (dataFile) {
    dataFile.print(sdpdfp);
    dataFile.print(",");
    dataFile.println(sdptmp);
    // dataFile.flush();
  } else {
    Serial.println("File is not open");
  }
}
 
void diffP() {
  // pressure and tempereature data from differential pressure sensor
  sdp.readMeasurement(sdpdfp, sdptmp);
}