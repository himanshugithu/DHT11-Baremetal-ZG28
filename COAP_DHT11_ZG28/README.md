# DHT11-COAP Project

This project demonstrates how to interface with a DHT11 temperature and humidity sensor using bare-metal C on a Silicon Labs EFR32ZG28 and expose the dht11 data using coap command. The code is designed for use with Simplicity Studio and the Gecko SDK.

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
   - In the list, under the provider section, find `Wi-SUN DHT11(2)` > `COAP_DHT11_ZG28` project.
   - Click on `Create` to automatically import the project into your workspace.
5. **Connect Hardware**
   - Connect the DHT11 data pin to Port C, Pin 1 (default in code: `gpioPortC`, pin 1) on board pin name is `C01`.
   - Adjust `DHT11_PORT` and `DHT11_PIN` in `dht.c` if using a different pin.
6. **Wi-SUN configuration**
   - Open the `COAP_DHT11_ZG28.slcp` file.
   - In the OVERVIEW section, find and open the `Wi-SUN Configurator`.
   - In the `Application` tab, set the `Network Name` to match your Wi-SUN Border Router's network name.
   - In the `Radio` tab, update the parameters to match your border router's configuration so the device can join the network.
7. **Build And Flash the Project**
   - Click the build button. 
   - After the project builds successfully, the binaries will be generated. 
   - Select the `.s37` file and flash it to the connected device.
8. **View Output**
   - Open the serial terminal to check the logs and confirm the device has started and joined the Wi-SUN network.

---

### Accessing DHT11 Data via CoAP

1. **Allow the device to join the Wi-SUN network.**
2. **Find the device's IPv6 address.**
   - You can find this in the serial terminal output or by checking your border router's device list using `wbsrd_cli status`.
3. **Use a CoAP client (`coap-client-notls`) on border router to query the endpoints:**
   - Get temperature:
     ```sh
     coap-client-notls -m get coap://[<device-ipv6>]:5683/temp
     ```
   - Get humidity:
     ```sh
     coap-client-notls -m get coap://[<device-ipv6>]:5683/humi
     ```
   - Get both as JSON:
     ```sh
     coap-client-notls -m get coap://[<device-ipv6>]:5683/dht_data
     ```
4. **Interpret the response:**
   - If successful, you will receive the sensor data as text or JSON.
   - If there is a wiring or timing issue, you may receive a `DHT read error` message.

---

### CoAP Endpoints

| Endpoint    | Description                              | Response Example                           |
|-------------|------------------------------------------|--------------------------------------------|
| `/temp`     | Returns temperature as text              | `Temperature : 23.0 C`                     |
| `/humi`     | Returns humidity as text                 | `Humidity : 45.0 %`                        |
| `/dht_data` | Returns both temperature and humidity (JSON) | `{"temperature":23.0, "humidity":45.0}` |

---

## Troubleshooting
- Ensure the sensor is wired correctly and powered.
- If you get repeated "DHT read error" messages, check the data pin and timing.
- Adjust delays or pin configuration as needed for your hardware.
- The driver uses microsecond timing and may require a stable clock.

## File Structure
- `dht.c`, `dht.h`: DHT11 driver
- `app_coap.c`: CoAP endpoint handlers for DHT11
- `main.c`: Main application entry point

---

###  Devloper
Himanshu Fanibhare
---
