/*
 * DHT11 reader using DWT cycle counter for microsecond timing.
 * Measures pulse widths (in us) to distinguish 0 vs 1.
 */
#include "dht.h"
#include "em_gpio.h"
#include "em_core.h"
#include "em_device.h"
#include <stdio.h>

// Configure these to match your wiring
#define DHT11_PORT gpioPortC
#define DHT11_PIN 1

// Host timing parameters
#define DHT11_START_SIGNAL_LOW_MS 20
// Threshold in microseconds used to distinguish a '0' from a '1'
#define DHT11_BIT_THRESHOLD_US 50

// Enable to get debug prints on the console
#define DHT_DEBUG 0

static uint32_t cycles_per_us;

static void dwt_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    cycles_per_us = SystemCoreClock / 1000000U;
}

static inline uint32_t micros(void)
{
    // Protect against zero division if SystemCoreClock not yet set
    return (uint32_t)(DWT->CYCCNT / (cycles_per_us ? cycles_per_us : 1));
}

static void delay_ms(uint32_t ms)
{
    uint32_t start = micros();
    while ((micros() - start) < (ms * 1000U))
    {
        __NOP();
    }
}

void DHT11_Init(void)
{
    dwt_init();
    GPIO_PinModeSet(DHT11_PORT, DHT11_PIN, gpioModeInputPull, 1);
}

static inline void dht_drive_low(void)
{
    GPIO_PinModeSet(DHT11_PORT, DHT11_PIN, gpioModePushPull, 0);
    GPIO_PinOutClear(DHT11_PORT, DHT11_PIN);
}

static inline void dht_release_input(void)
{
    GPIO_PinModeSet(DHT11_PORT, DHT11_PIN, gpioModeInputPull, 1);
}

static bool wait_level(uint32_t level, uint32_t timeout_us)
{
    uint32_t start = micros();
    while (GPIO_PinInGet(DHT11_PORT, DHT11_PIN) != level)
    {
        if ((micros() - start) > timeout_us)
            return false;
    }
    return true;
}

bool DHT11_Read(DHT11_Data_t *data)
{
    uint8_t bytes[5] = {0};
    const int max_retries = 3;

    dht_release_input();

    for (int attempt = 0; attempt < max_retries; ++attempt)
    {
#if DHT_DEBUG
        printf("DHT: attempt %d\r\n", attempt + 1);
#endif
        if (attempt > 0)
        {
            // Wait ~200ms between attempts
            for (volatile int i = 0; i < 200000; ++i)
                __NOP();
        }

#if DHT_DEBUG
        printf("DHT: driving pin low\r\n");
#endif
        // Send start signal
        dht_drive_low();
#if DHT_DEBUG
        printf("DHT: pin driven low\r\n");
#endif
        delay_ms(DHT11_START_SIGNAL_LOW_MS);
#if DHT_DEBUG
        printf("DHT: releasing pin (set high)\r\n");
#endif
        // Pull high for a short time then release
        GPIO_PinModeSet(DHT11_PORT, DHT11_PIN, gpioModePushPull, 1);
        for (volatile int i = 0; i < 80; ++i)
            __NOP();
        dht_release_input();
#if DHT_DEBUG
        printf("DHT: pin released, waiting for ACK low\r\n");
#endif
        if (!wait_level(0, 120))
        {
#if DHT_DEBUG
            printf("DHT: no ACK low (timeout)\r\n");
#endif
            continue;
        }
#if DHT_DEBUG
        printf("DHT: got ACK low, waiting for ACK high\r\n");
#endif
        if (!wait_level(1, 120))
        {
#if DHT_DEBUG
            printf("DHT: no ACK high (timeout)\r\n");
#endif
            continue;
        }
#if DHT_DEBUG
        printf("DHT: got ACK high, reading bits\r\n");
#endif
        // Read 40 bits: 5 bytes
        bool ok = true;
        for (int b = 0; b < 5 && ok; ++b)
        {
            bytes[b] = 0;
            for (int bit = 0; bit < 8; ++bit)
            {
#if DHT_DEBUG
                printf("DHT: waiting for bit %d.%d low\r\n", b, bit);
#endif
                if (!wait_level(0, 80))
                {
#if DHT_DEBUG
                    printf("DHT: bit %d.%d no low (timeout)\r\n", b, bit);
#endif
                    ok = false;
                    break;
                }
#if DHT_DEBUG
                printf("DHT: waiting for bit %d.%d high\r\n", b, bit);
#endif
                if (!wait_level(1, 120))
                {
#if DHT_DEBUG
                    printf("DHT: bit %d.%d no high (timeout)\r\n", b, bit);
#endif
                    ok = false;
                    break;
                }
                uint32_t t0 = micros();
#if DHT_DEBUG
                printf("DHT: waiting for bit %d.%d end\r\n", b, bit);
#endif
                if (!wait_level(0, 300))
                {
#if DHT_DEBUG
                    printf("DHT: bit %d.%d no end (timeout)\r\n", b, bit);
#endif
                    ok = false;
                    break;
                }
                uint32_t t_high = micros() - t0;
                if (t_high > DHT11_BIT_THRESHOLD_US)
                    bytes[b] |= (1 << (7 - bit));
#if DHT_DEBUG
                printf("DHT: b=%d bit=%d t_high=%lu\r\n", b, bit, (unsigned long)t_high);
#endif
            }
        }
        if (!ok)
            continue;
        data->humidity_int = bytes[0];
        data->humidity_dec = bytes[1];
        data->temperature_int = bytes[2];
        data->temperature_dec = bytes[3];
        data->checksum = bytes[4];
        uint8_t sum = bytes[0] + bytes[1] + bytes[2] + bytes[3];
        if (sum != bytes[4])
        {
#if DHT_DEBUG
            printf("DHT: checksum mismatch got=0x%02x expected=0x%02x\r\n", bytes[4], sum);
#endif
            continue;
        }
#if DHT_DEBUG
        printf("DHT: OK H=%d.%d T=%d.%d\r\n", data->humidity_int, data->humidity_dec, data->temperature_int, data->temperature_dec);
#endif
        return true;
    }
    return false;
}

void DHT11_Print(const DHT11_Data_t *data)
{
    printf("Humidity: %d.%d%%\r\n", data->humidity_int, data->humidity_dec);
    printf("Temperature: %d.%dC\r\n", data->temperature_int, data->temperature_dec);
}
