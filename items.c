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
  #pragma omp parallel private(mapping, set) shared(grammer)
  #pragma omp for
  for(i=0;i<100000;i++) {
  // print_state(grammer);
  // print_state(grammer);
  mapping = get_empty_mappings();
  set = lr0_items(grammer,START_SYMBOL,mapping);
  // print_set(set);
  // print_mappings(mapping);
  // printf("No of mapping: %d",mapping->no_of_mappings);
  // delete_state(grammer);
  // printf("\nNo: %d",i);
  delete_mapping(mapping);
  delete_set(set);}
  // printf("No: %d",i);
  return 0;
}
