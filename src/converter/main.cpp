#include "libconverter/headers.h"
#include <locale.h>
#include <stdio.h>
int main(int argc, char **argv) {
  setlocale(LC_ALL, "rus");
  FILE *input;
  FILE *output;
  if (argc <= 1) {
    printf("Введите название файла для конвертации\n");
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
  char in[200];
  char out[200];
  while (fgets(in, 200, input)) {
    if (in[0] == '#') {
      Header(in, out);
    }
    fprintf(output, "%s", out);
  }
  return 0;
}
