#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "states.h"
#include "sets.h"
#include "gotos.h"
#include <omp.h>


int main() {

  states *grammer;
  mappings *mapping;
  set *set;
  grammer = get_grammer("grammer");
  make_augmented_grammer(grammer);
  int i;
  
  #pragma omp parallel for private(mapping,set)
  for(i=0;i<1000;i++) {
    mapping = get_empty_mappings();
    set = lr0_items(grammer,START_SYMBOL,mapping);
    delete_mapping(mapping);
    delete_set(set);
  }
  return 0;
}
