typedef struct SensorData
{
  long value;
  long readTime;
} SensorData;

typedef struct Command
{
  int type;
  long value;
} Command;


uint8_t deserializeSensorData(SensorData *sensorData, uint8_t *buf, uint8_t offset);

uint8_t deserializeCommand(Command *command, uint8_t *buf, uint8_t offset);
