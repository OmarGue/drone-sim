# Drone Delivery Flight Simulator

##  Overview
A **flight simulator for a fleet of delivery drones** navigating a 2D map with obstacles.  
The project explores **concurrent programming** (multi-threaded simulation) and **network communication** (TCP/UDP over IPv4 Ethernet).

- Two modes:
  - **Simulation mode** (single process): multiple drones simulated with threads.
  - **Distributed mode** (networked): a **Controller** server + multiple **Drone** clients communicating over TCP or UDP.

## Tech Stack
- **Language:** C (C11), POSIX/Linux
- **Concurrency:** `pthreads`, mutexes, condition variables
- **Networking:** BSD sockets (TCP/UDP/IPv4), `select()`/`epoll` (Linux)
- **Build:** `make`, `gcc`
- **OS:** Linux (Ubuntu/Debian/Fedora/Arch)

##  Features
- 2D grid map with obstacles and no-fly zones
- Multiple drones (configurable), basic kinematics & discrete time steps
- Path planning (greedy/A* placeholder), collision avoidance (simple rules)
- Heartbeat, state updates, and command messages over TCP/UDP
- Deterministic seed for reproducible runs
- Structured logs (stdout/syslog)

##  Project Structure
