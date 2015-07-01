#include <Servo.h>
#include "wifi.h"
#include "http.h"

#define LED_PIN 13
#define BELL_PIN 10

#define BLINK_ERROR 10
#define BLINK_DEPLOYED 3
#define BLINK_NOT_DEPLOYED 1
#define BLINK_SETUP 1

String sendData(String command, const int timeout);
void blink(int count);
void ring(void);

Servo bell;

void setup() {
  Serial.begin(115700);

  sendData(ESP_RESET_CMD, 3000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  bell.attach(BELL_PIN);
  bell.write(50);
  delay(200);
  bell.detach();

  delay(5000);
  blink(BLINK_SETUP);
}

void loop() {
  String response;

  delay(2000);
  response = sendData(ESP_TCP_START_CMD, 1000);
  if (response.indexOf("ERROR") != -1) return blink(BLINK_ERROR);

  delay(2000);
  response = sendData(ESP_TCP_SEND_CMD, 3000);
  if (response.indexOf("ERROR") != -1) return blink(BLINK_ERROR);

  delay(2000);
  response = sendData(ESP_TCP_CONTENT, 5000);
  if (response.indexOf("ERROR") != -1) return blink(BLINK_ERROR);


  if (response.indexOf("status:1") != -1) {
    blink(BLINK_DEPLOYED);
    ring();
  } else {
    blink(BLINK_NOT_DEPLOYED);
  }

  delay(5000);
}

void blink(int count) {
  for (int i=0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);

    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void ring() {
  bell.attach(BELL_PIN);
  delay(100);
  bell.write(160);
  delay(200);
  bell.write(50);
  delay(200);
  bell.detach();
}

String sendData(String command, const int timeout) {
  String response = "";

  Serial.println(command);

  long int time = millis();

  while ((time + timeout) > millis()) {
    while (Serial.available()) {
      char c = Serial.read();
      response += c;
    }
  }

  return response;
}
