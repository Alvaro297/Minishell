#include "pipex.h"

int howmanycmds(char **argv)
{
    int c;
    int count;

    while (argv[c])
    {
        if(!ft_strcmp(argv[c], "|"))
            count++;
        c++;
    }
    c += 1;
    return (count);
}
