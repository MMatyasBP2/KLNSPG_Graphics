#include "cuboid.c"

int main(int argc, char* argv[])
{
	Cuboid cub;

	float length = read_sides("Give me the length: ");
    float width = read_sides("Give me the width: ");
    float height = read_sides("Give me the height: ");

	set_size(&cub, length, width, height);
    float volume = calc_volume(cub);
    float surface = calc_surface(cub);

    printf("Rectangle %s square side.", has_square_face(cub) ? "has" : "has not");
	
	return 0;
}
