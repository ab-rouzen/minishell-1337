#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char** argv) {
  rl_catch_signals = 0;  // Disable signal handling.
  char* line;
  while ((line = readline("prompt> ")) != NULL) {
    // Do something with the line here.
    free(line);
  }
  return 0;
}