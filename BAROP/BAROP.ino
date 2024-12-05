/*
Code for the Arduino-based magnetometer.
Logs magnetic data and GPS data.

Reinaldo Sabbagh and Nick Dorogy 
*/

// libraries for GPS 
#include <SoftwareSerial.h> 
#include <TinyGPS++.h>
// libraries for SD card 
#include <SD.h>
// libraries for Adafruit BMP390
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <SPI.h>
// libraries for Adafruit AHT20 
#include <Adafruit_AHTX0.h>

// -------------------------------//
//              global            // 
// -------------------------------//
const int samplerate = 1000;            // [ms] define the sampling period

// -------------------------------//
//           init modules         // 
// -------------------------------//
TinyGPSPlus gps;
// Adafruit_BMP3XX bmpa;       // first BMP sensor 
Adafruit_BMP3XX bmpb;       // second BMP sensor 

// -------------------------------//
//           init SD card         // 
// -------------------------------//
File dataFile; 

// -------------------------------//
//       init gps variables       // 
// -------------------------------//
static const int RXPin = 4, TXPin = 3;  
SoftwareSerial gpsSerial(RXPin,TXPin); 
float lat = -999.0, lon = -999.0; 
int mm = -999.0, dd = -999.0, yy = -999.0; 
int h = -999.0, m = -999.0, s = -999.0, cs = -999.0;

// -------------------------------//
//       init sdp variables       // 
// -------------------------------//
float sdpdfp = -999.0;
float sdptmp = -999.0;

// -------------------------------//
//       init bmp variables       // 
// -------------------------------//
// #define BMP_SCKa 13
// #define BMP_MISOa 12
// #define BMP_MOSIa 11
// #define BMP_CSa 10
#define BMP_SCKb 9
#define BMP_MISOb 8
#define BMP_MOSIb 7
#define BMP_CSb 6
#define SEALEVELPRESSURE_HPA (1013.25) // [hPa] sea level pressure for calibration on EVERY use 
// float bmptmpa = -999.0;
// float bmpabpa = -999.0;
// float bmpalta = -999.0; 
float bmptmpb = -999.0;
float bmpabpb = -999.0;
float bmpaltb = -999.0; 

// -------------------------------//
//       constant variables       // 
// -------------------------------//
const float err = -999.0; 

//----------------------------------------------------------------------------------// 
//                                   MAINS FUNCS                                    // 
//----------------------------------------------------------------------------------// 
void setup(){
  Serial.begin(9600); 
  while (!Serial){  delay(100); }
  // gpsSerial.begin(9600);
  // while (!gpsSerial){  delay(100); }
  // Serial.println("GPS configured.");
  // -------------------------------//
  //           init SD card         // 
  // -------------------------------//
  delay(100);

  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed!");
    delay(100);
    return;
  }
  Serial.println("SD card initialized succesfully!");
  delay(5000); 

  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("lat,");
    dataFile.print("lon,");
    dataFile.print("month,");
    dataFile.print("day,");
    dataFile.print("year,");
    dataFile.print("hour,");
    dataFile.print("min,");
    dataFile.print("sec,"); 
    dataFile.print("centisec,");
    // dataFile.print("bmptTemp A,");
    // dataFile.print("bmpAbsP A,"); 
    // dataFile.print("bmpAlta A,");
    dataFile.print("bmptTemp B,");
    dataFile.print("bmpAbsP B,"); 
    dataFile.println("bmpAlta B");
    dataFile.flush(); 
  } else { 
    Serial.println("Couldn't open data file to print headers.");
  }
  // -------------------------------//
  //            init BMP390         // 
  // -------------------------------//
  // if (! bmpa.begin_SPI(BMP_CSa, BMP_SCKa, BMP_MISOa, BMP_MOSIa)) { while (1); }
  // bmpa.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  // bmpa.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  // bmpa.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  // bmpa.setOutputDataRate(BMP3_ODR_50_HZ);
  // Serial.println("BMP390 A configured.");
  if (! bmpb.begin_SPI(BMP_CSb, BMP_SCKb, BMP_MISOb, BMP_MOSIb)) { while (1); }
  bmpb.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmpb.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmpb.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmpb.setOutputDataRate(BMP3_ODR_50_HZ);
  Serial.println("BMP390 B configured.");
}

void loop() {
  collectData();
  delay(samplerate);
}

//----------------------------------------------------------------------------------// 
//                                 CONTROL FUNCS                                    // 
//----------------------------------------------------------------------------------// 
void collectData() {
  // ccs();
  diffP(); 
  // baroP(); 
  write();
  Serial.print(lat, 10);
  Serial.print(",");
  Serial.print(lon, 10);
  Serial.print(",");
  Serial.print(mm);
  Serial.print(",");
  Serial.print(dd);
  Serial.print(",");
  Serial.print(yy);
  Serial.print(",");
  Serial.print(h);
  Serial.print(",");
  Serial.print(m);
  Serial.print(",");
  Serial.print(s);
  Serial.print(",");
  Serial.print(cs);
  Serial.print(",");
  // Serial.print(bmptmpa);
  // Serial.print(",");
  // Serial.print(bmpabpa);
  // Serial.print(",");
  // Serial.print(bmpalta);
  // Serial.print(",");
  Serial.print(bmptmpb);
  Serial.print(",");
  Serial.print(bmpabpb);
  Serial.print(",");
  Serial.println(bmpaltb);
  Serial.flush();
}

//----------------------------------------------------------------------------------// 
//                                 SUPPORT FUNCS                                    // 
//----------------------------------------------------------------------------------// 
void write() {
  if (dataFile) {
    dataFile.print(lat, 10);
    dataFile.print(",");
    dataFile.print(lon, 10);
    dataFile.print(",");
    dataFile.print(mm);
    dataFile.print(",");
    dataFile.print(dd);
    dataFile.print(",");
    dataFile.print(yy);
    dataFile.print(",");
    dataFile.print(h);
    dataFile.print(",");
    dataFile.print(m);
    dataFile.print(",");
    dataFile.print(s);
    dataFile.print(",");
    dataFile.print(cs);
    // dataFile.print(",");
    // dataFile.print(bmptmpa);
    // dataFile.print(",");
    // dataFile.print(bmpabpa);
    // dataFile.print(",");
    // dataFile.print(bmpalta);
    dataFile.print(",");
    dataFile.print(bmptmpb);
    dataFile.print(",");
    dataFile.print(bmpabpb);
    dataFile.print(",");
    dataFile.println(bmpaltb);
    dataFile.flush();
  } else {
    Serial.println("File is not open");
  }
}

void ccs() {
  unsigned long start = millis();
  while (gpsSerial.available() > 0 && millis() - start < 100) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    lat = gps.location.lat();    
    lon = gps.location.lng(); 
  } else {
    lat = err; 
    lon = err; 
  }
  if (gps.date.isValid()){
    mm = gps.date.month(); 
    dd = gps.date.day(); 
    yy = gps.date.year(); 
  } else { 

  }
  if (gps.time.isValid()) {
    h = gps.time.hour();
    m = gps.time.minute();
    s = gps.time.second(); 
    cs= gps.time.centisecond(); 
  } else {
    h = err;
    m = err; 
    s = err; 
  }
}

void baroP(){
  // temperature, pressure, and altitude data from absolute pressure sensor 
  // bmpa.performReading();
  // bmptmpa = bmpa.temperature;                         // [C] degree temperature  
  // bmpabpa = bmpa.pressure / 100.0;                    // [hPa] pressure reading  
  // bmpalta = bmpa.readAltitude(SEALEVELPRESSURE_HPA);  // [m] approx altitude 

  bmpb.performReading();
  bmptmpb = bmpb.temperature;                         // [C] degree temperature  
  bmpabpb = bmpb.pressure / 100.0;                    // [hPa] pressure reading  
  bmpaltb = bmpb.readAltitude(SEALEVELPRESSURE_HPA);  // [m] approx altitude 
}
