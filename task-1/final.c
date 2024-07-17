// #include <kipr/wombat.h>

void find_wall()
{
    while (!get_create_lbump() && !get_create_rbump())
    {
        create_drive_direct(200, 200);
    }

    if (get_create_lbump() && !get_create_rbump())
    {
        while (get_create_lbump() != get_create_rbump())
        {
            create_drive_direct(-70, 70);
        }
    }

    else
    {

        while (get_create_lbump() != get_create_rbump())
        {
            create_drive_direct(70, -70);
        }
    }

    create_drive_direct(-50, -50);
    msleep(500);

    create_drive_direct(0, 0);
}

void find_center()
{

    int distance;

    while (!get_create_lbump() && !get_create_rbump())
    {
        create_drive_direct(200, 200);
    }

    create_spin_CW(420);

    msleep(1000);

    set_create_distance(0);

    while (!get_create_lbump() && !get_create_rbump())
    {

        create_drive_direct(200, 200);
    }

    create_spin_CW(420);

    msleep(1000);

    distance = get_create_distance();

    set_create_distance(0);

    create_drive_direct(200, 200);

    while (get_create_distance() < distance / 2)
    {

        msleep(10);
    }

    create_spin_CW(165);

    msleep(1020);

    while (!get_create_lbump() && !get_create_rbump())
    {
        create_drive_direct(200, 200);
    }

    create_spin_CW(420);

    msleep(1000);

    set_create_distance(0);

    while (!get_create_lbump() && !get_create_rbump())
    {

        create_drive_direct(200, 200);
    }

    create_spin_CW(420);

    msleep(1000);

    distance = get_create_distance();
    printf("The distance: %d", distance);
    set_create_distance(0);

    create_drive_direct(200, 200);

    while (get_create_distance() < distance / 2)
    {

        msleep(10);
    }

    create_spin_CW(2000);

    msleep(1000);
}

int main()
{

    create_connect();

    find_wall();

    find_center();

    return 0;
}