/*
 *  ======== rfStructsEchoRx.c ========
*/

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* Data transmission files */
#include "data/dataFormat.h"

/* Time */
#define ONE_TENTH_OF_SECOND 100

/* Mockup data */
#define SENSORDATA_READTIME 1356
#define COMMAND_TYPE 'c'
#define COMMAND_VALUE 345


/* Packet that receives the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};

/* Packet that echos the data */
EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Define variable */
    uint32_t absTime;

    /* Call driver init functions */
    Board_initGeneral();

    /* Initialise the EasyLink parameters to their default values */
    EasyLink_Params easyLink_params;
    EasyLink_Params_init(&easyLink_params);

    /* Initialise EasyLink with the settings found in ti_easylink_config.h */
    if (EasyLink_init(&easyLink_params) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_init failed");
    }

    /* Period and duty in microseconds */
    uint16_t   pwmPeriod = 3000;
    uint16_t   duty = 2900;
    uint16_t   dutyInc = 100;

    /* Sleep time in microseconds */
    PWM_Handle pwm1 = NULL;
    PWM_Params params;

    /* Call driver init functions. */
    PWM_init();

    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;
    pwm1 = PWM_open(CONFIG_PWM_0, &params);
    if (pwm1 == NULL) {
        /* CONFIG_PWM_0 did not open */
        while (1);
    }

    PWM_start(pwm1);

    while (1)
    {
        /* Define structs to store data */
        SensorData sensorDataRx;
        Command commandRx;

        /* Receive the packet */
        EasyLink_Status resultRx = EasyLink_receive(&rxPacket);

        if (resultRx == EasyLink_Status_Success)
        {
            /* Deserialize data received into the proper struct */
            deserializeCommand(&commandRx, rxPacket.payload, deserializeSensorData(&sensorDataRx, rxPacket.payload, 0));

            PWM_setDuty(pwm1, sensorDataRx.value);

            /* Define structs to be sent */
            SensorData sensorDataTx;
            Command commandTx;

            duty = (duty + dutyInc);

            if (duty == pwmPeriod || (!duty))
            {
                dutyInc = -dutyInc;
            }

            /* Initialise mockup data to be sent */
            initializeSensorData(&sensorDataTx, duty, SENSORDATA_READTIME);
            initializeCommandData(&commandTx, COMMAND_TYPE, COMMAND_VALUE);

            /* Set the default address of the receiver */
            txPacket.dstAddr[0] = 0xaa;

            /* Serialize structs and set the payload's size */
            txPacket.len = serializeCommand(txPacket.payload, &commandTx, serializeSensorData(txPacket.payload, &sensorDataTx, 0));

            /* Set interval of transmission */
            EasyLink_getAbsTime(&absTime);
            txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(ONE_TENTH_OF_SECOND);

            /* Sending data back */
            EasyLink_Status resultTx = EasyLink_transmit(&txPacket);

            if (resultTx == EasyLink_Status_Success)
            {

            }
        }
    }
}
