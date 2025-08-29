#ifndef DHT_H
#define DHT_H

#include <stdint.h>
#include <stdbool.h>

// DHT11 sensor data structure
typedef struct
{
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t checksum;
} DHT11_Data_t;

// Initialize the DHT11 sensor (configure GPIO)
void DHT11_Init(void);

// Read data from the DHT11 sensor
// Returns true if successful, false otherwise
bool DHT11_Read(DHT11_Data_t *data);

// Print the sensor data to terminal
void DHT11_Print(const DHT11_Data_t *data);

#endif // DHT_H
