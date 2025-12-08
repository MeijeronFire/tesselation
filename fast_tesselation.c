// SPDX-License-Identifier: GPL
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include "fast_tesselation.h"
#include "defs.h"

int randMax(int max)
{
	return rand() % (max + 1);
}

sites *initialiseSites(void)
{
	// initilise the random function
	srand(time(NULL));

	static sites mutableInternal[SITEAMOUNT];

	for (int i = 0; i < SITEAMOUNT; i++) {
		mutableInternal[i].x = randMax(WIDTH);
		mutableInternal[i].y = randMax(HEIGHT);
	}
	return mutableInternal;
}
static pthread_once_t once = PTHREAD_ONCE_INIT;
static sites *externalSites;

void init_wrapper(void)
{
	externalSites = initialiseSites();
}

const sites *getSites(void)
{
	pthread_once(&once, init_wrapper);
	return externalSites;
}

sites closest(unsigned int x, unsigned int y)
{

}

// alr for this function we just gotta go and generate one tesselation
void worker(void *arg)
{
	const sites *Sites;

	Sites = getSites();
	for (int i = 0; i < SITEAMOUNT; i++)
		printf("%d, %d\n", Sites[i].x, Sites[i].y);
}
