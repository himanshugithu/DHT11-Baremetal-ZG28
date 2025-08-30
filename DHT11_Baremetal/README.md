# DHT11-Baremetal Project

This project demonstrates how to interface with a DHT11 temperature and humidity sensor using bare-metal C on a Silicon Labs microcontroller. The code is designed for use with Simplicity Studio and the Gecko SDK.

## DHT Driver Overview (`dht.c`/`dht.h`)

The DHT11 driver provides functions to initialize the sensor, read data, and print the results. It uses precise microsecond timing via the DWT cycle counter to communicate with the sensor.

### Key Functions
- **DHT11_Init()**: Initializes the GPIO pin and DWT timer for communication.
- **DHT11_Read(DHT11_Data_t *data)**: Reads temperature and humidity data from the sensor. Returns `true` if successful.
- **DHT11_Print(const DHT11_Data_t *data)**: Prints the sensor data to the terminal.

### How Data is Read
1. **Initialization**: The DWT cycle counter is enabled for microsecond timing. The data pin is set as input with pull-up.
2. **Start Signal**: The host pulls the data line low for at least 20ms, then releases it to signal the DHT11 to start transmission.
3. **Sensor Response**: The DHT11 pulls the line low and then high to acknowledge.
4. **Data Transmission**: The sensor sends 40 bits (5 bytes) of data. Each bit is sent as:
   - 50us low pulse
   - High pulse: ~26-28us for '0', ~70us for '1'
   - The code measures the high pulse width to distinguish between 0 and 1.
5. **Checksum**: The last byte is a checksum (sum of previous 4 bytes). The driver verifies this before returning data.

### Data Structure
```
typedef struct {
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t checksum;
} DHT11_Data_t;
```

## How to Build and Run

### Importing the Project from GitHub

1. **Copy the GitHub Repository Link**
   - `https://github.com/himanshugithu/Wi-SUN-DHT11.git`
2. **Open Simplicity Studio**
3. **Add External Repository**
   - Go to `Preferences` > `Simplicity Studio` > `External Repos`.
   - Click on `New` and paste the GitHub link above.
4. **Import the Project**
   - Go to the `Launcher` tab.
   - Select `Example Projects and Demos`.
   - In the list, under the provider section, find `dht baremetal-zg28` project.
   - Click on `Create` to automatically import the project into your workspace.
5. **Connect Hardware**
   - Connect the DHT11 data pin to Port C, Pin 1 (default in code: `gpioPortC`, pin 1).
   - Adjust `DHT11_PORT` and `DHT11_PIN` in `dht.c` if using a different pin.
6. **Build the Project**
   - Click the build button or use the build command in Simplicity Studio.
7. **Flash to Device**
   - Connect your Silicon Labs board and flash the binary.
8. **View Output**
   - Open the serial terminal. The application prints temperature and humidity readings, or an error if the read fails.

## Main Application Flow
- `main.c` initializes the system and calls `app_init()`.
- `app_init.c` creates the main application thread (`app_task`).
- `app.c` runs `DHT11_Init()` and repeatedly calls `DHT11_Read()` to get sensor data and print it.

## Troubleshooting
- Ensure the sensor is wired correctly and powered.
- If you get repeated "DHT11 read failed!" messages, check the data pin and timing.
- Adjust delays or pin configuration as needed for your hardware.

## File Structure
- `dht.c`, `dht.h`: DHT11 driver
- `app.c`: Application logic
- `main.c`: Entry point
- `app_init.c`: RTOS/thread setup

---

## **Author :** 

Himanshu Fanibhare
---