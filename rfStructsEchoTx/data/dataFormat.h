#include <stdint.h>

typedef struct SensorData
{
    uint16_t value;
    uint16_t readTime;
} SensorData;

typedef struct Command
{
    uint8_t type;
    uint16_t value;
} Command;


void initializeSensorData(SensorData *sensorData, uint16_t value, uint16_t readTime);

void initializeCommandData(Command *command, uint8_t type, uint16_t value);

uint8_t serializeSensorData(uint8_t *buf, SensorData *sensorData, uint8_t offset);

uint8_t serializeCommand(uint8_t *buf, Command *command, uint8_t offset);

uint8_t deserializeSensorData(SensorData *sensorData, uint8_t *buf, uint8_t offset);

uint8_t deserializeCommand(Command *command, uint8_t *buf, uint8_t offset);
