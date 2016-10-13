#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "states.h"


int main() {

  states *grammer = get_grammer("grammer");
  print_state(grammer);
  make_augmented_grammer(grammer);
  print_state(grammer);
  production *prod = get_empty_production();
  prod->head = 'Z';
  prod->body[0] = START_SYMBOL;
  prod->body[1] = '\0';
  prod->pos = 0;
  states *state = get_empty_state();
  push_prod_in_state(prod,state);
  print_state(state);
  print_state(closure(state,grammer));

  return 0;
}
