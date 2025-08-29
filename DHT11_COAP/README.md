## DHT11 Sensor & CoAP Endpoint Integration (Project Customization)

This project has been customized to add support for the DHT11 temperature and humidity sensor, exposing its data via CoAP endpoints. Below is a summary of the changes and instructions for use:

### Key Changes Made
- **DHT11 Sensor Integration:**
  - Added `dht.c` and `dht.h` driver files for the DHT11 sensor.
  - Sensor is initialized and read in each CoAP callback.
- **CoAP Endpoints Added:**
  - `/data` — Returns both temperature and humidity as JSON.
  - `/temp` — Returns temperature in Celsius with unit (e.g., `26.7 C`).
  - `/humi` — Returns humidity in percent with unit (e.g., `83.1 %`).
- **Code Cleanup:**
  - Removed all LED/relay code from the project.
  - Ensured all function prototypes and includes are correct.
  - Registered new endpoints in the CoAP resource handler.

### How to Initialize and Use the DHT11 Sensor
1. **Wiring:**
  - Connect the DHT11 sensor's data pin to the appropriate GPIO on your board (see `dht.c` for pin configuration).
  - Provide 3.3V and GND to the sensor.
2. **Initialization in Code:**
  - The DHT11 is initialized in each CoAP callback using `DHT11_Init()` before reading.
  - Reading is performed with `DHT11_Read(&dht_data)`, which fills a `DHT11_Data_t` struct.

### How the CoAP Endpoints Were Added
1. **Callback Functions:**
  - Implemented `coap_callback_dht_data`, `coap_callback_temp`, and `coap_callback_humi` in `app_coap.c`.
  - Each callback initializes and reads the DHT11, then formats the response.
2. **Resource Registration:**
  - In `app_coap_resources_init()`, registered the three endpoints:
    - `/dht_data` → `coap_callback_dht_data`
    - `/temp` → `coap_callback_temp`
    - `/humi` → `coap_callback_humi`
  - Set resource type, interface, and discoverability for each.
3. **Prototypes:**
  - Added function prototypes to `app_coap.h`.
4. **Includes:**
  - Added necessary includes for DHT, CoAP, and standard C headers.

### How to Test
- Build and flash the project to your Wi-SUN node.
- Use a CoAP client (e.g., `coap-client-notls`) to query the endpoints:
  - `coap-client-notls -m get coap://[<node-ip>]:5683/data`  → JSON with temperature and humidity
  - `coap-client-notls -m get coap://[<node-ip>]:5683/temp`  → Temperature with unit
  - `coap-client-notls -m get coap://[<node-ip>]:5683/humi`  → Humidity with unit

### Summary of Files Changed
- `app_coap.c` — Added DHT11 callbacks, includes, and resource registration.
- `app_coap.h` — Added function prototypes and includes.
- `dht.c`/`dht.h` — DHT11 driver (added if not present).
- Removed all LED/relay code from the project.

---
