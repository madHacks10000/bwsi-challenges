
#include <stdio.h>

int main(void) {
    qemu-arm -g 12345 ./hello_world
    printf("Hello, world.\n");
  return 0;
}
