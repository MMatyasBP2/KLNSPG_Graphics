#include "rectangle.c"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Rectangle rec;
	
	set_sides(&rec, 5, 10, 8);
    double volume = calc_volume(&rec);
    double surface = calc_surface(&rec);
    printf("Rectangle %s square side.", is_square_side(&rec) == 1 ? "has" : "has not");
	
	return 0;
}
