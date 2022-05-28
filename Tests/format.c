/*
 *  ======== rfStructsEchoTx.c ========
 */

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* Data transmission files */
#include "data/dataFormat.h"

/* Time */
#define ONE_SECOND 1000

/* Mockup data */
#define SENSORDATA_VALUE 555
#define SENSORDATA_READTIME 1412
#define COMMAND_TYPE 'a'
#define COMMAND_VALUE 123


/* Packet to be sent */
EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};

/* Packet that echos the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver initialisation functions */
    Board_initGeneral();
    GPIO_init();

    /* Configure LEDs pin */
    GPIO_setConfig(CONFIG_GPIO_RLED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_GLED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn off user LEDs */
    GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_OFF);
    GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);

    /* Initialise the EasyLink parameters to their default values */
    EasyLink_Params easyLink_params;
    EasyLink_Params_init(&easyLink_params);

    /* Initialise EasyLink with the settings found in ti_easylink_config.h */
    if (EasyLink_init(&easyLink_params) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_init failed");
    }

    while (1)
    {
        /* Define structs to be sent */
        SensorData sensorDataTx;
        Command commandTx;

        /* Initialise structs with mockup data */
        initializeSensorData(&sensorDataTx, SENSORDATA_VALUE, SENSORDATA_READTIME);
        initializeCommandData(&commandTx, COMMAND_TYPE, COMMAND_VALUE);

        /* Set the default address of the receiver */
        txPacket.dstAddr[0] = 0xaa;

        /* Serialize structs, and set the payload's size */
        txPacket.len = serializeCommand(txPacket.payload, &commandTx, serializeSensorData(txPacket.payload, &sensorDataTx, 0));

        /* Set interval of transmission 1000ms */
        txPacket.absTime = EasyLink_ms_To_RadioTime(ONE_SECOND);

        /* Send packet */
        EasyLink_Status result = EasyLink_transmit(&txPacket);

        if (result == EasyLink_Status_Success)
        {
            /* Toggle RLED to Indicate that a command has been sent, clear GLED */
            GPIO_toggle(CONFIG_GPIO_RLED);
            GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);

            /* Switch to Receiver and set interval of transmission */
            rxPacket.absTime = 0;

            /* Receive packet */
            EasyLink_Status resultRx = EasyLink_receive(&rxPacket);

            /* Define structs to be sent */
            SensorData sensorDataRx;
            Command commandRx;

            /* Deserialize data received into the proper struct */
            deserializeCommand(&commandRx, rxPacket.payload, deserializeSensorData(&sensorDataRx, rxPacket.payload, 0));

            if (resultRx == EasyLink_Status_Success)
            {
                if (sensorDataRx.value == 444 && sensorDataRx.readTime == 1356 && commandRx.type == 'c' && commandRx.value == 345)
                {
                    /* Toggle GLED to indicate Echo RX, clear RLED */
                    GPIO_toggle(CONFIG_GPIO_GLED);
                    GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_OFF);
                }
            }
        }
    }
}
