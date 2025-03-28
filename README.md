# Hardware Simulation Automation

## Overview
This project automates the process of testing a hardware architecture using **ModelSim**. It generates input vectors, updates configuration files, runs the simulation, and verifies the results by comparing expected vs. actual outputs. The system supports different levels of **parallelism (2, 4, 8-bit)**, ensuring flexibility in hardware validation.

## Features
- **Automated Input Generation**: Creates test vectors in binary format for different parallelism levels.
- **Dynamic Configuration Update**: Modifies `constants.vhd` to set the correct parallelism.
- **Simulation Execution**: Runs ModelSim through a Bash script.
- **Result Verification**: Compares the simulated results with expected values.
- **Logging System**: Generates `log.txt` with error details and simulation performance.

## How It Works
1. **Run the Simulation**
   - The program iterates over different parallelism values (`2, 4, 8-bit`).
   - Calls `generateInputVectors()` to create test patterns.
   - Updates `constants.vhd` to reflect the selected parallelism.
   - Executes the simulation via `runSimulation.sh`.
   - Renames the output files for organization.
   - Compares results and logs errors in `log.txt`.

2. **Error Checking**
   - Reads the expected results from `pattern_<parallelism>bit.txt`.
   - Compares them with the generated output (`output_results_<parallelism>bit.txt`).
   - Logs mismatches in `log.txt`.

## Prerequisites
- **C++ Compiler** (GCC, Clang, etc.)
- **ModelSim** (or another VHDL simulator)
- **Bash Shell** (for executing scripts)
- **Makefile** (optional, for automation)

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/hardware-sim-automation.git
   cd hardware-sim-automation
   ```
2. Compile the C++ program:
   ```sh
   g++ -o simulator sim.cpp
   ```
3. Run the simulation:
   ```sh
   ./simulator
   ```
4. Check the logs for errors:
   ```sh
   cat log.txt
   ```

## Example Log Output
```
LogFile per l'architettura a 4bit:
Errore per il pattern 0011 0101 1000: valore attuale 1001
Errore per il pattern 0110 1010 1111: valore attuale 1110
...
```

## Future Enhancements
- Add support for **FPGA testing**.
- Improve error visualization.
- Expand support for more parallelism levels.

---
This project streamlines the process of **validating a hardware architecture** before synthesis, making debugging more efficient.

