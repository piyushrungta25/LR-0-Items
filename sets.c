#include "sets.h"
#include "states.h"

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

void print_set(set *set) {
  states *state = set->states;
  int i=0;
  while(state != NULL) {
    printf("STATE %d\n",i);
    print_state(state);
    state = state->next_state;
    i++;
  }

}

set *lr0_items(states *grammer,char start_symbol) {
  set *set = get_empty_set();
  production *prod = get_empty_production();
  prod->head = 'Z';
  prod->body[0] = start_symbol;
  prod->body[1] = '\0';
  prod->pos = 0;
  states *state = get_empty_state();
  states *gt;
  push_prod_in_state(prod,state);
  push_state_in_set(closure(state,grammer),set);
  delete_state(state);
  bool added = false;
  char *symbols = get_grammer_symbols(grammer);
  int i=0;
  int state_no;
  while(1) {
    added = false;
    state = set->states;
    while(state != NULL) {
      for(i=0;i<strlen(symbols);i++) {
        gt = goTo(state,symbols[i],grammer);
        if(!is_empty(gt)) {
          state_no = state_in_set(gt,set);
          if(state_no < 0) {
            push_state_in_set(gt,set);
            added = true;
            // goto with next available state no
          }
          else {
            // goto with state_no
          }
        }
        else {
          delete_state(gt);
        }
      }
      state = state->next_state;
    }

    if(!added) {
      return set;
    }
  }


}
