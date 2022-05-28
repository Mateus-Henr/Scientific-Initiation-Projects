#include <stddef.h>
#include <time.h>
#include <string.h>

#include "dataFormat.h"


/* Initialise a struct of type SensorData.
 *
 * @param   sensorData    pointer to the struct.
 */
void initializeSensorData(SensorData *sensorData, uint16_t value, uint16_t readTime)
{
    sensorData->value = value;
    sensorData->readTime = readTime;
}


/* Initialise a struct of type Command.
 *
 * @param   command   pointer to the struct.
 */
void initializeCommandData(Command *command, uint8_t type, uint16_t value)
{
    command->type = type;
    command->value = value;
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
    memcpy(buf + offset + sizeof(sensorData->value), &sensorData->readTime, sizeof(sensorData->readTime));

    return offset + sizeof(sensorData->value) + sizeof(sensorData->readTime);
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
    memcpy(buf + offset + sizeof(command->type), &command->value, sizeof(command->value));

    return offset + sizeof(command->type) + sizeof(command->value);
}


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
    memcpy(&sensorData->readTime, buf + offset + sizeof(sensorData->value), sizeof(sensorData->readTime));

    return offset + sizeof(sensorData->value) + sizeof(sensorData->readTime);
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
    memcpy(&command->value, buf + offset + sizeof(command->type), sizeof(command->value));

    return offset + sizeof(command->type) + sizeof(command->value);
}

