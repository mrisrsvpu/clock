#ifndef _MAIN_H_
#define _MAIN_H_


#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <FS.h>

#include <DHT.h>
#include <Adafruit_BMP085.h>

#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ArduinoJson.h>


#include "settings.h"
#include "display.h"
#include "api.h"


struct measure_stat_t {
    uint64_t last_measure;
    float prevois_value;
    float current_value;
    bool initialized;
    bool error;
};

measure_stat_t temp_m, hum_m, press_m;


DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

settings_t settings;
String settings_filename = "/settings.json";

ESP8266WebServer server;
ESP8266HTTPUpdateServer updateServer;

typedef float (*measire_getter_t)();


bool init_wifi();
bool init_time();
bool init_sensors();
void get_measure(uint32_t ms, measure_stat_t& stat, measure_t& conf, measire_getter_t get);

void setup();
void loop();

float get_temperature();
float get_humidity();
float get_pressure();

void api_measures_get();

#endif // _MAIN_H_
