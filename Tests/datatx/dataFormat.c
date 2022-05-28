#include <stddef.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#include "dataFormat.h"


/* Initialise SensorData with some mockup data.
 *
 * @param   sensorData    pointer to the struct.
 */
void initializeMockupSensorData(SensorData *sensorData)
{
    sensorData->value = 5555;

    time_t raw_time = time(NULL);
    struct tm *now = localtime(&raw_time);
    // Arrange time into the format 025959 (hhmm)
    sensorData->readTime = now->tm_hour * 100 + now->tm_min;
}


/* Initialise Command with some mockup data.
 *
 * @param   command   pointer to the struct.
 */
void initializeMockupCommandData(Command *command)
{
    command->type = 'c';
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
    memcpy((uint8_t *) buf + offset, &sensorData->value, sizeof(sensorData->value));
    memcpy((uint8_t *) buf + offset + sizeof(sensorData->value), &sensorData->readTime, sizeof(sensorData->readTime));

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
    memcpy((uint8_t *) buf + offset, &command->type, sizeof(command->type));
    memcpy((uint8_t *) buf + offset + sizeof(command->type), &command->value, sizeof(command->value));

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
    memcpy(&sensorData->readTime, (uint8_t *) buf + offset + sizeof(sensorData->value), sizeof(sensorData->readTime));

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
    memcpy(&command->value, (uint8_t *) buf + offset + sizeof(command->type), sizeof(command->value));

    return offset + sizeof(command->type) + sizeof(command->value);
}