#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  int verified = 0;
  char user_key[10];

  printf("Enter password: ");

  // Usando o fgets ao inves do scanf conseguimos evitar a falha de design
  fgets(user_key, sizeof(user_key), stdin);  

  // Precisamos agora remover o \n deixado pelo fgets
  user_key[strcspn(user_key, "\n")] = '\0'; 

  if (!strcmp(user_key, "foo"))
    verified = 1;

  if (!verified) {
    printf("Access denied\n");
    exit(1);
  }

  printf("Access granted.\n");
  return 0;
}
