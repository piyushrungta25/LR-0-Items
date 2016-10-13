#include "sets.h"

set *get_empty_set() {
  set *new_set = (set *)malloc(sizeof(set));
  new_set->no_of_states = 0;
  new_set->states = NULL;
  return new_set;
}

void push_state_in_set(states *state, set *set) {
  set->no_of_states++;
  states *temp = set->states;
  if(temp == NULL) {
    set->states = state;
    return;
  }

  while(temp->next_state != NULL) {
    temp = temp->next_state;
  }

  temp->next_state = state;
}

states *get_state(set *set, int pos) {
  if( pos >= set->no_of_states) {
    return NULL;
  }

  int i=0;
  states *state = set->states;
  while(i< pos) {
    state = state->next_state;
  }

  return state;
}

int state_in_set(states *state, set *set) {
  int i=0;
  states *temp = set->states;
  for(i=0;i<set->no_of_states;i++) {
    if(equivalent_state(temp,state)) {
      return i;
    }
    temp = temp->next_state;
  }
  return -1;
}
