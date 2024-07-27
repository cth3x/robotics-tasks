#include <kipr/wombat.h>

int RED = 0, GREEN = 1, ORANGE = 2, target = 80;

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

int orange_detected()
{
    camera_update();

    return get_object_count(ORANGE);
}

point2 orange_center()
{
    camera_update();
    return get_object_center(ORANGE, 0);
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

void raise()
{
    set_servo_position(0, 1000);
    msleep(500);
}

void lower()
{
    set_servo_position(0, 0);
    msleep(500);
}

void open()
{
    set_servo_position(1, 0);
    msleep(500);
}

void close()
{
    set_servo_position(1, 600);
    msleep(500);
}

int main()
{
    create_connect();
    enable_servos();
    camera_open();

    raise();
    open();

    create_drive_direct(50, -50);
    msleep(1000);

    while (!orange_detected())
    {
        camera_update();
    }

    int orange_x = get_object_center(ORANGE, 0).x;

    while (get_object_area(ORANGE, 0) < 10000)
    {
        int error = target - orange_x;
        pid_control(error);

        if (get_object_area(ORANGE, 0) > 11000)
        {
            create_drive_direct(0, 0);
            lower();
            close();
            break;
        }

        camera_update();
        orange_x = get_object_center(ORANGE, 0).x;
    }

    raise();

    while (!green_detected())
    {
        camera_update();
    }

    green_x = get_object_center(GREEN, 0).x;

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

    lower();
    open();

    create_stop();

    return 0;
}