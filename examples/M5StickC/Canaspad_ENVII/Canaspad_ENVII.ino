#include <M5StickC.h>
#include <Canaspad.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SHT3X.h>

Canaspad api = Canaspad();

const char  ssid[]       = "WiFi_ssid";
const char  password[]   = "WiFi_pass";
const char* api_username = "user@mail.com";
const char* api_password = "password";


SHT3X sht30;
Adafruit_BMP280 bme;

String sensor_tmp;
String sensor_hum;
String sensor_press;
String sensor_housa;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

void setup() {
  M5.begin();
  
  Serial.begin(115200);
  
  if(not api.begin(ssid, password, 9, api_username, api_password)){
    Serial.println("Api Connection Faild");
    Serial.println(api.httpCode);
  }
  sensor_tmp = api.set("temp", "env2", "number", 3, true);
  sensor_hum = api.set("hum", "env2", "number", 3, true);
  sensor_press = api.set("press", "env2", "number", 3, true);
  sensor_housa = api.set("housa", "env2", "number", 3, true);
  Serial.print("sensor_temp Device_token : ");
  Serial.println(sensor_tmp);
  Serial.println(F("ENV Unit(SHT30 and BMP280) test..."));
  while (!bme.begin(0x76)){  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    M5.Lcd.println("Could not find a valid BMP280 sensor, check wiring!");
  }
}

void loop() {
  if (api.gettimestamp() % 60 == 0){
    pressure = bme.readPressure()/100;
    if(sht30.get()==0){
      tmp = sht30.cTemp;
      hum = sht30.humidity;
    }
    float housa = (100-hum)*(217*(6.1078*pow(10,(7.5*tmp/(tmp+237.3))))/(tmp+273.15))/100;
    Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  Pressure: %0.2fhPa\r\n", tmp, hum, pressure/100);
    api.add(String(tmp), sensor_tmp);
    api.add(String(hum), sensor_hum);
    api.add(String(pressure), sensor_press);
    api.add(String(housa), sensor_housa);

    if (api.send()) { 
      Serial.println(api.gettime());
      }
    else {
      int err_num = api.httpCode;
      Serial.print("Error on HTTP request!");
      Serial.println(err_num);
        
      }
    float res =  api.get(sensor_tmp);
    Serial.print("API RETURN DATA :");
    Serial.println(res);
    delay(10*1000);
  }
}