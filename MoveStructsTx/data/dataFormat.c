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


/*  Serializes data, and store it in an int array.
 *
 * @param    sensorData    pointer to the struct.
 * @return                 pointer to an int array.
 */
uint8_t *serializeSensorData(SensorData *sensorData)
{
    uint8_t *buf = (uint8_t *) malloc(sizeof(SensorData));

    memcpy(buf, &sensorData->value, sizeof(sensorData->value));
    memcpy(buf + sizeof(sensorData->value), &sensorData->readTime, sizeof(sensorData->readTime));

    return buf;
}


/*  Serializes data, and store it in an int array.
 *
 * @param    Command    pointer to the struct.
 * @return              pointer to an int array.
 */
uint8_t *serializeCommand(Command *command)
{
    uint8_t *buf = (uint8_t *) malloc(sizeof(Command));

    memcpy(buf, &command->type, sizeof(command->type));
    memcpy(buf + sizeof(command->type), &command->value, sizeof(command->value));

    return buf;
}
