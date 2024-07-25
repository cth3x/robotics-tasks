#include <kipr/wombat.h>

// Camera object colors
int RED = 0, GREEN = 1;

// Returns the number of red objects detected
int red_detected()
{
    camera_update();

    return get_object_count(RED);
}

// Returns the center of the red object
point2 red_center()
{
    camera_update();
    return get_object_center(RED, 0);
}

// Returns the center of the green object
point2 green_center()
{
    camera_update();
    return get_object_center(GREEN, 0);
}

// Returns the number of green objects detected
int green_detected()
{
    camera_update();

    return get_object_count(GREEN);
}

// Turn left
void turn_left()
{
    create_drive_direct(-50, 50);
}

// Turn right
void turn_right()
{
    create_drive_direct(50, -50);
}

// Move forward
void forward()
{
    create_drive_direct(150, 150);
}

int main()
{
    create_connect();
    // camera_load_config("default");
    camera_open();

    // Spin for one second
    create_drive_direct(50, -50);
    msleep(1000);

    while (!red_detected())
    {
    }

    // Variables
    int red_x = get_object_center(RED, 0).x;
    int left_window = 70;
    int right_window = 90;

    // Move forward, making adjustments until the red object is close
    while (get_object_area(RED, 0) < 12000) //! red == 79
    {
        if (red_x > left_window && red_x < right_window)
        {
            forward();
        }
        else if (red_x < 79)
        {
            turn_left();
        }

        else if (red_x > 83)
        {
            turn_right();
        }

        if (get_object_area(RED, 0) > 14000)
        {
            create_drive_direct(0, 0);
            break;
        }

        camera_update();
        red_x = get_object_center(RED, 0).x;
    }

    // Stop the robot
    create_drive_direct(0, 0);

    // Green center
    int green_x = get_object_center(GREEN, 0).x;
    while (get_object_area(GREEN, 0) < 14000) //! red == 79
    {
        if (green_x > left_window && green_x < right_window)
        {
            forward();
        }
        else if (green_x < 79)
        {
            turn_left();
        }

        else if (green_x > 83)
        {
            turn_right();
        }

        if (get_object_area(RED, 0) > 14000)
        {
            create_drive_direct(0, 0);
            break;
        }

        camera_update();
        green_x = get_object_center(GREEN, 0).x;
    }

    create_stop();

    return 0;
}
