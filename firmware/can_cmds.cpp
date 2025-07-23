#include "can_cmds.h"
#include <ESP32-TWAI-CAN.hpp>

void sendLocoCmd(uint8_t baseAddress, uint16_t locoId, int16_t locoSpeed, uint16_t funcs) {
  uint16_t locoSpeedInt8Array[2];
  locoSpeedInt8Array[0]= locoSpeed & 0xff;
  locoSpeedInt8Array[1]= (locoSpeed >> 8);

  uint16_t funcsUint8Array[2];
  funcsUint8Array[0]= funcs & 0xff;
  funcsUint8Array[1]= (funcs >> 8);

  CanFrame frame = { 0 };
  frame.identifier = baseAddress;
  frame.extd = 0;
  frame.data_length_code = 6;
  // loco cmd identifier
  frame.data[0] = 0x10;
  frame.data[1] = locoId;
  frame.data[2] = locoSpeedInt8Array[0];
  frame.data[3] = locoSpeedInt8Array[1];
  frame.data[4] = funcsUint8Array[0];
  frame.data[5] = funcsUint8Array[1];
  ESP32Can.writeFrame(frame);
}