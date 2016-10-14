#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "states.h"
#include "sets.h"
#include "gotos.h"


int main() {

  states *grammer = get_grammer("grammer");
  print_state(grammer);
  make_augmented_grammer(grammer);
  print_state(grammer);
  mappings *mapping = get_empty_mappings();
  set *set = lr0_items(grammer,START_SYMBOL,mapping);
  print_set(set);
  print_mappings(mapping);
  printf("No of mapping: %d",mapping->no_of_mappings);
  delete_state(grammer);
  delete_mapping(mapping);
  delete_set(set);
  return 0;
}
