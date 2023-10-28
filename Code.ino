#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "**********************" //Данные с BLYNK
#define BLYNK_TEMPLATE_NAME "********************" //Данные с BLYNK
#define BLYNK_AUTH_TOKEN "***********************" //Данные с BLYNK

char ssid[] = "Name"; // имя вашего вайфая
char pass[] = "Password"; // пароль от вайфая

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define relay 12 // Пин реле
#define switchPin 14 // Пин для выключателя

bool relay1 = 1; // 1 реле с обратной логикой 0 реле с прямой логикой 
bool switchState = 0; // Изначальное состояние выключателя

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, relay1);
  pinMode(switchPin, INPUT_PULLUP); // Используем внутренний подтягивающий резистор
}

BLYNK_WRITE(V0) //Витуальный пин для Blynk
{
  relay1 = param.asInt();
  digitalWrite(relay, relay1);
}

void loop()
{
  Blynk.run();

  // Считываем состояние выключателя
  int newSwitchState = digitalRead(switchPin);

  // Если состояние изменилось (кнопка нажата)
  if (newSwitchState != switchState) {
    switchState = newSwitchState;
    
    // Инвертируем значение реле
    relay1 = !relay1;
    digitalWrite(relay, relay1);
    
    // Отправляем обновленное значение в Blynk
    Blynk.virtualWrite(V0, relay1);
  }
}
