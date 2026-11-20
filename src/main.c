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
    if(argc != 2)
    {
        die("Missing parameters. Usage: ./vx <filename>.vx");
    }    
    
    // printf("%s\n", argv[1]);
       
    struct source_t src = source_read(argv[1]);
    printf("%s\n", src.content);

    return 0;
}