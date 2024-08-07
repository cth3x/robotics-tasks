#include <kipr/wombat.h>

int main()
{
    create_connect(); // Connect to the robot

    int lcliff; // Left cliff sensor
    int rcliff; // Right cliff sensor

    int lfcliff; // Other left sensor
    int rfcliff; // Other right sensor

    while (1) // Infinite loop for driving
    {
        lcliff = get_create_lcliff_amt();   // Get the left cliff sensor value
        lfcliff = get_create_lfcliff_amt(); // Get the left front sensor value
        rcliff = get_create_rcliff_amt();   // Get the right cliff sensor value
        rfcliff = get_create_rfcliff_amt(); // Get the right front sensor value

        if (lcliff > 2700 && rcliff > 2700) // If both back sensors are on the tape
        {
            create_drive_direct(0, 0); // Stop the robot
        }
        else if (lfcliff < 2700 && rfcliff < 2700) // If both front sensors are on the tape
        {
            create_drive_direct(250, 250); // Continue to move forward
        }
        else if (lfcliff > 2700 && rfcliff < 2700) // If the right is off the tape, then turn right
        {
            create_drive_direct(0, 150);

            msleep(100);
        }
        else if (lfcliff < 2700 && rfcliff > 2700) // If the left is off the tape, then turn left
        {
            create_drive_direct(150, 0);
            msleep(100);
        }
    }

    create_stop(); // Stop the robot

    create_disconnect(); // Disconnect from the robot

    return 0;
}