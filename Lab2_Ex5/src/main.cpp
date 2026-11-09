// LAB 2 - Exercise 5: Traffic Light System Simulation
// task_led_blinky   : on-board LED 1 s ON / 1 s OFF, continuously.
// task_traffic_light: NeoPixel RED 7 s -> AMBER 2 s -> GREEN 5 s, repeating.
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     GPIO_NUM_48
#define NEO_PIN     45
#define LED_COUNT   1

#define RED_MS      7000
#define AMBER_MS    2000
#define GREEN_MS    5000

void task_led_blinky(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1000));          // ON for 1 s
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));          // OFF for 1 s
  }
}

void task_traffic_light(void *pvParameters) {
  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.clear();
  strip.show();

  while (1) {
    strip.setPixelColor(0, strip.Color(255, 0, 0));     // RED
    strip.show();
    Serial.println("Traffic light: RED");
    vTaskDelay(pdMS_TO_TICKS(RED_MS));

    strip.setPixelColor(0, strip.Color(255, 120, 0));   // AMBER (yellow)
    strip.show();
    Serial.println("Traffic light: AMBER");
    vTaskDelay(pdMS_TO_TICKS(AMBER_MS));

    strip.setPixelColor(0, strip.Color(0, 255, 0));     // GREEN
    strip.show();
    Serial.println("Traffic light: GREEN");
    vTaskDelay(pdMS_TO_TICKS(GREEN_MS));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task_led_blinky,    "LED Blinky",    2048, NULL, 1, NULL);
  xTaskCreate(task_traffic_light, "Traffic Light", 4096, NULL, 1, NULL);
}

void loop() {
}
