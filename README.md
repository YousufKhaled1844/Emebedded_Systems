# Emebedded_Systems
Project about solar tracking system
Abstract:
This project presents the design and implementation of a solar tracking system using an Arduino Uno microcontroller. 
The system offers two modes of operation: automatic and manual control.
In manual mode, an infrared (IR) receiver with a remote control enables the user to adjust the position of the solar panel in both the vertical (up/down) and horizontal (left/right) axes. 
The system incorporates two motors and a motor drive L298N voltage regulator for precise movement in the X and Y axes. For automatic mode,
a Proportional-Integral-Derivative (PID) controller is employed, along with a photoresistor for accurate tracking of light intensity.

Introduction:
The utilization of renewable energy sources, such as solar power, has gained significant attention in recent years due to their sustainability and environmental benefits.
Maximizing the efficiency of solar panels is crucial for harnessing the maximum available solar energy.
This project aims to develop an embedded system that optimizes the positioning of a solar panel throughout the day,
ensuring it remains aligned with the sun's position, thus maximizing energy generation.

System Design:
The core of the solar tracking system is the Arduino Uno microcontroller,
chosen for its flexibility, ease of programming, and compatibility with various electronic components. 
The system incorporates two main modes: manual and automatic control.

Manual Control:
In manual mode, an IR receiver and a remote control enable the user to adjust the solar panel's position.
The remote control provides intuitive buttons for moving the panel up, down, left, and right.
To facilitate movement, two motors are employed, one for the vertical axis (Y) and the other for the horizontal axis (X).
The motor drive L298N voltage regulator ensures the motors receive appropriate power and control signals.

Automatic Control:
The automatic mode enables the system to autonomously track the sun's position using a PID controller and a photoresistor. 
The PID controller continuously adjusts the panel's orientation based on feedback from the photoresistor,
which measures the intensity of light falling on the panel. By maintaining optimal alignment with the sun,
the system maximizes the solar panel's energy absorption throughout the day.

Implementation and Results:
The solar tracking system was implemented on the Arduino Uno microcontroller,
utilizing the appropriate libraries and coding techniques.
In manual mode, the system successfully responded to commands from the IR receiver, 
allowing precise positioning of the solar panel in both the vertical and horizontal axes. 
In automatic mode, the PID controller effectively tracked the sun's position, ensuring the panel remained optimally aligned with the light source.

Conclusion:
This project presents a solar tracking system that combines manual and automatic control modes using an Arduino Uno microcontroller.
The system enables precise positioning of a solar panel through manual user control using an IR receiver and remote control. 
Additionally, the automatic mode employs a PID controller and a photoresistor for autonomous solar tracking, 
maximizing energy absorption throughout the day. The project demonstrates the feasibility and effectiveness of utilizing embedded systems to 
enhance the efficiency of solar power generation.
