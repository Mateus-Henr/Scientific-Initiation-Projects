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


void initializeMockupSensorData(SensorData *sensorData);

void initializeMockupCommandData(Command *command);

char *serializeSensorData(SensorData *sensorData);

char *serializeCommand(Command *command);

//SensorData *deserializeSensorData(uint8_t *buf, int offset);
//
//Command *deserializeCommand(uint8_t *buf, int offset);
