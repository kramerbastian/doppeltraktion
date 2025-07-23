#include <U8g2lib.h>
#include <ESP32-TWAI-CAN.hpp>
#include <PCF8574.h>
#include <Wire.h>
#include "screens.h"
#include "can_cmds.h"

#define BASE_ADDRESS 1
#define I2C_FREQ 400000
#define SDA 21
#define SCL 47
#define CS_DSP 10
#define PICO 11
#define SCK 12
#define A0 9
#define CAN_TX 5
#define CAN_RX 4
#define POTENTIOMETER_LOCO_1_PIN 6
#define POTENTIOMETER_LOCO_2_PIN 17
#define LIGHT_LOCO_1_PIN 48
#define LIGHT_LOCO_2_PIN 18
#define DIR_LOCO_1_PIN 45
#define DIR_LOCO_2_PIN 8

U8G2_ST7565_EA_DOGM128_1_4W_SW_SPI u8g2(U8G2_R0, SCK, PICO, CS_DSP, A0);
u8g2_uint_t offset;
u8g2_uint_t width;

TwoWire I2C = TwoWire(0);

PCF8574 ex1(0x20, &I2C);

uint16_t loco1Speed = 0;
uint16_t loco1SpeedPrevious = loco1Speed;
uint8_t loco1Address = 1;
bool loco1Dir = true;

uint16_t loco2Speed = 0;
uint16_t loco2SpeedPrevious = loco2Speed;
uint8_t loco2Address = 2;
bool loco2Dir = true;

void IRAM_ATTR onDirLoco1() {
  loco1Dir = !loco1Dir;
  loco1Speed = loco1Speed * -1;
}

void IRAM_ATTR onDirLoco2() {
  loco2Dir = !loco2Dir;
  loco2Speed = loco2Speed * -1;
}

void setup() {
  Serial.begin(9600);

  I2C.begin();

  if (!ex1.begin()){
    Serial.println("PCF8574 could not initialize");
  } if (!ex1.isConnected()) {
    Serial.println("PCF8574 not connected");
  }

  ESP32Can.setPins(CAN_TX, CAN_RX);
  if (!ESP32Can.begin(ESP32Can.convertSpeed(500))) {
    Serial.println("Starting CAN failed!");
  }

  u8g2.begin();
  u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.setFontMode(0);

  attachInterrupt(DIR_LOCO_1_PIN, onDirLoco1, FALLING);
  attachInterrupt(DIR_LOCO_2_PIN, onDirLoco2, FALLING);
}

void loop() {
  loco1SpeedPrevious = loco1Speed;
  loco1Speed = analogRead(POTENTIOMETER_LOCO_1_PIN);
  loco1Speed = map(loco1Speed, 0, 1023, 0, 180);
  
  if (loco1Speed != loco1SpeedPrevious) {
    if (!loco1Dir) {
      loco1Speed = loco1Speed * -1;
    }
    sendLocoCmd(BASE_ADDRESS, loco1Address, loco1Speed, 0x00);
  }

  loco2SpeedPrevious = loco2Speed;
  loco2Speed = analogRead(POTENTIOMETER_LOCO_2_PIN);
  loco2Speed = map(loco2Speed, 0, 1023, 0, 180);

  if (loco2Speed != loco2SpeedPrevious) {
    if (!loco2Dir) {
      loco1Speed = loco2Speed * -1;
    }
    sendLocoCmd(BASE_ADDRESS, loco2Address, loco2Speed, 0x00);
  }

  drawLocoScreen(u8g2, loco1Speed, loco2Speed);
}