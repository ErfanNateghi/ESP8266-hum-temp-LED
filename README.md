# IoT Temperature and Humidity Monitoring System

## Overview

This repository contains the code for an IoT-based temperature and humidity monitoring system using the **ESP8266** microcontroller. The project includes a web server code developed using the Arduino IDE that reads temperature and humidity data from a connected sensor and allows control of an LED (or any other device such as an air conditioning system) via a web interface.

The system is highly customizable, allowing you to implement logic directly in the code to automate responses based on sensor readings. For example, the LED or connected device can be turned on automatically if the temperature exceeds a specified threshold.

### Features

- **Real-time Monitoring:** Read temperature and humidity data from the sensor in real-time.
- **Web Interface:** Access and control the system through a simple web page hosted by the ESP8266.
- **Device Control:** Send commands to an LED (or any other connected device like an air conditioner) via the web interface.
- **Custom Logic Implementation:** Easily implement conditional logic in the Arduino code to automate device control.

## Project Components

### 1. ESP8266 Web Server Code

- **Temperature and Humidity Sensing:** The code reads data from a DHT11 or any compatible temperature and humidity sensor connected to the ESP8266.
- **Web Server:** The ESP8266 hosts a web page that displays the current temperature and humidity readings and includes buttons to control the LED (or other devices).
- **Customizable Logic:** Implement conditions in the code to automate device control.

### 2. Web Page Code

- **User Interface:** A simple HTML/CSS/JavaScript-based interface to display sensor data and control the connected devices.
- **Real-time Updates:** The web page updates sensor readings in real-time and allows immediate control over the devices.

![Screenshot 2024-09-01 143127](https://github.com/user-attachments/assets/12a474c0-fb37-437e-8432-8bba8d2ace95)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
