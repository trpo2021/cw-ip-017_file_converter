#include "libconverter/blockquote.h"
#include "libconverter/bold_italic.h"
#include "libconverter/code.h"
#include "libconverter/headers.h"
#include "libconverter/hr.h"
#include "libconverter/images.h"
#include "libconverter/list.h"
#include "libconverter/strikethrough.h"
#include "libconverter/url.h"
#include "libconverter/list2.h"
#include <cstring>
#include <stdio.h>
int main(int argc, char** argv)
{
	int check = 0, check_for_list = 0, check_for_list_2 = 0, check_2 = 0, is_list = 0, is_list_2 = 0;
    bool is_bold = false, is_code = false;
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
    while (fgets(in, 1000, input)) {
    	if ((in[0] == '*' || in[0] == '-' || in[0] == '+') && (in[1] == ' '))
    		check ++;
    	if ((in[0] >= '0' && in[0] <= '9') && in[1] == '.')
    		check_2 ++;
}
	for (int i = 0; i< 1000; i++)
	{
		in[i] = 0;
	}
	input = fopen(argv[1], "r");
    while (fgets(in, 1000, input)) {
        is_bold = false, is_code = false;
        if (in[0] == '#') {
            Header(in, out);
            strcpy(in, out);
        }
        else if (in[0] == '>') {
            blockquote(in, out);
            strcpy(in, out);
        }

        else if ((in[0] == '*' || in[0] == '-' || in[0] == '+') && (in[1] == ' ')) 
		{
        	if (is_list == 0)
			{
        		fprintf(output, "<ul>");
        		is_list = 1;
        		
        	}
            List(in, out);
            check_for_list ++;
            strcpy(in, out);
            if ((check_for_list == check) && check_for_list != 0)
        	{
            	strcat(in, "</ul>");
            	check_for_list = 0;
        	}
        }
		
        else if ((in[0] >= '0' && in[0] <= '9') && in[1] == '.') 
		{
			if (is_list_2 == 0)
			{
        		fprintf(output, "<ol>");
        		is_list_2 = 1;
        		
        	}
            List2(in, out);
            check_for_list_2 ++;
            strcpy(in, out);
       	 	if ((check_for_list_2 == check_2) && check_for_list_2 != 0)
        	{
            	strcat(in, "</ol>");
            	check_for_list_2 = 0;
    		}
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
            }
            else if (in[i] == '[') {
                onURL(in, out, i);
                strcpy(in, out);
            }
            else if (in[i] == '!') {
                Image(in, out);
                strcpy(in, out);
            }
            else if (in[i] == '`' && !is_code) {
                is_code = true;
                code(in, out);
                strcpy(in, out);
            }
            else if (in[i] == '~') {
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
    return 0;
}
