# Trajectory-generation-for-quadruped-robot-leg
Implementation of trajectory generation for a prototype leg using inverse kinematics, cubic splines and Arduino.

This project allows to control a quadruped robot prototype leg for describing a desired trajectory. The goal is to move the robot’s leg in a way such that point-foot of the robot follows a trajectory defined by a few points in the task space of the robot with respect to the shoulder position. Using the desired trajectory for the robot’s foot and the leg geometric configuration, it is possible to obtain the angle of each joint of the leg to achieve the desired foot position by means of inverse kinematics. Then, using cubic spline data interpolation, a cycle trajectory is obtained for each joint of the leg. Finally, using the Arduino Mega board and the Maestro servo controller, the servo motors at each joint are commanded to follow the desired trajectory at each time step, which results in the robot leg following the desired trajectory.  

## Files in this project
The desired foot position in task space is specified in the .xlsx file.
The codes for processing the data, inverse kinematics, trajectory generation and results plots are in the .m files. (I used Matlab for convenience and rapid prototyping, but the code is easily transferable to any other programming language i.e. Python).
The code for commanding the servo motors with the Arduino Mega board and Maestro servo controller is in the .ino file.

## Results
[[https://github.com/gcastillom90/Trajectory-generation-for-quadruped-robot-leg/blob/master/img/Desired_trajectory.png|alt=desired]]
