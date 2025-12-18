// SPDX-License-Identifier: GPL
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "fast_tesselation.h"
#include "defs.h"

static sites *completeSites;
static s_chunk *sChunkedSites; // special chunks, formed by 3x3 chunks

int randMax(int max)
{
	return rand() % (max + 1);
}

void initialiseSites(void)
{
	// initilise the random function
	srand(time(NULL));

	static sites mutableInternal[SITEAMOUNT];
	static s_chunk chunkedSitesTmp[CHUNK_AMOUNT];
	int colorChoice;
	int tX, tY; // x and y of the generated point
	int pX, pY; // x and y where it gets placed in the array
	char tR, tG, tB; // RGB coordinates of point

	for (int i = 0; i < CHUNK_AMOUNT; i++) // clear any garbage pointers present
		chunkedSitesTmp[i].siteArr = NULL;

	for (int i = 0; i < SITEAMOUNT; i++) {
		tX = randMax(WIDTH);
		tY = randMax(HEIGHT);

		colorChoice = randMax(COLORAMOUNT);
		tR = COLORS[colorChoice][0];
		tG = COLORS[colorChoice][1];
		tB = COLORS[colorChoice][2];

		mutableInternal[i].x = tX;
		mutableInternal[i].y = tY;
		mutableInternal[i].r = tR;
		mutableInternal[i].g = tG;
		mutableInternal[i].b = tB;
		// printf("[[%d, %d], [%d, %d, %d]],\n", mutableInternal[i].x, mutableInternal[i].y, (int) mutableInternal[i].r, (int) mutableInternal[i].g, (int) mutableInternal[i].b);

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; j++) {
				// something here
				// some more here
				pX = ;
				pY = ;
				chunkedSitesTmp[pY * pX + pX].siteArr = NULL;
			}
		}
	}
	completeSites = mutableInternal;

	// now once the complete sites have been generated,
	// we can divide these into chunks for faster lookup
	// 1 dimensional of pointers to items in mutableInternal for faster lookup

	sChunkedSites = chunkedSitesTmp;
}

void freeSites(void)
{
	free(completeSites);
	free(sChunkedSites);
}

double distance(int x1, int x2, int y1, int y2, float p)
{
	double dx = x1 - x2;
	double dy = y1 - y2;

	return pow(fabs(dx), p) + pow(fabs(dy), p);
}

int closest(int x, int y, float p)
{
	sites *siteOpts = completeSites;
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
	sites *Sites = completeSites;
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

	freeSites();
	free(imageRam.bytemap);
}
