<table border="0">
  <tr>
    <td align="left" valign="middle">
    <h1>SCRC Wi-SUN Node Monitoring</h1>
  </td>
  <td align="left" valign="middle">
    <a href="https://smartcitylivinglab.iiit.ac.in">
      <img src="https://smartcitylivinglab.iiit.ac.in/assets/img/logo.png"  title="Smart City Living Lab IIITH Logo" alt="Smart City Living Lab IIITH Logo" width="100"/>
    </a>
  </td>
  <td align="left" valign="middle"> 
    <a href="https://www.silabs.com">
      <img src="https://avatars.githubusercontent.com/u/7750191?s=280&v=4" alt="SiLabs Logo" width="100" /> 
    </a>
  </td>
  </tr>
</table>

![SiSDK Version](https://img.shields.io/badge/SiSDK%20Version-6.0-blue)

This Repository Supports 
![FAN 1.0 FSK](https://img.shields.io/badge/FAN%201.0-FSK-blue)
![FAN 1.1 FSK](https://img.shields.io/badge/FAN%201.1-FSK-blue)
![FAN 1.1 OFDM](https://img.shields.io/badge/FAN%201.1-OFDM-blue)
![EFR32xG12](https://img.shields.io/badge/EFR32xG12-Board-green)
![EFR32xG25](https://img.shields.io/badge/EFR32xG25-Board-green)
![EFR32xG28](https://img.shields.io/badge/EFR32xG28-Board-green)

## Table of Contents

 - [Introduction](#introduction)
 - [Software Required](#software-required)
   - [Installation of Simplicity Studio 5](#installation-of-simplicity-studio-5)
 - [Hardware Required](#hardware-required)
    - [Border Router Setup](#border-router-setup)
       - [Installation of Wi-SUN Border Router GUI](#installation-of-wi-sun-border-router-gui)
       - [Cockpit Launch](#cockpit-launch)
       - [Wi-SUN Dashboard Tab](#wi-sun-dashboard-tab)
    - [Wi-SUN Dashboard](#wi-sun-dashboard)
 - [Wi-SUN Tutorial](#wi-sun-tutorial)
    - [Starting the Application](#starting-the-application)
       - [Add the Wi-SUN Applications Repository to Simplicity Studio](#add-the-wi-sun-applications-repository-to-simplicity-studio)
    - [Create Bootloader Project](#create-bootloader-project)
    - [Creating Node Monitoring Application](#creating-node-monitoring-application)
 - [Wi-SUN Board Configuration](#wi-sun-board-configuration)
   - [Wi-SUN Configuration Table](#wi-sun-configuration-table)
 - [Checking Network Connection](#checking-network-connection)
   - [Retrieve the MAC Address](#retrieve-the-mac-address)
   - [Verify Connection in Cockpit Interface](#verify-connection-in-cockpit-interface)
   - [Cross-Check via Topology](#cross-check-via-topology)
 - [Nodes Information](#nodes-information)
 - [Pin Configuration of LEDs and RELAYS](#pin-configuration-of-leds-and-relays)
 - [oneM2M Overview](#onem2m-overview)
   - [oneM2M Architecture](#onem2m-architecture)
   - [Webpage Link](#webpage-link)
   - [About oneM2M Container](#about-onem2m-container)
   - [oneM2M Data Format](#onem2m-data-format)
 - [oneM2M Tutorial Videos](#onem2m-tutorial-videos)

## Introduction

This project aims to implement a Wi-SUN network monitoring system using a Linux Border Router and a Wi-SUN FAN1.1_FSK node monitoring flashed on EFR32FG25.

The block diagram of this application is shown in the image below:

<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/blockdiagram.jpg" alt="MLBC">



- To learn Wi-SUN technology basics, visit [the Wi-SUN pages on docs.silabs.com](https://docs.silabs.com/wisun/latest/wisun-start/).

- To learn code-level information on the node monitoring application, see [Add a Custom Application in the Wi-SUN Development Walkthrough](https://docs.silabs.com/wisun/latest/wisun-custom-application/)

# Software Required 
- Simplicity Studio

## Installation of Simplicity studio 5

To know more about Simplicity Studio, you can go through the [user guide](https://docs.silabs.com/simplicity-studio-5-users-guide/5.3.0/ss-5-users-guide-overview/)
Search Silicon labs Simplicity Studio on a browser,
Create an Account in Simplicity Studio and
Click on Required Installer
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20104138.png" alt="MLBC">

Go through the below video for complete installation process [here](https://youtu.be/ONrmMEgFYMo?si=FESHt9YXUVKaqHwz)

# Hardware Required

The following is required to run this Application:

 - EFR32 radio board
 - A Raspberry Pi 3 Model B+ or above with an Internet connection (another Linux host should also work)
 - An SD card (4 GB or more) and SD card slot/dongle
 - 2 WTSK/WPK boards


# Border Router Setup

The Wi-SUN RCP (Radio Co-Processor) must be connected to the Linux platform as detailed in [AN1332 Wi-SUN Network Configuration](https://www.silabs.com/documents/public/application-notes/an1332-wi-sun-network-configuration.pdf), either using

- A USB connection between the Linux Platform and a Wi-SUN Pro kit

<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Border_Router.jpg" alt="MLBC">
To know more about the Border Router Connections visit [linux-br](https://docs.silabs.com/wisun/1.8.0/wisun-network-configuration/03-wisun-linux-border-router/)

To setup Wi-SUN Br follow the below repository
(https://github.com/SiliconLabs/wisun-br-linux)

## Installation of Wi-SUN Border Router GUI
Follow the below Repository to setup BR GUI
(https://github.com/SiliconLabs/wisun-br-gui)

## Cockpit Launch
Cockpit features are accessible through its Web interface. It is available at http://[border router server]:9090/.
If the plugin was installed correctly, it should appear in the left side panel of Cockpit's Web interface as Wi-SUN Border Router.
After setting up login by providing the required credentials

<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20105145.png" alt="MLBC">

## Wi-SUN Dashboard tab

The Wi-SUN Dashboard tab provides direct access to wsbrd.conf configuration file. It gives the ability to change your wsbrd configuration without the need to physically access the Raspberry Pi. The Wi-SUN Border Router service box allows the user to start, restart or stop the Wi-SUN Border Router service by clicking the three dots dropdown. The other boxes expose the Wi-SUN Border Router active configuration.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20105200.png" alt="MLBC">

# WI-SUN Dashboard

The Wi-SUN dashboard is based on Wi-SUN technology deployed in devices on streetlights around the IIIT Hyderabad campus. Through this dashboard, we can control the streetlight status, turning them on or off. Additionally, the dashboard displays monitored parameters such as RSSI, RPL rank, ETX, and latency. A DODAG network is available to check the connections of nodes in real time. By clicking on a connection, you can see the distance between devices, and hovering over a node shows the distance from the border router to the device.
Visit the below link to view smart city wisun dashboard
[dashboard](https://smartcityresearch.iiit.ac.in/living_lab/dashboard/)

**Features**:
1. View the number of devices linked to a single control point. Control points are displayed in a rectangular shape.
2. Control the streetlights. 
3. A legend shows different versions of Wi-SUN deployments: FAN 1.0 FSK - green, FAN 1.1 OFDM - blue, FAN 1.1 FSK - pink, and another icon for LFN.
4. A dropdown is available to view different types of analytics.
5. An expanded view of analytics can be accessed via a side navigation panel.

## Wi-SUN Tutorial 
[Wi-SUN Day1 tutorial video](https://www.youtube.com/watch?v=hO6Trd54_mI&list=PL2dLj7mmI2T5j-odkPucoXsa9O4X_FmDm&pp=gAQBiAQB)

[Wi-SUN Day2 tutorial video](https://www.youtube.com/watch?v=pVbA5CXoIKc&list=PL2dLj7mmI2T5jtOT0xxCmvHUoWm25XDfD&pp=gAQBiAQB)

# Starting the Application

Add the Wi-SUN Applications Repository to Simplicity Studio
1. Open Simplicity Studio and connect the Main board.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20110119.png" alt="MLBC">
2. Navigate to `Window` -> `Preferences` -> `Simplicity Studio` -> `External Repos`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20110129.png" alt="MLBC">
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20110141.png" alt="MLBC">
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20110151.png" alt="MLBC">
3. Click on `Add` and paste the URI of the repository: 
(https://github.com/mssuhaas/SCRC_Wi-SUN.git)
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-07-04%20153103.png" alt="MLBC">
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-07-04%20151719.png" alt="MLBC">
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-07-04%20151812.png" alt="MLBC">
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20110232.png" alt="MLBC">



# Create Bootloader Project:
1.	Click on `Bootloader- SoC SPI Flash Storage( 1024)` and then click on `Create`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112354.png" alt="MLBC">
2.check the project configuration
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112402.png" alt="MLBC">
3.Open Configuration File
   - Open the `.slcp` file in your project directory.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112412.png" alt="MLBC">
4.Configure Software Components- Configure the necessary software components as required for your project.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112421.png" alt="MLBC">
Install LZMA
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112429.png" alt="MLBC">
5.Build the Project- Build the project to compile the code and prepare it for flashing.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112440.png" alt="MLBC">
Ensure the build completes with zero errors.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112448.png" alt="MLBC">
6.Erase and Flash to the Device:
   - Navigate to the `.s37` file in the binaries folder.
   - First, erase the existing firmware on the device.
   - Then, program and flash the new firmware onto the device.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112502.png" alt="MLBC">
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20112514.png" alt="MLBC">

# Creating Node Monitoring Application:

1. Click on start:
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114557.png" alt="MLBC">

2. Click on Example Projects and Demos.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114621.png" alt="MLBC">

3. Scroll down to the provider section, where you will find Wi-SUN applications listed along with the Gecko SDK.
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-07-04%20154640.png" alt="MLBC">

4. Click on `Wi-SUN Applications`.

5. Locate the resource called `Wi-SUN Node Monitoring Application` and click on `Create`.
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-07-04%20155104.png" alt="MLBC">

6. Project Configuration:
1. You will be prompted with the project configuration screen, where you can select the target SDK and examples.
2. Review and confirm the project name and location.
3. Click on `Finish` to complete the setup.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114645.png" alt="MLBC">

7. Board Configuration
Now a new project is created. Follow these steps to configure the board:
 
**Access the Project Configuration**:
1. Locate the project file in your project directory.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114655.png" alt="MLBC">
Right click on the project file and go to show in and then to system explorer
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-05-23%20121541.png" alt="MLBC">
Here we will find the all the files of our project
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-06-01%20120500.png" alt="MLBC">
Delete the following files from that place -app,app_check_neighbour,app_coap,app_init,app_rtt_traces,app_tcp_server,app_timestamp,app_udp_server,both .c and .h files and  main.c and go to this repository (https://github.com/vaibhavnaware01/FAN11_FSK_FG25)
<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/Screenshot%202024-06-01%20120526.png" alt="MLBC">
download those files from the Repository and paste them in your system project folder.
Go to the autogen folder of your project file ,in this Repository ,you will find all the files with the same names 
Delete the sl_wisun_config.h file and you will find the same file in our repository download it and place it here.

Click on the .slcp file in binary folder
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114703.png" alt="MLBC">
# Wi-SUN board configuration
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114715.png" alt="MLBC">
Applications: Here, you will find network information such as the network name and size.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114721.png" alt="MLBC">
Security: This section contains the device's private key, device certificate, and other security-related settings.

Radio:For Wi-SUN FAN 1.0: You can configure the regulatory domain, operating class, and operating mode.For Wi-SUN FAN 1.1: You can configure the regulatory domain, PHY operating mode ID, and channel ID.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114730.png" alt="MLBC">
# Wi-SUN Configuration table

|                       | FAN1.0                                         | FAN1.1_FSK                                  | FAN1.1_OFDM                            |
|-----------------------|------------------------------------------------|---------------------------------------------|----------------------------------------|
| Regulatory domain     | NA (0x01), BZ (0x07), IN (0x05), CN (0x04), JP (0x02), EU (0x03) | NA (0x01), BZ (0x07), IN (0x05), CN (0x04), JP (0x02), EU (0x03) | NA (0x01), BZ (0x07), IN (0x05), CN (0x04), JP (0x02), EU (0x03) |
| Operating class       | 1, 2                                      |                                              |                                        |
| Operating mode        | 1a, 1b                                    |                                              |                                        |
| PHY Operating Mode ID |                                               | 1, 3, 5                                  | 1, 3, 5                          |
| Channel Plan ID       |                                               | 1, 2, 3, 4, 5, 21, 22,                   | 1, 2, 3, 4, 5, 21, 22, 23, 24, 32, 33, |
|                       |                                               | 23, 24, 32, 33,                          | 34, 35, 36, 37                          |
|                       |                                               | 34, 35, 36, 37                           |                                        |

## Configuration used:

| **Config.**               | **FAN 1.0 FSK** | **FAN 1.1 FSK** | **FAN 1.1 OFDM** |
|---------------------------|-----------------|-----------------|------------------|
| **Regulatory Domain**     | IN              |  EU             | EU               |
| **PHY Operating Mode ID** | N/A             | 5               | 3                |
| **Channel Plan ID**       | N/A             | 33              | 35               |
| **Class**                 | 2               | N/A             | N/A              |
| **Mode**                  | 3               | N/A             | N/A              |

1. Provide the necessary information in each section.
2. Click on `Apply Configuration` and save the changes.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114752.png" alt="MLBC">
And press ctrl+s to save the Wi-SUN configuration
9.Build the Project 1.Go to the Project Explorer, right-click on your project name, and select `Build Project`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114800.png" alt="MLBC">
2. Ensure the build completes with zero errors.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114807.png" alt="MLBC">
10.Flash the Device
1.	After the build is finished, navigate to the `binaries` folder.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114831.png" alt="MLBC">
2. Locate the `.s37` file, click on it, and select `Flash to Device`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114840.png" alt="MLBC">
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20114847.png" alt="MLBC">

# Checking Network Connection
To verify if the device is connected to the desired network, follow these steps:
## Retrieve the MAC Address
1.	Connect the device to your system.
2.Go to Debug adapters and right click on the board name
3. Click on `Launch Console`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20121225.png" alt="MLBC">
4. If the device is successfully connected to the network, you will see the five states.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20121230.png" alt="MLBC">
5. You can get the MAC address of the device
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20121245.png" alt="MLBC">
## Verify Connection in Cockpit Interface
1. Open the Cockpit interface.
2. Click on `Terminal`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20121250.png" alt="MLBC">
3. Enter the command `wsbrd_cli status`.
<img src="https://github.com/Joswitha-123/wisunreadme/blob/master/Screenshot%202024-05-22%20121256.png" alt="MLBC">
4. This will display the connected nodes. You can check here to confirm if your device is connected to the network.
## Cross-Check via Topology
1. Alternatively, you can click on `Topology` in the Cockpit interface.
2. Locate your node in the displayed network topology to verify its connection status.
3. For this version ,this won’t work, we can do this for the versions which it can be applicable

## Nodes Information

| Node ID    | Pole Number                      | IPv6 Address                             | Lat, Long              | Relay(On/Off) Commands     |
|------------|----------------------------------|------------------------------------------|------------------------|--------------------------|
| WN-L031-30 | 2                                | FD12:3456::B635:22FF:FE98:2537           | 17.443894,78.349547    |relay(0/1)(on/off)          |
| WN-L032-30 | 4                                | FD12:3456::B635:22FF:FE98:2523           | 17.443754,78.349237    |relay(0/1)(on/off)          |
| WN-L033-30 | 6                                | FD12:3456::B635:22FF:FE98:252B           | 17.44443843,78.348820  |relay(0/1)(on/off)          |
| WN-L034-30 | 18                               | FD12:3456::62A4:23FF:FE37:A3B3           | 17.444449,78.350024    |relay(0/1)(on/off)          |
| WN-L035-30 | PT21                             | FD12:3456::B635:22FF:FE98:285B           | 17.4444563,78.34862    |relay(0/1)(on/off)          |
| WN-L036-30 | 17C                              | FD12:3456::62A4:23FF:FE37:A3A1           | 17.443230,78.348910    |relay(0/1)(on/off)          |
| WN-L037-30 | 17Z                              | FD12:3456::92FD:9FFF:FEEE:9D4D           | 17.4437708,78.3481379  |relay(0/1)(on/off)          |
| WN-OF04-34 | Faculty quarter control point    | FD12:3456::B635:22FF:FE98:285C           | 17.4438353,78.34898847 |relay(0/1)(on/off)          |
## Pin configuration of LEDs and RELAYS

| Board | LED0    | LED1    | Relay1    | Relay2    |
|-------|------   |------   |--------   |--------   |
| MG12  | PF4     |  PF5    |PF10       | PC2       |
| FG25  | PC6     |  PC7    |PA5        | PC2       |


# oneM2M Overview

oneM2M defines a horizontal service layer for IoT, enabling interoperability between devices, gateways, and applications. This open standard utilizes common protocols and APIs for secure data exchange and device management, fostering a unified and scalable IoT ecosystem.

## oneM2M Architecture
Below is the functional Architecture of onem2m 

<img src="https://github.com/vaibhavnaware01/FAN11_FSK_FG25/blob/main/images/onem2m.jpg" alt="MLBC">

## Webpage Link 
Visit the below link for onem2m webpage
[oneM2M Link](http://onem2m.iiit.ac.in:443/webpage/)


## About oneM2M Container

A container in oneM2M is a structured resource used to store and manage data instances, known as contentInstances. It functions like a directory, organizing data in a hierarchical structure. Containers support data storage, retrieval, and deletion, and can contain sub-containers for more granular organization. 

## oneM2M Data Format
**NOTE** : It should be in list format.


| Attribute                | Value                                                                                                                                                                                                                                                                                                             |
| ------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Data String Parameters**| `['Timestamp', 'Light_Status', 'Rsl_Out', 'Latency', 'Data_Rate', 'IPv6_Address', 'Packet_Size', 'Rsl_In', 'Etx', 'Rpl_Rank', 'Mac_tx_failed_count', 'Mac_tx_count', 'Parent', 'Running_time', 'Connected_time']`                                                                                                                                                            |



| Parameter              | Data Description                                                                                                                                                                           | Datatype | Units  | Resolution | Accuracy |
|------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------|--------|------------|----------|
| **Timestamp**          | The number of seconds that have elapsed since Thursday, 1970 Jan 1 00:00:00 UTC                                                                                                            | int      | s      | 60 s       | n/a      |
| **Light_Status**       | The instantaneous value of Light [L031on = on] or [L031off = off]                                                                                                                          | String   | n/a    | n/a        | n/a      |
| **Rsl_out**            | The Received Signal Level out is an EWMA of the received signal level for the node-to-neighbor direction. Provides a range of -174 (0) to +80 (254) dBm                                      | float    | dBm    | 0.1 dBm    | n/a      |
| **Latency**            | The instantaneous value of latency having a minimum of [0.2] sec to a maximum of [10] sec                                                                                                  | float    | sec    | 0.1 sec    | n/a      |
| **Data_Rate**          | The instantaneous rate of data is 150 kbps                                                                                                                                                | int      | kbps   | 1 kbps     | n/a      |
| **IPv6_Address**       | An IPv6 address is a 128-bit alphanumeric identifier used to uniquely identify devices on an IPv6 network                                                                                 | String   | n/a    | n/a        | n/a      |
| **Packet_Size**        | The size of a packet is 100 bytes                                                                                                                                                         | int      | bytes  | n/a        | n/a      |
| **Rsl_in**             | The Received Signal Level in is an EWMA of the received signal level for the neighbor-to-node direction. Provides a range of -174 (0) to +80 (254) dBm                                     | float    | dBm    | 0.1 dBm    | n/a      |
| **etx**                | Expected Transmission Count is an Exponentially Weighted Moving Average of the number of expected packet transmissions required for error-free reception at destination                     | float    | n/a    | n/a        | n/a      |
| **Rpl_rank**           | RPL rank represents the rank or hop distance from the tree root                                                                                                                           | float    | n/a    | n/a        | n/a      |
| **Mac_tx_failed_count**| MAC transmit failed represents the number of unsuccessful transmission attempts                                                                                                           | float    | n/a    | n/a        | n/a      |
| **Mac_tx_count**       | MAC transmission count represents the number of packets transmitted over the air                                                                                                          | float    | n/a    | n/a        | n/a      |
| **Parent**             | The last two bytes of the parent node’s MAC address                                                                                                                                       | String   | n/a    | n/a        | n/a      |
| **Running_time**       | Indicates the duration the application has been operational since the most recent power cycle                                                                                             | String    | n/a    | n/a        | n/a      |
| **Connected_time**     | Specifies the length of time the device has maintained its current connection to the Border Router                                                                                      | String    | n/a    | n/a        | n/a      |


## oneM2M Tutorial Videos
Go through the below videos to get a brief idea of onem2m

[![YouTube Playlist](https://img.shields.io/badge/YouTube-Playlist-red?logo=youtube)](https://www.youtube.com/playlist?list=PLCy4zhNMXeP928mSxxP-NDvsyMddWEi0L)



