/*
 *  ======== moveStructsTx.c ========
 */

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Data transmission files */
#include "data/dataFormat.h"

/* TI-RTOS Header files */
#include <ti/drivers/PIN.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* LaunchPad LED Red, Parent Signal: CONFIG_GPIO_RLED GPIO Pin, (DIO6) */
#define CONFIG_PIN_RLED 0x00000006
/* LaunchPad LED Green, Parent Signal: CONFIG_GPIO_GLED GPIO Pin, (DIO7) */
#define CONFIG_PIN_GLED 0x00000007

#define ONE_SECOND 1000


/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - The specified LEDs are off.
 */
PIN_Config pinTable[] = {CONFIG_PIN_GLED | CONFIG_PIN_RLED};

/* Packet to be sent */
EasyLink_TxPacket txPacket = {{0}, 0, 0, {0}};


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Initialise variables */
    uint8_t onOrOff = 0;
    uint32_t absTime;

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);

    /* Clear LED pins */
    PIN_setOutputValue(ledPinHandle, CONFIG_PIN_GLED, 0);
    PIN_setOutputValue(ledPinHandle, CONFIG_PIN_RLED, 0);

    // Initialise the EasyLink parameters to their default values
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
        /* Set the default address of the receiver */
        txPacket.dstAddr[0] = 0xaa;

        /* Define structs to be sent */
        SensorData sensorData;
        Command command;

        /* Initialise mockup data to be sent */
        initializeMockupSensorData(&sensorData);
        initializeMockupCommandData(&command);

        /* Serialize structs and set the payload's size */
        txPacket.len = serializeCommand(txPacket.payload, &command, serializeSensorData(txPacket.payload, &sensorData, 0));

        /* Set interval of transmission */
        EasyLink_getAbsTime(&absTime);
        txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(ONE_SECOND);

        /* Send packet */
        EasyLink_Status result = EasyLink_transmit(&txPacket);

        /* Indicate that a command has been sent */
        if (result == EasyLink_Status_Success)
        {
            if (onOrOff)
            {
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_GLED, 1);
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_RLED, 0);
            }
            else
            {
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_GLED, 0);
                PIN_setOutputValue(ledPinHandle, CONFIG_PIN_RLED, 1);
            }

            onOrOff = !onOrOff;
        }
    }
}
