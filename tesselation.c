#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct point {
	int pos[2];
	short rgb[3];
};

struct opts {
	int width;
	int height;
	int points;
	int interpols;
	struct point genpoints;
};

void selectcolor(short int *r, short int *g, short int *b)
{
	int colors[][3] = {
		{88, 91, 112},
		{69, 71, 90},
		{49, 50, 68},
		{30, 30, 46},
		{24, 24, 37},
		{17, 17, 27}
	};
	int chosen = random() % 6;
	*r = colors[chosen][0];
	*g = colors[chosen][1];
	*b = colors[chosen][2];
}

float getdistance2(int a[2], int b[2], float exp)
{
	float dx, dy;

	dx = abs(a[0] - b[0]);
	dy = abs(a[1] - b[1]);
	return pow(dx, exp) + pow(dy, exp);
}

void *makeImgs(void *args);

int main(int argc, char *argv[])
{
	int width = 1000;
	int height = 1000;
	int points = 200;
	int interpol = 1; // amount of images for interpolation between manhattan and euclidian

	if (argc > 1)
		sscanf(argv[1], "%d", &points);
	if (argc > 2)
		sscanf(argv[2], "%d", &interpol);
	if (argc > 3)
		sscanf(argv[3], "%d", &width);
	if (argc > 4)
		sscanf(argv[4], "%d", &height);

	printf("%d, %d, %d, %d\n", width, height, points, interpol);

	// srandom(782347234);
	srandom(clock());
	int i, j, k;

	struct point genpoints[points]; // generated points

	for (i = 0; i < points; i++) {
		/*
		 * genpoints[i].rgb[0] = random() % 256; //
		 * genpoints[i].rgb[1] = random() % 256; // get RGB values for point
		 * genpoints[i].rgb[2] = random() % 256; //
		 */
		selectcolor(&genpoints[i].rgb[0], &genpoints[i].rgb[1], &genpoints[i].rgb[2]);
		genpoints[i].pos[0] = random() % (width + 1);  // get location for point
		genpoints[i].pos[1] = random() % (height + 1); //
		//printf("%d, %d, %d at %d %d - point #%d.\n", genpoints[i].rgb[0], genpoints[i].rgb[1], genpoints[i].rgb[2], genpoints[i].pos[0], genpoints[i].pos[1], i);
	}
	struct opts Opts;

	Opts.width = width;
	Opts.height = height;
	Opts.points = points;
	Opts.interpols = interpols;
	Opts.genpoints = genpoints;
	pthread_t thread1;
}

void *makeImgs(void *args)
{
	float distance;
	float distancemin;
	int closepoint;
	int pos[2];

	int l;
	float exp = 1.0;
	char filename[50];

	for (l = 0; l < interpol; l++) {
		exp = 1 + ((l+1) / interpol);
		sprintf(filename, "img_%02d.ppm", l);
		FILE *f = fopen(filename, "w+");

		fprintf(f, "P3\n# img.ppm\n%d %d\n255\n", width, height);
		for (i = 0; i < width; i++) {
			for (j = 0; j < height; j++) {
				pos[0] = i;
				pos[1] = j;
				distancemin = 1e200;
				closepoint = 0;
				for (k = 0; k < points; k++) {
					distance = getdistance2(pos, genpoints[k].pos, exp);
					if (distance < distancemin) {
						distancemin = distance;
						closepoint = k;
					}
				}
				fprintf(f, "%d %d %d ", genpoints[closepoint].rgb[0], genpoints[closepoint].rgb[1], genpoints[closepoint].rgb[2]);
				//printf("closest to %d\n", closepoint);
			}
			fprintf(f, "\n");
		}
		fclose(f);
	}
	return 0;
}
