#include <stdio.h>
#include <stdlib.h>
#include <source.h>

void die(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        die("Missing parameters. Usage: ./vx <filename>.vx");
    }

    // printf("%s\n", argv[1]);

    struct source_t *src = source_read(argv[1]);

    if (src->status != SOURCE_OK)
    {
        source_error(src->status);
        source_free(src);
        printf("Successfully freed\n");
    }

    printf("path: %s\n", src->path);
    printf("content: %s\n", src->content);
    printf("size: %zu\n", src->size);
    printf("read status: %s\n", source_error(src->status));

    source_free(src);
    printf("Successfully freed\n");

    return 0;
}