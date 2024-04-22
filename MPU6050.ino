#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Wi-Fi credentials
const char* ssid = "vks iPhone";
const char* password = "petronas";

// Server IP and port
const char* server_ip = "172.20.10.3";
const int server_port = 12345;

// Create an instance of the MPU6050 sensor
Adafruit_MPU6050 mpu;



// Wi-Fi client
WiFiClient client;


// Define the OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Define the OLED display I2C address
#define OLED_ADDRESS 0x3C


// Create an instance of the Adafruit_SSD1306 class for the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
    // Start serial communication for debugging
    Serial.begin(115200);

    // Initialize I2C communication
    Wire.begin();

    // Initialize the OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("Failed to initialize OLED display");
        while (true);
    }

    // Clear the display
    display.clearDisplay();
    display.display();

    // Set the text color to white
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    // Initialize the MPU6050 sensor
    if (!mpu.begin()) {
        Serial.println("Failed to initialize MPU6050");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Failed to init");
        display.setCursor(0, 10);
        display.print("MPU6050");
        display.display();
        while (true);
    }

    // Set the sensor range and filter bandwidth
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // Connect to Wi-Fi network with infinite retries and a delay of 1 second
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(1000); // Retry every second
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Connecting to");
        display.setCursor(0, 10);
        display.print("Wi-Fi...");
        display.display();
        Serial.println("Connecting to Wi-Fi...");
    }

    // Display successful Wi-Fi connection
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Connected to Wi-Fi");
    display.display();
    Serial.println("Connected to Wi-Fi");

    // Connect to the TCP server with infinite retries and a delay of 1 second
    while (!client.connect(server_ip, server_port)) {
        delay(1000); // Retry every second
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Connecting to");
        display.setCursor(0, 10);
        display.print("server...");
        display.display();
        Serial.println("Connecting to server...");
    }

    // Display successful server connection
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Connected to server");
    display.display();
    Serial.println("Connected to server");
}


void loop() {
    // Check Wi-Fi connection and reconnect if necessary
    if (WiFi.status() != WL_CONNECTED) {
        // Try reconnecting to the Wi-Fi network
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            display.clearDisplay();
            display.setCursor(0, 0);
            display.print("Reconnecting to Wi-Fi..");
            display.display();
            Serial.println("Reconnecting to Wi-Fi...");
        }

        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Reconnected to Wi-Fi");
        display.display();
        Serial.println("Reconnected to Wi-Fi");
    }

    // Check server connection and reconnect if necessary
    if (!client.connected()) {
        if (!client.connect(server_ip, server_port)) {
            delay(1000);
            Serial.println("Failed to reconnect to server");
            display.clearDisplay();
            display.setCursor(0, 0);
            display.print("Failed to reconnect");
            display.setCursor(0, 20);
            display.print("to server");
            display.display();
            delay(1000);
            return; // Skip loop and try reconnecting later
        }
        Serial.println("Reconnected to server");
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Reconnected to ");
        display.setCursor(0, 1);
        display.print("server");
        display.display();
    }

    // Get sensor data from the MPU6050
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Create a string with sensor data
    String data = String(a.acceleration.x, 2) + "," + String(a.acceleration.y, 2) + "," +
                 String(a.acceleration.z, 2) + "," + String(g.gyro.x, 2) + "," +
                 String(g.gyro.y, 2) + "," + String(g.gyro.z, 2) + "," +
                 String(temp.temperature, 2);

    // Send data to the server
    client.println(data);
    Serial.println(data);

    

    // Display sensor data on the OLED display
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Accel:X=");
    display.print(a.acceleration.x, 2);
    display.setCursor(80, 0);
    display.print("Y=");
    display.print(a.acceleration.y, 2);
    display.setCursor(50, 10);
    display.print("Z=");
    display.print(a.acceleration.z, 2);

    display.setCursor(30, 20);
    display.print("Temp: ");
    display.print(temp.temperature, 2);
    display.print(" C");

    // Update the OLED display
    display.display();

    // Wait for a while before sending data again
    delay(200);
}
