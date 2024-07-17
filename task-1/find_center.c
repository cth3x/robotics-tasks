void find_center()
{

    int distance;
    create_connect();
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

    msleep(1000);

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
}

int main()
{
    find_wall();

    find_center();

    return 0;
}