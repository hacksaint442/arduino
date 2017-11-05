//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

#include <SimpleDHT.h>

// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11;


// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int state = 1;

void initLCD();
void initDHT();
void getConditions(byte* temperature, byte* humidity);
void writeConditions(byte temperature, byte humidity);

void setup() {
  initLCD();
  initDHT();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  Serial.println("=================================");
  byte temperature = 0;
  byte humidity = 0;
  getConditions(&temperature, &humidity);
  writeConditions(temperature, humidity);
  Serial.println("Sleeping until next sample.");
  delay(5000);
}

void initDHT(){
  Serial.begin(9600);
}

void initLCD() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
}

void getConditions(byte* temperature, byte* humidity){
  Serial.println("Sample DHT11...");

  // read with raw sample data.
  //byte temperature = 0;
  //byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, temperature, humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }

  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");

  Serial.print("Sample OK: ");
  Serial.print((int)*temperature); Serial.print(" *C, ");
  Serial.print((int)*humidity); Serial.println(" %");

}

void writeConditions(byte temperature, byte humidity){
  Serial.println("Updating display...");
  lcd.setCursor(0, 0);
  lcd.print("Temp / *C: ");
  lcd.setCursor(11, 0);
  lcd.print((int)temperature);
  lcd.setCursor(0, 1);
  lcd.print("Humidity / %: ");
  lcd.setCursor(14, 1);
  lcd.print((int)humidity);

  /*lcd.clear();
  if (state == 0){
    lcd.setCursor(0, 0);
    lcd.print("Anna is lovely!");
    lcd.setCursor(0, 1);
    lcd.print("Leo is awesome!");
    state = 1;
  }
  else{
    if (state == 1){
      lcd.setCursor(0, 0);
      lcd.print("Leo is awesome!");
      lcd.setCursor(0, 1);
      lcd.print("Heidi is cool!");
      state = 2;
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print("Heidi is cool!");
      lcd.setCursor(0, 1);
      lcd.print("Anna is lovely!");
      state = 0;
    }
  }*/
}
