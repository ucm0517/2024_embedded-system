🛠 Embedded Systems Lab – Sungkyul University
This repository contains practical assignments from the Embedded Systems course at the Department of Information and Communication Engineering, Sungkyul University.
Each project demonstrates embedded programming using the STM32F4 microcontroller and STM32 HAL libraries, and includes exercises from multiple chapters throughout the semester.

📁 Directory Structure
embedded_system/
├── CH3/ ~ CH14/           # Chapter-wise hands-on exercises
├── FreeRTOS_1_Sample/     # FreeRTOS sample: multitasking basics
├── FreeRTOS_2_msg_queue/  # FreeRTOS with message queues
├── HAL-3-1/               # HAL-level examples and variations
├── LIB_TLCD.c/.h          # Custom LCD control library
└── Common drivers/headers for STM32F4xx

⚙️ Tools & Environment
- Microcontroller: STM32F405RGTx (STM32F4 series)
- IDE: STM32CubeIDE
- Language: C
- Framework: STM32 HAL (Hardware Abstraction Layer)
- Hardware: 16x2 Character LCD (HD44780), UART, GPIO, Segments, etc.
- 
🧠 Learning Objectives
- GPIO control and peripheral interfacing using HAL
- LCD text display and positioning (via TLCD library)
- UART communication and debugging
- Timer usage, interrupts, and NVIC configuration
- Segment display control
- FreeRTOS fundamentals (task switching, message queues)

- 📌 Highlights
- Clean modular code per chapter (CH3–CH14)
- Custom libraries for LCD handling
- Real-time system examples with FreeRTOS

- 📎 Notes
This repository is part of a university course project and may require hardware (STM32 board + LCD, etc.) to reproduce.
Ensure proper pin mapping and header configurations when testing on different STM32 boards.
