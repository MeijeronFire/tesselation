/* SPDX-License-Identifier: GPL */
#ifndef __TESSELATION_H__
#define __TESSELATION_H__
#include "defs.h"

struct argument;
struct image_struct;
struct site_struct;
struct schunk_struct;

typedef struct image_struct image;
typedef struct site_struct sites;
typedef struct schunk_struct s_chunk;

// float power; int name;
struct argument {
	float power;
	int name;
};
// unsigned int width, height; unsigned char *bytemap;
struct image_struct {
	unsigned int width, height;
	unsigned char *bytemap;
};
// int x, y; unsigned char r, g, b;
struct site_struct {
	int x, y;
	unsigned char r, g, b; // color value at char
};
// sites **siteArr; int sitesHeld;
// special chunk, 3x3 chunks, with overlap
struct schunk_struct {
	sites **siteArr;
	int sitesHeld;
};

sites *closest(int x, int y, float p);
void initialiseSites(void);
void worker(void *arg);
void cleansites(void);

#endif
