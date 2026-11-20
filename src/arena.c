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
        free(r);
        return NULL;
    }

    r->next = NULL;
    r->offset = 0;
    r->size = size;

    return r;
}

void *region_alloc(struct region_t *region, size_t size)
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

struct region_t *region_destroy(struct region_t *region)
{
    if (region == NULL)
    {
        return NULL;
    }

    struct region_t *next_region = region->next;

    region->next = NULL;
    region->offset = 0;
    region->size = 0;
    free(region->data);
    free(region);

    return next_region;
}

void region_destroy_all(struct region_t *region)
{
    while (region != NULL)
    {
        struct region_t *next = region->next;

        region->next = NULL;
        region->offset = 0;
        region->size = 0;
        free(region->data);
        free(region);

        region = next;
    }
}