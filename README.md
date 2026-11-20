# Prometheus Mk1 (V1) — 4×4 Autonomous Mini Sumo Robot

**Prometheus Mk1** is an autonomous **4×4 (4WD) `10 × 10 cm`, `500 g` class Mini Sumo** competition robot designed in **Onshape** for **Techno Robotics**. Built to pack four `050`-size gearmotors, four `JS2622S` silicone wheels, four `JS40F` opponent sensors, dual `QRE1113` line sensors, a spring-loaded hinged front katana plow, and a rear anti-wedge blade inside the strict `100 × 100 mm` competition footprint, Prometheus pairs tight mechanical packaging with a fast **PlatformIO C++** firmware using single-pass port register polling and six DIP-selectable combat strategies.

> Unlike remote-controlled battlebots, international Mini Sumo robots operate **100% autonomously** inside a `77 cm` black dohyo ring with a white perimeter border—using high-speed IR opponent tracking and edge-avoidance control loops to locate, out-angle, and push opponents out of the ring.

<p align="center">
  <img src="renders/iso_front.png?raw=true" width="48%" alt="Prometheus Mk1 — Front Isometric CAD Render" />
  <img src="renders/iso_rear.png?raw=true" width="48%" alt="Prometheus Mk1 — Rear Isometric CAD Render" />
</p>

---

## Specifications

| Parameter | Specification |
| :--- | :--- |
| **Competition Class** | Mini Sumo (`10 × 10 cm`, `500 g` max) |
| **CAD Envelope (`Prometheus Mk1.step`)** | `100.00 mm × 100.24 mm × 38.40 mm` |
| **Estimated Weight** | ~300 g (ASA/PETG chassis) / ~400 g (stainless steel chassis) |
| **Controller** | JSumo XMotion V3 / MiniBeast V1 (`ATmega32U4`, `board = leonardo`) |
| **Drivetrain** | 4×4 Parallel Drive — 4× `050` DC Gearmotors (`LF`, `LR`, `RF`, `RR`) |
| **Wheels** | 4× JSumo `JS2622S` Steel-Silicone Wheels (`26 × 22 mm`) |
| **Opponent Sensors** | 4× JSumo `JS40F` Digital IR (`D2` Left, `D1` Mid-Left, `A2` Mid-Right, `A4` Right) |
| **Line / Edge Sensors** | 2× `QRE1113` IR Reflection Sensors (`D0` Left, `A1` Right) |
| **Wedge Blades** | 2× JSumo `10 cm` Mini Katana Blades (torsion-sprung front plow + fixed rear blade) |
| **Power** | 3S `370 mAh` `11.1V` LiPo (JST) |

---

## Mechanical & CAD Architecture

Prometheus Mk1 is modeled in Onshape as a single integrated `100 × 100 mm` assembly ([`3D Models/Prometheus Mk1.step`](3D%20Models/Prometheus%20Mk1.step)), with all structural printable parts exported as `Prometheus Mk1 - *.stl`:

- **4×4 Drivetrain Packaging (`Chassis Base` + `Motor Cover` ×4):** Four `050` motors sit symmetrically across the front and rear axles inside dedicated chassis pockets, clamped from above by four `Motor Cover` caps and eight `M3 × 19 mm` screws anchored into hex-nut pockets on the underside of `Chassis Base`.
- **Spring-Loaded Hinged Front Plow (`Front Plate` + `Blade Bracket V2` + `Blade`):** The front `10 cm` Mini Katana blade mounts to an articulated `Blade Bracket V2` pivoting on a `Ø2 mm × 50 mm` axle and tensioned downward by a torsion spring (`≤ 11 mm`) to maintain flush dohyo contact even over ring imperfections.
- **Rear Anti-Wedge Blade:** A second `10 cm` Mini Katana blade sits fixed along the rear edge (`Chassis Base`) to prevent opponents from getting underneath during flank or reverse recoveries.
- **4-Sensor Cross / Flank Array (`IR Sensor Holder 1` ×2 & `IR Sensor Holder 2` ×2):** Two front `JS40F` sensors sit recessed behind the sloped `Front Plate` in `IR Sensor Holder 2` mounts, while two lateral `JS40F` sensors sit tucked between the front and rear wheels in `IR Sensor Holder 1` housings for 180°+ target acquisition.
- **Wheel Protection & Top Electronics Deck (`Front Wall L/R`):** Left and right front side walls shield the front `JS2622S` tires from direct side impacts while supporting the upper `XMotion V3` controller above the recessed central `3S LiPo` bay.

---

## CAD Renders & Internal X-Ray

<p align="center">
  <img src="renders/front.png?raw=true" width="32%" alt="Front View" />
  <img src="renders/side.png?raw=true" width="32%" alt="Side View" />
  <img src="renders/top.png?raw=true" width="32%" alt="Top View" />
</p>
<p align="center">
  <img src="renders/bottom.png?raw=true" width="48%" alt="Bottom View" />
  <img src="renders/internal_xray.png?raw=true" width="48%" alt="Internal X-Ray CAD View" />
</p>

> *The **Internal X-Ray** view makes the outer chassis, front armor, side walls, and motor covers translucent to show internal packaging: 4× drive assemblies, 4× `JS40F` sensors, 2× red `QRE1113` line sensors, central `3S LiPo`, top `XMotion V3` board, and the torsion-spring plow hinge.*

---

## Firmware Architecture (`firmware/`)

The competition firmware in [`firmware/`](firmware/) is a **PlatformIO (Arduino / ATmega32U4)** C++ project built around the custom [`MiniBeastV1`](firmware/lib/MiniBeastV1/) H-bridge driver:

- **Single-Pass Register Sensor Polling:** `getAllOpponentSensorValues()` reads `((uint32_t)PIND << 8) | PINF` in one snapshot and applies bitmasks (`MASK_SENSOR_1..4`) for near-zero-latency 4-sensor state capture.
- **6 DIP-Switch Combat Strategies (read at boot on `D5`, `D6`, `D7`):**

| `Dip1` (`D5`) | `Dip2` (`D6`) | `Dip3` (`D7`) | Strategy | Match Behavior |
| :---: | :---: | :---: | :--- | :--- |
| `OFF` | `OFF` | `OFF` | **`normal`** | Line-safe memory-based tracking (`lastPos`) with graduated turn arcs & 2 s charge boost |
| `ON` | `OFF` | `OFF` | **`flankS`** | Flank-first opening (`handleOpponentDetection_Flank()`) until side or dual-front contact (`sideSaw`), then switches to `normal` |
| `OFF` | `ON` | `OFF` | **`allIn`** | Full 100% power scaling (`baseSpeed = 80`, `forward1/2/3 = 100`) |
| `OFF` | `OFF` | `ON` | **`lineTest`** | Ring-edge response test mode |
| `ON` | `ON` | `OFF` | **`zigzag`** | Non-blocking 400 ms alternating arc search (`checkTimer()`) + direct sensor pursuit |
| `ON` | `OFF` | `ON` | **`suicide`** | Opening 150 ms forward surge followed by 300 ms reverse-right spin |

- **Graduated Turn Profiles & Sustained Charge Boost:** Defines 5 turn severities (`left1..5` / `right1..5`, from full counter-rotation to gentle arcs) and automatically promotes sustained single-sensor diagonal locks (`pos_2` or `pos_4` held `≥ 2000 ms`) to full-power `forward1()` charge.
- **Bench Debug Modes:** Set `WhatToRun` in [`firmware/src/main.cpp`](firmware/src/main.cpp) to `printOpponentM`, `printLineM`, or `handleLineOnlyM` for serial sensor verification without triggering a match start.

---

## Repository Structure

```text
4x4-Mini-Sumo/
├── 3D Models/
│   ├── Prometheus Mk1.step                  # Full 3D CAD assembly (Onshape STEP)
│   ├── Prometheus Mk1 - Chassis Base.stl
│   ├── Prometheus Mk1 - Front Plate.stl
│   ├── Prometheus Mk1 - Blade Bracket V2.stl
│   ├── Prometheus Mk1 - Front Wall L.stl
│   ├── Prometheus Mk1 - Front Wall R.stl
│   ├── Prometheus Mk1 - IR Sensor Holder 1.stl
│   ├── Prometheus Mk1 - IR Sensor Holder 2.stl
│   ├── Prometheus Mk1 - Motor Cover.stl
│   └── Prometheus Mk1 - Part List.txt       # Printable STL quantity checklist
├── docs/
│   ├── BOM.md                               # Full hardware, electronics, printed parts & fasteners BOM
│   └── WIRING.md                            # ATmega32U4 pinout, port masks & DIP switch reference
├── firmware/
│   ├── platformio.ini                       # PlatformIO configuration (board = leonardo)
│   ├── src/
│   │   ├── main.cpp                         # State machine, register polling & 6 strategies
│   │   ├── headers/                         # config.h, flank.h
│   │   └── files/                           # config.cpp, flank.cpp
│   └── lib/MiniBeastV1/                     # Custom H-bridge motor & LED library
├── renders/                                 # 7× 1600×1200 Onshape-colored CAD & X-Ray renders
├── Images/                                  # Early design & CAD reference screenshots
├── BOM.csv                                  # Spreadsheet Bill of Materials ($277.38 total)
├── Prometheus-Mk1-Journal.md                # 80-hour engineering design & build log
└── README.md
```

---

## Documentation & Build Resources

- **Bill of Materials & Fasteners:** [`docs/BOM.md`](docs/BOM.md) & [`BOM.csv`](BOM.csv) — `$173.85` project items (`$277.38` grand total including international shipping & 23% import duty)
- **Pinout, Register Bitmasks & DIP Table:** [`docs/WIRING.md`](docs/WIRING.md)
- **80-Hour Engineering Journal:** [`Prometheus-Mk1-Journal.md`](Prometheus-Mk1-Journal.md)
