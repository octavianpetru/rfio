#include "rfio.h"

#include <cstdio>

#include "RCSwitch.h"
#include "wiringPi.h"

void tobin5str(long value, char* output);

int main(int argc, char **argv) {
	// setup wiringPi 
	if (wiringPiSetup() == -1) {
		return -1;
	}

	// setup led pin
	pinMode(LED_PIN, PWM_OUTPUT);
	pwmWrite(LED_PIN, LOW);

	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(TX_PIN);

	// Optional set protocol (default is 1, will work for most outlets)
	mySwitch.setProtocol(6);
	mySwitch.setRepeatTransmit(10);

	int txCount = 1;
	int minLedValue = 8;
	int maxLedValue = 256;
	for (;;) {
		int i = minLedValue;
		for (; i < maxLedValue; i = i + minLedValue) {

			pwmWrite(LED_PIN, i);

		    char s[13] = {'\0'};
		    tobin5str(i, s);
		    char str[38] = {'\0'};
		    sprintf(str, "1001000110010001%s110011000", s);
		    mySwitch.send(str);
			printf("%3d sent %3d\n", txCount++, i);

			//000001111011 123
			//mySwitch.send("1001000110010001000001111011110011000");
			delay(16500);

		    char s1[13] = {'\0'};
			tobin5str(256-i, s1);
		    char str1[38] = {'\0'};
		    sprintf(str1, "1001001000110010%s110011000", s1);
		    mySwitch.send(str1);
			printf("%3d sent %3d\n", txCount++, 256-i);

			//000101000001 321
			//mySwitch.send("1001001000110010000101000001110011000");
			delay(16500);

		}
	}

	return 0;
}

void tobin5str(long value, char* output)
{
    int i;
    output[12] = '\0';
    for (i = 11; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}
