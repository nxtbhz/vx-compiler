#ifndef SOURCE_H
#define SOURCE_H

#include <stddef.h>

#define SOURCE_MAX 1024u

enum source_read_status
{
    SOURCE_OK = 0,
    SOURCE_ARG_ERROR,
    SOURCE_OPEN_ERROR,
    SOURCE_READ_ERROR,
    SOURCE_MEM_ERROR,
    SOURCE_NULL_BYTE_ERROR,
};

struct source_t
{
    const char *path;
    char *content;
    size_t size;
    enum source_read_status status;
};

struct source_t *source_read(const char *path);
void source_free(struct source_t *src);
const char *source_error(enum source_read_status);

#endif /* SOURCE_H */