#include <stdint.h>

typedef struct SensorData
{
    uint16_t value;
    uint16_t readTime;
} SensorData;

typedef struct Command
{
    char type;
    uint16_t value;
} Command;


uint8_t deserializeSensorData(SensorData *sensorData, uint8_t *buf, uint8_t offset);

uint8_t deserializeCommand(Command *command, uint8_t *buf, uint8_t offset);
