# Motion Sensor with ESP32

A simple code to use a motion sensor on ESP32.

<p align="justify">At each detection, a webhook is sent to discord ; when the motion stop, another webhook is sent.
When the wifi connection is lost and then recovered, a webhook is sent with a "Connection lost for [n] seconds/minutes/hours" message.</p>

## Wiring

### Materials

* ESP-WROOM-32 Dev Module
* Micro USB cable
* HC-SR501 Motion Sensor
* Jumper Wires female-female

### Wiring Diagram

<div align="center">
  <img src="images/wiring-diagram.jpg" alt="Wiring diagram of a mensor detector on ESP32" width="50%" height="50%" title="Wiring Diagram">
  <p>More information <a href="https://esp32io.com/tutorials/esp32-motion-sensor">Here</a></p>
</div>

## Badges

![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Espressif](https://img.shields.io/badge/espressif-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
