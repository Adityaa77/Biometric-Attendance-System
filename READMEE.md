Biometric Attendance System
An IoT-based attendance tracking system using fingerprint authentication. The system identifies registered users via their fingerprint, displays a welcome message on an LCD screen, and sends attendance data to a cloud database in real-time.
Features

Biometric Authentication: Secure fingerprint scanning for user identification
Real-time Data Transmission: Sends attendance records to cloud storage via WiFi
User Interface: LCD display for system status and user feedback
Multiple User Support: Stores and recognizes multiple fingerprint profiles
Connectivity: WiFi integration for cloud data synchronization

Hardware Components

ESP8266 NodeMCU microcontroller
Adafruit Fingerprint Sensor
16x2 I2C LCD Display
Power supply

Software

Arduino IDE with ESP8266 support
Libraries:

Adafruit Fingerprint Sensor Library
ESP8266WiFi Library
LiquidCrystal_I2C Library



System Workflow

System initializes and connects to WiFi
User places finger on the fingerprint sensor
System scans and attempts to match the fingerprint
On successful recognition, system:

Displays welcome message with user name
Sends attendance data to cloud via PushingBox API


Invalid fingerprints trigger an error message

Implementation Details
The system has three main components:

Database Management: Functions to enroll new fingerprints and clear the database
Fingerprint Recognition: Real-time scanning and matching of fingerprints
Cloud Integration: WiFi connection and API communication for data transmission

Future Improvements

Add time-based attendance tracking
Implement user management through a web interface
Add backup power solution
Integrate with other authentication methods for redundancy
