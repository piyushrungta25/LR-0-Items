#ifndef states_h
#define states_h

#include "structures.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void print_state(states *);
states *get_empty_state();
production *get_empty_production();
void push_prod_in_state(production *,states *);
states *get_grammer(char *);
void make_augmented_grammer(states *);
bool equivalent_productions(production *, production *);
bool prod_in_state(production *, states *);
bool equivalent_state(states *, states *);
bool is_terminal(char);
production *duplicate_production(production *);
void delete_production(production *prod);
states *duplicate_state(states *);
states *closure(states *, states *);

#endif
