milestones-DS.txt
Damien Staebler
COSC303, 10/19/2026

# Github PR
https://github.com/TennesseeLunabotics/Lunabot-2027/pull/8

# Current To-Do List:
- Restructure repo from last year.
- ensure everything is documented.
- Setup Mini-bot (which we are currently building the hardware). This is mainly use to test drivetrain system eg lidar, path finding algorithm and auto.
- prerequisites (Docker n stuff), and build/run commands in README.md.
- [x] Lidar stuff

# Progress Summary:
I am currently working on getting all the data to work. so we use lidar from Unitree and they have C++ library, so I created a new ROS2 node in our main repo and have it link up with everything else and work with Nivida Nano jetson.

# Reflection
We got the codebase to compile without errors, but running the lidar node we get seg fault, not exactly sure why that is the case. Another issue we had is for some reason Nvidia Jetson Nano isn't communicating with ESP32. but if I connect my pc and serial monitor esp32, it works perfectly. So still couple things needs to get figured out. Last year, each of our ros2 node has its own constants file and shares the same value. so if you want to change something, you would have to change across all of the constants files which the whole purpose of constants is so u don't have to do that. So I created robot_constants node that keeps all that in one location. 

# Timelog
10-22-2026: 2hr  - working on getting lidar to work properly
10-21-2026: 1.5h - Got the code base to build without error, shovel node still not functioning. Also ESP32 is working now after flashing the firmware.
10-19-2026: 3h   - Fixing our build script, removed warnings from Jetson nano GPIO stuff, and SparkBase.


# Milestone Rubric
- 15 pts: Repo structure and doc
- 3 pts: docker, build/run documentation
- 8 pts: Hardware Assembly & LiDAR/Sensor Integration
- 8 pts: Drivetrain Control & Pathfinding Algorithm Implementation
- 6 pts: Autonomous Navigation & System Validation on Mini-Bot
