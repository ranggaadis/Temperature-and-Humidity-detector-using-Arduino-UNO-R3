#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 4;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2, 0);
  lcd.print("Temperature & Humidity");

  lcd.setCursor(6, 1);
  lcd.print("Detector");

  dht.begin();

  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed to read  ");
    lcd.setCursor(0, 1);
    lcd.print("from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print("%  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C  ");

  //heat index
  float hic = dht.computeHeatIndex(t, h, false);
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("  Heat Index  ");
  lcd.setCursor(0, 1);
  lcd.print("  ");
  lcd.print(hic);
  lcd.print((char)223);
  lcd.print("C    ");
  
}
