#include <stdint.h>

typedef struct SensorData
{
    unsigned short value;
    unsigned short readTime;
} SensorData;

typedef struct Command
{
    char type;
    unsigned short value;
} Command;


void initializeMockupSensorData(SensorData *sensorData);

void initializeMockupCommandData(Command *command);

uint8_t serializeSensorData(uint8_t *buf, SensorData *sensorData, uint8_t offset);

uint8_t serializeCommand(uint8_t *buf, Command *command, uint8_t offset);

uint8_t deserializeSensorData(SensorData *sensorData, uint8_t *buf, uint8_t offset);

uint8_t deserializeCommand(Command *command, uint8_t *buf, uint8_t offset);