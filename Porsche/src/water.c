#include "water.h"

float waterPoints[45][45][3];
int wiggleCount = 0;
float hold;

void init_water(const Water *water)
{
    water->delta = 0.0f;
}

void update_water(const Water *water, double elapsed_time)
{

}

void render_water(const Water *water)
{
    int x, y;
	float float_x, float_y, float_xb, float_yb;

    /*int x, y, delta;
	for (x = 0; x < 45; x++)
	{
		for (y = 0; y < 45; y++)
		{
			waterPoints[x][y][0] = (x / 5.0f) - 4.5f;
			waterPoints[x][y][1] = (y / 5.0f) - 4.5f;
			waterPoints[x][y][2] = sin((((x / 5.0f) * 40.0f) + delta / 360.0f) * 3.141592654 * 2.0f);
		}
	}*/

	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glDisable(GL_LIGHTING);
    glTranslatef(0.0f, 0.0f, -0.5f);
	glScalef(50.0f, 50.0f, 0.5f);

	glBegin(GL_QUADS);
	{
		for (x = 0; x < 44; x++)
		{
			for (y = 0; y < 44; y++)
			{
				float_x = (x) / 44.0f;
				float_y = (y) / 44.0f;
				float_xb = (x + 1) / 44.0f;
				float_yb = (y + 1) / 44.0f;

				glTexCoord2f(float_x, float_y);
				glVertex3f(waterPoints[x][y][0], waterPoints[x][y][1], waterPoints[x][y][2]);

				glTexCoord2f(float_x, float_yb);
				glVertex3f(waterPoints[x][y + 1][0], waterPoints[x][y + 1][1], waterPoints[x][y + 1][2]);

				glTexCoord2f(float_xb, float_yb);
				glVertex3f(waterPoints[x + 1][y + 1][0], waterPoints[x + 1][y + 1][1], waterPoints[x + 1][y + 1][2]);

				glTexCoord2f(float_xb, float_y);
				glVertex3f(waterPoints[x + 1][y][0], waterPoints[x + 1][y][1], waterPoints[x + 1][y][2]);
			}
		}
	}
	glEnd();

	if (wiggleCount == 10)
	{
		for (y = 0; y < 45; y++)
		{
			hold = waterPoints[0][y][2];
			for (x = 0; x < 44; x++)
			{
				waterPoints[x][y][2] = waterPoints[x + 1][y][2];
			}
			waterPoints[44][y][2] = hold;
		}
		wiggleCount = 0;
	}
	wiggleCount++;

	glEnable(GL_LIGHTING);
	glPopMatrix();
}