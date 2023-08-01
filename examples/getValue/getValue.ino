
#include <M5StickCPlus.h>
#include "Unit_MiniEncoderC.h"

TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);
UNIT_MINIENCODERC sensor;

uint16_t delay_time = 0;
int32_t last_value  = 0;

uint8_t i2c_address = 0;

void page_get_encoder(void) {
    int32_t encoder_value = sensor.getEncoderValue();
    bool btn_status       = sensor.getButtonStatus();
    Serial.println(encoder_value);
    if (last_value != encoder_value) {
        if (last_value > encoder_value) {
            sensor.setLEDColor(1, 0x000011);
        } else {
            sensor.setLEDColor(2, 0x110000);
        }
        last_value = encoder_value;
    } else {
        // sensor.setLEDColor(0, 0x001100);
    }
    if (!btn_status) {
        sensor.setLEDColor(0, 0x001100);
    }
    tftSprite.fillRect(0, 0, 135, 90, BLACK);
    tftSprite.setTextColor(WHITE);
    tftSprite.drawString("BTN:" + String(btn_status), 10, 10);
    tftSprite.drawString("ENCODER:", 10, 40);
    tftSprite.setCursor(10, 65);
    tftSprite.setTextColor(GREEN);
    tftSprite.printf("%d", encoder_value);
    tftSprite.setTextColor(WHITE);
    tftSprite.drawString("btnA:", 10, 120);
    tftSprite.setTextColor(ORANGE);
    tftSprite.drawString("get inc", 10, 150);
    tftSprite.setTextColor(WHITE);
    tftSprite.drawString("btnB:", 10, 180);
    tftSprite.setTextColor(ORANGE);
    tftSprite.drawString("reset", 10, 210);
    tftSprite.pushSprite(0, 0);
}

void get_inc_value(void) {
    int32_t inc_value = sensor.getIncrementValue();
    Serial.printf("Inc:%d", inc_value);
}

void setup() {
    M5.begin();  // Init M5Stack.  初始化M5Stack
    sensor.begin(&Wire, MINIENCODERC_ADDR, 0, 26, 100000UL);
    tftSprite.setRotation(1);
    tftSprite.createSprite(135, 240);
    tftSprite.setTextSize(2);
    delay_time  = 20;
    i2c_address = sensor.getI2CAddress();
    // sensor.setEncoderValue(97900);
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) {
        get_inc_value();
    } else if (M5.BtnB.wasPressed()) {
        sensor.resetCounter();
    }
    page_get_encoder();
}
