#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "states.h"
#include "sets.h"


int main() {

  states *grammer = get_grammer("grammer");
  print_state(grammer);
  make_augmented_grammer(grammer);
  print_state(grammer);
  set *set = lr0_items(grammer,START_SYMBOL);
  print_set(set);
  return 0;
}
