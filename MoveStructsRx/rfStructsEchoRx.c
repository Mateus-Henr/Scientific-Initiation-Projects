/*
 *  ======== moveStructsRx.c ========
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

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* Time */
#define ONE_SECOND 1000


/* Packet that receives the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};

/* Packet that echos the data */
EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
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
        SensorData sensorDataRx;
        Command commandRx;

        /* Receive the packet */
        EasyLink_Status resultRx = EasyLink_receive(&rxPacket);

        if (resultRx == EasyLink_Status_Success)
        {
            GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_ON);
            GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);

            /* Deserialize data received into the proper struct */
            deserializeCommand(&commandRx, rxPacket.payload, deserializeSensorData(&sensorDataRx, rxPacket.payload, 0));

            /* Check if data received is equal to the mockup data that was sent */
            if (sensorDataRx.value == 5555 && sensorDataRx.readTime == 250520022 && commandRx.type == 10 && commandRx.value == 50)
            {
                /* Initialise variables */
                SensorData sensorDataTx;
                Command commandTx;

                /* Initialise mockup data to be sent */
                initializeMockupSensorData(&sensorDataTx);
                initializeMockupCommandData(&commandTx);

                txPacket.absTime = 0;

                /*
                 * Address filtering is enabled by default on the Rx device with the
                 * an address of 0xAA. This device must set the dstAddr accordingly.
                 */
                txPacket.dstAddr[0] = 0xaa;

                /* Serialize structs and set the payload's size */
                txPacket.len = serializeCommand(txPacket.payload, &commandTx, serializeSensorData(txPacket.payload, &sensorDataTx, 0));

                /* Set interval of transmission */
                txPacket.absTime = EasyLink_ms_To_RadioTime(ONE_SECOND);

                /* Sending data back */
                EasyLink_Status resultTx = EasyLink_transmit(&txPacket);

                if (resultTx == EasyLink_Status_Success)
                {
                    /* Toggle GLED to indicate Echo TX, clear RLED */
                    GPIO_toggle(CONFIG_GPIO_GLED);
                    GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_OFF);
                }
            }
        }
    }
}
