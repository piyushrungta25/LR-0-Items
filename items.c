#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct production{
  char head;
  char *body;
  int pos;
  struct production *next_prod;
}production;

typedef struct states{
  production *productions;
  struct states *next_state;
}states;

typedef struct set{
  states *states;
}set;

int main() {
  



  return 0;
}
