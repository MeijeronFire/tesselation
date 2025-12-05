// SPDX-License-Identifier: GPL
#include <stdio.h>

struct image {
	int width, height;
	struct point {
		int x, y;
		int r, g, b;
	};
};

void *single(void)
{

}

int main(void)
{
	printf("test\n");
	return 0;
}
