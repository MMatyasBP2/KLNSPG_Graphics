#include "rectangle.h"

void set_sides(Rectangle* rec, double width, double height, double length)
{
	if (checking_scanf(width))
		rec->width = width;
	
	if (checking_scanf(height))
		rec->height = height;
	
	if (checking_scanf(length))
		rec->length = length;

	if (length > 0.0)
    {
		rec->length = length;
	}
    else
    {
		rec->length = NAN;
	}
}

double calc_volume(const Rectangle* rec)
{
	return rec->length * rec->width * rec->height;
}

double calc_surface(const Rectangle* rec)
{
	return 2 * (rec->length * rec->width + rec->length * rec->height + rec->width * rec->height);
}

int is_square_side(const Rectangle* rec)
{
	int slap1, slap2, slap3;

   	slap1 = rec->length;
   	slap2 = rec->width;
   	slap3 = rec->height;

   	if (slap1 == slap2)
      	return slap1 <= slap3;
	else if (slap1 == slap3)
      	return slap1 <= slap2;
	else if (slap2 == slap3)
      	return slap2 <= slap1;
	else
      	return 0;
}

bool checking_scanf(double num)
{
	bool ok = true;
    do
    {
        printf("Give me a number: ");
        if (scanf("%lf", num) != 1)
        {
            printf("Bad input format!\n");
            ok = false;
            while (getchar() != '\n');
        }
    } while (!ok);

	return ok;
}