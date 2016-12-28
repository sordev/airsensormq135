// Calibration https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library
#include <Wire.h>

#include <LiquidCrystal.h> // includes the LiquidCrystal Library

#include <MQ135.h> // MQ 135 Library from https://github.com/GeorgK/MQ135
// #define RZERO 1678.59 This needs to be defined in library 

#include <DHT.h> // DHT 11 Library from https://github.com/adafruit/DHT-sensor-library required https://github.com/adafruit/Adafruit_Sensor 
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <DHT_U.h>

LiquidCrystal lcd(2,3,4,5,6,7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

int mq135pin = A0;
int mq135sensorValue;
//dht DHT;
MQ135 mq135gasSensor = MQ135(mq135pin);

void setup() {
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display }
  dht.begin();
}
void loop() {
  mq135sensorValue = analogRead(mq135pin);
  float mq135rzero = mq135gasSensor.getRZero();
  
  lcd.print("A0=" + (String)mq135sensorValue + " RES=" + (String)mq135gasSensor.getResistance() + " ");  
  lcd.setCursor(0, 2);
  lcd.print("RZERO=" + (String)mq135rzero + " ");
  delay(1000);

  lcd.clear();
  float co2_ppm = mq135gasSensor.getPPM();
  //Vrl = val * ( 5.00 / 1024.0  );      // V
  //Rs = 20000 * ( 5.00 - Vrl) / Vrl ;   // Ohm
  //ratio =  Rs/Ro;
  lcd.print("S0 CO2 ppm=" + (String)co2_ppm + "    ");
  delay(2000);
  
  lcd.clear(); // Clears the display
  float humidity0 = dht.readHumidity();
  float temp0 = dht.readTemperature();
  lcd.print( "Humidity=" + (String)humidity0 );
  lcd.setCursor(0, 2);
  lcd.print( "Temp=" + (String)temp0 );
  delay(1000);
  lcd.clear();
}
