# Wiring & Pinout Reference — Prometheus Mk1

Hardware pin assignments for **Prometheus Mk1** on the **JSumo XMotion V3** controller (**ATmega32U4**, `board = leonardo`).

---

## ATmega32U4 Pinout Table

| Pin | Function | Component | Direction | Notes |
| :---: | :--- | :--- | :---: | :--- |
| `D0` | Left Line Sensor | QRE1113 IR Reflection Sensor | `INPUT` | Bottom front-left edge detection |
| `A1` | Right Line Sensor | QRE1113 IR Reflection Sensor | `INPUT` | Bottom front-right edge detection |
| `D2` | Left Opponent Sensor | JSumo JS40F | `INPUT` | Left flank distance sensor |
| `D1` | Middle-Left Opponent Sensor | JSumo JS40F | `INPUT` | Front-left distance sensor |
| `A2` | Middle-Right Opponent Sensor | JSumo JS40F | `INPUT` | Front-right distance sensor |
| `A4` | Right Opponent Sensor | JSumo JS40F | `INPUT` | Right flank distance sensor |
| `A0` | Start / Referee Signal | IR Start Module / Switch | `INPUT` | Match start / stop input |
| `D5`–`D7` | DIP Switches 1–3 | Onboard 3-Position DIP Switch | `INPUT` | Mode / preset selection |
| `D8`–`D9` | User LEDs 1–2 | Onboard Status LEDs (`UL1`, `UL2`) | `OUTPUT` | Status indicators |
| `A3` | Trimpot | Onboard Potentiometer (`TP`) | `INPUT` | Analog tuning input |
| `D10` | Left Drive PWM (`LM_PWM`) | H-Bridge Left Channel | `OUTPUT` | Drives `LF` + `LR` 050 motors in parallel |
| `D12` | Left Drive Dir (`LM_DIR`) | H-Bridge Left Channel | `OUTPUT` | Left motor pair direction control |
| `D11` | Right Drive PWM (`RM_PWM`) | H-Bridge Right Channel | `OUTPUT` | Drives `RF` + `RR` 050 motors in parallel |
| `D13` | Right Drive Dir (`RM_DIR`) | H-Bridge Right Channel | `OUTPUT` | Right motor pair direction control |

---

## 4×4 Parallel Motor Wiring

Because Prometheus Mk1 uses a **4-wheel-drive (4WD)** layout driven by a 2-channel H-bridge:
- **Left Channel (`D10` PWM / `D12` DIR):** Wire **Left-Front (`LF`)** and **Left-Rear (`LR`)** 050 motors in parallel with matching polarity so both spin forward together.
- **Right Channel (`D11` PWM / `D13` DIR):** Wire **Right-Front (`RF`)** and **Right-Rear (`RR`)** 050 motors in parallel with matching polarity so both spin forward together.
