/* SPDX-License-Identifier: GPL */
#ifndef __DEFS_H__
#define __DEFS_H__

#define num_threads 8
#define num_items 1

#define CHUNK_DIM 200

#define CHUNK_WIDTH 5
#define CHUNK_HEIGHT 5

#define CHUNK_AMOUNT (CHUNK_WIDTH*CHUNK_HEIGHT)

#define WIDTH (CHUNK_WIDTH * CHUNK_DIM)
#define HEIGHT (CHUNK_HEIGHT * CHUNK_DIM)

extern const unsigned char COLORS[20][3];

#define SITEAMOUNT 100
#define COLORAMOUNT 20

#endif
