#ifndef SHACRYPT_H
#define SHACRYPT_H

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/types.h>

#ifdef __APPLE__
#include <machine/endian.h>
#else
#ifdef _WIN32
#define	__LITTLE_ENDIAN	1234
#define __BYTE_ORDER __LITTLE_ENDIAN
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

char *stpncpy(char *dest, const char *src, size_t n);

#else
#include <endian.h>
#endif
#endif

#endif // SHACRYPT_H
