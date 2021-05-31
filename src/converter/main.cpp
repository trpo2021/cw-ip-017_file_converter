#include "libconverter/blockquote.h"
#include "libconverter/bold_italic.h"
#include "libconverter/code.h"
#include "libconverter/headers.h"
#include "libconverter/hr.h"
#include "libconverter/images.h"
#include "libconverter/list.h"
#include "libconverter/list_numbered.h"
#include "libconverter/strikethrough.h"
#include "libconverter/url.h"
#include <cstring>
#include <stdio.h>
int main(int argc, char** argv)
{
    bool is_bold = false, is_code = false, check_for_list = false,
         check_for_list_number = false;
    FILE* input;
    FILE* output;
    if (argc <= 1) {
        printf("Enter the name of the file to convert\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if (output == NULL) {
        output = stdout;
    }
    if (input == NULL) {
        printf("No access to file %s\n", argv[1]);
        return 1;
    }
    char in[1000];
    char out[1000];
    int i;
    for (int i = 0; i < 1000; i++) {
        in[i] = 0;
    }
    while (fgets(in, 1000, input)) {
        if ((!(in[0] == '*' || in[0] == '+' || in[0] == '-') && in[1] != ' ')
            && check_for_list) {
            fprintf(output, "</ul>\n");
            check_for_list = false;
        }

        if ((!(in[0] >= '0' && in[0] <= '9') && in[1] != '.')
            && check_for_list_number) {
            fprintf(output, "</ol>\n");
            check_for_list_number = false;
        }

        is_bold = false, is_code = false;
        if (in[0] == '#') {
            Header(in, out);
            strcpy(in, out);
        } else if (in[0] == '>') {
            blockquote(in, out);
            strcpy(in, out);
        }

        else if (in[0] == '-' || in[0] == '*' || in[0] == '+') {
            if (!check_for_list && in[1] == ' ') {
                fprintf(output, "<ul>\n");
                check_for_list = true;
            }
            List(in, out);
            strcpy(in, out);
        }

        else if (((in[0] >= '0' && in[0] <= '9') && in[1] == '.')) {
            if (!check_for_list_number && in[2] == ' ') {
                fprintf(output, "<ol>\n");
                check_for_list_number = true;
            }
            List_numbered(in, out);
            strcpy(in, out);
        }

        else if (in[0] == '*' || in[0] == '-' || in[0] == '_') {
            Hr(in, out);
            strcpy(in, out);
        }
        i = 0;
        while (in[i] != '\0' && in[i] != EOF) {
            if ((in[i] == '*' || in[i] == '_') && !is_bold) {
                is_bold = true;
                bold(in, out);
                strcpy(in, out);
            } else if (in[i] == '[') {
                onURL(in, out, i);
                strcpy(in, out);
            } else if (in[i] == '!') {
                Image(in, out);
                strcpy(in, out);
            } else if (in[i] == '`' && !is_code) {
                is_code = true;
                code(in, out);
                strcpy(in, out);
            } else if (in[i] == '~') {
                strikethrough(in, out);
                strcpy(in, out);
            }
            if (in[i] == '<') {
                while (in[i] != '>')
                    i++;
            }
            i++;
        }
        fprintf(output, "%s\n", in);

        // sprintf(in, "%s", "");
    }
    if (check_for_list)
        fprintf(output, "</ul>");
    if (check_for_list_number)
        fprintf(output, "</ol>");

    return 0;
}
