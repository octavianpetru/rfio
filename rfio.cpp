#include "rfio.h"

#include <cstdio>

#include "RCSwitch.h"
#include "wiringPi.h"

int main(int argc, char **argv) {
	// setup wiringPi 
	if (wiringPiSetup() == -1) {
		return -1;
	}

	// setup led pin
	pinMode(RX_PIN, INPUT);

	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(TX_PIN);

	// Optional set protocol
	mySwitch.setProtocol(1);
	mySwitch.setRepeatTransmit(8);

	int txCount = 1;
	int minLedValue = 8;
	int maxLedValue = 256;
	for (;;) {
		int i = minLedValue;
		for (; i < maxLedValue; i = i + minLedValue) {

			char s[13] = { '\0' };
			toBinStr(i, s, 12);
			char str[38] = { '\0' };
			sprintf(str, "1001000110010001%s110011000", s);
			mySwitch.sendString(str);
			printf("%3d sent %3d\n", txCount++, i);
			delay(24250);

			char s1[13] = { '\0' };
			toBinStr(256 - i, s1, 12);
			char str1[38] = { '\0' };
			sprintf(str1, "1001001000110010%s110011000", s1);
			mySwitch.sendString(str1);
			printf("%3d sent %3d\n", txCount++, 256 - i);
			delay(24250);

		}
	}

	return 0;
}

void toBinStr(long value, char* output, int i) {
	output[i] = '\0';
	for (i = i - 1; i >= 0; --i, value >>= 1) {
		output[i] = (value & 1) + '0';
	}
}
