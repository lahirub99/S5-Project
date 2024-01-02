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
1. Effect of slipping
2. Imperfectness of the robot’s rigid body
3. Wheels with different radiuses

### Effect of slipping:
`The distance a tire has travelled = 2 x pi x radius x no_of_cycles`

When there is a slippery surface, a wheel tends to rotate more cycles without going the distance estimated by that number of cycles.


## Proposed Solution

The proposed solution is to develop an algorithm to make the robot go the right way regardless of the effects of the abnormal wheel.

The existing solution is to get the readings of one frame and compare the encoder readings of the erroneous wheel with the readings of the wheel parallel to that. Both of those wheels must be the same according to the skid steering technique. If the difference between those readings is more than 2%, it is considered an erroneous reading. In such an occurrence, reading with a lower value is considered as the real reading while the higher value is considered erroneous due to the slipping effect of a wheel.

That would be the starting point of this project. It is expected to code using C++ since it has to be compatible with the Arduino devices inside the robot. It can be tested using the provided comma-separated file containing sample readings. In that file, the columns in a line will be separated as:
1. Encoder reading of tire 1: The number of circles tire 1 has turned since the last reading 
2. Encoder reading of tire 2: The number of circles tire 2 has turned since the last reading 
3. Encoder reading of tire 3: The number of circles tire 3 has turned since the last reading 
4. Encoder reading of tire 4: The number of circles tire 4 has turned since the last reading 
5. Time spent since the last reading

The time between the readings Usually varies in the 4 ms - 150 ms range. It uses an interrupt mechanism to get the readings. In the reading phase, it has a 10 ms timeout. Therefore, in that phase readings will come in time durations maximum of 10 ms. That reading process loops 10 times. Then the main loop goes through the other parts of execution, while encoders keep counting the number of cycles. When the main loop comes back to read the encoder values again, more time has passed than the time between previous readings. Usually it takes around 50 ms - 150 ms to get an value again when other part of the code starts executing.

```
Main loop <<<
  Initialization and other processes
  Collect encoder readings and process 
    -
    -
    - X 10
  Processes after that
>>>
```

The number of pulses reading provided by the encoder is directly proportional to the velocity of each wheel. Assumed that radiuses of all wheels are equal. Therefore we can use ‘number of cycles/ time’ for our calculations, without calculating the velocity of each tire separately. That will be an additional workload for the microcontroller restricting faster response because of the resource constraints.

