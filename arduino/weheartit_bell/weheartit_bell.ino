#include <Servo.h>

#define ESP_RESET_CMD "AT+RST\r"
#define ESP_CONNECT_CMD "AT+CWJAP=\"AP Name\",\"Password\"\r"       // connect to wifi
#define ESP_SET_AS_CLIENT_CMD "AT+CWMODE=1\r"                       // configure as client
#define ESP_GET_IP_CMD "AT+CIFSR\r"                                 // get ip address
#define ESP_SINGLE_CONNECTION_CMD "AT+CIPMUX=0"                     // configure for single connection
#define ESP_TCP_START_CMD "AT+CIPSTART=\"TCP\",\"10.0.0.2\",5000\r" // connect with my laptop
#define ESP_TCP_SEND_CMD "AT+CIPSEND=18\r"                          // will send 18 bytes
#define ESP_TCP_GET_CMD "GET / HTTP/1.0\r\n"                        // sent a GET /

#define LED_PIN 8
#define BELL_PIN 9

#define BLINK_ERROR 10
#define BLINK_OK 2

Servo bell;

void setup() {
  Serial.begin(115700);

  sendData(ESP_RESET_CMD, 3000);                                  // reset module
  pinMode(LED_PIN, OUTPUT);
  bell.attach(BELL_PIN);
}

void loop() {
  String response;

  sendData(ESP_TCP_START_CMD, 1000);
  if (response.indexOf("Error")) return blink(BLINK_ERROR);

  delay(1000);
  sendData(ESP_TCP_SEND_CMD, 1000);
  if (response.indexOf("Error")) return blink(BLINK_ERROR);

  delay(1000);
  response = sendData(ESP_TCP_GET_CMD, 3000);
  if (response.indexOf("Error")) return blink(BLINK_ERROR);

  if (response.indexOf("state:1") != -1) {
    blink(BLINK_OK);
    ring();
  } else {
    blink(BLINK_ERROR);
  }

  delay(5000);
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

void blink(int count) {
  for (int i=0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);

    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void ring() {
  bell.write(180);
  delay(1000);
  bell.write(0);
  delay(500);
  bell.write(90);
}
