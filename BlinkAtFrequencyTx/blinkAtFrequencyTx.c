/*
 *  ======== blinkAtFrequencyTx.c ========
 */

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

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

/* Time */
#define ONE_SECOND 1000
#define FIVE_MILLISECONDS 5000

/* Indexes */
#define COMMAND_INDEX 0
#define TIME_INDEX 1

/* Packet's length*/
#define PAYLOAD_LENGTH 2


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
    uint8_t time = 0;
    uint8_t command = 0;
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

        /* Set values to be sent */
        txPacket.payload[COMMAND_INDEX] = command;
        txPacket.payload[TIME_INDEX] = time;

        /* Set payload's size */
        txPacket.len = PAYLOAD_LENGTH;

        /* Set interval */
        EasyLink_getAbsTime(&absTime);
        txPacket.absTime = absTime + EasyLink_ms_To_RadioTime(ONE_SECOND * time);

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

        /* Reset values  or update values */
        if (command == 3)
        {
            command = 0;
        }
        else
        {
            command++;
        }

        if (time == 10)
        {
            time = 0;
        }
        else
        {
            time++;
        }
    }
}
