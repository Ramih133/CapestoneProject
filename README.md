

# Low-Cost Endpoint Communication for Home Temperature Regulation

This project addresses the inefficiencies and high costs associated with current home temperature regulation systems by implementing a low-cost endpoint communication solution. By eliminating the need for Wi-Fi-enabled expensive devices, we developed an affordable, efficient, and serverless communication system that ensures accurate temperature regulation in homes.

## Features
- **Master and Remote Communication:** Utilizes 433 MHz RF modules to establish direct communication between master and remote devices.
- **Temperature Regulation:** The master device sets a desired temperature and sends it to remote devices, which then decide whether to open or close vents based on the current temperature.
- **Modes:** Includes heating and cooling modes, with LED indicators for the selected mode.
- **Prototyping and Testing:** Components were rigorously tested and debugged to ensure reliability.

## Project Deliverables
1. **Master Device Circuit:**
   - Controlled by an Arduino Uno.
   - Sets the desired temperature and sends it to remote devices.
   - Allows switching between heating and cooling modes.
2. **Remote Device Circuit:**
   - Controlled by an Arduino Uno.
   - Simulates room temperature using a potentiometer.
   - Makes decisions to open or close vents based on received data.
3. **Serverless Communication:** Achieved using 433 MHz RF modules, ensuring affordability and reliability.

## Results
- Successfully implemented direct communication between master and remote devices.
- Achieved accurate temperature regulation in different rooms.
- Fully functional prototype demonstrating the project's objectives.

## Future Work
- Improve communication range and reliability using a spectrum analyzer.
- Enhance the system to support multiple remote devices.
- Integrate with a mobile app for real-time monitoring and control.
- Transition from Arduino to microcontrollers for cost reduction.



