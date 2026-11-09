// LAB 2 - Exercise 3: Independent Blinking Patterns
// task_led_blinky: LED 1.5 s ON / 0.5 s OFF.
// task_neo_blinky: NeoPixel RED (1 s) -> GREEN (2 s) -> BLUE (2 s), repeating.
// The two tasks share no variables and keep their own timing.
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     GPIO_NUM_48
#define NEO_PIN     45
#define LED_COUNT   1

void task_led_blinky(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(1500));          // ON for 1.5 s
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(500));           // OFF for 0.5 s
  }
}

void task_neo_blinky(void *pvParameters) {
  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.clear();
  strip.show();

  while (1) {
    strip.setPixelColor(0, strip.Color(255, 0, 0));   // RED
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(1000));                  // 1 s

    strip.setPixelColor(0, strip.Color(0, 255, 0));   // GREEN
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(2000));                  // 2 s

    strip.setPixelColor(0, strip.Color(0, 0, 255));   // BLUE
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(2000));                  // 2 s
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task_led_blinky, "LED Blinky", 2048, NULL, 1, NULL);
  xTaskCreate(task_neo_blinky, "NEO Blinky", 2048, NULL, 1, NULL);
}

void loop() {
}
