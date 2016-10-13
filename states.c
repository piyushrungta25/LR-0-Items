#include "states.h"

void print_state(states *state) {
  printf("=========\n");
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
    if(temp_prod->pos == strlen(temp_prod->body))
      printf("~");


    printf("\n");
    temp_prod = temp_prod->next_prod;
  }
  printf("=========\n");
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
  prod->body = (char *)malloc(16*sizeof(char));
  return prod;
}

void push_prod_in_state(production *prod,states *state) {
  if(!prod_in_state(prod,state)) {
    prod->next_prod = state->productions;
    state->productions = prod;
    state->no_of_prod++;
  }
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
    memcpy(prod->body,buffer+3,strlen(buffer)-2);
    push_prod_in_state(prod,grammer);

  }

  return grammer;
}

void make_augmented_grammer(states *grammer) {
  production *prod = get_empty_production();
  prod->head = 'Z';
  prod->body[0] = START_SYMBOL;
  prod->body[1] = '\0';
  push_prod_in_state(prod,grammer);
}

bool equivalent_productions(production *prod1, production *prod2) {
  if(prod1->pos == prod2->pos &&
    prod1->head == prod2->head &&
    (strcmp(prod1->body,prod2->body) == 0)
  ) {
    return true;
  }

  return false;
  }

bool prod_in_state(production *prod, states *state) {
  production *prod1 = state->productions;
  while(prod1 != NULL) {
    if(equivalent_productions(prod1,prod)) {
      return true;
    }
    prod1 = prod1->next_prod;
  }
  return false;
}

bool equivalent_state(states *state1, states *state2) {
  if(state1->no_of_prod != state2->no_of_prod) {
    return false;
  }

  production *prod1 = state1->productions;
  while(prod1 != NULL) {
     if(!prod_in_state(prod1,state2)) {
       return false;
     }
    prod1 = prod1->next_prod;
  }
  return true;
}

bool is_terminal(char c) {
  return isalpha(c) && isupper(c);
}

production *duplicate_production(production *prod) {
  production *new_prod = get_empty_production();
  new_prod->pos = prod->pos;
  new_prod->head = prod->head;
  new_prod->next_prod = NULL;
  strcpy(new_prod->body,prod->body);
  return new_prod;
}

void delete_production(production *prod) {
  free(prod->body);
  free(prod);
}

states *duplicate_state(states *state) {
  states *new_state = get_empty_state();
  production *prod = state->productions;
  while(prod != NULL) {
    push_prod_in_state(duplicate_production(prod),new_state);

    prod = prod->next_prod;
  }
  return new_state;
}

void delete_state(states *state) {
  production *prod = state->productions;
  production *next = prod;
  while(prod != NULL) {
    next = prod->next_prod;
    delete_production(prod);
    prod = next;
  }
}

states *closure(states *state, states *grammer) {
  states *closed = duplicate_state(state);
  production *prod = closed->productions;
  production *grammer_prod = grammer->productions;
  production *temp;
  bool changed = false;

  while(1) {
    changed = false;
    prod = closed->productions;
    while( prod != NULL ){
        if(
          prod->pos != strlen(prod->body) &&
          is_terminal(prod->body[prod->pos])
        ) {
          grammer_prod = grammer->productions;
          while(grammer_prod != NULL) {
            if(grammer_prod->head == prod->body[prod->pos]) {
                temp = duplicate_production(grammer_prod);
                temp->pos = 0;
                if(!prod_in_state(temp,closed)) {
                push_prod_in_state(temp,closed);
                changed = true;
              }
              else {
                delete_production(temp);
              }
            }
            grammer_prod = grammer_prod->next_prod;
          }
        }

      prod = prod->next_prod;
    }
    if(!changed) {
      return closed;
    }
  }

}

states *goTo(states *state, char c, states *grammer) {
  production *prod = state->productions;
  production *temp;
  states *result = get_empty_state();
  states *temp_state;

  while(prod != NULL) {
    if(
      prod->pos != strlen(prod->body) &&
      prod->body[prod->pos] == c
    ) {
      temp = duplicate_production(prod);
      temp->pos++;
      push_prod_in_state(temp,result);
    }
    prod = prod->next_prod;
  }
  temp_state = closure(result,grammer);
  delete_state(result);
  return temp_state;
}

bool is_empty(states *state) {
  return (state->no_of_prod == 0);
}
