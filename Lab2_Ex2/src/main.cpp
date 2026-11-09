// LAB 2 - Exercise 2: Coordinated LED and NeoPixel
// task_led_blinky: LED 2 s ON / 2 s OFF and publishes its state.
// task_neo_blinky: NeoPixel RED while the LED is ON, OFF while the LED is OFF.
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     GPIO_NUM_48
#define NEO_PIN     45
#define LED_COUNT   1
#define BLINK_MS    2000
#define POLL_MS     10

// Shared variable between the two tasks (written by LED task, read by NeoPixel task)
volatile bool ledState = false;

void task_led_blinky(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    ledState = true;                          // publish: LED is ON
    vTaskDelay(pdMS_TO_TICKS(BLINK_MS));

    digitalWrite(LED_PIN, LOW);
    ledState = false;                         // publish: LED is OFF
    vTaskDelay(pdMS_TO_TICKS(BLINK_MS));
  }
}

void task_neo_blinky(void *pvParameters) {
  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.clear();
  strip.show();

  bool lastState = false;
  bool first = true;
  while (1) {
    bool now = ledState;                      // read the shared state
    if (first || now != lastState) {          // update only when it changes
      if (now) {
        strip.setPixelColor(0, strip.Color(255, 0, 0));   // RED
      } else {
        strip.setPixelColor(0, strip.Color(0, 0, 0));     // OFF (BLACK)
      }
      strip.show();
      lastState = now;
      first = false;
    }
    vTaskDelay(pdMS_TO_TICKS(POLL_MS));       // check again in 10 ms
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task_led_blinky, "LED Blinky", 2048, NULL, 1, NULL);
  xTaskCreate(task_neo_blinky, "NEO Blinky", 2048, NULL, 1, NULL);
}

void loop() {
}
