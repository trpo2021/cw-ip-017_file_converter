#include "libconverter/blockquote.h"
#include "libconverter/bold_italic.h"
#include "libconverter/headers.h"
#include "libconverter/url.h"
#include <cstring>
#include <locale.h>
#include <stdio.h>
int main(int argc, char **argv) {
  setlocale(LC_ALL, "rus");
  FILE *input;
  FILE *output;
  if (argc <= 1) {
    printf("Введите название файла для конвертации\n);
    return 1;
  }
  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");
  if (output == NULL) {
    output = stdout;
  }
  if (input == NULL) {
    printf("Нет доступа к %s\n", argv[1]);
    return 1;
  }
  char in[1000];
  char out[1000];
  int i;
  while (fgets(in, 1000, input)) {
    if (in[0] == '#') {
      Header(in, out);
      strcpy(in, out);
    } else if (in[0] == '>') {
      blockquote(in, out);
      strcpy(in, out);
    }
    i = 0;
    while (in[i] != '\0' && in[i] != EOF) {
      if (in[i] == '*' || in[i] == '_') {
        bold(in, out);
        break;
      } else if (in[i] == '[') {
        onURL(in, out);
      }
      i++;
    }
    fprintf(output, "%s", out);
    sprintf(in, "%s", "");
  }
  return 0;
}
