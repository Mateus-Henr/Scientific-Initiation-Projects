typedef struct SensorData
{
  long value; // Same as uint_16t
  long readTime;
} SensorData;

typedef struct Command
{
  int type;
  long value;
} Command;


void initializeMockupSensorData(SensorData *sensorData);

void initializeMockupCommandData(Command *command);

uint8_t *serializeSensorData(SensorData *sensorData);

uint8_t *serializeCommand(Command *command);
