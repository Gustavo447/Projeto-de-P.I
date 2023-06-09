
#include <FirebaseESP8266.h>  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <DHT.h>    // Install DHT11 Library and Adafruit Unified Sensor Library

#define FIREBASE_HOST "dht11weatherstat-default-rtdb.firebaseio.com" // Sem os esquemas http:// ou https://
#define FIREBASE_AUTH "MndtKRC4Ul2PHfZrCdmjmOIVxqAh7kYP3n9cHUJb"

#define WIFI_SSID "Gustavo"
#define WIFI_PASSWORD "02018506"

#define DHTPIN D1    // Conecte o pino de dados do DHT ao D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int fireStatus;
int rele1 = D8;
int rele2 = D6;

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

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.print("Conectado com IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(firebaseData, "/rele1", 0);
  Firebase.setInt(firebaseData, "/rele2", 0);
  Firebase.setInt(firebaseData, "/automatico", 1);

}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Falha ao ler o sensor DHT!"));
    return;
  }

  Firebase.pushFloat(firebaseData, "/humidity", h);
  Firebase.pushFloat(firebaseData, "/temperature", t);
  delay(5000);

  if (Firebase.getInt(firebaseData, "/automatico") == 1)
  {
    if (t < 30)
    {
      digitalWrite(rele2, LOW);
      digitalWrite(rele1, HIGH);
    }
    else if (t > 32)
    {
      digitalWrite(rele2, LOW);
      digitalWrite(rele1, HIGH);
    }
    else
    {
      digitalWrite(rele1, LOW);
      digitalWrite(rele2, LOW);
    }
  }
  else
  {
    if (Firebase.getInt(firebaseData, "/rele1"))
    {
      fireStatus = firebaseData.intData();
      if (fireStatus == 1)
      {
        Serial.println("Relé 1 LIGADO");
        digitalWrite(rele1, HIGH);
      }
      else if (fireStatus == 0)
      {
        Serial.println("Relé 1 DESLIGADO");
        digitalWrite(rele1, LOW);
      }
    }

    if (Firebase.getInt(firebaseData, "/rele2"))
    {
      fireStatus = firebaseData.intData();
      if (fireStatus == 1)
      {
        Serial.println("Relé 2 LIGADO");
        digitalWrite(rele2, HIGH);
      }
      else if (fireStatus == 0)
      {
        Serial.println("Relé 2 DESLIGADO");
        digitalWrite(rele2, LOW);
      }
    }
  }
}
