#include <stdio.h>

extern unsigned short get_memory_size(void);

int main(void)   
{
  printf("Hello World\n");

  unsigned short mem_kb = get_memory_size();
  printf("Memory size: %u KB\n", mem_kb);

  return 0;
}
