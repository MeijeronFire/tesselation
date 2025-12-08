/* SPDX-License-Identifier: GPL */
#include "defs.h"

struct image_struct {
	unsigned int width, height;
	unsigned char **bytemap;
};
struct sites_struct {
	unsigned int x, y;
	unsigned char r, g, b; // color value at char
};

typedef struct image_struct image;
typedef struct sites_struct sites;

sites closest(unsigned int x, unsigned int y);
const sites *getSites(void);

void worker(void *arg);

