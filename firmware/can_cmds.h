#ifndef CANCMDS_H
#define CANCMDS_H
#include <stdint.h>

void sendLocoCmd(uint8_t baseAddress, uint16_t locoId, uint16_t locoSpeed, uint16_t funcs);

#endif