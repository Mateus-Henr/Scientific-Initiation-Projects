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


void initializeMockupSensorData(SensorData *sensorData);

void initializeMockupCommandData(Command *command);

uint8_t serializeSensorData(uint8_t *buf, SensorData *sensorData, uint8_t offset);

uint8_t serializeCommand(uint8_t *buf, Command *command, uint8_t offset);
