#include <source.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct source_t source_read(const char *path)
{
    struct source_t res = {path, NULL, 0, SOURCE_OK};

    if (path == NULL || path[0] == '\0')
    {
        res.status = SOURCE_ARG_ERROR;
        return res;
    }

    FILE *fptr = fopen(path, "rb");
    if (fptr == NULL)
    {
        res.status = SOURCE_OPEN_ERROR;
        return res;
    }

    size_t capacity = SOURCE_MAX;
    char *buffer = malloc(capacity);
    if (buffer == NULL)
    {
        fclose(fptr);
        res.status = SOURCE_MEM_ERROR;
        return res;
    }

    size_t size = 0;
    for (;;)
    {
        if (capacity - size <= 1)
        {
            if (capacity > SOURCE_MAX / 2)
            {
                free(buffer);
                fclose(fptr);
                res.status = SOURCE_MEM_ERROR;
                return res;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL)
            {
                free(buffer);
                fclose(fptr);
                res.status = SOURCE_MEM_ERROR;
                return res;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }

        size_t read_space = capacity - size - 1;
        size_t read = fread((buffer + size), 1, read_space, fptr);
        size += read;

        if (read < read_space)
        {
            if (ferror(fptr))
            {
                free(buffer);
                fclose(fptr);
                res.status = SOURCE_READ_ERROR;
                return res;
            }
            break;
        }
    }

    if (fclose(fptr) != 0)
    {
        free(buffer);
        res.status = SOURCE_READ_ERROR;
        return res;
    }

    if (memchr(buffer, '\0', size) != NULL)
    {
        free(buffer);
        res.status = SOURCE_NULL_BYTE_ERROR;
        return res;
    }

    buffer[size] = '\0';

    res.path = path;
    res.content = buffer;
    res.status = SOURCE_OK;
    res.size = size;
    return res;
}

void source_free(struct source_t *src)
{
    if (src == NULL)
    {
        return;
    }

    src->size = 0;
    src->status = 0;

    free(src->content);
    free(src);

    src = NULL;
}

const char *source_error(enum source_read_status status)
{
    switch (status)
    {
    case SOURCE_OK:
        return "Success";
    case SOURCE_ARG_ERROR:
        return "Invalid file path";
    case SOURCE_OPEN_ERROR:
        return "Couldn't open the file";
    case SOURCE_READ_ERROR:
        return "Failure during the file read";
    case SOURCE_MEM_ERROR:
        return "Insufficient memory to load the file";
    case SOURCE_NULL_BYTE_ERROR:
        return "File only contains null byte";
    default:
        return "Unknown error";
    }
}
