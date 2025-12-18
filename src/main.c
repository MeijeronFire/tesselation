// SPDX-License-Identifier: GPL
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tpool.h"
#include "fast_tesselation.h"
#include "defs.h"

int main(void)
{
	tpool *tm;
	struct argument *vals;
	size_t   i;

	initialiseSites(); // ignore output, just make threadsafe
	tm   = tpool_create(num_threads);
	vals = calloc(num_items, sizeof(*vals));

	for (i = 0; i < num_items; i++) {
		vals[i].name = i;
		vals[i].power = 1.0 + i * (1.0 / (num_items - 1));
		printf("%d, %.6f\n", vals[i].name, vals[i].power);
		tpool_add_work(tm, worker, vals+i);
	}

	tpool_wait(tm);

	free(vals);
	tpool_destroy(tm);
	return 0;
}
