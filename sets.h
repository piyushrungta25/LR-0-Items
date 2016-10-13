#ifndef sets_h
#define sets_h

#include "states.h"

set *get_empty_set();
void push_state_in_set(states *, set *);
states *get_state(set *, int);
int state_in_set(states *, set *);
set *lr0_items(states *,char);

#endif
