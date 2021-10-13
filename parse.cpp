#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <ctype.h>


void trim(char *const str);
int line_type(string line);

void trim(char *const str)
{
    char *begin = str;
    char *end = str;
    while (isspace(*begin))
    {
        ++begin;
    }
    char *s = begin;
    while (*s != '\0')
    {
        if (!isspace(*s++))
        {
            end = s;
        }
    }
    *end = '\0';
    const int dist = end - begin;
    if (begin > str && dist > 0)
    {
        memmove(str, begin, dist + 1);
    }
}

// 0=other, 1=add, 2=sub, 3=mult, 4=div, 5=expo, 6=comm, 7=function
int line_type(string line)
{
    // if (line.find("+") || line.find("+="))
    // {
    //     return 1;
    // }
    // else if(line.find("/*"))
    // {
    //     return 6;
    // }
    // else if(line.find("//") == 0)
    // {
    //     return 6;
    // }
    // else if
    
    return 0;
    
}