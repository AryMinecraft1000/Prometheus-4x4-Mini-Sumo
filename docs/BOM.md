# Bill of Materials — Prometheus Mk1

Complete hardware, electronics, 3D-printed structural parts, and fastener list for **Prometheus Mk1** (4×4 Autonomous `10 × 10 cm` Mini Sumo Robot).

---

## 1. Core Controller & Power

| Qty | Component | Specification | Notes / Link |
| :-: | :--- | :--- | :--- |
| 1 | **Controller Board** | **JSumo XMotion V3** / **MiniBeast V1** All-In-One Controller (`ATmega32U4`, `80 × 30 mm`) | Dual H-bridge, voltage regulator, DIP switches, user LEDs ([JSumo](https://www.jsumo.com/xmotion-robot-controller)) |
| 1 | **Battery** | **3S 370 mAh 11.1V LiPo** (`55 × 27 × 16 mm` bay in CAD) | Locally sourced, JST power connector |
| 1 set | **Power Connector** | **JST Male & Female** connector pair | Battery disconnect & harness |

---

## 2. Opponent & Line Sensors

| Qty | Component | Model / Specification | Pins | Notes / Link |
| :-: | :--- | :--- | :--- | :--- |
| 4 | **Opponent Sensors** | **JSumo JS40F** Digital IR Distance Sensor (min. 40 cm range) | `D2` (Left), `D1` (Mid-Left), `A2` (Mid-Right), `A4` (Right) | 2× front angled + 2× lateral flank sensors ([JSumo](https://www.jsumo.com/js40f-digital-infrared-ir-distance-sensor-min-40-cm-range)) |
| 2 | **Line / Edge Sensors** | **QRE1113** IR Reflection Sensor (`9 × 15 mm`) | `D0` (Left), `A1` (Right) | Bottom front corners; `0` = white border ([AliExpress](https://www.aliexpress.com/item/1005005682098178.html)) |

---

## 3. 4×4 Drivetrain & Hinged Plow Hardware

| Qty | Component | Specification | Notes / Link |
| :-: | :--- | :--- | :--- |
| 4 | **Drive Motors** | **050-Size DC Gearmotors** (`LF`, `LR`, `RF`, `RR`) | Wired as parallel Left (`LF+LR`) and Right (`RF+RR`) pairs ([AliExpress](https://www.aliexpress.com/item/1005008126068612.html)) |
| 4 (2 pairs) | **Wheels** | **JSumo JS2622S** Steel-Silicone Wheel Pair (`26 × 22 mm`) | High-grip silicone tread ([JSumo](https://www.jsumo.com/js2622-steel-silicone-wheel-pair-26mm-diameter)) |
| 2 | **Wedge Blades** | **JSumo 10 cm Mini Katana Blade** | 1× spring-loaded hinged front plow + 1× rear anti-wedge blade ([JSumo](https://www.jsumo.com/mini-katana-blade-for-mini-sumo-robot-10cm)) |
| 1 | **Hinge Axle** | `Ø2 mm` steel rod, `35–50 mm` length (`50 mm` recommended) | Front hinged plow pivot shaft |
| 1 | **Torsion Spring** | Torsion spring, `≤ 11 mm` max length | Keeps front katana blade pressed flat onto the dohyo |

---

## 4. 3D-Printed Structural Parts (from [`3D Models/Prometheus Mk1.step`](../3D%20Models/Prometheus%20Mk1.step))

> Recommended materials: **ASA** or **PETG** for impact and thermal resistance around the 050 gearmotors.

| Qty | STL File | CAD Dimensions (`mm`) | Function |
| :-: | :--- | :---: | :--- |
| 1 | [`Prometheus Mk1 - Chassis Base.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Chassis%20Base.stl) | `100.0 × 80.5 × 20.7` | Main 4×4 chassis bay, battery tray, motor pockets, and bottom sensor recesses |
| 1 | [`Prometheus Mk1 - Front Plate.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Front%20Plate.stl) | `100.0 × 21.5 × 36.0` | Sloped front armor shield with dual `JS40F` cutouts and hinged plow mounts |
| 1 | [`Prometheus Mk1 - Blade Bracket V2.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Blade%20Bracket%20V2.stl) | `100.0 × 18.4 × 5.9` | Articulated front katana plow hinge carrier and torsion spring mount |
| 1 | [`Prometheus Mk1 - Front Wall L.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Front%20Wall%20L.stl) | `11.0 × 28.6 × 33.4` | Left front wheel guard & structural side bulkhead |
| 1 | [`Prometheus Mk1 - Front Wall R.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Front%20Wall%20R.stl) | `11.0 × 28.6 × 33.4` | Right front wheel guard & structural side bulkhead |
| 2 | [`Prometheus Mk1 - IR Sensor Holder 1.stl`](../3D%20Models/Prometheus%20Mk1%20-%20IR%20Sensor%20Holder%201.stl) | `16.7 × 11.0 × 23.5` | Side-facing `JS40F` flank sensor mounts (between front & rear wheels) |
| 2 | [`Prometheus Mk1 - IR Sensor Holder 2.stl`](../3D%20Models/Prometheus%20Mk1%20-%20IR%20Sensor%20Holder%202.stl) | `22.0 × 11.9 × 17.1` | Front-angled `JS40F` sensor mounts behind `Front Plate` |
| 4 | [`Prometheus Mk1 - Motor Cover.stl`](../3D%20Models/Prometheus%20Mk1%20-%20Motor%20Cover.stl) | `21.8 × 13.8 × 3.8` | Top 050 motor clamping caps |

---

## 5. Fasteners & Miscellaneous Hardware

| Qty | Fastener / Item | Specification | Location |
| :-: | :--- | :--- | :--- |
| 8 | **M3 × 19 mm Screws** | 19 mm thread length | Clamping the 4× `Motor Cover` / motor mounts through `Chassis Base` |
| 4 | **M2 × 9 mm Screws** | 9 mm thread length | Mounting `Front Wall L` & `Front Wall R` |
| 2 | **M2 × 12–16 mm Screws** | 12 mm thread length (`M2×0.40 × 16` in CAD) | Hinged `Blade Bracket V2` / wing-blade pivot |
| 2 | **M2 × 6 mm Screws** | 6 mm thread length | Mounting `Front Plate` |
| 2 | **M2 × 5 mm Screws** | 5 mm full length | Mounting front `JS40F` opponent sensors |
| 2 | **M2 × 4 mm Screws** | 4 mm full length | Mounting side `JS40F` opponent sensors |
| 4+ | **M2 Hex Nuts** | `M2 × 0.4` | Plow hinge screws & sensor mounts (plus M3 nuts in chassis bottom pockets) |
| — | **Hookup Wire** | Silicone sensor/motor harnesses | Included with JSumo sensors + battery lead |

---

## 6. Cost Breakdown Summary (from [`BOM.csv`](../BOM.csv))

| Item / Category | Unit Price (USD) | Qty | Total (USD) |
| :--- | :---: | :---: | ---: |
| JSumo XMotion All-In-One Controller V3 | $44.95 | 1 | $44.95 |
| JSumo Mini Katana Blade (10 cm) | $4.95 | 2 | $9.90 |
| JSumo JS40F Digital Distance Sensor | $12.50 | 4 | $50.00 |
| JSumo JS2622S Steel-Silicone Wheel Pair | $14.50 | 2 | $29.00 |
| Generic 050 DC Motor | $5.00 | 4 | $20.00 |
| QRE1113 IR Reflection Sensor | *Region Dep.* | 2 | $0.00* |
| JSumo International Shipping | $46.95 | 1 | $46.95 |
| Import Tax (23% on JSumo items + shipping) | $41.58 | 1 | $41.58 |
| AliExpress Shipping (Motors / Sensors) | $15.00 | 1 | $15.00 |
| 3S LiPo Battery (Locally Sourced) | $20.00 | 1 | $20.00 |
| **Grand Total** | — | — | **$277.38** |
