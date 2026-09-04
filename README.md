<div align="center">

# 🚗 CANBusSimulator

**Simulate real CAN Bus protocol in C for automotive testing – complete with 8 ECUs, React dashboard, fuzzing, and anomaly detection.**  
*Perfect for devs building embedded systems without expensive hardware.*

[![GitHub Stars](https://img.shields.io/github/stars/semjhaydin/CANBusSimulator?style=for-the-badge&logo=github&logoColor=white&color=0891b2)](https://github.com/semjhaydin/CANBusSimulator)
[![License](https://img.shields.io/github/license/semjhaydin/CANBusSimulator?style=for-the-badge&color=6366f1)](https://github.com/semjhaydin/CANBusSimulator/blob/main/LICENSE)
[![Language](https://img.shields.io/badge/C-0891b2?style=for-the-badge&logo=c&logoColor=white)](https://github.com/semjhaydin/CANBusSimulator)

</div>

## Table of Contents
- [About / Overview](#about--overview)
- [Key Features](#key-features)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## About / Overview

Hey there! **CANBusSimulator** is your go-to tool for testing automotive systems without needing real CAN hardware. Written in efficient C, it faithfully recreates the CAN Bus protocol – arbitration, error handling, bit stuffing, and all. Imagine spinning up 8 virtual ECUs (Engine, ABS, Airbag, etc.) that talk over a simulated bus, complete with fuzzing attacks and anomaly detection.

This solves a huge pain point for **embedded devs, automotive engineers, and HIL (Hardware-in-the-Loop) testers**. No more waiting for physical buses or pricey tools – just compile, run, and test your algorithms locally. What sets it apart? A slick **React dashboard** for real-time visualization, candump-compatible logs, and security layers with 5 attack types. It's battle-tested for fuzzing and detection, making it ideal for research or production validation.

Whether you're prototyping ECUs, training ML models on CAN traffic, or hunting bus-off conditions, this sim has you covered. Created April 17, 2026 – fresh and ready to roll!

---

## Key Features

✨ **8 Simulated ECUs** — Engine, ABS, Airbag, Climate, Steering, Cabin, Tires, Dashboard with realistic message IDs and filters.

✨ **Full CAN Protocol Stack** — Arbitration, broadcast, bit stuffing, encode/decode via CANFrame struct.

✨ **Error Handling & States** — Error counters, NORMAL → ERROR-ACTIVE → BUS-OFF transitions per node.

✨ **Security Testing** — CANFuzzer with 5 attack types (fuzzing, replay, etc.) + CANDetector with 4 anomaly rules, logs to `logs/anomali.log`.

✨ **High-Perf Bus Layer** — 32-slot ring buffer for low-latency simulation.

✨ **React Dashboard** — Live visualization via `dashboard/public/can_dashboard.json`.

✨ **CAN Tools Suite** — Logger (candump format to `logs/can_traffic.log`), Parser (filter/stats), JSON exporter.

✨ **Turkish Support** — Bilingual docs for global automotive teams.

---

## Tech Stack

<div align="center">

[![C](https://img.shields.io/badge/C-0891b2?style=for-the-badge&logo=c&logoColor=white)](https://github.com/semjhaydin/CANBusSimulator)
[![React](https://img.shields.io/badge/React-61DAFB?style=for-the-badge&logo=react&logoColor=white)](https://github.com/semjhaydin/CANBusSimulator)
[![Node.js](https://img.shields.io/badge/Node.js-43853D?style=for-the-badge&logo=node.js&logoColor=white)](https://github.com/semjhaydin/CANBusSimulator)

</div>

---

## Getting Started

### Prerequisites
- **GCC** or any C compiler (tested with GCC 12+)
- **Node.js 18+** (for React dashboard)
- **make** (for building)
- Linux/macOS recommended; Windows via WSL

### Installation

1. Clone the repo:
   ```bash
   git clone https://github.com/semjhaydin/CANBusSimulator.git
   cd CANBusSimulator
   ```

2. Build the C simulator:
   ```bash
   make
   ```

3. Start the React dashboard (in a new terminal):
   ```bash
   cd dashboard
   npm install
   npm start
   ```
   Open http://localhost:3000

> 💡 **Tip:** Run `make clean` to rebuild from scratch.

---

## Usage

### Basic Simulation
Launch 8 ECUs on the virtual bus:

```bash
./can_simulator -n 8 -t 60  # Run 8 nodes for 60 seconds
```

Generates `logs/can_traffic.log` in candump format.

### Fuzzing & Detection
Test security layers:

```bash
./can_simulator -fuzz replay -d detect -o logs/anomali.log
```

> 📊 **View in Dashboard:** Dashboard auto-loads `can_dashboard.json` for live ECU stats, arbitration wins, and anomaly alerts.

### Parse Logs
```bash
./can_parser logs/can_traffic.log --filter=0x100 --stats
```

---

## Project Structure

```
CANBusSimulator/
├── src/
│   ├── can_node.c      # ECU logic, filters, error states
│   ├── can_bus.c       # Ring buffer, arbitration
│   ├── can_frame.c     # Encode/decode, bit stuffing
│   ├── can_fuzzer.c    # 5 attack types
│   └── can_detector.c  # 4 anomaly rules
├── tools/
│   ├── can_logger.c
│   ├── can_parser.c
│   └── can_json.c
├── dashboard/          # React app
│   └── public/can_dashboard.json
├── logs/
│   ├── can_traffic.log
│   └── anomali.log
├── Makefile
└── README.md
```

---

## Contributing

Love the project? Help make it even better!

1. Fork the repo and create your branch (`git checkout -b feature/AmazingFeature`).
2. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
3. Push to the branch (`git push origin feature/AmazingFeature`).
4. Open a Pull Request – mention any related [issues](https://github.com/semjhaydin/CANBusSimulator/issues).

> 🙌 Questions? Open an issue at [semjhaydin/CANBusSimulator/issues](https://github.com/semjhaydin/CANBusSimulator/issues).

---

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more info.

Created by Semih Aydın