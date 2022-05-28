#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "dataFormat.h"


/* Initialise SensorData with some mockup data.
 *
 * @param   sensorData    pointer to the struct.
 */
void initializeMockupSensorData(SensorData *sensorData)
{
  sensorData->value = 555555;

  time_t raw_time = time(NULL);
  struct tm *now = localtime(&raw_time);
  // Arrange data into the format 25022022 (ddmmaaaa)
  sensorData->readTime = ((now->tm_mday * 100 + now->tm_mon) * 10000 + now->tm_year);
}


/* Initialise Command with some mockup data.
 *
 * @param   command   pointer to the struct.
 */
void initializeMockupCommandData(Command *command)
{
  command->type = 10;
  command->value = 50;
}


/*
 * Serializes data, and store it in an array.
 *
 * @param     sensorData   pointer to the struct (dest).
 * @param     buf          buffer to store the data (src).
 * @param     offset       start position in the buffer.
 * @return                 final buffer's index.
 */
uint8_t serializeSensorData(uint8_t *buf, SensorData *sensorData, uint8_t offset)
{
    memcpy(buf + offset, &sensorData->value, sizeof(sensorData->value));
    memcpy(buf + offset + 1, &sensorData->readTime, sizeof(sensorData->readTime));

    return offset + 2;
}


/*
 * Serializes data, and store it in an array.
 *
 * @param     command      pointer to the struct (dest).
 * @param     buf          buffer to store the data (src).
 * @param     offset       start position in the buffer.
 * @return                 final buffer's index.
 */
uint8_t serializeCommand(uint8_t *buf, Command *command, uint8_t offset)
{
    memcpy(buf + offset, &command->type, sizeof(command->type));
    memcpy(buf + offset + 1, &command->value, sizeof(command->value));

    return offset + 2;
}
