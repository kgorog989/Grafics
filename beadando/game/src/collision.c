#include "collision.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

void calculate_bounding_box(BoundingBox *box, const char *model_file, vec3 position, float size)
{
    FILE *file = fopen(model_file, "r");
    if (file == NULL)
    {
        printf("Failed to open OBJ file.\n");
        exit(1);
    }

    // Count the number of vertices of the model
    int num_of_vertices = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strncmp(line, "v ", 2) == 0)
        {
            num_of_vertices++;
        }
    }

    // Storing vertices in an array
    vec3 *vertices = malloc(num_of_vertices * sizeof(vec3));

    fseek(file, 0, SEEK_SET);

    int vertex_index = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strncmp(line, "v ", 2) == 0)
        {
            sscanf(line, "v %f %f %f", &vertices[vertex_index].x, &vertices[vertex_index].y, &vertices[vertex_index].z);
            vertex_index++;
        }
    }

    fclose(file);

    // Scale the model for the appropiate size
    for (int i = 0; i < num_of_vertices; i++)
    {
        vertices[i].x *= size;
        vertices[i].y *= size;
        vertices[i].z *= size;
    }

    // Calculate the bounding box
    box->min.x = FLT_MAX;
    box->min.y = FLT_MAX;
    box->min.z = FLT_MAX;

    box->max.x = -FLT_MAX;
    box->max.y = -FLT_MAX;
    box->max.z = -FLT_MAX;

    for (int i = 0; i < num_of_vertices; i++)
    {
        vec3 *vertex = &vertices[i];

        if (vertex->x < box->min.x)
            box->min.x = vertex->x;
        if (vertex->y < box->min.y)
            box->min.y = vertex->y;
        if (vertex->z < box->min.z)
            box->min.z = vertex->z;

        if (vertex->x > box->max.x)
            box->max.x = vertex->x;
        if (vertex->y > box->max.y)
            box->max.y = vertex->y;
        if (vertex->z > box->max.z)
            box->max.z = vertex->z;
    }

    box->dimensions.x = box->max.x - box->min.x;
    box->dimensions.y = box->max.y - box->min.y;
    box->dimensions.z = box->max.z - box->min.z;

    // Updating box boundaries with the position of the model
    box->min.x += position.x;
    box->min.y += position.y;
    box->min.z += position.z;

    box->max.x += position.x;
    box->max.y += position.y;
    box->max.z += position.z;

    //printf("Minimum: (%f, %f, %f)\n", box->min.x, box->min.y, box->min.z);
    //printf("Maximum: (%f, %f, %f)\n", box->max.x, box->max.y, box->max.z);
    //printf("Dimensions: (%f, %f, %f)\n", box->dimensions.x, box->dimensions.y, box->dimensions.z);

    free(vertices);
}

int check_collision(BoundingBox *box1, BoundingBox *box2)
{
    if (box1->max.x < box2->min.x || box1->min.x > box2->max.x)
        return 0;

    if (box1->max.y < box2->min.y || box1->min.y > box2->max.y)
        return 0;

    if (box1->max.z < box2->min.z || box1->min.z > box2->max.z)
        return 0;

    return 1;
}

void handle_collision(BoundingBox *box1, BoundingBox *box2, vec3 *position)
{

    // Checking overlaps from both directions
    vec3 overlap1, overlap2;
    overlap1.x = box1->max.x - box2->min.x;
    overlap1.y = box1->max.y - box2->min.y;
    overlap1.z = box1->max.z - box2->min.z;

    overlap2.x = box2->max.x - box1->min.x;
    overlap2.y = box2->max.y - box1->min.y;
    overlap2.z = box2->max.z - box1->min.z;

    float smallest_overlap1 = overlap1.x;
    float smallest_overlap2 = overlap2.x;

    if (overlap1.y < smallest_overlap1)
    {
        smallest_overlap1 = overlap1.y;
    }

    if (overlap2.y < smallest_overlap2)
    {
        smallest_overlap2 = overlap2.y;
    }

    float separation_distance = smallest_overlap2;

    if (smallest_overlap1 < smallest_overlap2)
    {
        separation_distance = smallest_overlap1;

        if (overlap1.x > overlap1.y)
        {
            box1->max.x -= separation_distance;
            box1->min.x -= separation_distance;
            position->x -= separation_distance;
        }
        if (overlap1.y > overlap1.x)
        {
            box1->max.y -= separation_distance;
            box1->min.y -= separation_distance;
            position->y -= separation_distance;
        }
    }
    else
    {
        if (overlap2.x > overlap2.y)
        {
            box1->max.x += separation_distance;
            box1->min.x += separation_distance;
            position->x += separation_distance;
        }
        if (overlap2.y > overlap2.x)
        {
            box1->max.y += separation_distance;
            box1->min.y += separation_distance;
            position->y += separation_distance;
        }
    }

}
