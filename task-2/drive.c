// #include <kipr/wombat.h>

int main()
{
    create_connect();
    printf("Create is connected\n");

    int lcliff = 0;
    int rcliff = 0;

    int lfcliff = 0;
    int rfcliff = 0;

    lcliff = get_create_lcliff_amt();
    lfcliff = get_create_lfcliff_amt();
    rcliff = get_create_rcliff_amt();
    rfcliff = get_create_rfcliff_amt();

    while (1)
    {
        lfcliff = get_create_lfcliff_amt();
        rfcliff = get_create_rfcliff_amt();

        if (lfcliff < 2700 && rfcliff < 2700)
        {
            create_drive_direct(100, 100);
        }

        if (lfcliff > 2700 && rfcliff < 2700)
        {
            create_drive_direct(-60, 100);
        }

        else if (lfcliff < 2700 && rfcliff > 2700)
        {
            create_drive_direct(100, -60);
        }

        printf("%d, %d\n", lcliff, rcliff);

        // if (lfcliff < 2700 && rfcliff > 2700)
        // {
        //     create_drive_direct(80, 50);
        // }

        // else
        // {
        //     create_drive_direct(50, 80);
        // }
        msleep(500);
    }

    create_disconnect();

    return 0;
}