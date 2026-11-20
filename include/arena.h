#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct region_t
{
    struct region_t *next;
    size_t size;
    size_t offset;
    unsigned char *data;
};

struct region_t *create_region(size_t size);
void *arena_alloc(struct region_t *region, size_t size);

#endif /* ARENA_H */            