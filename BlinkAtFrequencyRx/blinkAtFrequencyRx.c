/*  ======== blinkAtFrequencyRx.c ========
*/

/* XDC Module Headers */
#include <xdc/runtime/System.h>

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/LED.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* EasyLink API Header files */
#include "easylink/EasyLink.h"

/* DIO6, LaunchPad LED Red */
#define CONFIG_LED_0 0

/* DIO6, LaunchPad LED Green */
#define CONFIG_LED_1 1

/* Number of LEDs */
#define CONFIG_LEDCOUNT 2

/* Number */
#define ONE_HUNDRED 100

/* Indexes */
#define COMMAND_INDEX 0
#define TIME_INDEX 1


/* LED handle */
LED_Handle ledHandle[CONFIG_LEDCOUNT];

/* Packet that receives the data */
EasyLink_RxPacket rxPacket = {{0}, 0, 0, 0, 0, {0}};


/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    LED_Params ledParams;

    /* Initialise drivers */
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
        /* Receive the packet */
        EasyLink_Status result = EasyLink_receive(&rxPacket);

        if (result == EasyLink_Status_Success)
        {
            /* Change LED according to the value received */
            switch (rxPacket.payload[COMMAND_INDEX])
            {
                case 0:
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 1);
                    LED_startBlinking(ledHandle[CONFIG_LED_0],
                                      rxPacket.payload[TIME_INDEX] * ONE_HUNDRED,
                                      LED_BLINK_FOREVER);
                    LED_stopBlinking(ledHandle[CONFIG_LED_1]);
                    LED_setOff(ledHandle[CONFIG_LED_1]);
                    break;

                case 1:
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 1);
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 0);
                    LED_startBlinking(ledHandle[CONFIG_LED_1],
                                      rxPacket.payload[TIME_INDEX] * ONE_HUNDRED,
                                      LED_BLINK_FOREVER);
                    LED_stopBlinking(ledHandle[CONFIG_LED_0]);
                    LED_setOff(ledHandle[CONFIG_LED_0]);
                    break;

                case 2:
                    LED_startBlinking(ledHandle[CONFIG_LED_0],
                                      rxPacket.payload[TIME_INDEX] * ONE_HUNDRED,
                                      LED_BLINK_FOREVER);
                    LED_startBlinking(ledHandle[CONFIG_LED_1],
                                      rxPacket.payload[TIME_INDEX] * ONE_HUNDRED,
                                      LED_BLINK_FOREVER);
                    break;

                default:
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_RLED, 0);
//                PIN_setOutputValue(pinHandle, CONFIG_PIN_GLED, 0);
                    break;
            }
        }
    }
}
