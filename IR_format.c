#include <xc.h>
#include <stdint.h>         /* For uint8_t definition */
#include "IR_format.h"

uint8_t checksum(uint8_t command, uint8_t* data, uint8_t dataCount)
{
	uint8_t r = command;

	for (uint8_t c = 0; c < dataCount; c++) {
		r ^= data[c];
	}
	
	r = (r ^ (7-(r >> 3)))&7;
	return ((r&1)<<2)|(r&2)|((r&4)>>2);
}
