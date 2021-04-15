#include "Wire.h"
#include "Adafruit_LiquidCrystal.h" // Install LCD Display I2C
#include "Adafruit_MLX90614.h"      // Install Library MLX90614

Adafruit_LiquidCrystal lcd(0);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float target_temp;
float ambient_temp;
int button;

void setup() {
  mlx.begin();
  lcd.begin(16, 2);   // set up the LCD's number of rows and columns:
  pinMode(10, OUTPUT); // laser diode
  pinMode(9, INPUT); // read button digital
  lcd.setBacklight(HIGH);
}

void loop() {
  button = digitalRead(9);// button read
  if (button == 1) {
    digitalWrite(10, HIGH);
    target_temp = mlx.readObjectTempC();
    ambient_temp = mlx.readAmbientTempC();
    lcd.setCursor(0, 0);   // set the cursor to column 0, line 0  row1
    lcd.print(String(target_temp));
    lcd.setCursor(0, 1);   // set the cursor to column 0, line 1  row2
    lcd.print(String(ambient_temp));
  }
  else {
    lcd.setCursor(0, 0);   // set the cursor to column 0, line 0  row1
    lcd.print("Press Reading");
    lcd.setCursor(0, 1);   // set the cursor to column 0, line 1  row2
    lcd.print("Press Reading");
  }
}
