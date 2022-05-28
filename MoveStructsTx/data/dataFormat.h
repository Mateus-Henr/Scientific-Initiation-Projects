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

uint8_t serializeSensorData(uint8_t *buf, SensorData *sensorData, uint8_t offset);

uint8_t serializeCommand(uint8_t *buf, Command *command, uint8_t offset);
