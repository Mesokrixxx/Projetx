#pragma once

#include <stdio.h>
#include <stdlib.h>

#define assert(c, fmt, ...) \
	do { \
		if (!(c)) { \
			fprintf(stderr, "[%s::%d::%s]\n" fmt "\n", \
				__FILE__, __LINE__, __func__, \
				##__VA_ARGS__); \
			exit(1); \
		} \
	} while (0);
