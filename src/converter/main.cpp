#include "libconverter/headers.h"
#include <stdio.h>
int main() {
  FILE *input;
  FILE *output;
  input = fopen("input.md", "r");
  output = fopen("output.html", "w");
  char in[200];
  char out[200];
  while (fgets(in, 200, input)) {
    Header(in, out);
    fprintf(output, "%s", out);
  }
}
