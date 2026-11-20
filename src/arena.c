#include <arena.h>
#include <stdio.h>
#include <stdlib.h>

struct region_t *create_region(size_t size)
{
    struct region_t *r = malloc(sizeof(struct region_t));
    if (r == NULL)
    {
        return NULL;
    }

    r->data = malloc(size);
    if (r->data == NULL)
    {
        return NULL;
    }

    r->next = NULL;
    r->offset = 0;
    r->size = size;

    return r;
}

void *arena_alloc(struct region_t *region, size_t size)
{
    if (region == NULL)
    {
        return NULL;
    }

    if (size > region->size - region->offset)
    {
        return NULL;
    }

    void *ptr = region->data + region->offset;

    region->offset += size;

    return ptr;
}
