
#include <Arduino.h>

// Pines de los LED
#define LED_ROJO 25
#define LED_VERDE 26

// Cola para comunicar las tareas
QueueHandle_t colaDatos;

// Tarea productora: nucleo 0
void tareaProductora(void *parametro) {
  int dato = 0;

  while (true) {
    dato = !dato;

    xQueueSend(colaDatos, &dato, portMAX_DELAY);

    digitalWrite(LED_ROJO, dato);
    Serial.printf("Nucleo 0: Enviado %d\n", dato);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Tarea consumidora: nucleo 1
void tareaConsumidora(void *parametro) {
  int datoRecibido;

  while (true) {
    if (xQueueReceive(colaDatos, &datoRecibido,
                      portMAX_DELAY) == pdTRUE) {

      digitalWrite(LED_VERDE, datoRecibido);

      Serial.printf("Nucleo 1: Recibido %d\n",
                    datoRecibido);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  colaDatos = xQueueCreate(5, sizeof(int));

  if (colaDatos == NULL) {
    Serial.println("Error al crear la cola");
    return;
  }

  xTaskCreatePinnedToCore(
    tareaProductora,
    "Productora",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    tareaConsumidora,
    "Consumidora",
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
