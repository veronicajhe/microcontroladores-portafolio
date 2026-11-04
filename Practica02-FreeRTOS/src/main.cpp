
#include <Arduino.h>

#define LED1 2
#define LED2 4

void tareaNucleo0(void *parameter) {
  pinMode(LED1, OUTPUT);

  while (true) {
    digitalWrite(LED1, HIGH);
    Serial.println("Nucleo 0: LED1 encendido");
    vTaskDelay(pdMS_TO_TICKS(500));

    digitalWrite(LED1, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void tareaNucleo1(void *parameter) {
  pinMode(LED2, OUTPUT);

  while (true) {
    digitalWrite(LED2, HIGH);
    Serial.println("Nucleo 1: LED2 encendido");
    vTaskDelay(pdMS_TO_TICKS(1000));

    digitalWrite(LED2, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    tareaNucleo0,
    "Tarea LED1",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    tareaNucleo1,
    "Tarea LED2",
    2048,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
