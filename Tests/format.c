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

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/LED.h>

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

/* Packet that echos the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Initialise variable */
    LED_Params ledParams;

    /* Call driver init functions */
    Board_initGeneral();
    GPIO_init();
    LED_init();

    /* Configure LEDs pin */
    GPIO_setConfig(CONFIG_GPIO_RLED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_GLED, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn off user LEDs */
    GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_OFF);
    GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);

    /* Initialise the LED parameters */
    LED_Params_init(&ledParams);

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);

    /* Clear LED pins */
    PIN_setOutputValue(ledPinHandle, CONFIG_PIN_GLED, 0);
    PIN_setOutputValue(ledPinHandle, CONFIG_PIN_RLED, 0);

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
        /* Define structs to be sent */
        SensorData sensorDataTx;
        Command commandTx;

        /* Initialise mockup data to be sent */
        initializeMockupSensorData(&sensorDataTx);
        initializeMockupCommandData(&commandTx);

        /* Set the default address of the receiver */
        txPacket.dstAddr[0] = 0xaa;

        /* Serialize structs and set the payload's size */
        txPacket.len = serializeCommand(txPacket.payload, &commandTx, serializeSensorData(txPacket.payload, &sensorDataTx, 0));

        /* Set interval of transmission */
        txPacket.absTime = EasyLink_ms_To_RadioTime(ONE_SECOND);

        /* Send packet */
        EasyLink_Status result = EasyLink_transmit(&txPacket);

        /* Indicate that a command has been sent */
        if (result == EasyLink_Status_Success)
        {
            if (sensorDataRx.value == 5555 && sensorDataRx.readTime == 250520022 && commandRx.type == 10 && commandRx.value == 50)
            {
                /* Switch to Receiver, set a timeout interval of 500ms */
                rxPacket.absTime = 0;
                rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(500);

                EasyLink_Status resultRx = EasyLink_receive(&rxPacket);

                if (resultTx == EasyLink_Status_Success)
                {
                    /* Toggle GLED to indicate Echo TX, clear RLED */
                    GPIO_toggle(CONFIG_GPIO_GLED);
                    GPIO_write(CONFIG_GPIO_GRLED, CONFIG_GPIO_LED_OFF);
                }
                else
                {
                    /* Set RLED and clear GLED to indicate error */
                    GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_ON);
                    GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);
                }
            }
        }
        else
        {
            /* Set RLED and clear GLED to indicate error */
            GPIO_write(CONFIG_GPIO_RLED, CONFIG_GPIO_LED_ON);
            GPIO_write(CONFIG_GPIO_GLED, CONFIG_GPIO_LED_OFF);
        }
    }
}
