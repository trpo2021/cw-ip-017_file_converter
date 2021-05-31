#include "libconverter/list_numbered.h"
#include <cstring>
#include <locale.h>
#include <stdio.h>

int List_numbered(char* in, char* out)
{
    char common[250];

            int j = 0, i = 2;
            
            while (in[i] == ' ') {
                i++;
            }

            while (j < 100 && in[i] != '\n' && in[i] != EOF && in[i] != '\0') {

                common[j] = in[i];

                j++;

                i++;
            }

            common[j] = '\0';

            sprintf(out, "<li>%s</li>", common);

    return 0;
}
