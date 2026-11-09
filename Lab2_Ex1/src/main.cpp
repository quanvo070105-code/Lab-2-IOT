// LAB 2 - Exercise 1: Simple Alternating Blink
// task_led_blinky: on-board LED (GPIO 48) ON for 1 s, OFF for 2 s.
#include <Arduino.h>

#define LED_PIN     GPIO_NUM_48
#define LED_ON_MS   1000
#define LED_OFF_MS  2000

void task_led_blinky(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);              // LED ON
    vTaskDelay(pdMS_TO_TICKS(LED_ON_MS));     // keep ON for 1 s
    digitalWrite(LED_PIN, LOW);               // LED OFF
    vTaskDelay(pdMS_TO_TICKS(LED_OFF_MS));    // keep OFF for 2 s
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task_led_blinky, "LED Blinky", 2048, NULL, 1, NULL);
}

void loop() {
  // Empty: all work is done in the FreeRTOS task.
}
