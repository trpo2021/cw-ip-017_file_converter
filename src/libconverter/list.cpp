#include "libconverter/list.h"
#include <cstring>
#include <locale.h>
#include <stdio.h>

int List(char* in, char* out, int i)
{
    if ((in[i] == '*' || in[i] == '-' || in[i] == '+') && in[i + 1] == ' ') {
        char common[100];

        int j = 0;

        i++;

        while (in[i] == ' ') {
            i++;
        }

        while (j < 100 && in[i] != '+' && in[i] != '-' && in[i] != '*'
               && in[i + 1] != '\n') {
            common[j] = in[i];

            j++;

            i++;
        }

        common[j] = '\0';

        sprintf(out, "<ul><li>%s</li></ul>", common);

        return 0;
    }

    else if ((in[i] >= '0' && in[i] <= '9') && in[i + 1] == '.') {
        char common[100];

        int j = 0, check = 0;

        common[j] = in[i];

        i++;

        j++;

        if (in[i] == '.') {
            common[j] = in[i];

            i++;

            j++;

            while (in[i] == ' ') {
                check = 1;

                i++;
            }
        }

        else
            return 1;

        while (in[i + 1] != '\n') {
            common[j] = in[i];

            i++;

            j++;
        }

        common[j] = '\0';

        if (check == 1) {
            sprintf(out, "<ol><li>%s</li></oi>", common);

            return 0;
        }

        return 1;
    }
    return 1;
}
