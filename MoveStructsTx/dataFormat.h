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

char *serializeComamnd(Command *command);

SensorData *deserializeSensorData(char *buf);

Command *deserializeCommand(char *buf);
