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
	size_t   i;

	// getSites(); // ignore output, just make threadsafe
	tm   = tpool_create(num_threads);

	for (i = 0; i < num_items; i++)
		tpool_add_work(tm, worker, NULL);

	tpool_wait(tm);

	tpool_destroy(tm);
	return 0;
}
