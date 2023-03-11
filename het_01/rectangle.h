#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>
#include <math.h>

typedef struct Rectangle
{
	double width;
	double height;
	double length;
} Rectangle;

void set_sides(Rectangle* rec, double width, double height, double length);
double calc_volume(const Rectangle* rec);
double calc_surface(const Rectangle* rec);
int is_square_side(const Rectangle* rec);
void checking_scanf(double num);

#endif