# Ethernet Example Trial Manual for mros2-esp32

# Table of Contents

1. [Introduction](#introduction)  
   1.1 [Purpose of the document](#purpose-of-the-document)  
   1.2 [Overview of the Ethernet Example](#overview-of-the-ethernet-example)  

2. [Overview](#overview)  
   2.1 [Hardware Requirements](#hardware-requirements)  
   2.2 [Software Requirements](#software-requirements)  

3. [Licenses and Security Policy](#licenses-and-security-policy)  
   3.1 [Espressif ESP-IDF License and Security Policy](#espressif-esp-idf-license-and-security-policy)  
   3.2 [mROS-base/mros2-esp32 License](#mros-base-mros2-esp32-license)  
   3.3 [mros2-host-examples License](#mros2-host-examples-license)  

4. [Files Related to Ethernet Example for mros2-esp32](#files-related-to-ethernet-example-for-mros2-esp32)  
   4.1 [Integration of ESP-IDF Ethernet Sample Code](#integration-of-esp-idf-ethernet-sample-code)  
   4.2 [Modifications and Renaming of Files](#modifications-and-renaming-of-files)  

5. [Connecting the Hardware](#connecting-the-hardware)  
   5.1 [Connecting the Ethernet Module to the ESP32](#connecting-the-ethernet-module-to-the-esp32)  
   5.2 [Hardware Pin Layout and SPI Configuration](#hardware-pin-layout-and-spi-configuration)  
   5.3 [Checklist](#checklist)  

6. [Configuration, Build, and Flash the Program](#configuration-build-and-flash-the-program)  
   6.1 [Ethernet Configuration via `idf.py menuconfig`](#ethernet-configuration-via-idfpy-menuconfig)  
   6.2 [Selecting the Example and SPI Settings](#selecting-the-example-and-spi-settings)  
   6.3 [Building and Flashing the Firmware](#building-and-flashing-the-firmware)  
   6.4 [Testing Ethernet Connectivity](#testing-ethernet-connectivity)  

7. [Testing Ethernet in Another Workspace](#testing-ethernet-in-another-workspace)  
   7.1 [Copying `Kconfig.projbuild`](#copying-kconfigprojbuild)  
   7.2 [Configuration and Build in Another Workspace](#configuration-and-build-in-another-workspace)  
   7.3 [Example Results](#example-results)  

8. [Troubleshooting](#troubleshooting)  
   8.1 [Common Issues and Solutions](#common-issues-and-solutions)  

9. [Appendix](#appendix)  
   9.1 [How to Check WiFi or Ethernet Settings After `idf.py menuconfig`](#how-to-check-wifi-or-ethernet-settings-after-idfpy-menuconfig)  



## 1. Introduction
This document provides instructions for trying Ethernet instead of WiFi in mros2-esp32.
The use of WiFi is standard in mros2-esp32, but here we will introduce an example of Ethernet connection.

## 2. Overview
- We will use the example code for Ethernet provided by espressif/esp-idf on GitHub.
- For the Ethernet connection, an SPI-connected Ethernet module will be used as the required hardware.
- We have prepared a new Kconfig.projbuild for Ethernet. It allows configuration for switching between WiFi and Ethernet, as well as setting up the SPI interface.
- We will proceed with the verification using workspace/sub_utint16_ethernet.
### 2.1 Hardware
- ESP32 development board : [ESP32-S3-DevKitC-1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/hw-reference/esp32s3/user-guide-devkitc-1.html)
- Ethernet SPI module : [W5500](https://docs.wiznet.io/Product/iEthernet/W5500/datasheet) is mounted on [WIZ850io](https://docs.wiznet.io/Product/ioModule/wiz850io)
- Standard Ethernet cable
- Ethernet router
- Ubuntu native computer with development tools installed
### 2.2 Software
-  [Espressif Systems](https://github.com/espressif) / [ESP-IDF](https://github.com/espressif/esp-idf) Ver5.5
    - [esp-idf/examples/ethernet/basic](https://github.com/espressif/esp-idf/tree/master/examples/ethernet/basic)
- Ethernet Example for evaluation
    - [ROS 2 Humble](https://docs.ros.org/en/humble/Installation.html#installation)
    - [mros2-host-examples](https://github.com/mROS-base/mros2-host-examples)

## 3. Licenses and Security policy
- esp-idf : [license](https://github.com/espressif/esp-idf?tab=Apache-2.0-1-ov-file), [Security Policy](https://github.com/espressif/esp-idf?tab=security-ov-file)
- mROS-base/mros2-esp32 : [license](https://github.com/mROS-base/mros2-esp32?tab=Apache-2.0-1-ov-file)
- mros2-host-examples : [license](https://github.com/mROS-base/mros2-host-examples?tab=Apache-2.0-1-ov-file)

## 4. About files related to Ethernet example for mros2-esp32
### 4.1 Integration of Ethernet sample source code from ESP-IDF
- Integrate [esp-idf/examples/ethernet/basic](https://github.com/espressif/esp-idf/tree/master/examples/ethernet/basic) from ESP-IDF into mros2-esp32.
- Renamed and modified.
- Please also read [examples/ethernet/basic/README.md](https://github.com/espressif/esp-idf/blob/master/examples/ethernet/basic/README.md).
### 4.2 Renaming of source code, addition of header files, and modifications to them
- Files and Directory  for the Ethernet Example.
```
$ tree ~/mros2-esp32
~/mros2-esp32
├── CMakeLists.txt
├── platform
│   ├── ethernet
│   │   ├── example_ethernet
│   │   │   ├── example_ethernet.c
│   │   │   └── example_ethernet.h
│   │   └── example_ethernet_components
│   │       ├── example_ethernet_components.c
│   │       └── example_ethernet_components.h
│   └── mros2-platform.cpp
└── workspace
    └── sub_uint16_ethernet
        ├── CMakeLists.txt
        ├── main
        │   ├── CMakeLists.txt
        │   ├── Kconfig.projbuild
        │   └── sub_uint16_ethernet.cpp
        └── README.md
```
#### 4.2.1 Copy , Rename and Modify 
- examples/ethernet/basic/main/ethernet_example_main.c -> example_ethernet.c
#### 4.2.2 Copy and Rename
- examples/ethernet/basic/components/ethernet_init/ethernet_init.c -> example_ethernet_components.c
- examples/ethernet/basic/components/ethernet_init/ethernet_init.h -> example_ethernet_components.h
#### 4.2.3  addition of header files
- example_ethernet.h : This is included from mros2-esp32/platform/mros2-platform.cpp
#### 4.2.4 Modifications to existing files
- mros2-esp32/platform/mros2-platform.cpp
  Switching between Wi-Fi and Ethernet, and calling functions related to Ethernet example.
- mros2-esp32/CMakeLists.txt
  Additional files and modifications related to Ethernet and SPI.
#### 4.2.5 Kconfig.projbuild
- By loading Kconfig.projbuild during idf.py menuconfig, settings related to Ethernet can be configured.
- Combine two files, [examples/ethernet/basic/main/Kconfig.projbuild]() and [examples/ethernet/basic/components/ethernet_init/Kconfig.projbuild](https://github.com/espressif/esp-idf/blob/master/examples/ethernet/basic/components/ethernet_init/Kconfig.projbuild)
- Prepare the mros2esp32-network-select.txt in advance.
```
# mros2esp32-network-select.txt
menu "mros2-esp32 network interface"
    choice
        prompt "mros2-esp32 network interface"
	    default MROS2_ESP32_NETIF_WIFI
            config MROS2_ESP32_NETIF_WIFI
                bool "WiFi"
            config MROS2_ESP32_NETIF_ETHERNET
                bool "Example-Ethernet"
	endchoice
endmenu
```
- It is generated using the following method.
```
#!/bin/bash
cat ./mros2esp32-network-select.txt \
    ~/esp/esp-idf/examples/ethernet/basic/components/ethernet_init/Kconfig.projbuild \
    ~/esp/esp-idf/examples/ethernet/basic/main/Kconfig.projbuild \
    > ./Kconfig.projbuild
if [ $? -eq 0 ]; then
    echo "Kconfig.projbuild has been generated. Merging the files."
else
fi
```

- For example, copy it into 'workspace/sub_utint16_ethernet/main' and use it.

## 5. Connecting the Hardware
### 5.1 Connect the Ethernet module to the ESP32 board according to the specifications.
- WIZ850io's 3.3V is supplied from a three-terminal regulator.
- Table 5.1 ESP32-S3 and WIZ850io Connection

<h3>Table 5.1 ESP32-S3 and WIZ850io Connection</h3>
<table>
  <thead>
    <tr>
      <th>ESP32-S3 GPIO No.</th>
      <th>WIZ850io Pin (W5500)</th>
      <th>idf.py menuconfig</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>GPIO12</td>
      <td>SCK</td>
      <td>SPI SCLK</td>
    </tr>
    <tr>
      <td>GPIO11</td>
      <td>MOSI</td>
      <td>SPI MOSI</td>
    </tr>
    <tr>
      <td>GPIO13</td>
      <td>MISO</td>
      <td>SPI MISO</td>
    </tr>
    <tr>
      <td>GPIO10</td>
      <td>SCNn</td>
      <td>SPI CS0</td>
    </tr>
    <tr>
      <td>GPIO4</td>
      <td>INTn</td>
      <td>Interrupt</td>
    </tr>
    <tr>
      <td>GPIO9</td>
      <td>RSTn</td>
      <td>PHY Reset</td>
    </tr>
  </tbody>
</table>

<!-- |ESP32-S3 GPIO No. | WIZ850io Pin  (W5500) | idf.py menuconfig | --> 
<!-- |----------------------------|---------------------------------|-------------------------| -->
<!-- | GPIO12                   | SCK                                | SPI SCLK            |  -->  
<!-- | GPIO11                   | MOSI                              | SPI MOSI            |  -->
<!-- | GPIO13                   | MISO                              | SPI MISO            | -->
<!-- | GPIO10                   | SCNn                             | SPI CS0              |  -->
<!-- | GPIO4                     | INTn                               | Interrupt              |  -->
<!-- | GPIO9                     | RSTn                              | PHY Reset          | -->

### 5.1.1  [ESP32-S3-DevKitC-1 Pin Layout](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html#pin-layout)

||
|:----:|
|![image](https://github.com/user-attachments/assets/f50b6a6f-b57c-4e01-8a85-b00644334851)|
|Fig 5.1.1  ESP32-S3-DevKitC-1 Pin Layout|

### 5.1.2  [WIZ850io Pin out](https://docs.wiznet.io/Product/ioModule/wiz850io#pin-out)
- The W5500 is mounted on the backside of the board.

||
|:---:|
|![image](https://github.com/user-attachments/assets/9645364b-6700-41cd-8bde-f8f975c44206)|
|Fig 5.1.2 WIZ850io Pin out||

### 5.1.3 Example idf.py menuconfig SPI configuration
- In this manual, "PHY Reset GPIO number of SPI Ethernet Module"  has been changed to GPIO9.
- The default value of "PHY Reset GPIO number of SPI Ethernet Module" is -1, which means it is not assigned to any GPIO. 
- However, by assigning it to a GPIO, the software can reset the PHY. This ensures a more stable initialization process for the W5500.

||
|:---:|
|![image](https://github.com/user-attachments/assets/f884895f-7a70-41ca-ab90-fa8168706ae8)|
|Fig 5.1.3 example idf.py menuconfig SPI setting|

### 5.2 Checklist
- Ensure all connections are secure and that the power supply is stable.
- When using the WIZ850io, a measured current of 130mA was observed. Ensure that the 3.3V power supply has sufficient capacity.

## 6. Configuration, Build and Flash the Program
### 6.1 Ethernet-related configuration"
- Run idf.py menuconfig. This is an example of the procedure.
```
$ cd ~/mros2-esp32/workspace/
$ cd sub_uint16_ethernet
$ . $HOME/esp/esp-idf/export.sh
$ rm -rf build
$ idf.py fullclean
$ idf.py set-target esp32s3
$ idf.py menuconfig
```
- Select the "mros2-esp32 network interface" and press the Enter key. This is to switch to Ethernet. In Fig. 6.1.1.

||
|:---:|
|![image](https://github.com/user-attachments/assets/15f671b4-d057-41be-b1c0-1d0d334c160b)|
|Fig. 6.1.1 Select Menu item, mros2-esp32 network interface|

- This represents the current WiFi configuration. Press Enter to switch to Ethernet. In Fig. 6.1.2.

||
|:---:|
|![image](https://github.com/user-attachments/assets/36b40b76-a3c7-4833-a48d-782a0ce48f10)|
|Fig. 6.1.2 Select mros2-esp32 network interface|

- This represents the current WiFi configuration. Press Enter to switch to Ethernet. In Fig. 6.1.3.

||
|:---:|
|![image](https://github.com/user-attachments/assets/a08d3c65-e77c-4ee2-9d9f-0b9d544541b1)|
|Fig. 6.1.3 Choice Example-Ethernet|

- It indicates that the connection has switched to Ethernet. In Fig. 6.1.4.
- Pressing the ESC key will exit this settings window.

||
|:---:|
|![image](https://github.com/user-attachments/assets/8473e0a9-4e58-4747-9f61-2afc35fa0c0a)|
|Fig. 6.1.4 Set Example-Ethernet|

### 6.2 Select "Example and SPI setting
- Select "Example Ethernet Configuration" and press the Enter key. After this, the SPI configuration will be done. In Fig. 6.2.1.

||
|:---:|
|![image](https://github.com/user-attachments/assets/a583f76f-4e48-4df1-92a7-23df282d5229)|
|Fig 6.2.1  Select Example Ethernet Configuration|

- "SPI Ethernet" is disabled. Press the space key or Enter key to enable it. In Fig. 6.2.2.

||
|:---:|
|![image](https://github.com/user-attachments/assets/0c82eb91-5bf2-4f3b-a06f-0e99f528e4e7)|
|Fig.6.2.2 Disable SPI Ethernet |

- This indicates that SPI Ethernet is enabled, and various settings for SPI connection are displayed. In Fig. 6.2.3.

||
|:---:|
|![image](https://github.com/user-attachments/assets/33f5cd28-47e3-4d5f-88a1-f68adc10dfa4)||
|Fig.6.2.3 SPI ethernet| 

- Select "PHY Reset GPIO number of SPI Ethernet Module" and press the Enter key. In Fig. 6.2.4.

||
|:----:|
|![image](https://github.com/user-attachments/assets/295279a9-c26d-4918-81ab-753621f9f771)|
|Fig.6.2.4 select PHY reset |

- Enter 9 and press the Enter key. This number represents the GPIO number.  In Fig. 6.2.5.

||
|:---:|
|![image](https://github.com/user-attachments/assets/c61ea3da-7a16-415e-bda4-f77dd20ddee2)|
| Fig 6.2.5 Assign  GPIO number to "PHY Reset GPIO number of SPI Ethernet Module |

- In this manual, do not modify 'Example Configuration'. The original description in Kconfig.projbuild has not been modified.

||
|:---:|
|![image](https://github.com/user-attachments/assets/8b67b222-b7cf-4730-be49-c59a1252594f)|
|Fig 6.2.6 Not change 'Example Configuration' |

- Save the settings. Press 'q' to open a confirmation window for saving the settings, then press 'y' to save. In Fig. 6.2.6.

||
|:---:|
|![image](https://github.com/user-attachments/assets/557910fd-ed27-4e96-9bf5-cbdd46bf610b)|
|Fig 6.2.6 Save Configuration |

### 6.3 Building and  Flash the Firmware.
- Connect the Ubuntu PC and the ESP32-S3 Board via USB-to-UART Port. In Fig 6.3.1 

||
|:---:|
|![image](https://github.com/user-attachments/assets/89996870-2634-49e7-be9a-4dbbc4b9a243)|
|Fig 6.3.1 Connect to the USB-to-UART Port|

- Configure the settings to access the USB-to-UART Port

```
$ sudo chmod 666 /dev/ttyUSB0
```

- Build and flash the firmware.

```
$ idf.py build
$ idf.py -p /dev/ttyUSB0 flash
```

## 6.4 Testing Ethernet Connectivity
### 6.4.1 After flashing, monitor the device logs using:
- Power on all the devices and connect the Ethernet cable.
- Run idf.py -p /dev/ttyUSB0 monitor.
```
$ idf.py -p /dev/ttyUSB0 monitor
```
- Check the terminal log. When the ESP32 board successfully obtains an IP address from the Ethernet router.
```
I (197) app_init: Project name:     sub_uint16_ethernet
I (292) main_task: Started on CPU0
I (312) main_task: Calling app_main()
I (332) esp_eth.netif.netif_glue: xx:xx:xx:xx:xx:xx
I (332) esp_eth.netif.netif_glue: ethernet attached to netif
I (342) eth_example: Ethernet Started
I (2342) eth_example: Ethernet Link Up
I (2342) eth_example: Ethernet HW Addr xx:xx:xx:xx:xx:xx
I (4342) esp_netif_handlers: eth ip: 192.168.11.2, mask: 255.255.255.0, gw: 192.168.11.1
I (4342) eth_example: Ethernet Got IP Address
I (4342) eth_example: ~~~~~~~~~~~
I (4342) eth_example: ETHIP:192.168.11.2
I (4342) eth_example: ETHMASK:255.255.255.0
I (4352) eth_example: ETHGW:192.168.11.1
I (4352) eth_example: ~~~~~~~~~~~
```

### 6.4.2 Topic communication with  [mros2-host-examples](https://github.com/mROS-base/mros2-host-examples)
- Perform aPublish/Subscribe test with mros2-host-examples

```
# Terminal-1 / mros2-esp32, Subscribe node
$ idf.py -p /dev/ttyUSB0 monitor
```
```
# Terminal-2 / mros2-host-examples, mros2_pub_uint16 pub_node
$ cd ~/ros2_ws
$ source /opt/ros/humble/setup.bash
$ source install/local_setup.bash
$ ros2 run mros2_pub_uint16 pub_node
```
- Etternet example of successful Subscribe. In Fig 6.4.1

||
|:---:|
|![image](https://github.com/user-attachments/assets/12eeb07e-9bd6-4623-88e9-175881b763ba)|
|Fig 6.4.1 Etternet example of successful Subscribe|

## 7. Testing Ethernet in another Workspace
- Example workspace/echoback_string
### 7.1 Copy Kconfig.projbuild
```
$ cd ~/mros2-esp32/workspace
$ cp ./sub_uint16_ethernet/main/Kconfig.projbuild ./echoback_string/main
```
### 7.2 Configuration and Build
```
$ cd echoback_string
$ . $HOME/esp/esp-idf/export.sh
$ rm -rf build
$ idf.py fullclean
$ idf.py set-target esp32s3
$ idf.py menuconfig
```

## 7.3 Example of the results after building and running in another workspace
Terminalログを添付

## 8. Troubleshooting
- Lower the SPI clock speed  below the default value in idf.py menuconfig.
- In idf.py menuconfig, the "PHY Reset GPIO number of SPI Ethernet Module" has not been changed and remains at its default value.

## 9 .Appendix
### 9.1 How to check whether the setting is for WiFi or Ethernet after running "idf.py menuconfig".
- Search the sdkconfig file to determine whether Ethernet or Wi-Fi is configured.
```
# example
$ cd ~/mros2-esp32/workspace/sub_uint16_ethernet
$ grep "MROS2_ESP32_NETIF" sdkconfig
```

- Check for when Ethernet enabled, WiFi nou define Fig 9.1.1

||
|:---:|
|![image](https://github.com/user-attachments/assets/0327645d-a3e7-4dcc-a23e-417591f80f6b)|
|![image](https://github.com/user-attachments/assets/701765ad-4ad8-480f-bfb0-6f077b082531)|
|![image](https://github.com/user-attachments/assets/c0f3aa24-99c2-4f09-8642-0ddff2fdba1e)|
|Fig 9.1.1 Ethernet is enabled |

- Check for when WiFi enabled, Ethernet not define Fig 9.1.2

||
|:---:|
|![image](https://github.com/user-attachments/assets/922f0457-6616-43e5-950e-fbef750279c2)|
|![image](https://github.com/user-attachments/assets/37493007-77bf-4703-8e13-35a0ce82cecf)|
|![image](https://github.com/user-attachments/assets/999c0cbb-f7b5-494a-a444-53806e5c7ac1)|
|Fig 9.1.2 Wifi enabled |

- The log when sub_uint16_ethernet is set to Wi-Fi configuration.

||
|:---:|
|![image](https://github.com/user-attachments/assets/1aacc93a-1397-4159-bff8-400b75aded93)|
|FIg 9.1.3 No changes to the source file of sub_uint16_ethernet, enable Wi-Fi idf.py menuconfig.|


## 9.2 Verify if it operates as expected using the conventional procedure
- Take echoback_string as an example. We will proceed with the standard procedure.
- First step, set the target.  In Fig 9.2.1.

||
|:---:|
|![image](https://github.com/user-attachments/assets/7fab56f1-eb88-4b72-a35f-0464143ba093)|
|Fig 9.2.1. The flow up to set-target.|

- 2nd step, Verify that the items displayed in idf.py menuconfig are the same as before, and ensure that there are no Ethernet-related settings. In, Fig 9.2.2.

||
|:--:|
|![image](https://github.com/user-attachments/assets/1e15313e-cea9-4e18-a8c6-1916dc3b76a8)|
|Fig 9.2.2. As usual idf.py menuconfig|

- Verify that MROS2_ESP32_NETIF for switching between Wi-Fi and Ethernet is not present in the sdkconfig.

||
|:---:|
|![image](https://github.com/user-attachments/assets/9f25f287-6b7b-450c-91c5-9109a33b582e)|
|Fig 9.2.3 There is no setting to switch between Wi-Fi and Ethernet.|

- Check the logs.

```
# Terminal-1 / mros2-esp32, Subscribe node
$ idf.py -p /dev/ttyUSB0 monitor
```
```
# Terminal-2 / mros2-host-examples, mros2_pub_uint16 pub_node
$ cd ~/ros2_ws
$ source /opt/ros/humble/setup.bash
$ source install/local_setup.bash
$ ros2 run  ros2 run mros2_echoback_string sub_node
```
- Even without the Kconfig.projbuild, the logs are as usual.

||
|:---:|
|![image](https://github.com/user-attachments/assets/af88e10f-8aff-4d3a-9dd5-4d57f9b80e03)|
|Fig 9.2.4 Ooperates as usual.|

