<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/8/87/Arduino_Logo.svg" height="80">
</p>

<h1 align="center">PID Line Follower Robot using Arduino</h1>

<p align="center">
  A smooth and precise line-following robot using PID control and IR sensors for real-time path correction.
</p>

<p align="center">
  <img src="https://img.shields.io/badge/platform-Arduino-blue?logo=arduino&style=flat-square" />
  <img src="https://img.shields.io/badge/license-MIT-green?style=flat-square" />
</p>

---

## 📸

![Linefollower](https://github.com/user-attachments/assets/cd5cd10d-a66c-4650-b494-8e0a8003625f)


---

## 🚀 Features

- PID (Proportional–Integral–Derivative) control for precise path following
- 3 digital IR sensors (left, center, right)
- Dynamic motor speed correction based on sensor input
- Smooth cornering, minimal oscillation
- Stops automatically when line is lost
- Well-commented, modular, and tunable code

---

## 🧰 Hardware Required

| Component            | Quantity | Description                                      |
|---------------------|----------|--------------------------------------------------|
| Arduino Uno / Nano  | 1        | Microcontroller board                            |
| L298N Motor Driver  | 1        | For driving two DC motors                        |
| IR Sensor Modules   | 3        | For line detection (left, center, right)         |
| DC BO Motors      | 2        | For robot movement                               |
| Wheels              | 2        | Attached to motors                               |
| Chassis             | 1        | Robot base frame                                 |
| Power Supply        | 1        | 7.4V–12V battery or power bank                   |
| Jumper Wires        | Several  | For connections                                  |

---

## 🧠 PID Control Logic

| Sensor Readings (L-C-R) | Line Position  | Error Value |
|-------------------------|----------------|-------------|
| 0 1 1                   | Far Left       | -1          |
| 0 0 1                   | Slight Left    | -0.5        |
| 1 0 1                   | Centered       | 0           |
| 1 0 0                   | Slight Right   | +0.5        |
| 1 1 0                   | Far Right      | +1          |
| 0 0 0                   | Centered       | 0           |
| 1 1 1                   | Lost Line      | STOP        |

---

