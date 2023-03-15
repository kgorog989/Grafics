#include "cuboid.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void set_cuboid_data(Cuboid *cuboid, double x, double y, double z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        printf("Error. Cuboid has at least one side that is 0 or negative. ");
        exit(1);
    }

    cuboid->x = x;
    cuboid->y = y;
    cuboid->z = z;
}

double calc_cuboid_surface(const Cuboid *cuboid)
{
    double surface = 2 * (cuboid->x * cuboid->y + cuboid->x * cuboid->z + cuboid->y * cuboid->z);
    return surface;
}

double calc_cuboid_volume(const Cuboid *cuboid)
{
    double volume = cuboid->x * cuboid->y * cuboid->z;
    return volume;
}

int cuboid_has_square(const Cuboid *cuboid)
{
    if (cuboid->x == cuboid->y || cuboid->x == cuboid->z || cuboid->y == cuboid->z)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
