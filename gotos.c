#include "gotos.h"

gotos *get_empty_goto() {
  gotos *new_goto = (gotos *)malloc(sizeof(gotos));
  new_goto->next_goto = NULL;
  new_goto->from = -1;
  new_goto->to = -1;
  return new_goto;
}

mappings *get_empty_mappings() {
  mappings *mapping = (mappings *)malloc(sizeof(mappings));
  mapping->no_of_mappings = 0;
  mapping->goTo = NULL;
  return mapping;
}

void push_goto_in_mapping(gotos *map, mappings *mapping) {
  mapping->no_of_mappings++;
  map->next_goto = mapping->goTo;
  mapping->goTo = map;
}

void print_mappings(mappings *mapping) {
  gotos *map = mapping->goTo;
  printf("================\n");
  while(map != NULL) {
    printf("goto(I%d,%c) = I%d\n",map->from,map->symbol,map->to);
    map = map->next_goto;
  }
  printf("================\n");
}

bool equivalent_goto(gotos *goto1,gotos *goto2) {
  return (
    goto1->from == goto2->from &&
    goto1->to == goto2->to &&
    goto1->symbol == goto2->symbol
  );
}

bool goto_in_mapping(gotos *map1,mappings *mapping) {
  gotos *map = mapping->goTo;

  while(map != NULL) {
    if(equivalent_goto(map,map1)) {
      return true;
    }
    map = map->next_goto;
  }
  return false;
}

void delete_gotos(gotos *map) {
  free(map);
}
