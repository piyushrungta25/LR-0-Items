#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char START_SYMBOL;

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

void print_state(states *state) {
  production *temp_prod;
  temp_prod = state->productions;

  while(temp_prod != NULL) {
    printf("%c -> ",temp_prod->head);
    int i = 0;
    while(temp_prod->body[i] != '\0') {
      if(temp_prod->pos == i)
        printf("~");
      printf("%c",temp_prod->body[i]);
      i++;
    }

    printf("\n");
    temp_prod = temp_prod->next_prod;
  }
}

states *get_empty_state() {
  states *state = (states *)malloc(sizeof(states));
  state->next_state = NULL;
  state->productions = NULL;
  return state;
}

states *get_grammer(char *file_name) {

  char buffer[256];
  FILE *fp = fopen(file_name,"r");
  fgets(buffer,256,fp);
  START_SYMBOL = buffer[0];

  production *prod;
  states *grammer = get_empty_state();

  while(fgets(buffer,256,fp)) {
    buffer[strlen(buffer)-1] = '\0';
    prod = (production *)malloc(sizeof(production));
    prod->next_prod = NULL;
    prod->head = buffer[0];
    prod->body = (char *)malloc(16*sizeof(char));
    prod->pos = -1;
    memcpy(prod->body,buffer+3,strlen(buffer)-2);
    prod->next_prod = grammer->productions;
    grammer->productions = prod;

  }

  return grammer;
}

int main() {

  states *grammer = get_grammer("grammer");
  print_state(grammer);

  return 0;
}
