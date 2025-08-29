#ifndef DHT_H
#define DHT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t checksum;
} DHT11_Data_t;

void DHT11_Init(void);
bool DHT11_Read(DHT11_Data_t *data);
void DHT11_Print(const DHT11_Data_t *data);

#endif // DHT_H
