// Calibration https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
#include <MQ135.h> // MQ 135 Library from https://github.com/GeorgK/MQ135
#include <Wire.h>
#include <DHT.h> // DHT 11 Library from https://github.com/adafruit/DHT-sensor-library required https://github.com/adafruit/Adafruit_Sensor 
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <DHT_U.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

int pin0 = A0;
int pin1 = A1;
int sensorValue0;
int sensorValue1;
//dht DHT;
MQ135 gasSensor0 = MQ135(pin0);
MQ135 gasSensor1 = MQ135(pin1);

void setup() {
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display }
  dht.begin();
}
void loop() {
  sensorValue0 = analogRead(pin0);
  sensorValue1 = analogRead(pin1);
  lcd.print("A0=" + (String)sensorValue0 + " Resis=" + (String)gasSensor0.getResistance() + " ");
  lcd.setCursor(0, 2);
  lcd.print("A1=" + (String)sensorValue1 + " Resis=" + (String)gasSensor1.getResistance() + " ");
  delay(4000);

  lcd.clear();
  float rzero0 = gasSensor0.getRZero();
  float rzero1 = gasSensor1.getRZero();
  lcd.print("S0 RZERO=" + (String)rzero0 + " ");
  lcd.setCursor(0, 2);
  lcd.print("S1 RZERO=" + (String)rzero1 + " ");
  delay(4000);

  lcd.clear();
  float co2_ppm0 = gasSensor0.getPPM();
  float co2_ppm1 = gasSensor1.getPPM();
  int ppm0 = co2_ppm0 / 4;
  int ppm1 = co2_ppm1 / 4;
  //Vrl = val * ( 5.00 / 1024.0  );      // V
  //Rs = 20000 * ( 5.00 - Vrl) / Vrl ;   // Ohm
  //ratio =  Rs/Ro;
  lcd.print("S0 CO2 ppm=" + (String)co2_ppm0 + "    ");
  lcd.setCursor(0, 2);
  lcd.print("S1 CO2 ppm=" + (String)co2_ppm1 + "    ");
  delay(4000);
  
  lcd.clear(); // Clears the display
  float humidity0 = dht.readHumidity();
  float temp0 = dht.readTemperature();
  lcd.print( "Humidity=" + (String)humidity0 );
  lcd.setCursor(0, 2);
  lcd.print( "Temp=" + (String)temp0 );
  delay(4000);
  lcd.clear();
}
