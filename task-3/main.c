#include <kipr/wombat.h>
#include <time.h>

int main()
{

    create_connect();
    enable_servos();
    set_servo_position(0, 150);
    set_servo_position(1, 688);
    msleep(1000);
    // return 0;

    int value_r;
    int value_l;
    int value_lf;
    int value_rf;
    int distance_from_right;
    int distance_from_left;

    create_drive_direct(300, 300);

    int mask_l = (1);
    int mask_r = (1);

    while (1)
    {

        value_rf = get_create_rfcliff_amt();
        value_lf = get_create_lfcliff_amt();
        value_r = get_create_rcliff_amt();
        value_l = get_create_lcliff_amt();

        distance_from_right = analog(0);
        distance_from_left = analog(1);

        // Finish line
        if (value_l > 2600 && value_r > 2600)
        {
            create_drive_direct(0, 0);
        }

        // Drive normally
        else if (value_lf < 2600 && value_rf < 2600)
        {
            create_drive_direct(175, 175);
        }

        // Steer right
        else if (value_lf > 2600 && value_rf < 2600)
        {
            create_drive_direct(-50, 600);
        }

        // Steer left
        else if (value_lf < 2600 && value_rf > 2600)
        {
            create_drive_direct(600, -50);
        }

        // Bucket is close to left side
        if (distance_from_right > 2100 && mask_r)
        {
            create_drive_direct(0, 0);
            msleep(700);

            create_drive_direct(100, 100);
            msleep(1200);

            create_drive_direct(0, 0);
            set_servo_position(0, 1000);
            msleep(2500);

            set_servo_position(0, 150);
            msleep(200);

            mask_r = 0;
        }

        // Bucket is close to right side
        else if (distance_from_left > 1500 && mask_l)
        {
            create_drive_direct(0, 0);
            msleep(700);

            create_drive_direct(100, 100);
            msleep(1300);
            create_drive_direct(0, 0);
            set_servo_position(1, 1200);
            msleep(2500);

            set_servo_position(1, 688);
            msleep(200);

            mask_l = 0;
        }
    }

    create_stop();

    return 0;
}
