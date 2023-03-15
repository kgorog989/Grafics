#ifndef CUBOID_H
#define CUBOID_H

typedef struct Cuboid
{
    double x;
    double y;
    double z;
} Cuboid;

void set_cuboid_data(Cuboid *cuboid, double x, double y, double z);

double calc_cuboid_surface(const Cuboid *cuboid);

double calc_cuboid_volume(const Cuboid *cuboid);

int cuboid_has_square(const Cuboid *cuboid);

#endif