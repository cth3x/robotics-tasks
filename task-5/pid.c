#include <kipr/wombat.h>

int RED = 0, GREEN = 1, target = 80; // Camera object colors

double Kp = 1, Ki = 0, Kd = 0; // PID constants

double previous_error = 0, integral = 0; // PID variables

int red_detected() // Returns the number of red objects detected (1 if the calibration is correct)
{
    camera_update(); // Update the camera

    return get_object_count(RED);
}

point2 red_center() // Returns the center of the red object (coordinates)
{
    camera_update(); // Update the camera

    return get_object_center(RED, 0);
}

point2 green_center() // Returns the center of the green object (coordinates)
{
    camera_update();
    return get_object_center(GREEN, 0);
}

int green_detected() // Returns the number of green objects detected (1 if the calibration is correct)
{
    camera_update();

    return get_object_count(GREEN);
}

void pid_control(int error)
{
    // PID control
    integral += error;
    double derivative = error - previous_error;
    double output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;

    int base_speed = 250; // Base speed set to 250

    int left_speed = base_speed - output;  // Left speed based on the PID output
    int right_speed = base_speed + output; // Right speed based on the PID output

    create_drive_direct(left_speed, right_speed); // Drive the robot
}

int main()
{
    create_connect(); // Connect to the robot

    camera_open(); // Open the camera

    create_drive_direct(50, -50); // Turn left for 1 second (scanning for the red object)
    msleep(1000);

    while (!red_detected()) // While the red object is not detected
    {
        camera_update(); // Update the camera
    }

    int red_x = get_object_center(RED, 0).x; // Get the x-coordinate of the red object

    while (get_object_area(RED, 0) < 10000) // While the red object is not close enough
    {
        int error = target - red_x; // Calculate the error
        pid_control(error);         // Control the robot based on the error

        if (get_object_area(RED, 0) > 11000) // When close enough, stop the robot
        {
            create_drive_direct(0, 0);
            break;
        }

        camera_update();                     // Update the camera
        red_x = get_object_center(RED, 0).x; // Get the x-coordinate of the red object
    }

    create_drive_direct(0, 0);
    msleep(1000);

    previous_error = 0; // Reset the previous error
    integral = 0;       // Reset the integral

    int green_x = get_object_center(GREEN, 0).x; // Get the x-coordinate of the green object
    while (get_object_area(GREEN, 0) < 10000)    // While the green object is not close enough
    {
        int error = target - green_x; // Calculate the error
        pid_control(error);           // Control the robot based on the error

        if (get_object_area(GREEN, 0) > 11000) // When close enough, stop the robot
        {
            create_drive_direct(0, 0); // Stop the robot
            break;
        }

        camera_update();                         // Update the camera
        green_x = get_object_center(GREEN, 0).x; // Get the x-coordinate of the green object
    }

    create_stop();

    return 0;
}
