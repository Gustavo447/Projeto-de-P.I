//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <DHT.h>    // Install DHT11 Library and Adafruit Unified Sensor Library


#define FIREBASE_HOST "dht11weatherstat-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "MndtKRC4Ul2PHfZrCdmjmOIVxqAh7kYP3n9cHUJb"

#define WIFI_SSID "Wlan.net(JAIRO)"
#define WIFI_PASSWORD "29387298"

#define DHTPIN D3    // Connect Data pin of DHT to D3
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;


void setup()
{

  Serial.begin(115200);

  dht.begin();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  //Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

   String fireHumid = String(h) + String(" %");
   String fireTemp = String(t) + String(" °C");

   Firebase.pushString(firebaseData, "/DHT11/Humidity", fireHumid);           //setup path to send Humidity readings
   Firebase.pushString(firebaseData, "/DHT11/Temperature", fireTemp);
   delay(5000);
  }
}
