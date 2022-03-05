
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define true 0x1
#define false 0x0

#define MAX_ARG_COUNT 16
#define MAX_ARG_LENGTH 64

void clear(char **args, int *argc)
{
}

char **init()
{

    char **ret;

    ret = (char **)calloc(1, MAX_ARG_COUNT * sizeof(char *));
    *(ret + 0) = (char *)calloc(1, MAX_ARG_COUNT * (MAX_ARG_LENGTH + 1) * sizeof(char));
    for (int i = 0; i < MAX_ARG_COUNT; i++)
    {
        *(ret + i) = (*ret + (MAX_ARG_LENGTH + 1) * i);
    }

    return ret;
}

void parse(const char *str, char **args, int *argc)
{
    int pos = 0;
    int i = 0;
    int ch = 0;
    int len = 0;
    int intoken = true;
    int inliteral = false;

    *argc = 0;
    memset(*(args + 0), 0, MAX_ARG_COUNT * (MAX_ARG_LENGTH + 1) * sizeof(char));

    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        ch = str[i];
        if (ch == 32)
        {
            if (inliteral)
            {
                *(args[*argc] + pos) = ch;
                pos += 1;
                // printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
            }
            else
            {
                if (intoken)
                {
                    intoken = false;
                    inliteral = false;
                    pos = 0;
                    // printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
                }
            }
        }
        else if (ch == 34)
        {
            if (inliteral)
            {
                intoken = false;
                inliteral = false;
                pos = 0;
                // printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
            }
            else
            {
                intoken = true;
                inliteral = true;
                *argc += 1;
                pos = 0;
                // printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
            }
        }
        else if (ch >= 33 && ch <= 126)
        {

            if (intoken)
            {
                *(args[*argc] + pos) = ch;
                pos += 1;
                // printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
            }
            else
            {
                *argc += 1;
                pos = 0;
                *(args[*argc] + pos) = ch;
                pos += 1;
                //printf("%c token = %d, literal = %d, argc = %d, pos = %d\n", ch, intoken, inliteral, *argc, pos);
            }
            intoken = true;
        }
    }

    *argc += 1;
    return;
}

int main(void)
{

    int argc;
    char **args;

    args = init();

    parse("load   ding    dong", args, &argc);

    for (int b = 0; b < argc; b++)
    {
        printf("[%s]\n", args[b]);
    }

    parse("save    \"8/8/8/4p1K1/2k1P3/8/8bleebleee bleee/8 b - - 0 1\"  \"fred frank tom\"", args, &argc);

    for (int b = 0; b < argc; b++)
    {
        printf("[%s]\n", args[b]);
    }

    return 0;
}