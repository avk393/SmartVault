#include <stdint.h>
#define CLOSED 0
#define OPEN 1
#define LIMBO 2

void Limit_Sensor_Init(void);
uint8_t getDoorStatus(void);
