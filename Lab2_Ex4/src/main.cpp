// LAB 2 - Exercise 4: Advanced NeoPixel Sequence
// task_led_blinky : LED 2 s ON / 2 s OFF.
// task_neo_rainbow: NeoPixel cycles RED -> YELLOW -> GREEN -> CYAN -> BLUE,
//                   3 s per color. The color list and the step time are passed
//                   to the task as a parameter (task parameterization).
// The LED (4 s period) and the NeoPixel (15 s period) are not synchronized.
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     GPIO_NUM_48
#define NEO_PIN     45
#define LED_COUNT   1

// Parameters handed to task_neo_rainbow through pvParameters
struct RainbowParams {
  const uint32_t *colors;   // list of colors (0xRRGGBB)
  uint8_t count;            // number of colors
  uint32_t stepMs;          // time per color
};

static const uint32_t RAINBOW_COLORS[] = {
  0xFF0000,   // RED
  0xFFFF00,   // YELLOW
  0x00FF00,   // GREEN
  0x00FFFF,   // CYAN
  0x0000FF    // BLUE
};

// Must stay valid while the task runs, so it is a global (static) object
static RainbowParams rainbowParams = { RAINBOW_COLORS, 5, 3000 };

void task_led_blinky(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  while (1) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(2000));          // ON for 2 s
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(2000));          // OFF for 2 s
  }
}

void task_neo_rainbow(void *pvParameters) {
  RainbowParams *p = (RainbowParams *)pvParameters;

  Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.clear();
  strip.show();

  uint8_t i = 0;
  while (1) {
    uint32_t c = p->colors[i];
    strip.setPixelColor(0, strip.Color((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF));
    strip.show();
    vTaskDelay(pdMS_TO_TICKS(p->stepMs));     // 3 s per color
    i = (i + 1) % p->count;                   // next color, wrap around
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(task_led_blinky,  "LED Blinky",  2048, NULL,           1, NULL);
  xTaskCreate(task_neo_rainbow, "NEO Rainbow", 2048, &rainbowParams, 1, NULL);
}

void loop() {
}
