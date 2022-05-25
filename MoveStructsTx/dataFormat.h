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

char *serializeSensorData(SensorData *sensorData);

char *serializeCommand(Command *command);

SensorData *deserializeSensorData(int *buf, int offset);

Command *deserializeCommand(int *buf, int offset);
