#include "sha_1.h"

uint32_t circularLeftShift(uint32_t word, int n) {
	uint32_t tempLShift = word << n;
	uint32_t tempRShift = word >> (32 - n);
	return tempLShift | tempRShift;
};

uint32_t logicalFunction(int t, uint32_t B, uint32_t C, uint32_t D) {
	if (t <= 19) {
		return (B & C) | ((~B) & D);
	}
	else if (t <= 39) {
		return B ^ C ^ D;
	}
	else if (t <= 59) {
		return (B & C) | (B & D) | (C & D);
	}
	else {
		return B ^ C ^ D;
	}
}

uint32_t K(int t) {
	if (t <= 19) {
		return 0x5A827999;
	}
	else if (t <= 39) {
		return 0x6ED9EBA1;
	}
	else if (t <= 59) {
		return 0x8F1BBCDC;
	}
	else {
		return 0xCA62C1D6;
	}
}
