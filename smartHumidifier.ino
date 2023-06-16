
#include "DHT.h"                     // подключение библиотеки
#define DHTPIN 2                     // пин для подключения датчика DHT-11
#define DHTTYPE DHT11                // тип датчика DHT
#define LED 10                       // пин для подключения LED
#define MOS 9                        // пин для подключения модуля MOSFET-IRF520
DHT dht(DHTPIN, DHTTYPE);            // создание экземпляра объекта DHT

void setup() {
  
  Serial.begin(9600);                // подключение последовательного порта
  dht.begin();                       // запуск датчика DHT
  pinMode(LED, OUTPUT);              // Инициализируем порт со Светодиодом как выход.
  pinMode(MOS, OUTPUT);              // Инициализируем порт с Мосфетом как выход.
  digitalWrite(MOS, 0);              // отключение модуля MOSFET-IRF520
  digitalWrite(LED, 0);              // отключение LED
}

void loop() {

  float h = dht.readHumidity();      // получение данных влажности
  float t = dht.readTemperature();   // получение данных температуры

  if (isnan(h)) {
    Serial.print("Error reading Humidity! ");      // если есть ошибка чтения данных по влажности с датчика DHT-11
    digitalWrite(LED, 1);                          // включение LED
    digitalWrite(MOS, 0);                          // отключение модуля MOSFET-IRF520
  }

  else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(F("%, "));
    digitalWrite(LED, 0);                          // выключение LED
  }

  if (isnan(t)) {
    Serial.println("Error reading Temperature!");  // если есть ошибка чтения данных по температуре с датчика DHT-11
    digitalWrite(LED, 1);                          // включение LED
    digitalWrite(MOS, 0);                          // отключение модуля MOSFET-IRF520
  }
  
  else {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(F("° "));
    digitalWrite(LED, 0);                          // выключение LED
  }

  if (h < 50) {
    digitalWrite(MOS, 1);                          // если влажность меньше 50
    Serial.println("Humidifier is ON");            // включение модуля MOSFET-IRF520
  }
  else {
    digitalWrite(MOS, 0);                          // если влажность больше 50
    Serial.println("Humidifier is OFF");           // отключение модуля MOSFET-IRF520
  }

  delay(5000);                                     // пауза 5 секунд
}
