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


SensorData *deserializeSensorData(uint8_t *buf, int offset);

Command *deserializeCommand(uint8_t *buf, int offset);
