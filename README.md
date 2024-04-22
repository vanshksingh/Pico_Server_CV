# MPU6050 Sensor Data Server


![IMG_3591](https://github.com/vanshksingh/Pico_Server_CV/assets/114809624/5e00723e-62bf-402a-a14d-c297cf2af777)


This project demonstrates how to establish a TCP server and client connection to send sensor data from an MPU6050 sensor to a server. It consists of a Python script for the server and an Arduino sketch for the client.

## Contents

- [Description](#description)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Description

The project involves reading data from an MPU6050 sensor (accelerometer, gyroscope, and temperature) using an Arduino microcontroller. The Arduino sketch connects to a Wi-Fi network and sends the sensor data to a server via a TCP connection.

The server is implemented in Python and listens for incoming connections. It accepts sensor data from the client and prints the data in a formatted manner.

## Hardware Requirements

- MPU6050 sensor
- Arduino microcontroller (e.g., Arduino Uno, ESP32, etc.)
- Wi-Fi connectivity module (if not using an ESP32)
- OLED display (optional for visual feedback)

## Software Requirements

- Python 3.x with the following libraries:
    - `socket`
- Arduino IDE
- Adafruit libraries:
    - Adafruit_MPU6050
    - Adafruit_SSD1306
    - Adafruit_GFX

## Setup

1. Clone this repository to your local machine.
2. **Server Setup**:
    - Open the Python script (`server.py`).
    - Set the desired host and port for the server.
    - Run the script to start the server: `python server.py`.
3. **Client Setup**:
    - Open the Arduino sketch (`arduino_client.ino`).
    - Update the Wi-Fi credentials (`ssid` and `password`) and the server IP and port in the sketch.
    - Compile and upload the sketch to your Arduino microcontroller.
4. Once both the server and client are running, the client will send sensor data to the server.

## Usage

- **Server**:
    - Start the server by running the Python script (`server.py`).
    - Monitor the server output for incoming data and client connections.
- **Client**:
    - Once the sketch is uploaded to your microcontroller, the client will automatically connect to the specified Wi-Fi network and server.
    - Sensor data will be sent periodically to the server.

## Code Explanation

- **Server**:
    - The server script uses the `socket` library to create a TCP server.
    - It accepts connections from clients and receives data.
    - The data is decoded, parsed, and printed in a structured format.
- **Client**:
    - The client sketch uses Adafruit libraries to interface with the MPU6050 sensor and an OLED display.
    - The sensor data is read from the MPU6050.
    - The client connects to a Wi-Fi network and establishes a TCP connection to the server.
    - Sensor data is sent to the server at regular intervals.
    - The OLED display provides visual feedback of sensor data and connection status.

## License

This project is open-source and available under the MIT License.

## Acknowledgments

This project uses Adafruit libraries for sensor and display management. Many thanks to the Adafruit community for their open-source contributions.

