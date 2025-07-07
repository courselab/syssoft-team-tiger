#include <stdio.h>

extern unsigned short pega_tamanho_memoria(void);

int main(void)   
{
  unsigned short tamanho = pega_tamanho_memoria();
  printf("Tamanho da memoria: %u\n", tamanho);

  return 0;
}
