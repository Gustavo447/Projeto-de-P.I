#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <DHT.h>    // Install DHT11 Library and Adafruit Unified Sensor Library
#include <Servo.h>

#define FIREBASE_HOST "dht11weatherstat-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "MndtKRC4Ul2PHfZrCdmjmOIVxqAh7kYP3n9cHUJb"

#define WIFI_SSID "Gustavo"
#define WIFI_PASSWORD "02018506"

#define DHTPIN D1    // Connect Data pin of DHT to D3
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

Servo servo;
int servoAngle = 0;

int fireStatus;
int rele1 = D3;
int rele2 = D6;

// Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

void setup()
{
  Serial.begin(9600);

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, LOW);
  digitalWrite(rele2, LOW);

  dht.begin();

  servo.attach(D5); // Connect servo to D5 pin

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(firebaseData, "rele1", 0);
  Firebase.setInt(firebaseData, "rele2", 0);
  Firebase.setInt(firebaseData, "servoAngle", servoAngle); // Set initial servo angle to 0
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Firebase.pushFloat(firebaseData, "/humidity", h);        // Setup path to send humidity readings
  Firebase.pushFloat(firebaseData, "/temperature", t);
  delay(5000);

  if (Firebase.getInt(firebaseData, "/rele1"))
  {
    fireStatus = firebaseData.intData();
    if (fireStatus == 1)
    {
      Serial.println("Relé 1 ON");
      digitalWrite(rele1, HIGH);
    }
    else if (fireStatus == 0)
    {
      Serial.println("Relé 1 OFF");
      digitalWrite(rele1, LOW);
    }
    else
    {
      Serial.println("Wrong Credential! Please send 0 or 1");
    }
  }

  if (Firebase.getInt(firebaseData, "/rele2"))
  {
    fireStatus = firebaseData.intData();
    if (fireStatus == 1)
    {
      Serial.println("Relé 2 ON");
      digitalWrite(rele2, HIGH);
    }
    else if (fireStatus == 0)
    {
      Serial.println("Relé 2 OFF");
      digitalWrite(rele2, LOW);
    }
    else
    {
      Serial.println("Wrong Credential! Please send 0 or 1");
    }
  }

  if (Firebase.getInt(firebaseData, "/servoAngle"))
  {
    servoAngle = firebaseData.intData();
    if (servoAngle >= 0 && servoAngle <= 180)
    {
      Serial.print("Setting servo angle: ");
      Serial.println(servoAngle);
      servo.write(servoAngle);
    }
    else
    {
      Serial.println("Invalid servo angle! Please send a value between 0 and 180");
    }
  }
}
