# Task 1: Wall Detection and Centering
This task demonstrates a method to locate a wall using the robot’s bump sensors and then navigate to the center of an area. The robot drives forward until it touches a wall, adjusts its position based on the bumper input, and reverses slightly before finding the center of the room.

## Main Features:
Wall Detection: The robot drives forward until the bump sensors are triggered.
Center Finding: After locating the wall, the robot calculates the center based on distance traveled and bumper inputs.
Spin Movement: The robot uses spins to refine its position during the center-finding process.

 # Task 2: Cliff Sensor Navigation
This task uses the robot’s cliff sensors to detect the edges of a surface (we used white tape to replicate this) and adjust movement accordingly. The robot followed a piece of white tape on the ground, and it could not lose track of the tape.

## Main Features:
Cliff Detection: The robot uses front and back cliff sensors to detect the presence of edges.
Directional Control: Depending on which sensor detects the tape, the robot turns to avoid going off-track.

# Task 3 & 4: Servo and Cliff Sensor Integration
This task integrates the use of servos and cliff sensors, building off of Task 2. It still followed the white tape, but buckets of different colors were placed around the "track" of white tape. When it recognized the buckets, sesnors were 
configured to dump ping-pong balls into the bucket.

## Main Features:
Line Following: The robot follows a line using cliff sensors.
Servo Control: Based on sensor readings (e.g., proximity), the robot activates its servos to open a gate that allowed the ping-pong balls to roll down an arm.

# Task 5: Object Tracking Using Camera (Red and Green Objects)
This task implements object tracking with the robot’s camera, specifically detecting red and green objects. The robot adjusts its movement based on the location and size of these objects in its camera view.

## Main Features:
Red Object Detection: The robot tracks and moves towards a red object until it is close enough.
Green Object Detection: After stopping near the red object, the robot switches to track the green object.
PID Control: The robot uses a basic PID controller to ensure smooth tracking of the objects.


