#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define I2C_ADDR 0x27 //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3 // Declaring LCD Pins
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

// Initial Value
float temp_amb = 28;
float temp_obj = 36;
float P = 1;
float Q = 0.1;
float R = 4;
float P_xz;
float P_zz;

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  mlx.begin();
  lcd.begin (16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH); //Lighting backlight
  lcd.home ();
}

void loop() {
  //Loading...........................
  lcd.setCursor(0, 0);
  lcd.print("Reading...");
  lcd.setCursor(0, 1);
  lcd.print("in 5");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 4");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 3");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 2");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in 1");
  delay(1000);
  lcd.clear();
  

  // Kalman Filter
    // Time Update
  temp_amb = temp_amb;
  temp_obj = temp_obj;
  P = P + Q;

    // Measurement Update
  P_xz = P;
  P_zz = P + R;

  temp_amb = temp_amb + (P_xz/P_zz)*(mlx.readAmbientTempC()-temp_amb);
  temp_obj = temp_obj + (P_xz/P_zz)*(mlx.readObjectTempC()-temp_obj);

  P = P - (P_xz*P_xz)/P_zz;
  
  //Print to lcd
  lcd.setCursor(0, 0);
  lcd.print("Ambient ");
  lcd.print(String(temp_amb));
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Target  ");
  lcd.print(String(temp_obj));
  lcd.print(" C");

  delay(5000);
  lcd.clear();
}
