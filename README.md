# Prometheus Mk1 — 4×4 Autonomous Mini Sumo Robot

**Prometheus Mk1** is an autonomous **4×4 (4WD) `10 × 10 cm`, `500 g` class Mini Sumo** competition robot designed in **Onshape** for **Techno Robotics**. Built to pack four `050`-size gearmotors, four `JS2622S` silicone wheels, four `JS40F` opponent sensors, dual `QRE1113` line sensors, a spring-loaded hinged front katana plow, and a rear anti-wedge blade inside the strict `100 × 100 mm` competition footprint, Prometheus pairs compact 4WD mechanical packaging with custom **PlatformIO C++** control firmware.

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

## Competition Photo

<p align="center">
  <img src="photos/prometheus_mk1_oradea_14th.jpg?raw=true" width="65%" alt="Prometheus Mk1 at the 14th Edition of Robotics Championship in Oradea" />
</p>
<p align="center"><em>Prometheus Mk1 on the dohyo during the 14th Edition of the Robotics Championship in Oradea.</em></p>

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

## Firmware Overview (`firmware/`)

The firmware in [`firmware/`](firmware/) is a **PlatformIO (Arduino / ATmega32U4)** C++ project targeting the **JSumo XMotion V3 / MiniBeast V1** controller:

- **Sensor Integration:** Polls the four `JS40F` digital IR opponent sensors (front-left, front-right, and left/right flanks) along with the two bottom `QRE1113` IR reflection sensors for white-border ring recovery.
- **4×4 Drivetrain Control:** Uses the [`MiniBeastV1`](firmware/lib/MiniBeastV1/) H-bridge driver to control the left (`LF + LR`) and right (`RF + RR`) parallel motor channels via PWM speed and direction pins.
- **Match & Strategy Control:** Supports referee start/stop module control (`A0`) and onboard DIP switch configuration (`D5`–`D7`).

---

## Repository Structure

```text
Prometheus-4x4-Mini-Sumo/
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
│   └── WIRING.md                            # ATmega32U4 hardware pinout & 4WD motor wiring reference
├── firmware/
│   ├── platformio.ini                       # PlatformIO configuration (board = leonardo)
│   ├── src/
│   │   ├── main.cpp                         # Autonomous control firmware
│   │   ├── headers/                         # Configuration headers
│   │   └── files/                           # Configuration sources
│   └── lib/MiniBeastV1/                     # H-bridge motor & LED library
├── photos/
│   └── prometheus_mk1_oradea_14th.jpg       # 14th Robotics Championship (Oradea) competition photo
├── renders/                                 # 7× 1600×1200 Onshape-colored CAD & X-Ray renders
├── Images/                                  # Early design & CAD reference screenshots
├── BOM.csv                                  # Spreadsheet Bill of Materials ($277.38 total)
├── Prometheus-Mk1-Journal.md                # 80-hour engineering design & build log
├── LICENSE                                  # MIT License
└── README.md
```

---

## Documentation & Build Resources

- **Bill of Materials & Fasteners:** [`docs/BOM.md`](docs/BOM.md) & [`BOM.csv`](BOM.csv) — `$173.85` project items (`$277.38` grand total including international shipping & 23% import duty)
- **Hardware Pinout & Wiring Reference:** [`docs/WIRING.md`](docs/WIRING.md)
- **80-Hour Engineering Journal:** [`Prometheus-Mk1-Journal.md`](Prometheus-Mk1-Journal.md)
