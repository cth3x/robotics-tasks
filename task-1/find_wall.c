void find_wall()
{
    create_connect();
    while (!get_create_lbump() && !get_create_rbump())
    {
        create_drive_direct(200, 200);
    }

    if (get_create_lbump() && !get_create_rbump())
    {
        while (get_create_lbump() != get_create_rbump())
        {
            create_drive_direct(-100, 100);
        }
    }

    else
    {

        while (get_create_lbump() != get_create_rbump())
        {
            create_drive_direct(100, -100);
        }
    }
}

int main()
{

    find_wall();

    return 0;
}