#include "cuboid.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    Cuboid cuboid;
    double surface, volume;
    int has_square;

    set_cuboid_data(&cuboid, 15, 10, 20);
    surface = calc_cuboid_surface(&cuboid);
    volume = calc_cuboid_volume(&cuboid);

    printf("Cuboid surface: %lf, \nCuboid volume: %lf.\n", surface, volume);

    has_square = cuboid_has_square(&cuboid);

    if (has_square == 1)
    {
        printf("Cuboid has squares. \n");
    }
    else
    {
        printf("Cuboid does not have squares. \n");
    }

    return 0;
}