/* SPDX-License-Identifier: GPL */
#ifndef __DEFS_H__
#define __DEFS_H__

#define num_threads 8
#define num_items 2

#define CHUNK_DIM 100

#define CHUNK_WIDTH 100
#define CHUNK_HEIGHT 100

#define CHUNK_AMOUNT (CHUNK_WIDTH*CHUNK_HEIGHT)

#define WIDTH (CHUNK_WIDTH * CHUNK_DIM)
#define HEIGHT (CHUNK_HEIGHT * CHUNK_DIM)

#define COLORAMOUNT 5
#define SITEAMOUNT 10000

extern const unsigned char COLORS[COLORAMOUNT][3];

#endif
