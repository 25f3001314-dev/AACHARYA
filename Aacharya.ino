#include <Arduino_GFX_Library.h>
#include <ESP_I2S.h>
#include "pins.h"

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCL, TFT_SDA, GFX_NOT_DEFINED);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, TFT_RST, 0, true);

I2SClass mic;
I2SClass spk;

void showText(const char *line1, const char *line2 = "") {
  gfx->fillScreen(BLACK);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 100);
  gfx->println(line1);
  gfx->setCursor(50, 130);
  gfx->println(line2);
}

int micLevel() {
  int16_t buf[256];
  size_t n = mic.readBytes((char *)buf, sizeof(buf));
  int count = n / 2;
  long sum = 0;
  for (int i = 0; i < count; i++) sum += abs(buf[i]);
  return count ? sum / count : 0;
}

void beep() {
  int16_t buf[160];
  for (int n = 0; n < 50; n++) {
    for (int i = 0; i < 160; i++) {
      buf[i] = ((i / 20) % 2) ? 6000 : -6000;
    }
    spk.write((uint8_t *)buf, sizeof(buf));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);

  gfx->begin();
  showText("Aacharya", "starting...");

  mic.setPins(MIC_SCK, MIC_WS, -1, MIC_SD);
  mic.begin(I2S_MODE_STD, 16000, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT);

  spk.setPins(SPK_BCLK, SPK_LRC, SPK_DIN);
  spk.begin(I2S_MODE_STD, 16000, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT);

  showText("Touch me");
}

void loop() {
  if (digitalRead(TOUCH_PIN) == HIGH) {
    showText("Listening...");
    long total = 0;
    for (int i = 0; i < 20; i++) total += micLevel();
    String level = String(total / 20);
    showText("Mic level", level.c_str());
    Serial.println(level);
    beep();
    delay(1500);
    showText("Touch me");
  }
  delay(50);
}