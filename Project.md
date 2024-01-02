## Background 

Xavier bot is a robotic device for autonomous navigation in unstructured clattered environments. It is capable of detailed maps of the areas it explores. 

In the robot, there are 4 wheels. Each wheel has its own motor to turn the wheels. 

![image](https://github.com/lahirub99/S5-Project/assets/91234872/9a289e40-72df-4b58-9447-8fb5440ae3d0)


Every wheel has its own encoder to measure the number of rounds each wheel has turned. 
The encoder transfers information about the number of cycles each wheel has turned on each cycle of the processing loop. The time of that loop can vary according to various reasons, therefore the reading of the number of cycles might be different. 

Of those 4 wheels, there is one wheel that shows abnormal behaviour. 
There are no shock absorbers on the robot wheels at the moment. Its wheels are fixed into its rigid body. It’s assumed that there is a slight deviation of angles in the rigid body. In other words, the erroneous wheel can be placed in a slightly different position than the place it is supposed to be placed on the robot due to that slight deviation in the rigid body.

This robot uses the ‘skid steering’ technique ( also known as tank steering or differential steering) to make turns and rotations. Skid steering involves changing the speed and direction of one side of the wheels relative to the other to create a skidding motion.  By slowing down or stopping one set of wheels while the other set continues to move, the robot can pivot around the slowed or stationary wheels, enabling turns.

![image](https://github.com/lahirub99/S5-Project/assets/91234872/c43cdd04-c453-4305-a696-e5b6ca00a26b)

When making a turn using the skid steering technique, the speed of the inside wheels is lower than the wheels outside. That makes the robot rotate or turn.

## Problem Statement


There is one wheel with abnormal behaviour. Developers assumed that the slipping was the reason for that. 

When taking a turn, first it has to calculate how much of an angle it has to turn. It is done by sensor readings and obstacle avoidance techniques. When making the turn, the robot has to keep calculating the angle it has already turned. Once the robot completes turning to the required angle, it goes ahead with the next tasks.

To turn the vehicle, the speed of one set of wheels is adjusted relative to the other. For example, if the right wheels move faster than the left wheels, the vehicle will turn to the left. To turn, the wheels on one side of the vehicle move faster or slower than the wheels on the other side. If the right wheels rotate faster than the left wheels, the vehicle turns to the left. If the left wheels rotate faster than the right wheels, the vehicle turns to the right.

![image](https://github.com/lahirub99/S5-Project/assets/91234872/e3b2e14d-4cb8-4a16-b0fe-177f3edd3327)

Basically what I have to do is to find a way to predict the abnormal behaviour of the wheel. It can happen due to two reasons:
Effect of slipping
Imperfectness of the robot’s rigid body
Wheels with different radiuses




