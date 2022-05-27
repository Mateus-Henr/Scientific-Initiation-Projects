#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "dataFormat.h"

#define NULL_TERMINATOR 1


/*
 *   Deserialize the data back to the specified struct.
 *
 *  @param     buf      buffer to store the data.
 *  @param     offset   start position in the buffer.
 *  @return             pointer to the struct.
 */
SensorData *deserializeSensorData(uint8_t *buf, int offset)
{
    SensorData *sensorData = (SensorData *) malloc(sizeof(SensorData));

    memcpy(&sensorData->value, buf + offset, sizeof(sensorData->value));
    memcpy(&sensorData->readTime, buf + offset + sizeof(sensorData->value), sizeof(sensorData->readTime));

    return sensorData;
}


/*
 *   Deserialize the data back to the specified struct.
 *
 *  @param     buf      buffer to store the data.
 *  @param     offset   start position in the buffer.
 *  @return             pointer to the struct.
 */
Command *deserializeCommand(uint8_t *buf, int offset)
{
    Command *command = (Command *) malloc(sizeof(Command));

    memcpy(&command->type, buf + offset, sizeof(command->type));
    memcpy(&command->value, buf + offset + sizeof(command->type), sizeof(command->value));

    return command;
}
