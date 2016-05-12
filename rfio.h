#ifndef _rfio_H_
#define _rfio_H_

#define TX_PIN 0
#define RX_PIN 1
#define TX_POWER_PIN 2

typedef struct {
	unsigned int indexReceive;
	char startLabel[5];
	short id;
	short canal;
	short temperature;
	char temperatureStr[6];
	char endLabel[5];
	unsigned long time;
} TemperatureMessage;

void toBinStr(long value, char* output, int i);
TemperatureMessage *readReceivedValue(unsigned long receivedValue);

#endif
