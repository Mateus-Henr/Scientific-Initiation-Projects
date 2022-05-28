#include <stdio.h>

#include "datatx/dataFormat.h"

int main()
{
    uint8_t payload[128];

    SensorData sensorDataTx;
    Command commandTx;

    initializeMockupSensorData(&sensorDataTx);
    initializeMockupCommandData(&commandTx);

    uint8_t len = serializeCommand(payload, &commandTx, serializeSensorData(payload, &sensorDataTx, 0));

    printf("Len = %d", len);

    for (int i = 0; i < len; i++)
    {
        printf("\nPayload[%d] = %d", i, payload[i]);
    }

    SensorData sensorDataRx;
    Command commandRx;

    deserializeCommand(&commandRx, payload, deserializeSensorData(&sensorDataRx, payload, 0));

    printf("\n\nSensorData => Value = %hu | Readtime = %hu", sensorDataRx.value, sensorDataRx.readTime);
    printf("\n\nCommand => type = %c | Value = %hu\n", commandRx.type, commandRx.value);

    return 0;
}
