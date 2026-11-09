# Lab 2 – Working with LEDs (YoloUNO / ESP32-S3 + FreeRTOS)

CO3038 – Internet of Things Application Development (Lab) · Class CC06 · Group 1

| No. | Name | Student ID |
|---|---|---|
| 1 | Vo Minh Quan | 2353022 |
| 2 | Nguyen Thanh Phong | 2352908 |
| 3 | Tran Uy Danh | 2352160 |

Each folder is a complete PlatformIO project (VS Code + PlatformIO, board `yolo_uno`, framework Arduino).
Single LED: GPIO 48 (D13) · NeoPixel: GPIO 45.

| Folder | Exercise | Behaviour |
|---|---|---|
| `Lab2_Ex1` | Simple Alternating Blink | LED 1 s ON / 2 s OFF |
| `Lab2_Ex2` | Coordinated LED and NeoPixel | LED 2 s / 2 s, NeoPixel red while LED is ON (shared variable) |
| `Lab2_Ex3` | Independent Blinking Patterns | LED 1.5 s / 0.5 s, NeoPixel R 1 s → G 2 s → B 2 s |
| `Lab2_Ex4` | Advanced NeoPixel Sequence | LED 2 s / 2 s, `task_neo_rainbow` 5 colours × 3 s (task parameters) |
| `Lab2_Ex5` | Traffic Light Simulation | LED 1 s / 1 s, NeoPixel red 7 s → amber 2 s → green 5 s |

## Build & upload
1. Open one exercise folder in VS Code (File → Open Folder).
2. Build (✓), then Upload (→).
3. First upload: hold BOOT, press RST, release BOOT, then upload; press RST to run.
