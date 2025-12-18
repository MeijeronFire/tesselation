// SPDX-License-Identifier: GPL
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "fast_tesselation.h"
#include "defs.h"

static pthread_once_t once = PTHREAD_ONCE_INIT;
static sites *externalSites;

int randMax(int max)
{
	return rand() % (max + 1);
}

void initialiseSites(void)
{
	// initilise the random function
	srand(time(NULL));

	static sites mutableInternal[SITEAMOUNT];
	int colorChoice;

	for (int i = 0; i < SITEAMOUNT; i++) {
		colorChoice = randMax(COLORAMOUNT);
		mutableInternal[i].x = randMax(WIDTH);
		mutableInternal[i].y = randMax(HEIGHT);
		mutableInternal[i].r = COLORS[colorChoice][0];
		mutableInternal[i].g = COLORS[colorChoice][1];
		mutableInternal[i].b = COLORS[colorChoice][2];
	}
	externalSites = mutableInternal;
}

void freeSites(void)
{
	free(externalSites);
}

double distance(int x1, int x2, int y1, int y2, float p)
{
	double dx = x1 - x2;
	double dy = y1 - y2;

	return pow(fabs(dx), p) + pow(fabs(dy), p);
}

int closest(int x, int y, float p)
{
	sites *siteOpts = externalSites;
	int d;
	int closestIndex = 0;

	double minD = distance(x, siteOpts[0].x, y, siteOpts[0].y, p);

	for (int i = 1; i < SITEAMOUNT; i++) {
		d = distance(x, siteOpts[i].x, y, siteOpts[i].y, p);
		if (d < minD) {
			minD = d;
			closestIndex = i;
		}
	}
	return closestIndex;
}

// alr for this function we just gotta go and generate one tesselation
void worker(void *arg)
{
	struct argument *val = arg;
	image imageRam;
	sites *Sites = externalSites;
	int closestSite;

	// Sites = getSites();
	imageRam.bytemap = malloc(WIDTH*HEIGHT*3*sizeof(unsigned char));

	if (!imageRam.bytemap)
		perror("malloc failed");

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			closestSite = closest(i, j, (*val).power);
			imageRam.bytemap[i*WIDTH*3 + j*3 + 0] = Sites[closestSite].r;
			imageRam.bytemap[i*WIDTH*3 + j*3 + 1] = Sites[closestSite].g;
			imageRam.bytemap[i*WIDTH*3 + j*3 + 2] = Sites[closestSite].b;
		}
	}
	char fileName[20];

	sprintf(fileName, "out/test%d.ppm", (*val).name);

	FILE *f = fopen(fileName, "wb");

	if (!f)
		printf("ehh file open error idk what to do\n");

	fprintf(f, "P6\n%u %u\n255\n", WIDTH, HEIGHT);

	if (fwrite(imageRam.bytemap, sizeof(unsigned char), WIDTH * HEIGHT * 3, f) != (unsigned long) WIDTH * HEIGHT * 3) {
		fclose(f);
		printf("uhh file write error idk\n");
	} else {
		fclose(f);
	}

	// freeSites();
	free(imageRam.bytemap);
}
