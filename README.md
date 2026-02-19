# 🚗 AVR RC Car — Bluetooth-Controlled with Autonomous Mode

A fully featured RC car built on the **ATmega32 AVR microcontroller**, supporting both **Bluetooth remote control** and **autonomous obstacle-avoidance driving**. Written in bare-metal C with custom peripheral drivers.

---

## 📋 Table of Contents

- [Features](#features)
- [Hardware Components](#hardware-components)
- [Pin Configuration](#pin-configuration)
- [Project Structure](#project-structure)
- [System Architecture](#system-architecture)
- [Modes of Operation](#modes-of-operation)
- [Control Commands](#control-commands)
- [How to Build & Flash](#how-to-build--flash)
- [Author](#author)

---

## ✨ Features

- 🎮 **RC Mode** — Control the car via a Bluetooth app using UART commands
- 🤖 **Auto Mode** — Ultrasonic sensor-based obstacle detection and avoidance
- ⚡ **PWM Speed Control** — Variable motor speed mapped from 0–9 scale
- 📺 **LCD Display** — Real-time status showing current mode and direction
- 🔄 **Smooth Direction Steering** — Differential motor speed for diagonal movement
- ⏱️ **Timeout Safety** — Car stops automatically if Bluetooth signal is lost

---

## 🔧 Hardware Components

| Component | Description |
|---|---|
| ATmega32 | Main microcontroller (8MHz) |
| HC-05 / HC-06 | Bluetooth module (UART) |
| L298N Motor Driver | Dual H-bridge for 2 DC motors |
| HC-SR04 | Ultrasonic distance sensor |
| 16×2 LCD | Status display (8-bit parallel mode) |
| DC Motors (×2) | Left and right drive wheels |

---

## 📌 Pin Configuration

| Pin | Function |
|---|---|
| PORTA (all) | LCD Data Bus |
| PORTC PIN0 | LCD RS |
| PORTC PIN1 | LCD RW |
| PORTC PIN2 | LCD EN |
| PORTD PIN0 | UART RX ← Bluetooth TX |
| PORTD PIN1 | UART TX → Bluetooth RX |
| PORTB PIN3 | Timer0 PWM — Left Motor Speed |
| PORTD PIN7 | Timer2 PWM — Right Motor Speed |
| PORTB PIN4–5 | Left Motor Direction (INT1, INT2) |
| PORTB PIN6–7 | Right Motor Direction (INT3, INT4) |
| PORTD PIN5 | Ultrasonic TRIG |
| PORTD PIN6 | Ultrasonic ECHO (ICP1) |

---

## 📁 Project Structure

```
avr-rc-car/
├── main.c                  # Application entry point & main loop
│
├── Drivers/
│   ├── DIO/
│   │   ├── DIO_program.c   # Digital I/O driver (pins & ports)
│   │   ├── DIO_interface.h
│   │   ├── DIO_private.h
│   │   └── DIO_config.h
│   │
│   ├── UART/
│   │   ├── UART_program.c  # UART driver (blocking, non-blocking, number receive)
│   │   ├── UART_interface.h
│   │   ├── UART_private.h
│   │   └── UART_config.h
│   │
│   ├── LCD/
│   │   ├── LCD_program.c   # 16x2 LCD driver (8-bit mode)
│   │   ├── LCD_interface.h
│   │   ├── LCD_private.h
│   │   └── LCD_config.h
│   │
│   ├── TIMER0/
│   │   ├── TIMER0_program.c  # Timer0: Fast PWM for left motor
│   │   ├── TIMER0_interface.h
│   │   ├── TIMER0_private.h
│   │   └── TIMER0_config.h
│   │
│   ├── TIMER1/
│   │   ├── TIMER1_program.c  # Timer1: Input Capture for ultrasonic
│   │   ├── TIMER1_interface.h
│   │   ├── TIMER1_private.h
│   │   └── TIMER1_config.h
│   │
│   ├── TIMER2/
│   │   ├── Timer2_program.c  # Timer2: Fast PWM for right motor
│   │   ├── Timer2_interface.h
│   │   └── Timer2_private.h
│   │
│   ├── GI/
│   │   ├── Gl_program.c      # Global Interrupt enable/disable
│   │   └── GI_interface.h
│   │
│   └── WDT/
│       ├── WDT_program.c     # Watchdog Timer driver
│       └── WDT_interface.h
│
└── Utils/
    ├── STD_TYPES.h           # Portable type definitions (u8, u16, u32...)
    └── BIT_MATH.h            # Bit manipulation macros (SET, CLR, TOG, GET)
```

---

## 🏗️ System Architecture

```
Bluetooth App
     │  UART (9600 baud)
     ▼
 ATmega32
     │
     ├──► LCD (16×2) ─────── Mode & Direction display
     │
     ├──► Timer0 PWM ────────► L298N ENA (Left motor speed)
     ├──► Timer2 PWM ────────► L298N ENB (Right motor speed)
     │
     ├──► PORTB [4–7] ───────► L298N IN1–IN4 (Direction control)
     │
     └──► Timer1 (ICP) ◄───── HC-SR04 ECHO
          PORTD PIN5 ────────► HC-SR04 TRIG
```

---

## 🕹️ Modes of Operation

### RC Mode (`K`)
The car responds in real-time to commands received over Bluetooth. Speed is adjustable from the app. If no command is received for ~300ms, the car stops automatically.

### Auto Mode (`P`)
The car drives forward autonomously. When an obstacle is detected within **20 cm**, it stops, turns right, then continues forward.

---

## 📡 Control Commands (Bluetooth)

| Command Byte | Action |
|---|---|
| `F` | Forward |
| `B` | Backward |
| `L` | Left |
| `R` | Right |
| `G` | Forward Left |
| `I` | Forward Right |
| `H` | Back Left |
| `J` | Back Right |
| `S` | Stop |
| `0`–`9` | Speed (0 = min, 9 = max) |
| `K` | Switch to RC Mode |
| `P` | Switch to Auto Mode |

> Compatible with the **Bluetooth RC Controller** app (Arduino Car layout).

---

## 🛠️ How to Build & Flash

1. **Toolchain required:** AVR-GCC, AVRDUDE
2. Clone the repo and open in **Atmel Studio** or your preferred AVR IDE
3. Set the target MCU to `ATmega32` at `8 MHz`
4. Build the project — no external libraries required
5. Flash via USBasp or any compatible ISP programmer:

```bash
avrdude -c usbasp -p m32 -U flash:w:rc_car.hex:i
```

---

## 👤 Author

**Mohamed**  
AVR Embedded Systems Project — 2025/2026
