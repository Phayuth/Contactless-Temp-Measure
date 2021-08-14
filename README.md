# Contactless Temperature Measure
Building a contactless temperrature measurement device with arduino

## List of Items

Arduino Nano | LCD I2C | GY-906 | Battery Pack | 9v Battery | Accessories |
------------ | ------------- | ------------- | ------------- | ------------- | ------------- |
<img src="https://www.gmelectronic.com/data/product/480_480/pctdetail.774-025.1.jpg" width="130" height="130">|<img src="https://www.aranacorp.com/wp-content/uploads/screen-lcd-16x2.jpg" width="130" height="130">|<img src="https://www.digitspace.com/image/cache/catalog/products/GY-906%20MLX90614ESF%20Infrared%20Temperature%20Sensor%20Module-1-694x696.jpg" width="130" height="130"> | <img src="https://m.media-amazon.com/images/I/61YfY85-y7L._AC_SL1500_.jpg" width="130" height="130">| <img src="https://webobjects2.cdw.com/is/image/CDW/5499085?$product-main$" width="130" height="130">| <ul><li>Wire</li><li>PCB</li><li>Case</li><li>Bolts and Nuts</li></ul>|

## Connection

<img src="https://github.com/Phayuth/IOT-Contactless-Temp-Measure/blob/main/connection_v1.png" width="60%">

## Code

1. Install library in Arduino IDE via Sketch → Include Library → Search for library
    - Adafruit MLX90614 Library
    - LiquidCrystal I2C

2. Upload Arduino Code from the Repo

-----------------------------------------------------------------------------------------------
# Kalman Filter Implementation
### Algorithm
<img src="https://www.researchgate.net/profile/Chun-Ho-Wu-2/publication/282604538/figure/fig2/AS:391415088599041@1470332037287/Kalman-filter-algorithm-15.png" width="60%">


### Code Implement
```c++
// Initial Value
float temp_amb = 28;
float temp_obj = 36;
float P = 1;
float Q = 0.1;
float R = 4;
float P_xz;
float P_zz;


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
```
