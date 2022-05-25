#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "dataFormat.h"


void initializeMockupSensorData(SensorData *sensorData)
{
  sensorData->value = 555555;

  time_t raw_time;
  time(&raw_time);
  struct tm *now = localtime(&raw_time);
  sensorData->readTime = ((now->tm_mday * 100 + now->tm_mon) * 10000 + now->tm_year);
}


void initializeMockupCommandData(Command *command)
{
  command->type = 10;
  command->value = 50;
}


char *serializeSensorData(SensorData *sensorData)
{
    char *buf = (char *) malloc(sizeof(SensorData));

    memcpy(buf, &sensorData->value, sizeof(sensorData->value));
    memcpy(buf + sizeof(sensorData->value), &sensorData->readTime, sizeof(sensorData->readTime));

    return buf;
}


char *serializeCommand(Command *command)
{
    char *buf = (char *) malloc(sizeof(Command));

    memcpy(buf, &command->type, sizeof(command->type));
    memcpy(buf + sizeof(command->type), &command->value, sizeof(command->value));

    return buf;
}


//SensorData *deserializeSensorData(uint8_t *buf, int offset)
//{
//    SensorData *sensorData = (SensorData *) malloc(sizeof(SensorData));
//
//    memcpy(&sensorData->value, buf + offset, sizeof(sensorData->value));
//    memcpy(&sensorData->readTime, buf + offset + sizeof(sensorData->value), sizeof(sensorData->readTime));
//
//    return sensorData;
//}
//
//
//
//Command *deserializeCommand(uint8_t *buf, int offset)
//{
//    Command *command = (Command *) malloc(sizeof(Command));
//
//    memcpy(&command->type, buf + offset, sizeof(command->type));
//    memcpy(&command->value, buf + offset + sizeof(command->type), sizeof(command->value));
//
//    return command;
//}
