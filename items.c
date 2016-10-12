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
  int no_of_prod;
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
  state->no_of_prod =0;
  return state;
}

production *get_empty_production() {
  production *prod = (production *)malloc(sizeof(production));
  prod->next_prod = NULL;
  prod->pos = -1;
  prod->body = NULL;
  return prod;
}

void push_prod_in_state(production *prod,states *state) {
  prod->next_prod = state->productions;
  state->productions = prod;
  state->no_of_prod++;
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
    prod = get_empty_production();
    prod->head = buffer[0];
    prod->body = (char *)malloc(16*sizeof(char));
    memcpy(prod->body,buffer+3,strlen(buffer)-2);
    push_prod_in_state(prod,grammer);

  }

  return grammer;
}

void make_augmented_grammer(states *grammer) {
  production *prod = get_empty_production();
  prod->head = 'Z';
  prod->body = (char *)malloc(16*sizeof(char));
  prod->body[0] = START_SYMBOL;
  prod->body[1] = '\0';
  push_prod_in_state(prod,grammer);
}

int main() {

  states *grammer = get_grammer("grammer");
  print_state(grammer);
  make_augmented_grammer(grammer);
  print_state(grammer);


  return 0;
}
