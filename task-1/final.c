#include <kipr/wombat.h>

// Function to find the wall
void find_wall()
{
    while (!get_create_lbump() && !get_create_rbump()) // Not touching the bumpers
    {
        create_drive_direct(200, 200); // Move forward
    }

    if (get_create_lbump() && !get_create_rbump()) // When left bumper is activated only
    {
        while (get_create_lbump() != get_create_rbump()) // Turn until both are activated
        {
            create_drive_direct(-70, 70);
        }
    }

    else // For when the right bumper is activated only
    {

        while (get_create_lbump() != get_create_rbump()) // Turn until both are activated
        {
            create_drive_direct(70, -70);
        }
    }

    create_drive_direct(-50, -50); // Move backward for half a second
    msleep(500);

    create_drive_direct(0, 0); // Stop the robot
}

// Function to find the center
void find_center()
{

    int distance; // Variable to store the distance

    while (!get_create_lbump() && !get_create_rbump()) // Not touching either bumpers
    {
        create_drive_direct(200, 200); // Move forward
    }

    create_spin_CW(420); // Spin clockwise

    msleep(1000); // Wait for 1 second

    set_create_distance(0); // Set the distance to 0

    while (!get_create_lbump() && !get_create_rbump()) // Not touching either bumpers
    {

        create_drive_direct(200, 200); // Move forward
    }

    create_spin_CW(420); // Spin clockwise

    msleep(1000); // Wait for 1 second

    distance = get_create_distance(); // Get the distance

    set_create_distance(0); // Set the distance to 0

    create_drive_direct(200, 200); // Move forward

    while (get_create_distance() < distance / 2) // Until the distance is half of the total distance
    {

        msleep(10); // Wait for 10 milliseconds
    }

    create_spin_CW(165); // Spin clockwise

    msleep(1020); // Wait for 1 second and 20 milliseconds

    while (!get_create_lbump() && !get_create_rbump()) // Not touching either
    {
        create_drive_direct(200, 200); // Move forward
    }

    create_spin_CW(420); // Spin clockwise

    msleep(1000); // Wait for 1 second

    set_create_distance(0); // Set the distance to 0

    while (!get_create_lbump() && !get_create_rbump())
    {

        create_drive_direct(200, 200); // Move forward
    }

    create_spin_CW(420); // Spin clockwise

    msleep(1000);

    distance = get_create_distance(); // Get the distance

    set_create_distance(0); // Set the distance to 0

    create_drive_direct(200, 200); // Move forward

    while (get_create_distance() < distance / 2) // Until the distance is half of the total distance
    {

        msleep(10);
    }

    create_spin_CW(2000); // Spin clockwise

    msleep(1000);
}

int main()
{

    create_connect();

    find_wall();

    find_center();

    return 0;
}