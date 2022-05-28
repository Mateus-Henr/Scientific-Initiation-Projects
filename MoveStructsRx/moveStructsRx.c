/*  ======== moveStructsRx.c ========
*/

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Data transmission files */
#include "data/dataFormat.h"

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/LED.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* DIO6, LaunchPad LED Red */
#define CONFIG_LED_0                    0

/* DIO6, LaunchPad LED Green */
#define CONFIG_LED_1                    1

/* Number of LEDs */
#define CONFIG_LEDCOUNT        2

/* Time */
#define ONE_SECOND 1000


/* LED handle */
LED_Handle ledHandle[CONFIG_LEDCOUNT];

/* Packet that receives the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Initialise variable */
    LED_Params ledParams;

    /* Open LED pins */
    LED_init();
    Board_initGeneral();

    /* Open LED0 and LED1 with default parameters */
    LED_Params_init(&ledParams);
    ledHandle[CONFIG_LED_0] = LED_open(CONFIG_LED_0, &ledParams);
    ledHandle[CONFIG_LED_1] = LED_open(CONFIG_LED_1, &ledParams);

    /* Initialise the EasyLink parameters to their default values */
    EasyLink_Params easyLink_params;
    EasyLink_Params_init(&easyLink_params);

    /*
     * Initialise EasyLink with the settings found in ti_easylink_config.h
     * Modify EASYLINK_PARAM_CONFIG in ti_easylink_config.h to change the default
     * PHY
     */
    if (EasyLink_init(&easyLink_params) != EasyLink_Status_Success)
    {
        System_abort("EasyLink_init failed");
    }

    while (1)
    {
        /* Initialise variables */
        SensorData sensorData;
        Command command;

        /* Receive the packet */
        EasyLink_Status result = EasyLink_receive(&rxPacket);

        if (result == EasyLink_Status_Success)
        {
            /* Deserialize data received into the proper struct */
            deserializeCommand(&command, rxPacket.payload, deserializeSensorData(&sensorData, rxPacket.payload, 0));

            /* Check if data received is equal to the mockup data that was sent */
            if (sensorData.value == 555555 && sensorData.readTime == 250520022 && command.type == 10 && command.value == 50)
            {
                LED_startBlinking(ledHandle[CONFIG_LED_0], ONE_SECOND, LED_BLINK_FOREVER);

                /* Sending data back */

            }
        }
    }
}
