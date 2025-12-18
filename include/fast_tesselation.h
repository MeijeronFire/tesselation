/* SPDX-License-Identifier: GPL */
#ifndef __TESSELATION_H__
#define __TESSELATION_H__
#include "defs.h"

struct image_struct {
	unsigned int width, height;
	unsigned char *bytemap;
};
struct site_struct {
	int x, y;
	unsigned char r, g, b; // color value at char
};

typedef struct image_struct image;
typedef struct site_struct sites;

int closest(int x, int y, float p);
void initialiseSites(void);
void worker(void *arg);

#endif
