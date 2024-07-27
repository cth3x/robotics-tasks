#include <kipr/wombat.h>

int RED = 0, GREEN = 1, target = 80;

double Kp = 1, Ki = 0, Kd = 0;

double previous_error = 0;
double integral = 0;

int red_detected()
{
    camera_update();

    return get_object_count(RED);
}

point2 red_center()
{
    camera_update();
    return get_object_center(RED, 0);
}

point2 green_center()
{
    camera_update();
    return get_object_center(GREEN, 0);
}

int green_detected()
{
    camera_update();

    return get_object_count(GREEN);
}

void pid_control(int error)
{
    integral += error;
    double derivative = error - previous_error;
    double output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;

    int base_speed = 250;

    int left_speed = base_speed - output;
    int right_speed = base_speed + output;

    create_drive_direct(left_speed, right_speed);
}

int main()
{
    create_connect();

    camera_open();

    create_drive_direct(50, -50);
    msleep(1000);

    while (!red_detected())
    {
        camera_update();
    }

    int red_x = get_object_center(RED, 0).x;

    while (get_object_area(RED, 0) < 10000)
    {
        int error = target - red_x;
        pid_control(error);

        if (get_object_area(RED, 0) > 11000)
        {
            create_drive_direct(0, 0);
            break;
        }

        camera_update();
        red_x = get_object_center(RED, 0).x;
    }

    create_drive_direct(0, 0);
    msleep(1000);

    previous_error = 0;
    integral = 0;

    int green_x = get_object_center(GREEN, 0).x;
    while (get_object_area(GREEN, 0) < 10000)
    {
        int error = target - green_x;
        pid_control(error);

        if (get_object_area(GREEN, 0) > 11000)
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
