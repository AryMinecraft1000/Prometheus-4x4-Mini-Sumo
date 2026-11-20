# Wiring & Pinout Reference — Prometheus Mk1 (V1)

All pin assignments and direct-port register masks match [`firmware/src/main.cpp`](../firmware/src/main.cpp) and [`firmware/lib/MiniBeastV1/miniBeastV1.cpp`](../firmware/lib/MiniBeastV1/miniBeastV1.cpp) running on the **JSumo XMotion V3 / MiniBeast V1** controller (**ATmega32U4**, `board = leonardo` in `platformio.ini`).

---

## ATmega32U4 Pinout Table

| Pin | Function | Component | Direction | Active State / Notes |
| :---: | :--- | :--- | :---: | :--- |
| `D0` | Left Line Sensor | QRE1113 IR Reflection Sensor | `INPUT` | `0` = White border, `1` = Black dohyo |
| `A1` | Right Line Sensor | QRE1113 IR Reflection Sensor | `INPUT` | `0` = White border, `1` = Black dohyo |
| `D2` | Left Opponent Sensor | JSumo JS40F | `INPUT` | `1` = Opponent seen, `0` = Clear (`PIND` bit 1) |
| `D1` | Middle-Left Opponent Sensor | JSumo JS40F | `INPUT` | `1` = Opponent seen, `0` = Clear (`PIND` bit 3) |
| `A2` | Middle-Right Opponent Sensor | JSumo JS40F | `INPUT` | `1` = Opponent seen, `0` = Clear (`PINF` bit 5) |
| `A4` | Right Opponent Sensor | JSumo JS40F | `INPUT` | `1` = Opponent seen, `0` = Clear (`PINF` bit 1) |
| `A0` | Start / Referee Signal | IR Start Module / Switch | `INPUT` | `HIGH` = Match active, `LOW` = Standby / Stop |
| `D5` | Strategy Switch 1 | Onboard DIP Switch `Dip1` | `INPUT` | `LOW` = Switch ON, `HIGH` = Switch OFF |
| `D6` | Strategy Switch 2 | Onboard DIP Switch `Dip2` | `INPUT` | `LOW` = Switch ON, `HIGH` = Switch OFF |
| `D7` | Strategy Switch 3 | Onboard DIP Switch `Dip3` | `INPUT` | `LOW` = Switch ON, `HIGH` = Switch OFF |
| `D8` | Status LED 1 | Onboard User LED `UL1` | `OUTPUT` | Status / debug indicator |
| `D9` | Status LED 2 | Onboard User LED `UL2` | `OUTPUT` | Status / debug indicator |
| `A3` | Trimpot | Onboard Potentiometer `TP` | `INPUT` | Analog tuning input (`MiniBeastV1::Trimpot()`) |
| `D10` | Left Drive PWM (`LM_PWM`) | H-Bridge Left Channel | `OUTPUT` | Drives `LF` + `LR` 050 motors in parallel |
| `D12` | Left Drive Dir (`LM_DIR`) | H-Bridge Left Channel | `OUTPUT` | `HIGH` = Forward, `LOW` = Reverse |
| `D11` | Right Drive PWM (`RM_PWM`) | H-Bridge Right Channel | `OUTPUT` | Drives `RF` + `RR` 050 motors in parallel |
| `D13` | Right Drive Dir (`RM_DIR`) | H-Bridge Right Channel | `OUTPUT` | `HIGH` = Forward, `LOW` = Reverse |
| `D4` | Servo (Optional / Reserved) | `ServoPin` | — | Defined in `main.cpp`; currently disabled |

---

## 4×4 Parallel Motor Wiring

Because Prometheus Mk1 uses a **4-wheel-drive (4WD)** layout driven by a 2-channel H-bridge:
- **Left Channel (`D10` PWM / `D12` DIR):** Wire **Left-Front (`LF`)** and **Left-Rear (`LR`)** 050 motors in parallel with matching polarity so both spin forward together.
- **Right Channel (`D11` PWM / `D13` DIR):** Wire **Right-Front (`RF`)** and **Right-Rear (`RR`)** 050 motors in parallel with matching polarity so both spin forward together.

---

## Single-Pass Register Polling (`PIND` / `PINF`)

Instead of calling `digitalRead()` four separate times per loop iteration, `getAllOpponentSensorValues()` snapshots both ATmega32U4 input port registers at once:

```cpp
uint32_t allPinsValues{ ((uint32_t)PIND << 8) | PINF };
```

| Bitmask Constant | Pin | ATmega32U4 Register Bit | Combined `allPinsValues` Bit | Sensor Bit |
| :--- | :---: | :--- | :---: | :---: |
| `MASK_SENSOR_1` | `D2` | `PIND` bit 1 (`PD1`) | `1 << 9` | `SENSOR_1_BIT` (Left) |
| `MASK_SENSOR_2` | `D1` | `PIND` bit 3 (`PD3`) | `1 << 11` | `SENSOR_2_BIT` (Middle-Left) |
| `MASK_SENSOR_3` | `A2` | `PINF` bit 5 (`PF5`) | `1 << 5` | `SENSOR_3_BIT` (Middle-Right) |
| `MASK_SENSOR_4` | `A4` | `PINF` bit 1 (`PF1`) | `1 << 1` | `SENSOR_4_BIT` (Right) |

---

## Strategy DIP Switch Matrix

DIP switch states are read once at boot in `setup()` (`0` = switch ON / `LOW`, `1` = switch OFF / `HIGH`):

| `Dip1` (`D5`) | `Dip2` (`D6`) | `Dip3` (`D7`) | Strategy Enum | Behavior Summary |
| :---: | :---: | :---: | :--- | :--- |
| `OFF` (`1`) | `OFF` (`1`) | `OFF` (`1`) | `normal` | Standard line-safe opponent tracking + 2 s diagonal charge boost |
| `ON` (`0`) | `OFF` (`1`) | `OFF` (`1`) | `flankS` | Ignores diagonal/center until side (`D2`/`A4`) or dual-front hits (`sideSaw`), then switches to `normal` |
| `OFF` (`1`) | `ON` (`0`) | `OFF` (`1`) | `allIn` | Full 100% forward speed (`baseSpeed = 80`, `forward1/2/3 = 100`) |
| `OFF` (`1`) | `OFF` (`1`) | `ON` (`0`) | `lineTest` | Line-detection test mode (`handleLineDetection()`) |
| `ON` (`0`) | `ON` (`0`) | `OFF` (`1`) | `zigzag` | Alternating 400 ms left/right arc search (`speedM1M2(7,20)` / `(20,7)`) + direct sensor pursuit |
