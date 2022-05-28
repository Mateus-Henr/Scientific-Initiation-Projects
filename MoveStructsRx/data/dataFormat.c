#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "dataFormat.h"


/*
 * Deserialize the data back to the specified struct.
 *
 * @param     sensorData      pointer to the struct (dest).
 * @param     buf             buffer to store the data (src).
 * @param     offset          start position in the buffer.
 * @return                    final position in the buffer.
 */
uint8_t deserializeSensorData(SensorData *sensorData, uint8_t *buf, uint8_t offset)
{
    memcpy(&sensorData->value, buf + offset, sizeof(sensorData->value));
    memcpy(&sensorData->readTime, buf + offset + 1, sizeof(sensorData->readTime));

    return offset + 2;
}


/*
 * Deserialize the data back to the specified struct.
 *
 * @param     command      pointer to the struct (dest).
 * @param     buf          buffer to store the data (src).
 * @param     offset       start position in the buffer.
 * @return                 final position in the buffer.
 */
uint8_t deserializeCommand(Command *command, uint8_t *buf, uint8_t offset)
{
    memcpy(&command->type, buf + offset, sizeof(command->type));
    memcpy(&command->value, buf + offset + 1, sizeof(command->value));

    return offset + 2;
}
