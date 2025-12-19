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

// grows the 'site array' in 's_chunk structs'
// at given pointer by one and adds argument to it
void append(s_chunk *workingChunk, sites *item)
{
	size_t arrSizeOld = (*workingChunk).sitesHeld;

	// if (arrSizeOld > 0) {
	// 	printf("duly noted.\n");
	// }

	// reallocate the array to the size of itself
	(*workingChunk).siteArr = realloc((*workingChunk).siteArr, (arrSizeOld + 1) * sizeof(item));
	if ((*workingChunk).siteArr == NULL) {
		printf("Well, fuck. The adding of one element to the array complains for some reason");
		printf("diagnose maybe idk\n");
		exit(1);
	}

	// now also increment the arrSize
	(*workingChunk).sitesHeld = arrSizeOld + 1;
	// since it is 0 indexed, using the old size as index yields the last element
	(*workingChunk).siteArr[arrSizeOld] = item;
	// printf("%p\n", (*workingChunk).siteArr[arrSizeOld]);
}

void cleanSites(void)
{
	free(completeSites);
	for (int i = 0; i < SITEAMOUNT; i++)
		free((*sChunkedSites).siteArr);

	free(sChunkedSites);
}

void initialiseSites(void)
{
	// initilise the random function
	srand(time(NULL));
	// srand(8008135);

	static sites mutableInternal[SITEAMOUNT];
	static s_chunk chunkedSitesTmp[CHUNK_AMOUNT];
	int colorChoice;
	int tX, tY; // x and y of the generated point
	int cX, cY; // x and y in the chunk grid, so chunk coordinates
	char tR, tG, tB; // RGB coordinates of point

	for (int i = 0; i < CHUNK_AMOUNT; i++) { // clear any garbage pointers and values
		chunkedSitesTmp[i].siteArr = NULL;
		chunkedSitesTmp[i].sitesHeld = 0;
	}

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

		// j is for Y, k is for X
		for (int j = -1; j <= 1; j++) {
			// if the current Y falls outside of chunk boundaries (< 0, > max), skip
			cY = (tY / CHUNK_DIM) + j;
			if (cY < 0 || cY >= CHUNK_HEIGHT)
				goto j_end;

			for (int k = -1; k <= 1; k++) {
				// if the current X falls outside of chunk boundaries (< 0, > max), skip
				cX = (tX / CHUNK_DIM) + k;
				if (cX < 0 || cX >= CHUNK_WIDTH)
					goto k_end;

				// printf("I AM GOING TO ADD %p\n", &mutableInternal[i]);
				append(&chunkedSitesTmp[(cY * CHUNK_WIDTH) + cX], &mutableInternal[i]);
k_end:
			}
j_end:
		}
	}
	completeSites = mutableInternal;
	sChunkedSites = chunkedSitesTmp;
	// for (int i = 0; i < CHUNK_AMOUNT; i++)
	// 	printf("%d,\n", sChunkedSites[i].sitesHeld);
}

double distance(int x1, int x2, int y1, int y2, float p)
{
	double dx = x1 - x2;
	double dy = y1 - y2;

	return pow(fabs(dx), p) + pow(fabs(dy), p);
}

sites *closest(int x, int y, float p)
{
	int cX = x / CHUNK_DIM;
	int cY = y / CHUNK_DIM;
	int sitesInChunk = sChunkedSites[cY * CHUNK_WIDTH + cX].sitesHeld;

	if (sitesInChunk == 0) {
		static sites zeroSite;

		zeroSite.x = 0;
		zeroSite.y = 0;
		zeroSite.r = 0;
		zeroSite.g = 0;
		zeroSite.b = 0;

		return &zeroSite;
	}

	// now that we now this adress is populated:
	sites **siteOpts = sChunkedSites[cY * CHUNK_WIDTH + cX].siteArr;

	double d;
	int closestIndex = 0;

	double minD = distance(x, siteOpts[0]->x, y, siteOpts[0]->y, p);

	for (int i = 1; i < sitesInChunk; i++) {
		d = distance(x, siteOpts[i]->x, y, siteOpts[i]->y, p);
		if (d < minD) {
			minD = d;
			closestIndex = i;
		}
	}
	return siteOpts[closestIndex];
}

// alr for this function we just gotta go and generate one tesselation
void worker(void *arg)
{
	struct argument *val = arg;
	image imageRam;
	sites *closestSite; // just pointer to single one

	// Sites = getSites();
	imageRam.bytemap = malloc(WIDTH*HEIGHT*3*sizeof(unsigned char));

	if (!imageRam.bytemap)
		perror("malloc failed");

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			closestSite = closest(j, i, (*val).power); // => 2
			// printf("%p\n", closestSite);
			imageRam.bytemap[i*WIDTH*3 + j*3 + 0] = closestSite->r;
			imageRam.bytemap[i*WIDTH*3 + j*3 + 1] = closestSite->g;
			imageRam.bytemap[i*WIDTH*3 + j*3 + 2] = closestSite->b;
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

	free(imageRam.bytemap);
}
