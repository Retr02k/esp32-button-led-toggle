# 🔘 ESP32 GPIO Control: LED Toggle with Button

A simple yet fundamental ESP32-IDF project demonstrating digital input/output control. Press a button to toggle an LED on and off - perfect for beginners learning embedded systems!

![ESP32](https://img.shields.io/badge/ESP32-ESP--IDF-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## 📋 Table of Contents
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Configuration](#-pin-configuration)
- [Installation](#-installation)
- [How It Works](#-how-it-works)
- [Project Structure](#-project-structure)
- [Building and Flashing](#-building-and-flashing)
- [Serial Monitor Output](#-serial-monitor-output)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [License](#-license)

## ✨ Features

- **Digital Input Reading**: Pull-down button configuration
- **Digital Output Control**: LED toggling
- **Edge Detection**: Button press detection (rising edge only)
- **Debouncing**: Software debouncing to prevent false triggers
- **Serial Debugging**: Real-time status messages via UART

## 🔧 Hardware Requirements

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 DevKit v1 | 1 | DOIT ESP32 board |
| LED | 1 | Any color (5mm recommended) |
| Current-limiting resistor | 1 | 220Ω - 330Ω |
| Push button | 1 | Momentary tactile switch |
| Breadboard | 1 | For prototyping |
| Jumper wires | Several | Male-to-male |

## 📐 Circuit Diagram

```
                    ESP32 DevKit v1
                   ┌─────────────┐
                   │             │
                   │   3.3V      ├──────┐
                   │             │      │
                   │             │     ╱
                   │             │    ╱  Button
                   │             │   ╱
                   │             │   │
                   │     GPIO 4  ├───┴─────────
                   │             │
                   │             │
                   │     GPIO 5  ├─────┐
                   │             │     │
                   │         GND ├───┐ │
                   └─────────────┘   │ │
                                     │ │
                                    ─┴─│
                                    GND│
                                       │
                                      ┌─┴─┐
                                      │   │ 220Ω Resistor
                                      └─┬─┘
                                        │
                                       ┌┴┐
                                       │ │ LED (Anode)
                                       └┬┘
                                        │ LED (Cathode)
                                       ─┴─
                                       GND


Detailed Connection:
─────────────────────────────────────────────
Button Circuit (GPIO 4):
  • One leg of button → GPIO 4
  • Other leg of button → 3.3V
  • Internal pull-down resistor enabled in software

LED Circuit (GPIO 5):
  • GPIO 5 → 220Ω Resistor → LED Anode (+)
  • LED Cathode (-) → GND

```

### Hardware Layout View

```
╔════════════════════════════════════════════════════════════╗
║        ESP32 GPIO Control - Hardware Setup                 ║
╚════════════════════════════════════════════════════════════╝

    Power Supply                ESP32 Board
   ┌──────────┐           ┌─────────────────┐
   │  USB 5V  │           │                 │
   │  or 3.3V │           │   [ESP32 Chip]  │
   └────┬─────┘           │                 │
        │                 │  ┌───────────┐  │
        │                 │  │   3.3V    │──┼────┐
        │                 │  └───────────┘  │    │
        │                 │                 │    │
        │                 │  ┌───────────┐  │    │
        │                 │  │  GPIO 4   │◄─┼────┤
        │                 │  └───────────┘  │    │   Button
        │                 │                 │   ╱          
        │                 │  ┌───────────┐  │  ╱ │         
        │                 │  │  GPIO 5   │──┼────┼─────────┐
        │                 │  └───────────┘  │              │
        │                 │                 │              │
        │                 │  ┌───────────┐  │              │
        │                 │  │   GND     │──┼──────────────┤
        │                 │  └───────────┘  │              │
        │                 └─────────────────┘             ─┴─
        │                                                 GND
        │
        │                     LED Circuit
        │                 ┌─────────────┐
        └─────────────────┤  220Ω Res   │
                          └──────┬──────┘
                                 │
                              ┌──┴──┐
                              │  ▲  │ LED
                              │  │  │ (Anode to Resistor)
                              └──┬──┘
                                 │
                                ─┴─
                                GND
```

## 📌 Pin Configuration

| GPIO Pin | Function | Configuration |
|----------|----------|---------------|
| GPIO 4 | Button Input | Input with internal pull-down |
| GPIO 5 | LED Output | Output (active HIGH) |

> **Note**: GPIO 4 and 5 are safe to use on ESP32 and don't have special boot-time requirements.

## 💾 Installation

### Prerequisites
- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) (v4.4 or later)
- USB cable for ESP32- USB cable for ESP32
- CP2102 or similar USB-to-Serial driver installed

### Clone the Repository
```bash
git clone https://github.com/Retr02k/esp32-gpio-led-toggle.git
cd esp32-gpio-led-toggle
```

## ⚙️ How It Works

### Software Flow

1. **Initialization**
   - Configure GPIO 5 as output for LED
   - Configure GPIO 4 as input with pull-down resistor
   - Print startup message to serial

2. **Main Loop**
   - Read button state from GPIO 4
   - Detect rising edge (button press)
   - Toggle LED state on GPIO 5
   - Add debounce delay (50ms)
   - Repeat

### Key Concepts Demonstrated

#### Edge Detection
```c
int button_pressed(int state){
    static int last_state = 0;
    int ret = 0;
    
    // Only trigger on rising edge (0 → 1)
    if (!last_state && state){
        ret = 1;
    }
    
    last_state = state;
    return ret;
}
```

#### State Toggle
```c
void toggle_led(){
    static int led_state = 0;
    led_state = !led_state;  // Flip state
    gpio_set_level(LED_PIN, led_state);
}
```

## 📁 Project Structure

```
button_led_toggle/
├── main/
│   ├── main.c              # Main application code
│   └── CMakeLists.txt      # Main component CMake
├── CMakeLists.txt          # Project CMake configuration
├── sdkconfig               # ESP-IDF SDK configuration
└── README.md
```

## 🔨 Building and Flashing

### Using ESP-IDF Command Line

1. **Set up ESP-IDF environment**
   ```bash
   # Navigate to your ESP-IDF installation directory
   . $HOME/esp/esp-idf/export.sh
   ```

2. **Configure the project** (optional, first time only)
   ```bash
   idf.py menuconfig
   ```

3. **Build the project**
   ```bash
   idf.py build
   ```

4. **Flash to ESP32**
   ```bash
   # Replace /dev/ttyUSB0 with your ESP32 port
   idf.py -p /dev/ttyUSB0 flash
   ```

5. **Open Serial Monitor**
   ```bash
   idf.py -p /dev/ttyUSB0 monitor
   ```

6. **Build, Flash, and Monitor (all in one)**
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

**Quick tips:**
- Press `Ctrl+]` to exit the serial monitor
- Use `idf.py -p PORT flash monitor` for complete workflow
- Find your port with `ls /dev/ttyUSB*` or `ls /dev/ttyACM*`

### Alternative: Using VS Code with ESP-IDF Extension

1. Install the [ESP-IDF VS Code Extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension)
2. Open the project folder
3. Use the ESP-IDF buttons in the status bar:
   - 🔨 **Build** - Compile project
   - 📤 **Flash** - Upload to ESP32
   - 📺 **Monitor** - View serial output
4. Or use Command Palette (`Ctrl+Shift+P`):
   - **ESP-IDF: Build your project**
   - **ESP-IDF: Flash your project**
   - **ESP-IDF: Monitor your device**
```

> **💡 Tip**: The GUI method is recommended for beginners and provides a more user-friendly experience!

## 📺 Serial Monitor Output

```
ESP32 Starting...
GPIO configured. Press button on GPIO 4 to toggle LED on GPIO 5
Button pressed! LED toggled.
Button pressed! LED toggled.
Button pressed! LED toggled.
```

**Baud Rate**: 115200

## 🐛 Troubleshooting

### LED doesn't light up
- ✅ Check resistor value (should be 220-330Ω)
- ✅ Verify LED polarity (long leg is anode/+)
- ✅ Confirm GPIO 5 connection
- ✅ Test LED with multimeter in diode mode

### Button doesn't work
- ✅ Verify button connections (one leg to GPIO 4, other to GND)
- ✅ Check if button is working with multimeter in continuity mode
- ✅ Ensure pull-down mode is enabled in code

### No serial output
- ✅ Check USB cable connection
- ✅ Verify serial driver installation
- ✅ Confirm baud rate is 115200
- ✅ Try pressing EN (reset) button on ESP32

### ESP32 won't flash
- ✅ Hold BOOT button while running `idf.py flash`
- ✅ Press EN button to reset
- ✅ Check USB port permissions (Linux: `sudo usermod -a -G dialout $USER`)
- ✅ Verify ESP-IDF is properly sourced: `. $HOME/esp/esp-idf/export.sh`

## 🎓 Learning Outcomes

By completing this project, you'll understand:

- ✅ ESP32 GPIO configuration (input/output modes)
- ✅ Internal pull-up/pull-down resistors
- ✅ Edge detection for button presses
- ✅ Software debouncing techniques
- ✅ LED current limiting with resistors
- ✅ FreeRTOS task delays
- ✅ Serial debugging with `printf()`
- ✅ ESP-IDF project structure and build system

## 🚀 Next Steps

Want to expand this project? Try:

- [ ] Add multiple buttons and LEDs
- [ ] Implement different LED patterns
- [ ] Add PWM for LED brightness control
- [ ] Create a state machine for complex behaviors
- [ ] Use interrupts instead of polling
- [ ] Add a buzzer for audio feedback

## 📖 Additional Resources

- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [GPIO & RTC GPIO Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)

## 📄 License

This project is open source and available under the MIT License.

---


*If you found this helpful, please ⭐ star the repository!*
