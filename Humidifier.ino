
#include "DHT.h"                     // подключение библиотеки
#define DHTPIN 2                     // пин для подключения датчика DHT
#define DHTTYPE DHT11                // тип датчика DHT
#define LED 10                       // LED PWM pin
#define MOS 9                        // Mosfet Module pin
DHT dht(DHTPIN, DHTTYPE);            // создание экземпляра объекта DHT

void setup() {
  
  //Serial.begin(9600);    // подключение последовательного порта
  dht.begin();           // запуск датчика DHT
  pinMode(LED, OUTPUT);  // Инициализируем порт со Светодиодом как выход.
  pinMode(MOS, OUTPUT);  // Инициализируем порт с Мосфетом как выход.
  digitalWrite(MOS, 0);
  digitalWrite(LED, 0);
}

void loop() {

  float h = dht.readHumidity();     // получение данных влажности
  float t = dht.readTemperature();  // получение данных температуры

  // ошибочные данные с датчика!
  if (isnan(h)) {
    Serial.print("Error reading Humidity! ");
    digitalWrite(LED, 1);
    digitalWrite(MOS, 0);
  }

  else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(F("%, "));
    digitalWrite(LED, 0);
  }

  if (isnan(t)) {
    Serial.println("Error reading Temperature!");
    digitalWrite(LED, 1);
    digitalWrite(MOS, 0);
  }
  
  else {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(F("° "));
    digitalWrite(LED, 0);
  }

  if (h < 50) {
    digitalWrite(MOS, 1);
    Serial.println("Humidifier is ON");
  }
  else {
    digitalWrite(MOS, 0);
    Serial.println("Humidifier is OFF");
  }

  delay(2000);        // пауза 5 секунд
}
