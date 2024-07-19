// #include <kipr/wombat.h>

int main()
{
    create_connect();

    int lcliff;
    int rcliff;

    int lfcliff;
    int rfcliff;

    while (1)
    {
        lcliff = get_create_lcliff_amt();
        lfcliff = get_create_lfcliff_amt();
        rcliff = get_create_rcliff_amt();
        rfcliff = get_create_rfcliff_amt();

        if (lcliff > 2700 && rcliff > 2700)
        {
            create_drive_direct(0, 0);
        }
        else if (lfcliff < 2700 && rfcliff < 2700)
        {
            create_drive_direct(250, 250);
        }
        else if (lfcliff > 2700 && rfcliff < 2700)
        {
            create_drive_direct(0, 150);
            msleep(100);
        }
        else if (lfcliff < 2700 && rfcliff > 2700)
        {
            create_drive_direct(150, 0);
            msleep(100);
        }
    }

    create_stop();

    create_disconnect();

    return 0;
}