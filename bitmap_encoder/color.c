#include <stdio.h>

int cprint(char buffer[], int buflen, int red, int green, int blue) {
  return snprintf(buffer, buflen, "\033[48;2;%d;%d;%dm \033[0m", red, green,
                  blue);
}

int main() {
  char buffer[50];

  // Set background color to a shade of blue
  cprint(buffer, sizeof(buffer), 0, 0, 255);
  printf("%sThis text has a blue background.%s\n", buffer,
         "\033[0m"); // Resetting colors

  // Set background color to a shade of green
  cprint(buffer, sizeof(buffer), 0, 255, 0);
  printf("%sThis text has a green background.%s\n", buffer,
         "\033[0m"); // Resetting colors

  // Set background color to a shade of red
  cprint(buffer, sizeof(buffer), 255, 0, 0);
  printf("%sThis text has a red background.%s\n", buffer,
         "\033[0m"); // Resetting colors

  return 0;
}
