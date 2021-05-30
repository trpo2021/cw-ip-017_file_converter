#include "libconverter/list2.h"
#include <cstring>
#include <locale.h>
#include <stdio.h>

int List2(char* in, char* out)
{
    int check = 0;
    char new_list[250], all[250], end[250];
    for (int i = 0; i < 100; i++) {
        if (in[i] >= '0' && in[i] <= '9' && in[i + 1] == '.') {

            char common[100], start[100], temp[100];

            int j = 0, z = 0;

            z = i;

            z += 2;

            while (in[z] == ' ') {
                z++;
            }

            while (j < 99 && in[z + 1] != '\n' && in[z] != EOF && in[z] != '\0' && ((in[z] != '+' && in[z] != '-' && in[z] != '*')) && in[z + 1] != '.') {

                common[j] = in[z];

                j++;

                z++;
            }

            common[j] = '\0';

            if (check == 1 || check == 2) {
                sprintf(temp, "<li>%s</li>", common);

                sprintf(all, "%s", temp);

                check = 2;
            }

            if (check == 0) {
                sprintf(start, "<ul><li>%s</li>", common);

                sprintf(new_list, "%s", start);

                check = 1;
            }
        }

        if ((in[i] >= '0' && in[i] <= '9' && in[i + 1] == '.') && check == 2 && in[i] != '\n') {
            strcat(end, all);
        }
    }
    sprintf(out, "%s%s</ul>", new_list, end);

    return 0;
}
